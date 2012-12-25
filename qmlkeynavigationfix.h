#ifndef QMLKEYNAVIGATIONFIX_H
#define QMLKEYNAVIGATIONFIX_H

#include <QObject>

/// This class is needed in order to fix a few issues with the way Tab and Back_Tac are recognized by qml's KeyNavigation
class QmlKeyNavigationFix : public QObject
{
    Q_OBJECT
public:
    explicit QmlKeyNavigationFix(QObject *parent = 0);
    
    bool eventFilter(QObject* qml, QEvent* event);
};

#endif // QMLKEYNAVIGATIONFIX_H
