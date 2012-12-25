#include "qmlkeynavigationfix.h"
#include <QKeyEvent>
#include <QApplication>
#include "enums.h"

QmlKeyNavigationFix::QmlKeyNavigationFix(QObject *parent) :
    QObject(parent)
{
}

bool QmlKeyNavigationFix::eventFilter(QObject* qml, QEvent* event)
{
    if(event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        QKeyEvent* newEvent = 0;

        if(keyEvent->key() == Qt::Key_Tab){
            if(keyEvent->modifiers() & Qt::ControlModifier)
                newEvent = new QKeyEvent(QEvent::KeyPress, Enums::ControlTabKey, Qt::NoModifier);
        } else if(keyEvent->key() == Qt::Key_Backtab){
            if(keyEvent->modifiers() & Qt::ControlModifier)
                newEvent = new QKeyEvent(QEvent::KeyPress, Enums::ControlShiftTabKey, Qt::NoModifier);
        }

        if(newEvent){
            QApplication::postEvent(qml, newEvent);
            return true;
        }
    }

    return false;
}
