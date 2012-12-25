#ifndef AMFREADER_H
#define AMFREADER_H

#include <memory>
#include <stdexcept>
#include <QIODevice>
#include <QVariant>
#include <QHash>
#include <QStringList>
#include <QDebug>
#include "debugamf.h"
#include "amfexternalizableobjectmap.h"

class AmfObject : public QHash<QString, QVariant> {
public:
    AmfObject(){}

    explicit AmfObject(const QString& tName) :
        typeName(tName)
    {}

    const QString& getTypeName() const
    {
        return typeName;
    }

    QString dump(int level = 0)
    {
        QString s;
        s += (typeName.isEmpty()? "(anonymous object)" : ("("+typeName+")") ) + QString("\n");
        ++level;
        foreach(const QString& prop, keys())
            s += QString(level, '\t') + prop + " - " + debugAmf(value(prop), level) + "\n";
        return s;
    }

private:
    QString typeName;
};

struct AmfClassDef{
    QStringList members;
    QString name;
    bool externalizable;
    bool dynamic;
};

typedef std::shared_ptr<QList<QVariant> > AmfArrayPtr;
typedef std::shared_ptr<QHash<QString, QVariant> > AmfMapPtr;
typedef std::shared_ptr<AmfObject> AmfObjectPtr;

Q_DECLARE_METATYPE(AmfArrayPtr)
Q_DECLARE_METATYPE(AmfMapPtr)
Q_DECLARE_METATYPE(AmfObjectPtr)

// helper functions for client type management

template <class T>
struct is_shared_ptr_ext_obj{
    enum{ value = false };
};

template <class T>
struct is_shared_ptr_ext_obj<std::shared_ptr<T> >{
    enum{ value = std::is_base_of<AmfExternalizableObject, T>::value };
};

// every value that isnt an ext object
template <class T>
typename std::enable_if<
    !std::is_base_of<AmfExternalizableObject, T>::value &&
    !is_shared_ptr_ext_obj<T>::value, bool>::type
inline isAmfType(const QVariant& v)
{
    return v.canConvert<T>();
}

template <> bool inline isAmfType<AmfObject>(const QVariant &v)
{
    return isAmfType<AmfObjectPtr>(v);
}

template <> bool inline isAmfType<QList<QVariant> >(const QVariant &v)
{
    return isAmfType<AmfArrayPtr>(v);
}

template <> bool inline isAmfType<QHash<QString, QVariant> >(const QVariant &v)
{
    return isAmfType<AmfMapPtr>(v);
}

// ext objects
template <class T>
typename std::enable_if<std::is_base_of<AmfExternalizableObject, T>::value, bool>::type
inline isAmfType(const QVariant &v)
{
    return v.canConvert<AmfExternalizableObjectPtr>() &&
            std::dynamic_pointer_cast<T>(v.value<AmfExternalizableObjectPtr>());
}

template <class T>
typename std::enable_if<is_shared_ptr_ext_obj<T>::value, bool>::type
inline isAmfType(const QVariant &v)
{
    return isAmfType<typename T::element_type>(v);
}

// convert functions
template <class T>
typename std::enable_if<
    !std::is_base_of<AmfExternalizableObject, T>::value &&
    !is_shared_ptr_ext_obj<T>::value &&
    !std::is_same<AmfObject, T>::value && !std::is_same<QList<QVariant>, T>::value &&
    !std::is_same<QHash<QString, QVariant>, T>::value
,T>::type
inline toAmfType(const QVariant& v)
{
    return v.value<T>();
}

template <class T>
typename std::enable_if<std::is_same<AmfObject, T>::value, AmfObjectPtr>::type
inline toAmfType(const QVariant &v)
{
    return toAmfType<AmfObjectPtr>(v);
}

template <class T>
typename std::enable_if<std::is_same<QList<QVariant>, T>::value, AmfArrayPtr>::type
inline toAmfType(const QVariant &v)
{
    return toAmfType<AmfArrayPtr>(v);
}

template <class T>
typename std::enable_if<std::is_same<QHash<QString, QVariant>, T>::value, AmfMapPtr>::type
inline toAmfType(const QVariant &v)
{
    return toAmfType<AmfMapPtr>(v);
}

template <class T>
typename std::enable_if<std::is_base_of<AmfExternalizableObject, T>::value, std::shared_ptr<T> >::type
inline toAmfType(const QVariant& v)
{
    return std::dynamic_pointer_cast<T>(v.value<AmfExternalizableObjectPtr>());
}

template <class T>
typename std::enable_if<is_shared_ptr_ext_obj<T>::value, T>::type
inline toAmfType(const QVariant& v)
{
    return toAmfType<typename T::element_type>(v);
}

inline AmfObjectPtr toAmfObject(const QVariant& v)
{
    return toAmfType<AmfObjectPtr>(v);
}


class AmfReaderException : public std::runtime_error{
public:
    AmfReaderException(std::string s = "amf reader exception") : std::runtime_error(s){}
};

class AmfUnsupportedDataTypeException : public AmfReaderException {};
class AmfInvalidFormatException : public AmfReaderException {};

class AmfExternalizableObjectMissingException : public AmfReaderException {
public:
    AmfExternalizableObjectMissingException(std::string className) : AmfReaderException(className) {}
};

class AmfReader
{
public:
    enum AMF0DataType {
        AMF_NUMBER = 0, AMF_BOOLEAN, AMF_STRING, AMF_OBJECT,
        AMF_MOVIECLIP,		/* reserved, not used */
        AMF_NULL, AMF_UNDEFINED, AMF_REFERENCE, AMF_ECMA_ARRAY, AMF_OBJECT_END,
        AMF_STRICT_ARRAY, AMF_DATE, AMF_LONG_STRING, AMF_UNSUPPORTED,
        AMF_RECORDSET,		/* reserved, not used */
        AMF_XML_DOC, AMF_TYPED_OBJECT,
        AMF_SWITCHAMF3,
        AMF_INVALID = 0xff
    };

    enum AMF3DataType {
        AMF3_UNDEFINED = 0, AMF3_NULL, AMF3_FALSE, AMF3_TRUE,
        AMF3_INTEGER, AMF3_DOUBLE, AMF3_STRING, AMF3_XML_DOC, AMF3_DATE,
        AMF3_ARRAY, AMF3_OBJECT, AMF3_XML, AMF3_BYTE_ARRAY
    };

    AmfReader(QIODevice* buffer, AmfExternalizableObjectMap* extMap);

    QVariant readNext();
    QVariant readAmf3Next();

    quint8 readByte();

    // AMF0
    double readNumber();
    bool readBool();
    QString readString();
    QVariant readAnonymousObject();

    // AMF3
    qint32 readAmf3Int();
    double readAmf3Double();
    QString readAmf3String();
    QDateTime readAmf3Date();
    QVariant readAmf3Array();
    QVariant readAmf3Object();
    QByteArray readAmfByteArray();

    void dump();

private:
    QString readUtf8(quint32 size);

    void addStringRef(const QString& str);
    QString readStringRef(int handle);

    void addObjectRef(const QVariant& obj);

    template <class T = QVariant>
    T readObjectRef(int handle)
    {
        return objects.at(handle).value<T>();
    }

    AmfClassDef* addClassDefRef(const QString& typeName);
    const AmfClassDef* readClassDefRef(int handle);

    QList<QString> strings;
    QList<QVariant> objects;
    QList<AmfClassDef> classes;
    QIODevice* buff;
    AmfExternalizableObjectMap* extObjMap;
};

#endif // AMFREADER_H
