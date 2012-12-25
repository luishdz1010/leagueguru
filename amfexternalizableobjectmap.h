#ifndef AMFOBJECTASSOCIATIONDIRECTORY_H
#define AMFOBJECTASSOCIATIONDIRECTORY_H

#include <functional>
#include <memory>
#include <QHash>
#include <QMetaType>
#include <QStringBuilder>

class AmfReader;

class AmfExternalizableObject{
public:
    virtual ~AmfExternalizableObject(){}

    virtual void read(AmfReader*) = 0;
    //virtual void write(AmfWritter*);

    virtual QString dump(int level) = 0;
};

typedef std::shared_ptr<AmfExternalizableObject> AmfExternalizableObjectPtr;

Q_DECLARE_METATYPE(AmfExternalizableObjectPtr)

typedef std::function<AmfExternalizableObjectPtr()> AmfExternalizableObjectConstructor;

/*! Serves as a directory for the AFMReader to decode Externalizable objects
  Most objects on this class just eat as much data as they can so we can get our primary
  targets (champion/game stats)
*/
class AmfExternalizableObjectMap : public QHash<QString, AmfExternalizableObjectConstructor> {};

// Standard ext objs follow
class AmfExtArrayCollection : public AmfExternalizableObject, public QList<QVariant>{
public:
    void read(AmfReader* stream);
    QString dump(int level);

};

typedef std::shared_ptr<AmfExtArrayCollection> AmfArrayCollectionPtr;

#endif // AMFOBJECTASSOCIATIONDIRECTORY_H
