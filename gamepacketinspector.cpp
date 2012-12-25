#include "gamepacketinspector.h"
#include <stdexcept>
#include "basicexternalizablemessage.h"
#include "qslog/QsLog.h"

GamePacketInspector::GamePacketInspector(const QString& gameServer, const QString& cert,
                                         const QString& key, QObject *parent) :
    QObject(parent),
    selfAccountId(0),
    remoteAddr(gameServer)
{
    clearGameState();

    localEndpoint.setLocalCertificate(cert);
    localEndpoint.setPrivateKey(key);
    localEndpoint.setProtocol(QSsl::TlsV1);
    localEndpoint.setPeerVerifyMode(QSslSocket::VerifyNone);

    QLOG_DEBUG() << "Cert - isValid:" << localEndpoint.localCertificate().isValid() << " isNull:"
                 << localEndpoint.localCertificate().isNull() << " Key - isNull:" << localEndpoint.privateKey().isNull();

    // local
    connect(&localServer, SIGNAL(localConnectionMade(int)), this, SLOT(localConnectionMade(int)));

    connect(&localEndpoint, SIGNAL(encrypted()), this, SLOT(localEndpointConnected()));
    connect(&localEndpoint, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(localEndpointError(QAbstractSocket::SocketError)));
    connect(&localEndpoint, SIGNAL(sslErrors(const QList<QSslError>&)),
            this, SLOT(localEndpointSslError(const QList<QSslError>&)));
    connect(&localEndpoint, SIGNAL(disconnected()), this, SLOT(localEndpointDisconnected()));

    // remote
    connect(&remoteEndpoint, SIGNAL(encrypted()), this, SLOT(remoteEndpointConnected()));
    connect(&remoteEndpoint, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(remoteEndpointError(QAbstractSocket::SocketError)));
    connect(&remoteEndpoint, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(remoteEndpointSslError(QList<QSslError>)));
    connect(&remoteEndpoint, SIGNAL(readyRead()), this, SLOT(remoteEndpointReceive()));
    connect(&remoteEndpoint, SIGNAL(disconnected()), this, SLOT(remoteEndpointDisconnected()));    
}

void GamePacketInspector::start()
{    
    if(localServer.listen(QHostAddress::LocalHost, 2099))
        QLOG_INFO() << "Listening for a local connection on localhost:2099";
    else
        QLOG_INFO() << "Failed to listen for a local connection on localhost:2099";

}

void GamePacketInspector::stopInspection()
{
    decoder.reset();
}

void GamePacketInspector::localConnectionMade(int socketDescriptor)
{
    QLOG_INFO() << "Local connection attempt";
    localEndpoint.setSocketDescriptor(socketDescriptor);
    localEndpoint.startServerEncryption();
}

void GamePacketInspector::localEndpointConnected()
{
    QLOG_INFO() << "Local connection made";
    remoteEndpoint.setProtocol(QSsl::TlsV1);
    remoteEndpoint.setPeerVerifyMode(QSslSocket::QueryPeer);
    remoteEndpoint.connectToHostEncrypted(remoteAddr, 2099);
}

void GamePacketInspector::localEndpointError(QAbstractSocket::SocketError e)
{
    QLOG_FATAL() << "Local endpoint socket error" << e;
    emit connectionError();
}

void GamePacketInspector::localEndpointSslError(const QList<QSslError>& e)
{
    QLOG_FATAL() << "Local endpoint ssl errors" << e;
    emit connectionError();
}

void GamePacketInspector::localEndpointSend()
{
    QLOG_TRACE() << "Local endpoint sending" << localEndpoint.bytesAvailable() << "bytes";
    remoteEndpoint.write(localEndpoint.readAll());
}

void GamePacketInspector::localEndpointDisconnected()
{
    QLOG_INFO() << "Local endpoint disconnected, remote endpoint state is" << remoteEndpoint.state();
    if(remoteEndpoint.state() == QAbstractSocket::ConnectedState){
        remoteEndpoint.disconnectFromHost();
        emit disconnected();
    }
}

void GamePacketInspector::remoteEndpointConnected()
{
    QLOG_INFO() << "Remote endpoint connected";
    // ensure we have a fresh decoder object, this comes handy on client reconnections
    decoder.reset(new RtmpDecoder());
    connect(decoder.get(), SIGNAL(flexInvokeDecoded(RtmpFlexInvokePacket)),
            this, SLOT(remotePacketDecoded(RtmpFlexInvokePacket)));

    if(localEndpoint.bytesAvailable() > 0)
        localEndpointSend();

    connect(&localEndpoint, SIGNAL(readyRead()), this, SLOT(localEndpointSend()));

    emit connected();
}

void GamePacketInspector::remoteEndpointError(QAbstractSocket::SocketError e)
{
    QLOG_ERROR() << "Remote endpoint socket error" << e;
    localEndpoint.disconnectFromHost();
    emit connectionError();
}

void GamePacketInspector::remoteEndpointSslError(const QList<QSslError>& e)
{    
    QLOG_FATAL() << "Remote endpoint ssl errors" << e;
    localEndpoint.disconnectFromHost();
    emit connectionError();
}

void GamePacketInspector::remoteEndpointReceive()
{
    QLOG_TRACE() << "Remote endpoint sent" << remoteEndpoint.bytesAvailable() << " bytes";
    auto data = remoteEndpoint.readAll();    
    localEndpoint.write(data);

    if(decoder){
        try{
            decoder->write(data);
        }catch(std::exception& e){
            QLOG_ERROR() << "Exception ocurred while decoding an incoming packet. What:" << e.what();
            emit inspectionError();
        }
    }
}

void GamePacketInspector::remoteEndpointDisconnected()
{
    QLOG_INFO() << "Remote endpoint disconnected, local endpoint state" << localEndpoint.state();
    if(localEndpoint.state() == QAbstractSocket::ConnectedState){
        localEndpoint.disconnectFromHost();
        emit disconnected();
    }
}

void GamePacketInspector::remotePacketDecoded(RtmpFlexInvokePacket packet)
{
    if(isAmfType<BasicExternalizableMessage>(packet.getBody())){
        auto& m = toAmfType<BasicExternalizableMessage>(packet.getBody())->getBody();

        if(isAmfType<AmfObject>(m)){
            auto msg = toAmfObject(m);

            if(msg->getTypeName().endsWith("GameDTO"))
                parseGameData(msg);
            else if(msg->getTypeName().endsWith("Session"))
                parsePlayerData(msg);
            else
                QLOG_TRACE() << "Ignoring an unknown" << msg->getTypeName() << "remote packet";

        } else if(isAmfType<AmfExtArrayCollection>(m)){
            auto msg = toAmfType<AmfExtArrayCollection>(m);

            if(!msg->isEmpty() && isAmfType<AmfObject>(msg->at(0))){
                auto firstItem = toAmfObject(msg->at(0));

                if(firstItem->getTypeName().endsWith("ChampionBanInfoDTO"))
                    parseChampionAvailability(msg);
            } else {
                QLOG_TRACE() << "Ignoring an unknown AmfExtArrayCollection(" << msg->size() << ") remote packet";
            }

        } else {
            QLOG_TRACE() << "Ignoring an unknown BasicExternalizableMessage remote packet";
        }
    }

    QLOG_TRACE() << "Ignoring an unknown remote packet";
}

void GamePacketInspector::parsePlayerData(AmfObjectPtr& msg)
{
    if(selfAccountId != 0)
        return;

    auto acc = toAmfObject(msg->value("accountSummary"));

    if(!acc){
        QLOG_ERROR() << "GamePacketInspector can't find \"accountSummary\" entry in" << msg->dump();
        return;
    }

    bool ok;
    selfAccountId = acc->value("accountId").toLongLong(&ok);

    if(!ok){
        QLOG_ERROR() << "GamePacketInspector unable to obtain integer from" << acc->value("accountId");
        return;
    }

    QLOG_INFO() << "GamePacketInspector Player logged in with accountId =" << selfAccountId;
    emit playerLoggedIn();
}

void GamePacketInspector::parseGameData(AmfObjectPtr& msg)
{
    // todo add more elegant way to check for these, and maybe admit other game modes
    if(msg->value("gameMode") != "CLASSIC"){
        QLOG_INFO() << "Ignoring a" << msg->getTypeName() << "packet: gameMode(" << msg->value("gameMode") << ") != \"CLASSIC\"";
        return;
    }

    QLOG_TRACE() << "Parsing game data packet " << msg->dump();
    updateGameState(msg);

    if(game.state == GameState::ChampSelect){
        updatePlayersState(msg);

    } else if(game.state == GameState::PreChampSelect){
        // only spells change in PreChampSelect, but as they dont mean anything without a champion pick, it is safe
        // to defer detection in ChamSelect
        //updatePlayersState(msg);

        // update bans
        auto bans = toAmfType<AmfExtArrayCollection>(msg->value("bannedChampions"));

        if(bans){
            foreach(const QVariant& e, *bans){
                auto entry = toAmfObject(e);
                int champ = entry->value("championId").toInt();

                if(!game.bannedChamps.contains(champ)){
                    game.bannedChamps.insert(champ);
                    int teamId = game.firstMove == entry->value("pickTurn").toInt()%2?
                                    game.teamId : game.teamId%2 + 1;
                    emit championBanned(champ, teamId);
                }
            }
        } else {
            QLOG_DEBUG() << "No \"bannedChampions\" key in game data packet";
        }

    } else if(game.state == GameState::PostChampSelect){
        for(auto it = game.playerState.begin(); it != game.playerState.end(); ++it){
            if(!it->lockedIn){
                it->lockedIn = true;
                emit playerLockedIn(it->id, it->currentChamp);
            }
        }

    }else if(game.state == GameState::EveryoneJoinedRoom){
        InspectedMatch info;
        parseGameInfo(msg, info);

        // player states
        auto players = toAmfType<AmfExtArrayCollection>(msg->value("playerChampionSelections"));
        foreach(const QVariant& e, *players)
            game.playerState.insert(toAmfObject(e)->value("summonerInternalName").toString(), PlayerState());

        int i = 0;
        foreach(const InspectedMatchParticipant& p, info.selfTeam) // 0-4 our team
            game.playerState[p.summonerInternalName].id = i++;
        foreach(const InspectedMatchParticipant& p, info.enemyTeam) // 5-9 enemy
            game.playerState[p.summonerInternalName].id = i++;

        // team
        game.firstMove = info.firstMove;
        game.teamId = info.selfTeamId;

        emit matchupCreated(info);

    } else if(game.state == GameState::Null){
        InspectedMatch info;
        parseGameInfo(msg, info);

        emit matchupBeingCreated(info);

        game.state = GameState::JoiningChampSelect;

    } else if(game.state == GameState::GameStarted){
        //clearGameState();

    } else if(game.state == GameState::Terminated) {
        clearGameState();
        emit matchupDisbanded();
    }
}

void GamePacketInspector::updateGameState(AmfObjectPtr& msg)
{
    auto s = msg->value("gameState").toString();

    if(s == "CHAMP_SELECT"){
        if(game.state == GameState::JoiningChampSelect)
            game.state = GameState::EveryoneJoinedRoom;
        else
            game.state = GameState::ChampSelect;

    } else if(s == "PRE_CHAMP_SELECT"){
        if(game.state == GameState::JoiningChampSelect)
            game.state = GameState::EveryoneJoinedRoom;
        else
            game.state = GameState::PreChampSelect;

    } else if(s == "POST_CHAMP_SELECT"){
        game.state = GameState::PostChampSelect;
    } else if(s == "TERMINATED") {
        game.state = GameState::Terminated;
    }
}

void GamePacketInspector::parseGameInfo(AmfObjectPtr& msg, InspectedMatch& g)
{
    g.queueTypeName = msg->value("queueTypeName").toString();
    g.gameMode = msg->value("gameMode").toString();
    g.gameType = msg->value("gameType").toString();
    g.maxNumPlayers = msg->value("maxNumPlayers").toInt();
    g.mapId = msg->value("mapId").toInt();

    QList<InspectedMatchParticipant> teamA;
    if(parseParticipantsInfo(msg->value("teamOne"), teamA)){
        g.selfTeam = teamA;
        parseParticipantsInfo(msg->value("teamTwo"), g.enemyTeam);
        g.selfTeamId = 1;
    } else {
        g.enemyTeam = teamA;
        parseParticipantsInfo(msg->value("teamTwo"), g.selfTeam);
        g.selfTeamId = 2;
    }

    auto banOrder = toAmfType<AmfArrayCollectionPtr>(msg->value("banOrder"));
    if(banOrder && !banOrder->isEmpty())
        g.firstMove = banOrder->at(0).toInt() == g.selfTeamId;
}

bool GamePacketInspector::parseParticipantsInfo(const QVariant& msg, QList<InspectedMatchParticipant> &team)
{
    bool selfTeam = false;
    auto t = toAmfType<AmfArrayCollectionPtr>(msg);
    foreach(const QVariant& e, *t){
        auto entry = toAmfObject(e);

        if(entry->getTypeName().endsWith("PlayerParticipant")){
            InspectedMatchParticipant p;
            p.summonerName = entry->value("summonerName").toString();
            p.summonerInternalName = entry->value("summonerInternalName").toString();
            p.accountId = entry->value("accountId").toUInt();
            p.summonerId = entry->value("summonerId").toUInt();

            if(p.accountId == selfAccountId){
                p.isSelfUser = true;
                selfTeam = true;
            } else {
                p.isSelfUser = false;
            }

            team.append(p);
        }
    }

    return selfTeam;
}

void GamePacketInspector::updatePlayersState(AmfObjectPtr& msg)
{
    auto players = toAmfType<AmfArrayCollectionPtr>(msg->value("playerChampionSelections"));

    foreach(const QVariant& e, *players){
        auto entry = toAmfObject(e);
        auto playerInternalName = entry->value("summonerInternalName").toString();
        auto& playerState = game.playerState[playerInternalName];

        // check spells
        auto newSpell1 = entry->value("spell1Id").toInt();
        auto newSpell2 = entry->value("spell2Id").toInt();
        if(playerState.spell1 != newSpell1 || playerState.spell2 != newSpell2){
            playerState.spell1 = newSpell1;
            playerState.spell2 = newSpell2;

            emit playerSpellsChanged(playerState.id, newSpell1, newSpell2);
        }

        // check pick start
        auto teamA = toAmfType<AmfArrayCollectionPtr>(msg->value("teamOne"));
        auto teamB = toAmfType<AmfArrayCollectionPtr>(msg->value("teamTwo"));
        auto allPlayers = *teamA + *teamB;

        if(!playerState.picking){
            foreach(const QVariant& playerData, allPlayers){
                auto pEntry = toAmfObject(playerData);

                if(pEntry->value("summonerInternalName").toString() == playerInternalName){
                    if(pEntry->value("pickMode").toInt() == 1){
                        playerState.picking = true;

                        emit playerStartsPicking(playerState.id);
                    }
                    break;
                }
            }
        }

        // check champion pick/switch
        auto newChampId = entry->value("championId").toInt();
        if(newChampId != playerState.currentChamp){
            playerState.currentChamp = newChampId;

            if(playerState.lockedIn){
                // TODO handle champion switch
            } else {
                emit playerChampionPicked(playerState.id, newChampId);
            }
        }

        // check lock in
        if(newChampId != 0 && !playerState.lockedIn){
            foreach(const QVariant& playerData, allPlayers){
                auto pEntry = toAmfObject(playerData);

                if(pEntry->value("summonerInternalName").toString() == playerInternalName){
                    int pickMode = pEntry->value("pickMode").toInt();

                    if(pickMode == 0 || pickMode == 2){ // champId != 0 && pickPode == 0|2  = locked in
                        playerState.lockedIn = true;

                        emit playerLockedIn(playerState.id, newChampId);
                    }
                    break;
                }
            }
        }
    }
}

void GamePacketInspector::clearGameState()
{
    game.bannedChamps.clear();
    game.playerState.clear();
    game.state = GameState::Null;
}

void GamePacketInspector::parseChampionAvailability(AmfArrayCollectionPtr& champs)
{
    InspectedEnemyRoster ret;

    foreach(const QVariant& it, *champs){
        auto champ = toAmfObject(it);

        if(champ && champ->value("enemyOwned").toBool())
            ret.championIds.append(champ->value("championId").toInt());
    }

    emit enemyRosterReceived(ret);
}
