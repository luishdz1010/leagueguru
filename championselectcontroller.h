#ifndef CHAMPIONSELECTCONTROLLER_H
#define CHAMPIONSELECTCONTROLLER_H

#include <memory>
#include <QObject>
#include "processinjector.h"
#include "gamepacketinspector.h"
#include "summonerstatsprovider.h"
#include "matchparticipantmodel.hpp"
#include "enemyrostermodel.h"
#include "bansuggestionsmodel.h"
#include "enums.h"
#include "guruserver.h"
#include "championfiltermodel.h"
#include "processwatcher.h"

class ClientEmulator;

class ChampionSelectController : public QObject
{
    Q_OBJECT
public:
    explicit ChampionSelectController(QObject *parent = 0);
    
signals:
    void injectionSucceed();
    void injectionFailed();

    void summonerLoggedIn();
    void connectionError();

    void matchupCreated(QAbstractItemModel* bansModel, QObject* enemyRosterModel, QAbstractItemModel* participantsModel);
    void matchupDisbanded();
    void matchupDestroyed();

public slots:
    void init();

    void setServerRegion(int);
    void setParticipantRole(int participant, int role);
    void OnLastLastWindowsClosed();

private slots:
    void onInjected(InjectionStatus status);

    void onConnectionError();
    void onInspectionError();
    void onDisconnected();

    void onMatchupBeingCreated(InspectedMatch match);
    void onSummonerLookupSucceed(int summonerId, SummonerStats stats);
    void onSummonerLookupFailed(int summonerId);
    void setSummonerStats(MatchupParticipantItem* item, const SummonerStats& stats);

    void onMatchupCreated(InspectedMatch match);
    void onMatchupDisbanded();
    void onEnemyRosterReceived(InspectedEnemyRoster roster);
    void onChampionBanned(int championId, int teamId);
    void onPlayerStartsPicking(int player);
    void onPlayerChampionPicked(int player, int championId);
    void onPlayerLockedIn(int player, int championId);
    void onPlayerSpellsChanged(int player, int spellA, int spellB);

    void onConnectedToGuruServer();
    void onErrorWhileConnectingToGuruServer(QAbstractSocket::SocketError);
    void onGuruMatchupCreated(guru::MatchupCreated&);
    void onGuruBanSuggestionsChanged(guru::BanSuggestions&);
    void onGuruParticipantSuggestionsChanged(guru::ParticipantsSuggestions& sugggestions);

private:
    friend class ClientEmulator;
    friend class ClientEmulatorWindow;

    // holds the list of events that we havent sent to the server
    struct BufferedClientEvents{
        InspectedMatch match;
        std::unique_ptr<guru::EnemyRoster> enemyRoster;
        QList<guru::ChampionBan> bans;
        QList<guru::ParticipantChampion> championPicks;
        QList<guru::ParticipantSpells> spells;
        QList<guru::ParticipantRole> roles;
        QList<guru::ParticipantStartsPicking> pickingTimers;
        QList<guru::LockParticipant> lockedParticipants;

       // QQueue<google::protobuf::Message> > messages;
    };

    void connectToGuruServer();
    bool connectedToGuruServer();

    GuruServerConnection statsServer;
    std::unique_ptr<BufferedClientEvents> bufferedEvents;

    int currentRegion;

    ProcessInjector* injector;
    GamePacketInspector* packetInspector;

    SummonerStatsProvider* summonerStatsProvider;
    QHash<int, SummonerStats> summonerStats;

    BanSuggestionsModel bansModel;
    EnemyRosterModel enemyRosterModel;
    MatchupParticipantModel participantsModel;

    SingleChampionFilterModel enemyRosterFilterModel;

    std::unique_ptr<ProcessWatcher> lolClientWatcher;
};

#endif // CHAMPIONSELECTCONTROLLER_H
