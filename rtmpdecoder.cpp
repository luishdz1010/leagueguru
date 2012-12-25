#include "rtmpdecoder.h"
#include "asyncexternalizablemessage.h"
#include "acknowledgeexternalizablemessage.h"
#include "qslog/QsLog.h"

namespace{

const int headerSize[] = {11, 7, 3, 0};

unsigned int AMF_DecodeInt24(QIODevice& buff)
{
    unsigned char h[3];
    buff.read((char*)h, 3);
    return (h[0] << 16) | (h[1] << 8) | h[2];
}

unsigned int AMF_DecodeInt32(QIODevice& buff)
{
    unsigned char h[4];
    buff.read((char*)h, 4);
    return (h[0] << 24) | (h[1] << 16) | (h[2] << 8) | h[3];
}

int DecodeInt32LE(QIODevice& buff)
{
    unsigned char h[4];
    buff.read((char*)h, 4);
    return (h[3] << 24) | (h[2] << 16) | (h[1] << 8) | h[0];
}

}

RtmpDecoder::RtmpDecoder() :
    nextReadSize(HandshakeSize*2 + 1),
    state(AwaitingHanshake)
{
    buff.open(QIODevice::ReadWrite);

    extObjMap.insert("flex.messaging.io.ArrayCollection", []{ return std::make_shared<AmfExtArrayCollection>(); });

    extObjMap.insert("DSA", []{ return std::make_shared<AsyncExternalizableMessage>(); });
    extObjMap.insert("DSK", []{ return std::make_shared<AcknowledgeExternalizableMessage>(); });

}

void RtmpDecoder::write(const QByteArray &data)
{
    auto pos = buff.pos();
    buff.seek(buff.size());
    buff.write(data);
    buff.seek(pos);

    while(buff.bytesAvailable() >= nextReadSize){
        switch(state){
        case AwaitingPacket:
            decodeInitialByte();
            break;
        case AwaitingHeaderType:
            decodeHeaderType();
            break;
        case AwaitingHeader:
            decodeHeader();
            break;
        case AwaitingExTimestamp:
            decodeExTimestamp();
            break;
        case AwaitingBodyChunk:
            decodeBodyChunk();
            if(buff.bytesAvailable() == 0)
                resetBuffer();
            break;
        case AwaitingHanshake:
            resetBuffer(); // discard hanshake
            nextReadSize = 1;
            state = AwaitingPacket;
            break;
        }
    }
}

void RtmpDecoder::resetBuffer()
{
    buff.buffer().resize(0);
    buff.reset();
}

void RtmpDecoder::decodeInitialByte()
{
    uint8_t h;
    buff.getChar((char*)&h);
    currentChannel = h;

    if((currentChannel & 0x3F) < 2) {
        state = AwaitingHeaderType;
        nextReadSize = currentChannel + 1;
    } else {
        decodeHeaderType();
    }
}

void RtmpDecoder::decodeHeaderType()
{
    uint8_t headerType = (currentChannel & 0xC0) >> 6;

    if ((currentChannel & 0x3F) == 0){
        uint8_t ch;
        buff.getChar((char*)&ch);
        currentChannel = ch + 64 ;
    } else if ((currentChannel & 0x3F) == 1){
        uint8_t ch[2];
        buff.read((char*)ch, 2);
        currentChannel = (ch[1] << 8) + ch[0] + 64;
    } else {
        currentChannel &= 0x3F;
    }

    if(!context.lastPackets[currentChannel]){
        QLOG_INFO() << "RtmpDecoder new channel" << currentChannel << "requested";
        context.lastPackets[currentChannel] = new RtmpPacket();
        context.lastPackets[currentChannel]->message.open(QIODevice::ReadWrite);
    }

    currentPacket = context.lastPackets[currentChannel];
    currentPacket->headerType = headerType;

    if(headerSize[headerType] != 0){
        state = AwaitingHeader;
        nextReadSize = headerSize[headerType];
    } else{
        waitForBody();
    }
}

void RtmpDecoder::decodeHeader()
{
    int hSize = headerSize[currentPacket->headerType];

    if (hSize >= 3){
        currentPacket->timestamp = AMF_DecodeInt24(buff);

        if (hSize >= 6){
            currentPacket->payloadSize = AMF_DecodeInt24(buff);
            buff.getChar((char*)&currentPacket->messageType);

            if (hSize == 11)
                currentPacket->streamId = DecodeInt32LE(buff);
        }

        if (currentPacket->timestamp == 0xFFFFFF)
        {
            state = AwaitingExTimestamp;
            nextReadSize = 4;
            return;
        }
    }

    waitForBody();
}

void RtmpDecoder::decodeExTimestamp()
{
    currentPacket->timestamp = AMF_DecodeInt32(buff);
    waitForBody();
}

void RtmpDecoder::waitForBody()
{
    state = AwaitingBodyChunk;
    nextReadSize = std::min((qint64)context.chunkSizeIn, currentPacket->payloadSize - currentPacket->message.size());
}

void RtmpDecoder::decodeBodyChunk()
{
    currentPacket->message.write(buff.read(nextReadSize));
    state = AwaitingPacket;
    nextReadSize = 1;

    if (currentPacket->message.size() == currentPacket->payloadSize){
        currentPacket->message.reset();

        try{
            processPacket();

        }catch(AmfExternalizableObjectMissingException& e){
            QLOG_WARN() << "Skipping RTMP packet, unknow externalizable object" << e.what();
        }catch(AmfUnsupportedDataTypeException&){
            QLOG_ERROR() << "Skipping RTMP packet, unsupported data type";
        }catch(AmfInvalidFormatException&){
            QLOG_ERROR() << "Skipping RTMP packet, invalid format";
        }catch(std::exception&){
            currentPacket->message.buffer().resize(0);
            currentPacket->message.reset();
            throw;
        }

        currentPacket->message.buffer().resize(0);
        currentPacket->message.reset();
    }
}

void RtmpDecoder::processPacket()
{
    switch(currentPacket->messageType){
    case 17: // AMF3Invoke
        decodeFlexInvoke(currentPacket->message);
        break;
    case 20: // AMF0
        decodeInvoke(currentPacket->message);
        break;
    default:
        QLOG_INFO() << "RtmpDecoder ignoring unknown packet type" << currentPacket->messageType;
    }
}

void RtmpDecoder::decodeFlexInvoke(QBuffer& stream)
{
    stream.read(1); // amf version, always 0

    AmfReader reader(&stream, &extObjMap);

    auto cmd = reader.readNext().toString();
    auto id = reader.readNext().toInt();
    reader.readNext(); // params, always null

    emit flexInvokeDecoded(RtmpFlexInvokePacket(cmd, id, reader.readNext()));
}

void RtmpDecoder::decodeInvoke(QBuffer& /*stream*/)
{
    /*AmfReader reader(&stream, &extObjMap);
    auto cmd = reader.readNext();
    reader.readNext();
    reader.readNext();*/
}
