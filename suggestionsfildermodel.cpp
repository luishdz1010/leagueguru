#include "suggestionsfildermodel.h"
#include <QDeclarativeContext>

SuggestionsFilderModel::SuggestionsFilderModel(QObject *parent) :
    SingleChampionFilterModel((int)ParticipantSuggestionsData::ChampionId, parent)
{
}

ParticipantSuggestionsModel* SuggestionsFilderModel::getSuggestionsModel()
{
    return static_cast<ParticipantSuggestionsModel*>(sourceModel());
}

int SuggestionsFilderModel::championIndex(int championId)
{
    for(int i = 0; i < rowCount(); ++i)
        if(data(index(i, 0), (int)ParticipantSuggestionsData::ChampionId) == championId)
            return i;

    return -1;
}

QList<QObject*> SuggestionsFilderModel::getStrongVs(int championId)
{
    return get<ParticipantSuggestionsData::StrongAgainst>(championId);
}

QList<QObject*> SuggestionsFilderModel::getWeakVs(int championId)
{
     return get<ParticipantSuggestionsData::BadAgainst>(championId);
}

QList<QObject*> SuggestionsFilderModel::getGoodWith(int championId)
{
    return get<ParticipantSuggestionsData::GoodWith>(championId);
}
