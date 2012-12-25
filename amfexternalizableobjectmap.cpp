#include "amfexternalizableobjectmap.h"
#include "amfreader.h"

void AmfExtArrayCollection::read(AmfReader* stream)
{
    // TODO can this crash?
    append(*(stream->readAmf3Next().value<AmfArrayPtr>().get()));
}

QString AmfExtArrayCollection::dump(int level)
{
    QString s;
    s += "(flash.ArrayCollection)\n";
    int i = 0;
    ++level;
    foreach(const QVariant& v, *this)
        s += QString(level, '\t') % '[' % QString::number(i++) % "]: " % debugAmf(v, level) % "\n";
    return s;
}
