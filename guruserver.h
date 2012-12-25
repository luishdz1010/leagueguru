#ifndef GURUSERVER_H
#define GURUSERVER_H

#include <stdint.h>
#include <QTcpSocket>
#include <QQueue>
#include "guru/packet.pb.h"
#include "guru/matchupinfo.pb.h"
#include "guru/matchupcreated.pb.h"
#include "guru/logincredentials.pb.h"
#include "guru/bansuggestions.pb.h"
#include "guru/lockparticipant.pb.h"
#include "guru/enemyroster.pb.h"
#include "guru/participantspells.pb.h"
#include "guru/participantrole.pb.h"
#include "guru/championban.pb.h"
#include "guru/participantchampion.pb.h"
#include "guru/participantstartspicking.pb.h"
#include "guru/participantssuggestions.pb.h"

class GuruServerConnection : public QTcpSocket
{
    Q_OBJECT
public:
    enum {
        MaxPacketSize = 32767
    };

    explicit GuruServerConnection(QObject *parent = 0);

    void login(const guru::LoginCredentials& msg)
    {
        sendRequest<guru::LOGIN, guru::LoginCredentials>(msg);
    }
    
    void createMatchup(const guru::MatchupInfo& msg)
    {
        sendRequest<guru::CREATE_MATCHUP, guru::MatchupInfo>(msg);
    }

    void setEnemyRoster(const guru::EnemyRoster& msg)
    {
        sendRequest<guru::SET_ENEMY_ROSTER, guru::EnemyRoster>(msg);
    }

    void addChampionBan(const guru::ChampionBan& msg)
    {
        sendRequest<guru::ADD_CHAMPION_BAN, guru::ChampionBan>(msg);
    }

    void setParticipantRole(const guru::ParticipantRole& msg)
    {
        sendRequest<guru::SET_PARTICIPANT_ROLE, guru::ParticipantRole>(msg);
    }

    void participantStartsPicking(const guru::ParticipantStartsPicking& msg)
    {
        sendRequest<guru::PARTICIPANT_STARTS_PICKING, guru::ParticipantStartsPicking>(msg);
    }

    void setParticipantSpells(const guru::ParticipantSpells& msg)
    {
        sendRequest<guru::SET_PARTICIPANT_SPELLS, guru::ParticipantSpells>(msg);
    }

    void setParticipantChampion(const guru::ParticipantChampion& msg)
    {
        sendRequest<guru::SET_PARTICIPANT_CHAMPION, guru::ParticipantChampion>(msg);
    }

    void lockParticipant(const guru::LockParticipant& msg)
    {
        sendRequest<guru::LOCK_PARTICIPANT, guru::LockParticipant>(msg);
    }

    void send(guru::MessageType type, const google::protobuf::Message& msg);


    //GetBanSuggestions
    //GetPlayerSuggestions

signals:
    void status(guru::MessageType requestCode, guru::StatusCode status);

    void matchupCreated(guru::MatchupCreated& matchup);
    void banSuggestionsChanged(guru::BanSuggestions& suggestions);
    void participantsSuggestionsChanged(guru::ParticipantsSuggestions& suggestions);

    void protocolError();
    
private slots:
    void onReadyRead();

private:
    template <guru::MessageType code, class Message>
    void sendRequest(const Message& msg)
    {
        send(code, msg);
        requestCodeQueue.enqueue(code);
    }

    void parseIncomingPacketHeader();
    void parseIncomingPacket();

    char buffer[MaxPacketSize];
    QQueue<guru::MessageType> requestCodeQueue;
    quint16 inPacketSize;
    quint8 inPacketType;
};

#endif // GURUSERVER_H
