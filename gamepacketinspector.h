#ifndef GAMEPACKETINSPECTOR_H
#define GAMEPACKETINSPECTOR_H

#include <QTcpServer>
#include <QSslSocket>
#include <QSslKey>
#include <memory>
#include "rtmpdecoder.h"

struct InspectedMatchParticipant{
    QString summonerName;
    QString summonerInternalName;
    quint32 summonerId;
    quint32 accountId;
    bool isSelfUser = false;
};

struct InspectedMatch{
    QString queueTypeName;
    QString gameMode;
    QString gameType;
    QList<InspectedMatchParticipant> selfTeam;
    QList<InspectedMatchParticipant> enemyTeam;
    int maxNumPlayers;
    int mapId;
    bool firstMove;
    int selfTeamId;
    int selfSummonerIndex;
};

inline QDebug operator<<(QDebug dbg, const InspectedMatch& m)
{
    dbg.nospace() << "[queueTypeName: " << m.queueTypeName << ", gameMode: " << m.gameMode << ", gameType: " << m.gameType << "]";
    return dbg.space();
}

struct InspectedEnemyRoster{
    QList<int> championIds;
};

class InspectorLocalSslServer : public QTcpServer{
    Q_OBJECT
signals:
    void localConnectionMade(int socketDescriptor);

protected:
    void incomingConnection (int handle)
    {
        close();
        emit localConnectionMade(handle);
    }
};

/*TODO
    parse the login packet in order to obtain the summonerId/name    
    implement roster signal
*/
class GamePacketInspector : public QObject
{
    Q_OBJECT
public:
    GamePacketInspector(const QString& gameServer, const QString& cert,
                        const QString& key, QObject *parent = 0);

    void start();

    // enters in passive move, delivering packets to their respective end without inspecting them
    void stopInspection();

signals:
    void connected();    
    void disconnected();

    void connectionError();
    void inspectionError();

    void playerLoggedIn();

    void matchupBeingCreated(InspectedMatch);
    void matchupDisbanded();
    void matchupCreated(InspectedMatch);

    void enemyRosterReceived(InspectedEnemyRoster);
    void championBanned(int championId, int teamId);

    void playerStartsPicking(int player);
    void playerChampionPicked(int player, int championId);
    void playerLockedIn(int player, int championId);
    void playerSpellsChanged(int player, int spellA, int spellB);

private slots:
    void localConnectionMade(int socketDescriptor);

    void localEndpointConnected();    
    void localEndpointError(QAbstractSocket::SocketError e);
    void localEndpointSslError(const QList<QSslError>& e);
    void localEndpointSend();
    void localEndpointDisconnected();

    void remoteEndpointConnected();
    void remoteEndpointError(QAbstractSocket::SocketError e);
    void remoteEndpointSslError(const QList<QSslError>& e);
    void remoteEndpointReceive();
    void remoteEndpointDisconnected();

    void remotePacketDecoded(RtmpFlexInvokePacket packet);

private:
    void clearGameState();

    // we use this instead of login data for now
    void parsePlayerData(AmfObjectPtr& msg);

    void parseGameData(AmfObjectPtr& msg);
    void parseGameInfo(AmfObjectPtr& msg, InspectedMatch& g);
    bool parseParticipantsInfo(const QVariant& msg, QList<InspectedMatchParticipant>& team);
    void updateGameState(AmfObjectPtr& msg);
    void updatePlayersState(AmfObjectPtr& msg);

    void parseChampionAvailability(AmfArrayCollectionPtr& champs);

    struct PlayerState{
        int id = 0;
        int currentChamp = 0;
        int spell1 = -1;
        int spell2 = -1;
        bool picking = false;
        bool lockedIn = false;
    };

    struct GameState{
        QSet<int> bannedChamps;
        QHash<QString, PlayerState> playerState;
        int firstMove;
        int teamId;
        enum{
            Null,
            JoiningChampSelect,
            Terminated,
            EveryoneJoinedRoom,
            PreChampSelect,
            ChampSelect,
            PostChampSelect,
            GameStarted
        } state;
    };

    GameState game;
    quint32 selfAccountId;

    InspectorLocalSslServer localServer;
    QSslSocket localEndpoint;
    QSslSocket remoteEndpoint;
    QString remoteAddr;
    std::unique_ptr<RtmpDecoder> decoder;
};

#endif // GAMEPACKETINSPECTOR_H
