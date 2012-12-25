#include "debugamf.h"
#include "amfreader.h"
#include "amfexternalizableobjectmap.h"
#include <QMetaType>

QString debugAmf(QVariant v, int level){
    QString s;
    auto t = v.userType();

    if(t == qMetaTypeId<AmfObjectPtr>())
        return v.value<AmfObjectPtr>()->dump(level);
    else if(t == qMetaTypeId<AmfExternalizableObjectPtr>())
        return v.value<AmfExternalizableObjectPtr>()->dump(level);
    else if(t == qMetaTypeId<AmfMapPtr>()){
        s += "(dictionary)\n";
        ++level;
        foreach(const QString& prop, v.value<AmfMapPtr>()->keys())
            s += QString(level, '\t') % prop % debugAmf(v.value<AmfMapPtr>()->value(prop), level) % '\n';

    } else if(t == qMetaTypeId<AmfArrayPtr>()) {
        s += "(array)\n";
        ++level;
        int i = 0;
        foreach(const QVariant& v, *v.value<AmfArrayPtr>())
            s += QString(level, '\t') + '[' + i++ + "]: " + debugAmf(v, level) + '\n';
    } else
        s += "(" + QString(v.typeName()) + ") " + v.toString();

    return s;
}
