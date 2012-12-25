#include "amfreader.h"
#include "amfexternalizableobjectmap.h"
#include <QDateTime>
#include <QDebug>

namespace {

unsigned short AMF_DecodeInt16(const char *data)
{
    unsigned char *c = (unsigned char *) data;
    unsigned short val;
    val = (c[0] << 8) | c[1];
    return val;
}

double AMF_DecodeNumber(const char *data)
{
    double dVal;
    unsigned char *ci, *co;
    ci = (unsigned char *)data;
    co = (unsigned char *)&dVal;
    co[0] = ci[7];
    co[1] = ci[6];
    co[2] = ci[5];
    co[3] = ci[4];
    co[4] = ci[3];
    co[5] = ci[2];
    co[6] = ci[1];
    co[7] = ci[0];
    return dVal;
}

}

AmfReader::AmfReader(QIODevice* buffer, AmfExternalizableObjectMap* extMap) :
    buff(buffer),
    extObjMap(extMap)
{
    if(!buff->isOpen())
        buff->open(QIODevice::ReadOnly);
}

QVariant AmfReader::readNext()
{
    auto type = readByte();

    switch(type){
    case AMF_NUMBER:
        return readNumber();
    case AMF_BOOLEAN:
        return readBool();
    case AMF_STRING:
        return readString();
    case AMF_OBJECT:
        return readAnonymousObject();
    case AMF_NULL:
    case AMF_UNDEFINED:
        return QVariant();
    case AMF_SWITCHAMF3:
        return readAmf3Next();
    default:
        throw AmfUnsupportedDataTypeException();
    }
}

quint8 AmfReader::readByte()
{
    quint8 ret;
    if(!buff->getChar((char*)&ret))
        throw AmfInvalidFormatException();

    return ret;
}

double AmfReader::readNumber()
{
    char v[8];
    if(buff->read(v, 8) != 8)
        throw AmfInvalidFormatException();

    return AMF_DecodeNumber(v);
}

bool AmfReader::readBool()
{
    return readByte() != 0;
}

QString AmfReader::readString()
{
    char s[2];
    if(buff->read(s, 2) != 2)
        throw AmfInvalidFormatException();

    return readUtf8(AMF_DecodeInt16(s));
}

QVariant AmfReader::readAnonymousObject()
{
    auto obj = std::make_shared<AmfObject>();
    QString key;
    while(!(key = readString()).isEmpty())
        obj->insert(key, readNext());
    readByte();
    return QVariant::fromValue(obj);
}

QVariant AmfReader::readAmf3Next()
{
    auto type = readByte();

    switch(type){
    case AMF3_UNDEFINED:
    case AMF3_NULL:
        return QVariant();
    case AMF3_FALSE:
        return false;
    case AMF3_TRUE:
        return true;
    case AMF3_INTEGER:
        return readAmf3Int();
    case AMF3_DOUBLE:
        return readAmf3Double();
    case AMF3_STRING:
        return readAmf3String();
    case AMF3_XML_DOC:
        qDebug() << "gg doc";
        throw AmfUnsupportedDataTypeException();
    case AMF3_DATE:
        return readAmf3Date();
    case AMF3_ARRAY:
        return readAmf3Array();
    case AMF3_OBJECT:
        return readAmf3Object();
    case AMF3_XML:
         qDebug() << "gg xml";
         throw AmfUnsupportedDataTypeException();
    case AMF3_BYTE_ARRAY:
        return readAmfByteArray();
    default:
        qDebug() << "gg " << type;
        throw AmfUnsupportedDataTypeException();
    }
}

qint32 AmfReader::readAmf3Int()
{
    qint32 acc = readByte();
    if(acc < 128)
        return acc;

    acc = (acc & 0x7f) << 7;
    qint32 tmp = readByte();

    if(tmp < 128){
        acc = acc | tmp;
    } else {
        acc = (acc | (tmp & 0x7f)) << 7;
        tmp = readByte();

        if(tmp < 128)
            acc = acc | tmp;
        else
            acc = ((acc | (tmp & 0x7f)) << 8) | readByte();
    }

    return -(acc & (1 << 28)) | acc;
}

double AmfReader::readAmf3Double()
{
    return readNumber();
}

QString AmfReader::readAmf3String()
{
    auto size = readAmf3Int();
    bool ref = (size & 1) == 0;
    size >>= 1;

    if(ref)
        return readStringRef(size);

    if(size == 0)
        return QString();

    auto str = readUtf8(size);
    addStringRef(str);
    return str;
}

QDateTime AmfReader::readAmf3Date()
{
    auto handle = readAmf3Int();

    if((handle & 1) == 0)
        return readObjectRef<QDateTime>(handle >> 1);

    QDateTime date;
    date.setTimeSpec(Qt::UTC);
    date.setMSecsSinceEpoch(readAmf3Double());

    addObjectRef(date);
    return date;
}

QVariant AmfReader::readAmf3Array()
{
    auto handle = readAmf3Int();
    bool ref = (handle & 1) == 0;
    handle >>= 1;

    if(ref)
        return readObjectRef(handle);

    auto key = readAmf3String();
    if(!key.isEmpty()){
        auto map = std::make_shared<QHash<QString, QVariant> >();
        addObjectRef(QVariant::fromValue(map));

        while(!key.isEmpty()){
            map->insert(key, readAmf3Next());
            key = readAmf3String();
        }

        for(int i = 0; i < handle; ++i)
            map->insert(QString::number(i), readAmf3Next());

        return QVariant::fromValue(map);

    } else {
        auto vec = std::make_shared<QList<QVariant> >();
        addObjectRef(QVariant::fromValue(vec));

        for(int i = 0; i < handle; ++i)
            vec->append(readAmf3Next());

        return QVariant::fromValue(vec);
    }
}

QVariant AmfReader::readAmf3Object()
{
    auto handle = readAmf3Int();
    bool ref = (handle & 1) == 0;
    handle >>= 1;

    if(ref)
        return readObjectRef(handle);

    const AmfClassDef* classDef;
    ref = (handle & 1) == 0;
    handle >>= 1;

    if(ref){
        classDef = readClassDefRef(handle);
    } else {
        auto newClassDef = addClassDefRef(readAmf3String());
        newClassDef->externalizable = (handle & 1) != 0; handle >>= 1;
        newClassDef->dynamic = (handle & 1) != 0; handle >>= 1;

        for(int i = 0; i < handle; ++i)
            newClassDef->members.append(readAmf3String());

        classDef = newClassDef;
    }

    if(classDef->externalizable){
        if(extObjMap){
            auto extObjConstructor = extObjMap->find(classDef->name);

            if(extObjConstructor != extObjMap->end()){
                auto extObj = (*extObjConstructor)();
                addObjectRef(QVariant::fromValue(extObj));
                extObj->read(this);
                return QVariant::fromValue(extObj);
            }
        }

        throw AmfExternalizableObjectMissingException(classDef->name.toStdString());

    } else {
        auto obj = std::make_shared<AmfObject>(classDef->name);
        addObjectRef(QVariant::fromValue(obj));

        foreach(const QString& propName, classDef->members)
            obj->insert(propName, readAmf3Next());

        if(classDef->dynamic){
            auto propName = readAmf3String();
            while(!propName.isEmpty()){
                obj->insert(propName, readAmf3Next());
                propName = readAmf3String();
            }
        }

        return QVariant::fromValue(obj);
    }
}

QByteArray AmfReader::readAmfByteArray()
{
    auto handle = readAmf3Int();
    bool ref = (handle & 1) == 0;
    handle >>= 1;

    if(ref)
        return readObjectRef<QByteArray>(handle);

    auto v = buff->read(handle);
    if((qint32)v.size() != handle)
        throw AmfInvalidFormatException();

    addObjectRef(v);
    return v;
}

void AmfReader::dump()
{
    qDebug() << "\n(begin dump)";

    while(buff->bytesAvailable() > 0)
        qDebug().maybeSpace() << debugAmf(readNext(), 0);

    qDebug() << "(end dump)\n";
}

QString AmfReader::readUtf8(quint32 size)
{
    auto str = buff->read(size);
    if((quint32)str.size() != size)
        throw AmfInvalidFormatException();

    return QString::fromUtf8(str.data(), size);
}

void AmfReader::addStringRef(const QString &str)
{
    strings.append(str);
}

QString AmfReader::readStringRef(int handle)
{
    return strings.at(handle);
}

void AmfReader::addObjectRef(const QVariant &obj)
{
    objects.append(obj);
}

AmfClassDef* AmfReader::addClassDefRef(const QString &typeName)
{
    AmfClassDef cls;
    cls.name = typeName;
    classes.append(cls);
    return &classes.last();
}

const AmfClassDef* AmfReader::readClassDefRef(int handle)
{
    return &classes.at(handle);
}
