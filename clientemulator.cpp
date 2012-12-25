#include "clientemulator.h"

namespace {
const int ids[] = {18990650, 21095888, 25812566, 20030831, 20819969};
}

void ClientEmulator::start()
{
    InspectedMatch match;

    match.gameMode = "CLASSIC";
    match.gameType = "RANKED_GAME";
    match.maxNumPlayers = 10;
    match.firstMove = true;
    match.selfTeamId = 1;

    for(int i = 0; i < 5; ++i){
        InspectedMatchParticipant p;
        p.summonerId = ids[i];
        p.summonerName = "Wey #" + QString::number(i+1);
        match.selfTeam.append(p);
    }

    cont->onMatchupBeingCreated(match);
    cont->onMatchupCreated(match);

    InspectedEnemyRoster r;
    for(int i = 1; i < 106; ++i)
        r.championIds.append(i);

    cont->onEnemyRosterReceived(r);
}
