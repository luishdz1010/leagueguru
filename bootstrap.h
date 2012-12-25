#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H

#include "championselectcontroller.h"
#include "dataupdater.h"
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QProcess>

class Bootstrap : public QObject
{
    Q_OBJECT
public:
    Bootstrap();
    
    void startUpdater();

private slots:
    void onUpdateError(DataUpdater::ErrorType);
    void startApplication();

private:
    QDeclarativeEngine engine;
    ChampionSelectController controller;
    QDeclarativeComponent component;
    QProcess localServer;
};

#endif // BOOTSTRAP_H
