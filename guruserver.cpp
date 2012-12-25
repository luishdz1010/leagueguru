#include "guruserver.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>

using namespace guru;
using namespace google::protobuf::io;

GuruServerConnection::GuruServerConnection(QObject *parent) :
    QTcpSocket(parent),
    inPacketSize(0),
    inPacketType(0)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void GuruServerConnection::send(guru::MessageType type, const google::protobuf::Message& msg)
{
    Q_ASSERT((unsigned)msg.ByteSize()+8 <= sizeof(buffer));

    ArrayOutputStream output((void*)buffer, sizeof(buffer));
    CodedOutputStream stream(&output);

    stream.WriteRaw((void*)&type, 1);
    quint16 size = msg.ByteSize();
    stream.WriteRaw((void*)&size, 2);
    msg.SerializeWithCachedSizes(&stream);

    write(buffer, stream.ByteCount());
}

void GuruServerConnection::onReadyRead()
{
    for(int currentBytes = bytesAvailable(); currentBytes > 0; currentBytes = bytesAvailable()){
        if(inPacketSize > 0){
            if(currentBytes >= inPacketSize){
                parseIncomingPacket();
                inPacketSize = 0;
            } else {
                return;
            }
        } else if(currentBytes >= 3){
            parseIncomingPacketHeader();
        } else {
            return;
        }
    }
}

void GuruServerConnection::parseIncomingPacketHeader()
{
    read(buffer, 3);
    inPacketType = static_cast<quint8>(buffer[0]);
    inPacketSize = *reinterpret_cast<quint16*>(buffer+1);
}

void GuruServerConnection::parseIncomingPacket()
{
    read(buffer, inPacketSize);
    ArrayInputStream input((void*)buffer, inPacketSize);
    CodedInputStream stream(&input);

    switch(inPacketType){
    case MATCHUP_CREATED:
    {
        MatchupCreated msg;
        if(msg.ParseFromCodedStream(&stream))
            emit matchupCreated(msg);
        else
            emit protocolError();
        break;
    }
    case STATUS:
    {
        Status msg;
        if(msg.ParseFromCodedStream(&stream))
            emit status(requestCodeQueue.takeFirst(), msg.code());
        else
            emit protocolError();
        break;
    }
    case BAN_SUGGESTIONS_UPDATE:
    {
        BanSuggestions msg;
        if(msg.ParseFromCodedStream(&stream))
            emit banSuggestionsChanged(msg);
        else
            emit protocolError();
        break;
    }
    case PARTICIPANT_SUGGESTIONS_UPDATE:
    {
        ParticipantsSuggestions msg;
        if(msg.ParseFromCodedStream(&stream))
            emit participantsSuggestionsChanged(msg);
        else
            emit protocolError();
        break;
    }
    default:
       ; // log
    }
}


