#ifndef PARTICIPANTSUGGESTIONSMODEL_H
#define PARTICIPANTSUGGESTIONSMODEL_H

#include "basicitemmodel.hpp"

class ChampionMatchupDetails : public QObject{
    Q_OBJECT
    Q_PROPERTY(int championId READ getChampionId CONSTANT)
    Q_PROPERTY(qreal percentPositive READ getPercentPositive CONSTANT)
public:
    ChampionMatchupDetails(int champId, qreal pPositive, QObject* parent) :
        QObject(parent),
        championId(champId),
        percentPositive(pPositive)
    {}

    int getChampionId()
    {
        return championId;
    }

    qreal getPercentPositive()
    {
        return percentPositive;
    }

private:
    int championId;
    qreal percentPositive;
};

Q_DECLARE_METATYPE(QList<ChampionMatchupDetails*>)

enum class ParticipantSuggestionsData{
    ChampionId = Qt::UserRole + 1,
    SuggestedRole,
    StrongAgainst,
    BadAgainst,
    GoodWith
};

class ParticipantSuggestionsItem : public BasicItem<ParticipantSuggestionsData>{
public:
    ParticipantSuggestionsItem(){}

    ParticipantSuggestionsItem(InitList init) :
        BasicItem(init)
    {}
};

class ParticipantSuggestionsModel : public BasicItemModel<ParticipantSuggestionsItem>
{
public:
    explicit ParticipantSuggestionsModel(QObject *parent = 0) :
        BasicItemModel(parent)
    {
        QHash<int, QByteArray> r;
        r[(int)ParticipantSuggestionsData::ChampionId] = "championId";
        r[(int)ParticipantSuggestionsData::SuggestedRole] = "suggestedRole";
        r[(int)ParticipantSuggestionsData::StrongAgainst] = "strongAgainst";
        r[(int)ParticipantSuggestionsData::BadAgainst] = "badAgainst";
        r[(int)ParticipantSuggestionsData::GoodWith] = "goodWith";
        setRoleNames(r);
    }
};

Q_DECLARE_METATYPE(ParticipantSuggestionsModel*)

#endif // PARTICIPANTSUGGESTIONSMODEL_H
