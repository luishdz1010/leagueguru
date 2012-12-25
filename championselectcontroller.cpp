#include "championselectcontroller.h"
#include <algorithm>
#include <QFile>
#include <QDateTime>
#include <QDeclarativeContext>
#include <QApplication>
#include "qslog/QsLog.h"
#include "matchparticipantmodel.hpp"
#include "participantsuggestionsmodel.h"
#include "rosterfiltermodel.h"
#include "suggestionsfildermodel.h"
#include "championdata.h"
#include <QDir>

ChampionSelectController::ChampionSelectController(QObject *parent) :
    QObject(parent),
    currentRegion(-1),
    packetInspector(0),    
    enemyRosterFilterModel((int)EnemyRosterData::ChampionId)
{}

void ChampionSelectController::init()
{
    connect(qApp, SIGNAL(lastWindowClosed()), this, SLOT(OnLastLastWindowsClosed()));

    // stats providers
    summonerStatsProvider = new LolKingSummonerStatsProvider(this);
    connect(summonerStatsProvider, SIGNAL(lookupSucceed(int,SummonerStats)),
            this, SLOT(onSummonerLookupSucceed(int,SummonerStats)));
    connect(summonerStatsProvider, SIGNAL(lookupFailed(int)), this, SLOT(onSummonerLookupFailed(int)));

    // enemy roster
    enemyRosterFilterModel.setSourceModel(&enemyRosterModel);

    // guru server
    connect(&statsServer, SIGNAL(connected()), this, SLOT(onConnectedToGuruServer()));
    connect(&statsServer, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onErrorWhileConnectingToGuruServer(QAbstractSocket::SocketError)));
    connect(&statsServer, SIGNAL(matchupCreated(guru::MatchupCreated&)),
            this, SLOT(onGuruMatchupCreated(guru::MatchupCreated&)));
    connect(&statsServer, SIGNAL(banSuggestionsChanged(guru::BanSuggestions&)),
            this, SLOT(onGuruBanSuggestionsChanged(guru::BanSuggestions&)));
    connect(&statsServer, SIGNAL(participantsSuggestionsChanged(guru::ParticipantsSuggestions&)),
            this, SLOT(onGuruParticipantSuggestionsChanged(guru::ParticipantsSuggestions&)));

    // enemy roster model
    enemyRosterFilterModel.setDynamicSortFilter(true);
    enemyRosterFilterModel.sort(0, Qt::AscendingOrder);

    // injection
    injector = new ProcessInjector(this);
    connect(injector, SIGNAL(injected(InjectionStatus)), this, SLOT(onInjected(InjectionStatus)));

    injector->inject();

    QLOG_INFO() << "ChampionSelectController initialized, client injection service started";
}

void ChampionSelectController::onInjected(InjectionStatus status)
{
    if(status == InjectionStatus::Succeed){
        QLOG_INFO() << "Client injection succeed";
        emit injectionSucceed();
    } else {
        QLOG_ERROR() << "Client injection error" << (int)status;
        emit injectionFailed();
    }
}

void ChampionSelectController::onConnectionError()
{
    emit connectionError();
}

void ChampionSelectController::onInspectionError()
{
    // this likely won't happen
}

void ChampionSelectController::onDisconnected()
{
    // hope for a reconnection, in GamePacketInspector
}

void ChampionSelectController::onMatchupBeingCreated(InspectedMatch match)
{
    QLOG_INFO() << "Matchup being created" << match;

    emit matchupDestroyed(); // give the ui some time to update

    bufferedEvents.reset();
    summonerStats.clear();
    participantsModel.clear();
    enemyRosterModel.clear();
    bansModel.clear();

    foreach(const InspectedMatchParticipant& p, match.selfTeam )
        summonerStatsProvider->lookupSummonerStats((Enums::ServerRegion)currentRegion, p.summonerId);
}

void ChampionSelectController::onSummonerLookupSucceed(int summonerId, SummonerStats stats)
{
    summonerStats.insert(summonerId, stats);

    for(int i = 0; i < participantsModel.size(); ++i){
        if(participantsModel[i]->data(MatchupParticipantData::SummonerId) == summonerId){
            setSummonerStats(participantsModel[i], stats);
            break;
        }
    }

    // we're likely going to receive all the summoner stats after the match has been created
    if(summonerStats.size() == participantsModel.size() && bufferedEvents){
        QLOG_DEBUG() << "Receiving last summoner lookup after matchup started";
        connectToGuruServer();
    }
}

void ChampionSelectController::setSummonerStats(MatchupParticipantItem* item, const SummonerStats& stats)
{
    item->setData(MatchupParticipantData::Ranking, stats.solo5Rating);

    // season 2
    auto s2filterModel = item->data(MatchupParticipantData::S2RosterModel).value<RosterFilterModel*>();
    auto s2rosterModel = s2filterModel->getRosterModel();
    for(auto it = stats.s2ChampionStats.begin(); it != stats.s2ChampionStats.end(); ++it){
        s2rosterModel->append(new ParticipantRosterItem{
            {ParticipantRosterData::ChampionId, it.key()},
            {ParticipantRosterData::Wins, it->wins},
            {ParticipantRosterData::Loses, it->loses},
            {ParticipantRosterData::Winrate, it->wins * 100 / double(it->loses + it->wins)},
            {ParticipantRosterData::Kills, it->kills},
            {ParticipantRosterData::Deaths, it->deaths},
            {ParticipantRosterData::Assists, it->assists}
        });
    }

    s2filterModel->sort(1, "down");

    // season 3
    auto s3filterModel = item->data(MatchupParticipantData::S3RosterModel).value<RosterFilterModel*>();
    auto s3rosterModel = s3filterModel->getRosterModel();
    for(auto it = stats.s3ChampionStats.begin(); it != stats.s3ChampionStats.end(); ++it){
        s3rosterModel->append(new ParticipantRosterItem{
            {ParticipantRosterData::ChampionId, it.key()},
            {ParticipantRosterData::Wins, it->wins},
            {ParticipantRosterData::Loses, it->loses},
            {ParticipantRosterData::Winrate, it->wins * 100 / double(it->loses + it->wins)},
            {ParticipantRosterData::Kills, it->kills},
            {ParticipantRosterData::Deaths, it->deaths},
            {ParticipantRosterData::Assists, it->assists}
        });
    }

    s3filterModel->sort(1, "down");
}

void ChampionSelectController::onSummonerLookupFailed(int summonerId)
{
    summonerStats.insert(summonerId, SummonerStats());

    if(summonerStats.size() == participantsModel.size() && bufferedEvents){
        QLOG_DEBUG() << "Receiving last summoner lookup after matchup started";
        connectToGuruServer();
    }
}

void ChampionSelectController::onMatchupCreated(InspectedMatch match)
{
    QLOG_INFO() << "Matchup created" << match;

    bufferedEvents.reset(new BufferedClientEvents());
    bufferedEvents->match = match;

    int idx = 0;

    foreach(const InspectedMatchParticipant& p, match.selfTeam){
        auto it = new MatchupParticipantItem{
            {MatchupParticipantData::ParticipantIndex, idx++},
            {MatchupParticipantData::SummonerName, p.summonerName},
            {MatchupParticipantData::SummonerId, p.summonerId},
            {MatchupParticipantData::PickState, Enums::NotPicking},
            {MatchupParticipantData::ChampionId, 0},
            {MatchupParticipantData::SelfSummoner, p.isSelfUser}
        };

        auto filterSuggestionsModel = new SuggestionsFilderModel(it);
        filterSuggestionsModel->setSourceModel(new ParticipantSuggestionsModel(it));
        filterSuggestionsModel->setDynamicSortFilter(true);

        auto s2FilterRosterModel = new RosterFilterModel(it);
        s2FilterRosterModel->setSourceModel(new ParticipantRosterModel(it));

        auto s3FilterRosterModel = new RosterFilterModel(it);
        s3FilterRosterModel->setSourceModel(new ParticipantRosterModel(it));

        auto globalFilterModel = new MultipleChampionFilterModel(it);
        globalFilterModel->addModel(filterSuggestionsModel);
        globalFilterModel->addModel(s2FilterRosterModel);
        globalFilterModel->addModel(s3FilterRosterModel);

        it->setData(MatchupParticipantData::SuggestionsModel, QVariant::fromValue(filterSuggestionsModel));
        it->setData(MatchupParticipantData::S2RosterModel, QVariant::fromValue(s2FilterRosterModel));
        it->setData(MatchupParticipantData::S3RosterModel, QVariant::fromValue(s3FilterRosterModel));
        it->setData(MatchupParticipantData::FilterModel, QVariant::fromValue(globalFilterModel));

        auto stats = summonerStats.find(p.summonerId);
        if(stats != summonerStats.end())
            setSummonerStats(it, *stats);

        participantsModel.append(it);
    }

    // we might have received all the stats already
    if(summonerStats.size() == participantsModel.size()){
        QLOG_DEBUG() << "All summoner lookups were ready before matchup started";
        connectToGuruServer();
    }

    emit matchupCreated(&bansModel, &enemyRosterFilterModel, &participantsModel);
}

void ChampionSelectController::onEnemyRosterReceived(InspectedEnemyRoster roster)
{
    QLOG_INFO() << "Setting enemy roster" << roster.championIds;
    std::unique_ptr<guru::EnemyRoster> msg(new guru::EnemyRoster());

    foreach(int champId, roster.championIds){
        auto it = new EnemyRosterItem{ {EnemyRosterData::ChampionId, champId} };
        enemyRosterModel.append(it);
        msg->add_championids(champId);
    }

    if(connectedToGuruServer())
        statsServer.setEnemyRoster(*msg);
    else
        bufferedEvents->enemyRoster.reset(msg.release());
}

void ChampionSelectController::onMatchupDisbanded()
{
    QLOG_INFO() << "Matchup disbanded";
    statsServer.disconnectFromHost();
    bufferedEvents.reset();
    summonerStats.clear();

    emit matchupDisbanded();
}

void ChampionSelectController::onChampionBanned(int championId, int teamId)
{
    QLOG_INFO() << "Champion" << ChampionDataProvider::championDebugString(championId) << "banned";
    guru::ChampionBan ban;
    ban.set_championid(championId);
    ban.set_selfteam(bufferedEvents->match.selfTeamId == teamId);

    if(connectedToGuruServer())
        statsServer.addChampionBan(ban);
    else
        bufferedEvents->bans.append(ban);

    // todo remove from bans model, server is going to do that in the next update,
    // but we can do it faster
}

void ChampionSelectController::onPlayerStartsPicking(int player)
{
    QLOG_INFO() << "Participant " << player << " started picking";
    guru::ParticipantStartsPicking msg;
    msg.set_participant(player);
    msg.set_start(QDateTime::currentMSecsSinceEpoch());
    msg.set_timer(60);

    if(connectedToGuruServer()){
        //statsServer.setParticipantStartPicking(msg);
    } else {
        // bufferedEvents->enqueue(msg);
    }

    if(player < participantsModel.size())
        participantsModel[player]->setData(MatchupParticipantData::PickState, (int)Enums::Picking);
}

void ChampionSelectController::onPlayerChampionPicked(int player, int championId)
{
    QLOG_INFO() << "Champion" << ChampionDataProvider::championDebugString(championId) << "picked by participant" << player;
    guru::ParticipantChampion msg;
    msg.set_participant(player);
    msg.set_championid(championId);

    if(connectedToGuruServer()){
        statsServer.setParticipantChampion(msg);
    } else {
        bufferedEvents->championPicks.append(msg);
    }

    if(player < participantsModel.size())
        participantsModel[player]->setData(MatchupParticipantData::ChampionId, championId);
}

void ChampionSelectController::onPlayerLockedIn(int player, int championId)
{
    QLOG_INFO() << "Champion" << ChampionDataProvider::championDebugString(championId) << "locked in by participant" << player;
    guru::LockParticipant msg;
    msg.set_participant(player);
    msg.set_championid(championId);

    if(connectedToGuruServer()){
        statsServer.lockParticipant(msg);
    } else {
        bufferedEvents->lockedParticipants.append(msg);
    }

    if(player < participantsModel.size())
        participantsModel[player]->setData(MatchupParticipantData::PickState, (int)Enums::LockedIn);
}

void ChampionSelectController::onPlayerSpellsChanged(int player, int spellA, int spellB)
{
    QLOG_INFO() << "Spells changed to [" << spellA << ", " << spellB << "] by participant" << player;
    guru::ParticipantSpells msg;
    msg.set_participant(player);
    msg.set_spell1(spellA);
    msg.set_spell2(spellB);

    if(connectedToGuruServer()){
        statsServer.setParticipantSpells(msg);
    } else {
        bufferedEvents->spells.append(msg);
    }
}

void ChampionSelectController::setParticipantRole(int participant, int role)
{
    QLOG_INFO() << "Participant" << participant << "role set to" << role;
    guru::ParticipantRole msg;
    msg.set_participant(participant);
    msg.set_role((guru::ChampionRole)role);

    if(connectedToGuruServer()){
        statsServer.setParticipantRole(msg);
    } else {
        bufferedEvents->roles.append(msg);
    }
}

void ChampionSelectController::connectToGuruServer()
{
    QLOG_INFO() << "Connecting to GuruServer on" << "[localhost:7171]";
    statsServer.connectToHost("localhost", 7171);
}

bool ChampionSelectController::connectedToGuruServer()
{
    return statsServer.state() == QAbstractSocket::ConnectedState;
}

void ChampionSelectController::onConnectedToGuruServer()
{
    QLOG_INFO() << "Connected to guru server on" << "[localhost:7171]";
    guru::LoginCredentials cred;
    statsServer.login(cred);


    auto& currentMatch = bufferedEvents->match;
    guru::MatchupInfo m;
    m.set_region((guru::Region)currentRegion);
    m.set_gamemode(currentMatch.gameMode.toStdString());
    m.set_gametype(currentMatch.gameType.toStdString());
    m.set_mapid(currentMatch.mapId);
    m.set_maxnumplayers(currentMatch.maxNumPlayers);
    m.set_hostplayer(currentMatch.selfSummonerIndex);

    // add riot game info

    // add participant info
    int i = 0;
    for(auto p : currentMatch.selfTeam){
        auto mp = m.add_participants();
        mp->set_participantindex(i++);
        mp->set_summonerid(p.summonerId);
        mp->set_summonername(p.summonerName.toStdString());

        SummonerStats s = summonerStats[p.summonerId];

        if(s.solo5Rating > 0)
            mp->set_solo5rating(s.solo5Rating);

        if(s.solo5TopRating > 0)
            mp->set_solo5toprating(s.solo5TopRating);

        for(auto it = s.s2ChampionStats.begin(); it != s.s2ChampionStats.end(); ++it){
            auto c = mp->add_championstats();
            auto s3 = s.s3ChampionStats.find(it.key());

            c->set_championid(it.key());
            c->set_wins(it->wins + (s.s3ChampionStats.end() != s3? s3->wins : 0));
            c->set_loses(it->loses + (s.s3ChampionStats.end() != s3? s3->loses : 0));
        }

        for(auto it = s.s3ChampionStats.begin(); it != s.s3ChampionStats.end(); ++it){
            if(!s.s2ChampionStats.contains(it.key())){
                auto c = mp->add_championstats();
                c->set_championid(it.key());
                c->set_wins(it->wins);
                c->set_loses(it->loses);
            }
        }
    }

    statsServer.createMatchup(m);

    // send buffered events
    if(bufferedEvents->enemyRoster)
        statsServer.setEnemyRoster(*bufferedEvents->enemyRoster);

    foreach(const guru::ChampionBan& ban, bufferedEvents->bans)
        statsServer.addChampionBan(ban);

    foreach(const guru::ParticipantStartsPicking& t, bufferedEvents->pickingTimers)
        statsServer.participantStartsPicking(t);

    foreach(const guru::ParticipantChampion& ch, bufferedEvents->championPicks)
        statsServer.setParticipantChampion(ch);

    foreach(const guru::ParticipantRole& role, bufferedEvents->roles)
        statsServer.setParticipantRole(role);

    foreach(const guru::ParticipantSpells& spells, bufferedEvents->spells)
        statsServer.setParticipantSpells(spells);

    foreach(const guru::LockParticipant& ch, bufferedEvents->lockedParticipants)
        statsServer.lockParticipant(ch);
}

void ChampionSelectController::onErrorWhileConnectingToGuruServer(QAbstractSocket::SocketError e)
{
    QLOG_ERROR() << "GuruServer socket error" << e;
}

void ChampionSelectController::onGuruMatchupCreated(guru::MatchupCreated& msg)
{
    QLOG_INFO() << "GuruServer matchup created" << QString::fromStdString(msg.DebugString());
    // here we can generate the link to the future webpage using roomId/key
}

void ChampionSelectController::onGuruBanSuggestionsChanged(guru::BanSuggestions &msg)
{
    QLOG_INFO() << "GuruServer ban suggestions changed";// << QString::fromStdString(msg.DebugString());
    QList<BanSuggestionItem*> newSuggestions;
    for(auto s : msg.suggestions()){
        newSuggestions.append(new BanSuggestionItem{
            {BanSuggestionsData::ChampionId, s.championid()},
            {BanSuggestionsData::WinPercent, s.winrate()},
            {BanSuggestionsData::TotalGames, s.totalgames()},
            {BanSuggestionsData::Popularity, s.popularity()}
        });
    }

    bansModel.reset(newSuggestions);
}

void ChampionSelectController::onGuruParticipantSuggestionsChanged(guru::ParticipantsSuggestions &msg)
{
    QLOG_INFO() << "GuruServer participant suggestions changed" ;//<<QString::fromStdString(msg.DebugString());
    for(auto s : msg.suggestions()){
        auto sm = participantsModel[s.participant()]->data(MatchupParticipantData::SuggestionsModel)
                        .value<SuggestionsFilderModel*>()->getSuggestionsModel();

        QList<ParticipantSuggestionsItem*> newSuggestions;

        for(auto c : s.champions()){
            auto it = new ParticipantSuggestionsItem{
                {ParticipantSuggestionsData::ChampionId, c.championid()},
                {ParticipantSuggestionsData::SuggestedRole, (int)c.role()},
            };

            QList<QObject*> strongAgainst;
            QList<QObject*> goodWith;
            QList<QObject*> badVs;

            for(auto matchup : c.strongagainst())
                strongAgainst.append(new ChampionMatchupDetails(matchup.championid(), matchup.winrate(), it));

            for(auto sinergy : c.goodwith()){
                qDebug() << ChampionDataProvider::championDebugString(c.championid()) << "good with"
                            << ChampionDataProvider::championDebugString(sinergy.championid());
                goodWith.append(new ChampionMatchupDetails(sinergy.championid(), sinergy.winrate(), it));
            }

            for(auto matchup : c.badagainst())
                badVs.append(new ChampionMatchupDetails(matchup.championid(), matchup.winrate(), it));

            it->setData(ParticipantSuggestionsData::StrongAgainst, QVariant::fromValue(strongAgainst));
            it->setData(ParticipantSuggestionsData::GoodWith, QVariant::fromValue(goodWith));
            it->setData(ParticipantSuggestionsData::BadAgainst, QVariant::fromValue(badVs));

            newSuggestions.append(it);
        }

        sm->reset(newSuggestions);
    }
}

void ChampionSelectController::setServerRegion(int region)
{
    if(currentRegion == region)
        return;

    currentRegion = region;

    if(packetInspector){
        delete packetInspector;
        packetInspector = nullptr;
    }

    QString server;

    switch(currentRegion){
    case Enums::NorthAmerica:
        server = "prod.na1.lol.riotgames.com";
        break;
    case Enums::EuropeWest:
        server = "prod.eu.lol.riotgames.com";
        break;
    case Enums::EuropeNordicEast:
        server = "prod.eun1.lol.riotgames.com";
        break;
    default:
        QLOG_FATAL() << "Invalid server region(" << currentRegion << ") passed to ChampionSelectController";
        return;
    }

    QLOG_INFO() << "Server region changed to" << server;

    packetInspector = new GamePacketInspector(server, "cert/pem/" + server + ".cer", ":/ssl/" + server + ".key", this);

    connect(packetInspector, SIGNAL(connectionError()), this, SLOT(onConnectionError()));
    connect(packetInspector, SIGNAL(inspectionError()), this, SLOT(onInspectionError()));

    connect(packetInspector, SIGNAL(playerLoggedIn()), this, SIGNAL(summonerLoggedIn()));

    connect(packetInspector, SIGNAL(matchupBeingCreated(InspectedMatch)),
            this, SLOT(onMatchupBeingCreated(InspectedMatch)));
    connect(packetInspector, SIGNAL(matchupCreated(InspectedMatch)),
            this, SLOT(onMatchupCreated(InspectedMatch)));
    connect(packetInspector, SIGNAL(matchupDisbanded()), this, SLOT(onMatchupDisbanded()));
    connect(packetInspector, SIGNAL(enemyRosterReceived(InspectedEnemyRoster)),
            this, SLOT(onEnemyRosterReceived(InspectedEnemyRoster)));
    connect(packetInspector, SIGNAL(championBanned(int, int)),
            this, SLOT(onChampionBanned(int, int)));
    connect(packetInspector, SIGNAL(playerStartsPicking(int)),
            this, SLOT(onPlayerStartsPicking(int)));
    connect(packetInspector, SIGNAL(playerChampionPicked(int,int)),
            this, SLOT(onPlayerChampionPicked(int, int)));
    connect(packetInspector, SIGNAL(playerLockedIn(int,int)),
            this, SLOT(onPlayerLockedIn(int, int)));
    connect(packetInspector, SIGNAL(playerSpellsChanged(int,int,int)),
            this, SLOT(onPlayerSpellsChanged(int,int,int)));

    connect(packetInspector, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

    packetInspector->start();
}


void ChampionSelectController::OnLastLastWindowsClosed()
{
    packetInspector->stopInspection();
    lolClientWatcher.reset(new ProcessWatcher());
    connect(lolClientWatcher.get(), SIGNAL(processClosed()), qApp, SLOT(quit()));
    lolClientWatcher->start();
}

