#ifndef PARTICIPANTROSTERMODEL_HPP
#define PARTICIPANTROSTERMODEL_HPP

#include "basicitemmodel.hpp"

enum class ParticipantRosterData{
    ChampionId = Qt::UserRole + 1,
    Wins,
    Loses,
    Winrate,
    Kills,
    Deaths,
    Assists,
    Minions
};

class ParticipantRosterItem : public BasicItem<ParticipantRosterData>{
public:
    ParticipantRosterItem(){}

    ParticipantRosterItem(InitList init) :
        BasicItem(init)
    {}
};

class ParticipantRosterModel : public BasicItemModel<ParticipantRosterItem>
{
public:
    explicit ParticipantRosterModel(QObject *parent = 0) :
        BasicItemModel(parent)
    {
        QHash<int, QByteArray> r;
        r[(int)ParticipantRosterData::ChampionId] = "championId";
        r[(int)ParticipantRosterData::Wins] = "wins";
        r[(int)ParticipantRosterData::Loses] = "loses";
        r[(int)ParticipantRosterData::Winrate] = "winrate";
        r[(int)ParticipantRosterData::Kills] = "kills";
        r[(int)ParticipantRosterData::Deaths] = "deaths";
        r[(int)ParticipantRosterData::Assists] = "assists";
        setRoleNames(r);
    }
};


#endif // PARTICIPANTROSTERMODEL_HPP
