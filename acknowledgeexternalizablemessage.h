#ifndef ACKNOWLEDGEEXTERNALIZABLEMESSAGE_H
#define ACKNOWLEDGEEXTERNALIZABLEMESSAGE_H

#include "asyncexternalizablemessage.h"

class AcknowledgeExternalizableMessage : public AsyncExternalizableMessage
{
public:
    AcknowledgeExternalizableMessage();

    void read(AmfReader *stream);
};

#endif // ACKNOWLEDGEEXTERNALIZABLEMESSAGE_H
