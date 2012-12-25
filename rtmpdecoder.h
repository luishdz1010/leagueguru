#ifndef RTMPDECODER_H
#define RTMPDECODER_H

#include <QObject>
#include <QBuffer>
#include "amfreader.h"
#include "amfexternalizableobjectmap.h"

class RtmpFlexInvokePacket{
public:
    RtmpFlexInvokePacket(QString cmd_, int id_/*, params*/, QVariant body_) :
        body(body_),
        cmd(cmd_),
        id(id_)
    {}

    QVariant& getBody(){ return body; }
    QString& getCommand(){ return cmd; }
    int getId(){ return id; }

private:
    QVariant body;
    QString cmd;
    int id;
};

/*! Decoding for the client packets
    This only implements a subset of the actual RTMP, just enough to parse LoL packets
*/
class RtmpDecoder : public QObject
{
    Q_OBJECT
public:
    enum RtmpConstants {
        HandshakeSize=1536,
        MaxHeaderSize=18
    };

    RtmpDecoder();

    void write(const QByteArray& data);

signals:
    void flexInvokeDecoded(RtmpFlexInvokePacket);

public:
    enum State{
        AwaitingHanshake,
        AwaitingPacket,
        AwaitingHeaderType,
        AwaitingHeader,
        AwaitingExTimestamp,
        AwaitingBodyChunk
    };

    struct RtmpPacket{
        QBuffer message;
        int32_t timestamp;
        int32_t payloadSize;
        int32_t streamId;
        uint8_t messageType;
        uint8_t headerType;
    };

    struct RtmpContext{
        //RtmpPacket* lastPackets[65600] = {0};
        RtmpPacket* lastPackets[100] = {0};
        int chunkSizeIn = 128;
        int chunkSizeOut = 128;
    };

    void resetBuffer();

    void decodeInitialByte();
    void decodeHeaderType();
    void decodeHeader();
    void waitForBody();
    void decodeExTimestamp();
    void decodeBodyChunk();

    void processPacket();
    void decodeFlexInvoke(QBuffer& stream);
    void decodeInvoke(QBuffer& stream);

    RtmpContext context;
    AmfExternalizableObjectMap extObjMap;
    QBuffer buff;
    RtmpPacket* currentPacket;
    int currentChannel;
    int nextReadSize;
    State state;
};

#endif // RTMPDECODER_H
