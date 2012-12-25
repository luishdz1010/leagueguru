#ifndef SUMMONERSTATS_H
#define SUMMONERSTATS_H

#include <QHash>

struct SummonerChampionStats{
    int wins = 0;
    int loses = 0;
    float kills = 0;
    float deaths = 0;
    float assists = 0;
};

struct SummonerStats{
    int solo5Rating = -1;
    int solo5TopRating = -1;
    QHash<int, SummonerChampionStats> s2ChampionStats;
    QHash<int, SummonerChampionStats> s3ChampionStats;
};

#endif // SUMMONERSTATS_H
