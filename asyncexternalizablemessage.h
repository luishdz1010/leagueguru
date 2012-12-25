#ifndef ASYNCEXTERNALIZABLEMESSAGE_H
#define ASYNCEXTERNALIZABLEMESSAGE_H

#include "basicexternalizablemessage.h"

class AsyncExternalizableMessage : public BasicExternalizableMessage
{
public:
    enum{
        CORRELATION_ID_FLAG = 1,
        CORRELATION_ID_BYTES_FLAG = 2
    };

    AsyncExternalizableMessage();

    QString& getCorrelationId() { return correlationId; }
    QByteArray& getCorrelationIdBytes() { return correlationIdBytes; }

    void read(AmfReader *stream);

private:
    QString correlationId;
    QByteArray correlationIdBytes;
};

#endif // ASYNCEXTERNALIZABLEMESSAGE_H
