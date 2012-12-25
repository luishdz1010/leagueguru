#include "basicexternalizablemessage.h"
#include "amfreader.h"

BasicExternalizableMessage::BasicExternalizableMessage()
{}

void BasicExternalizableMessage::read(AmfReader *stream)
{
    int byteN = 0;
    foreach(quint8 flag, readFlags(stream)){
        int bits = 0;

        if(byteN == 0){
            if((flag & BODY_FLAG) != 0)
                body = stream->readAmf3Next();
            if((flag & CLIENT_ID_FLAG) != 0)
                clientId = stream->readAmf3Next().toString();
            if((flag & DESTINATION_FLAG) != 0)
                dest = stream->readAmf3Next().toString();
            if((flag & HEADERS_FLAG) != 0)
                headers = stream->readAmf3Next();
            if((flag & MESSAGE_ID_FLAG) != 0)
                messageId = stream->readAmf3Next().toString();
            if((flag & TIMESTAMP_FLAG) != 0)
                timestamp = stream->readAmf3Next().toLongLong();
            if((flag & TIME_TO_LIVE_FLAG) != 0)
                timestamp = stream->readAmf3Next().toLongLong();

            bits = 7;

        } else if(byteN == 1){
            if((flag & CLIENT_ID_BYTES_FLAG) != 0)
                clientIdBytes = stream->readAmf3Next().toByteArray();
            if((flag & MESSAGE_ID_BYTES_FLAG) != 0)
                messageIdBytes = stream->readAmf3Next().toByteArray();

            bits = 2;
        }

        discardRemaining(stream, flag, bits);
        ++byteN;
    }
}

QString BasicExternalizableMessage::dump(int level)
{
    QString s;
    QString ident = QString(++level, '\t');
    s += QString(level-1, '\t') % "(basic message)\n" %
            ident % "body - " % debugAmf(body, level) % '\n' %
            ident % "timeToLive - (double) " % QString::number(timeToLive) % '\n' %
            ident % "destination - (QString) " % dest % '\n' %
            ident % "clientId - (QString) " % clientId % '\n' %
            ident % "headers - " % debugAmf(headers, level) % '\n' %
            ident % "timestamp - (double) " % QString::number(timestamp) % '\n' %
            ident % "messageId - (QString) " % messageId % '\n' %
            ident % "clientIdBytes - (QString) " % clientIdBytes % '\n' %
            ident % "messageIdBytes - (QString) " % messageIdBytes;
    return s;
}

QList<quint8> BasicExternalizableMessage::readFlags(AmfReader *stream)
{
    QList<quint8> bytes;
    quint8 byte;

    do{
        bytes.append(byte = stream->readByte());
    }while((byte & HAS_NEXT_FLAG) != 0);

    return bytes;
}

void BasicExternalizableMessage::discardRemaining(AmfReader *stream, int flag, int startBit)
{
    if ((flag >> startBit) == 0)
        return;

    for(int b = startBit; b < 6; ++b){
        if ((flag >> b & 1) != 0){
            auto v = stream->readAmf3Next();
        }
    }
}
