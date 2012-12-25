#ifndef MATCHUPPARTICIPANTMODEL_HPP
#define MATCHUPPARTICIPANTMODEL_HPP

#include "basicitemmodel.hpp"

enum class MatchupParticipantData{
    SummonerName = Qt::UserRole + 1,
    SummonerId,
    Ranking,
    ChampionId,
    PickState,
    SuggestionsModel,
    S2RosterModel,
    S3RosterModel,
    FilterModel,
    ParticipantIndex,
    SelfSummoner
};

class MatchupParticipantItem : public BasicItem<MatchupParticipantData>{
public:
    MatchupParticipantItem(){}

    MatchupParticipantItem(InitList init) :
        BasicItem(init)
    {}
};

class MatchupParticipantModel : public BasicItemModel<MatchupParticipantItem>
{
public:
    explicit MatchupParticipantModel(QObject *parent = 0) :
        BasicItemModel(parent)
    {
        QHash<int, QByteArray> r;
        r[(int)MatchupParticipantData::SummonerName] = "summonerName";
        r[(int)MatchupParticipantData::Ranking] = "ranking";
        r[(int)MatchupParticipantData::ChampionId] = "championId";
        r[(int)MatchupParticipantData::PickState] = "pickState";
        r[(int)MatchupParticipantData::ParticipantIndex] = "participantIndex";
        r[(int)MatchupParticipantData::SuggestionsModel] = "suggestionsModel";
        r[(int)MatchupParticipantData::S2RosterModel] = "s2RosterModel";
        r[(int)MatchupParticipantData::S3RosterModel] = "s3RosterModel";
        r[(int)MatchupParticipantData::FilterModel] = "filterModel";
        r[(int)MatchupParticipantData::SelfSummoner] = "selfSummoner";
        setRoleNames(r);
    }
};

#endif // MATCHUPPARTICIPANTMODEL_HPP
