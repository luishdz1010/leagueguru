#include "clientemulatorwindow.h"
#include <QDebug>
#include <cstdlib>

namespace {
//QPair<QString, int> ids[] = { {"MeixcanMid", 25812566}, {"Feitank", 28771657}, {"KemzVall", 28835761},
 //                             {"Destroumble", 31411374}, {"LoanNova" ,28937588}/*, {"Random #2" ,23421}, {"Random #2" ,7460},
   //                         {"Random #2" ,5908}, {"Random #2" ,20044486}, {"Random #2" ,407750}*/};

QPair<QString, int> ids[] = { {"Dyrus", 5908}, {"TheOddOne", 60783}, {"ReginaId", 17772},
                            {"Chaox", 7460}, {"Xpecial", 19199530}};
}


ClientEmulatorWindow::~ClientEmulatorWindow()
{
    delete ui;
}


void ClientEmulatorWindow::on_createMatchup_clicked()
{
    InspectedMatch match;

    match.gameMode = "CLASSIC";
    match.gameType = "RANKED_GAME";
    match.maxNumPlayers = 10;
    match.firstMove = true;
    match.selfTeamId = 1;

    for(uint i = 0; i < 5; ++i){
        InspectedMatchParticipant p;
        p.summonerId = ids[i].second;
        p.summonerName = ids[i].first;
        match.selfTeam.append(p);
    }

    cont->onMatchupBeingCreated(match);
    cont->onMatchupCreated(match);


}


void ClientEmulatorWindow::on_setEnemyRoster_clicked()
{
    InspectedEnemyRoster r;
    for(uint i = 0; i < 250; ++i)
        r.championIds.append(i);

    cont->onEnemyRosterReceived(r);
}

void ClientEmulatorWindow::on_startsPickingButton_clicked()
{
    for(uint i = 0; i < 2; ++i)
        cont->onPlayerStartsPicking(i);
}

void ClientEmulatorWindow::on_randomPickButtom_clicked()
{
    for(uint i = 0; i < 5; ++i)
        cont->onPlayerChampionPicked(i, champs[i]= rand() % 100);
}

void ClientEmulatorWindow::on_lockInNextButton_clicked()
{
    cont->onPlayerLockedIn(lockInPos, champs[lockInPos]);
    ++lockInPos;
}

void ClientEmulatorWindow::on_pushButton_clicked()
{
    cont->onMatchupDisbanded();
}

void ClientEmulatorWindow::on_lockEnemiesButton_clicked()
{
    cont->onPlayerLockedIn(5, 122);
    cont->onPlayerLockedIn(6, 55);
    cont->onPlayerLockedIn(7, 32);
    cont->onPlayerLockedIn(8, 21);
    cont->onPlayerLockedIn(9, 22);
}
