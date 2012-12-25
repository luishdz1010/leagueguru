#include "acknowledgeexternalizablemessage.h"

AcknowledgeExternalizableMessage::AcknowledgeExternalizableMessage()
{}

void AcknowledgeExternalizableMessage::read(AmfReader *stream)
{
    AsyncExternalizableMessage::read(stream);

    foreach(quint8 flag, readFlags(stream))
        discardRemaining(stream, flag, 0);
}
