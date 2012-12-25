#ifndef BASICEXTERNALIZABLEMESSAGE_H
#define BASICEXTERNALIZABLEMESSAGE_H

#include "amfexternalizableobjectmap.h"
#include <QVariant>

class BasicExternalizableMessage : public AmfExternalizableObject
{
public:
     enum{
         HAS_NEXT_FLAG = 128,
         MESSAGE_ID_FLAG = 16,
         TIME_TO_LIVE_FLAG = 64,
         TIMESTAMP_FLAG = 32,
         CLIENT_ID_BYTES_FLAG = 1,
         DESTINATION_FLAG = 4,
         CLIENT_ID_FLAG = 2,
         HEADERS_FLAG = 8,
         BODY_FLAG = 1,
         MESSAGE_ID_BYTES_FLAG = 2
     };

    BasicExternalizableMessage();

    void read(AmfReader* stream);

    QVariant& getBody() { return body; }
    QString& getClientId(){ return clientId; }
    QByteArray& getClientIdBytes(){ return clientIdBytes; }
    QString& getDestination(){ return dest; }
    QVariant& getHeaders(){ return headers; }
    QString getMessageId(){ return messageId; }
    QByteArray& getMessageIdBytes(){ return messageIdBytes; }
    qint64 getTimeStamp() const { return timestamp; }
    qint64 getTimeToLive() const { return timeToLive; }

    QString dump(int level);

protected:
    QList<quint8> readFlags(AmfReader* stream);
    void discardRemaining(AmfReader* stream, int flag, int startBit);

private:
    QVariant body;
    QString clientId;
    QByteArray clientIdBytes;
    QString dest;
    QVariant headers;
    QString messageId;
    QByteArray messageIdBytes;
    qint64 timestamp;
    qint64 timeToLive;
};

#endif // BASICEXTERNALIZABLEMESSAGE_H
