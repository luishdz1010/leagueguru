#ifndef CLIENTEMULATOR_H
#define CLIENTEMULATOR_H

#include <QObject>
#include "championselectcontroller.h"

class ClientEmulator : public QObject
{
    Q_OBJECT
public:
    explicit ClientEmulator(ChampionSelectController* c) : cont(c){}
    
    void start();

signals:
    
public slots:

private:
    ChampionSelectController* cont;

};

#endif // CLIENTEMULATOR_H
