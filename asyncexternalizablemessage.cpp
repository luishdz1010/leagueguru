#include "asyncexternalizablemessage.h"
#include "amfreader.h"

AsyncExternalizableMessage::AsyncExternalizableMessage()
{}

void AsyncExternalizableMessage::read(AmfReader *stream)
{
    BasicExternalizableMessage::read(stream);

    int byteN = 0;
    foreach(quint8 flag, readFlags(stream)){
        int bits = 0;

        if(byteN == 0){
            if((flag & CORRELATION_ID_FLAG) != 0)
                correlationId = stream->readAmf3Next().toString();
            if((flag & CORRELATION_ID_BYTES_FLAG) != 0)
                correlationIdBytes = stream->readAmf3Next().toByteArray();

            bits = 2;
        }
        discardRemaining(stream, flag, bits);
    }
}
