#ifndef CLIENTEMULATORWINDOW_H
#define CLIENTEMULATORWINDOW_H

#include <QMainWindow>
#include "championselectcontroller.h"
#include "ui_clientemulatorwindow.h"

namespace Ui {
class ClientEmulatorWindow;
}

class ClientEmulatorWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    ~ClientEmulatorWindow();

    explicit ClientEmulatorWindow(ChampionSelectController* c) :
        ui(new Ui::ClientEmulatorWindow),
        cont(c)
    {
        ui->setupUi(this);
    }


private slots:
    void on_createMatchup_clicked();

    void on_setEnemyRoster_clicked();

    void on_startsPickingButton_clicked();

    void on_randomPickButtom_clicked();

    void on_lockInNextButton_clicked();

    void on_pushButton_clicked();

    void on_lockEnemiesButton_clicked();

private:
    Ui::ClientEmulatorWindow *ui;
    ChampionSelectController* cont;
    int lockInPos = 0;
    int champs[5];
};

#endif // CLIENTEMULATORWINDOW_H
