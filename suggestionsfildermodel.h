#ifndef SUGGESTIONSFILDERMODEL_H
#define SUGGESTIONSFILDERMODEL_H

#include "championfiltermodel.h"
#include "participantsuggestionsmodel.h"
#include <QDebug>

class SuggestionsFilderModel : public SingleChampionFilterModel
{
    Q_OBJECT
public:
    explicit SuggestionsFilderModel(QObject *parent = 0);

    ParticipantSuggestionsModel* getSuggestionsModel();

    Q_INVOKABLE int championIndex(int championId);
    
    Q_INVOKABLE QList<QObject*> getStrongVs(int championId);
    Q_INVOKABLE QList<QObject*> getWeakVs(int championId);
    Q_INVOKABLE QList<QObject*> getGoodWith(int championId);

private:
    template <ParticipantSuggestionsData Stat>
    QList<QObject*> get(int championId)
    {
        for(int i = 0; i < getSuggestionsModel()->size(); ++i)
            if(getSuggestionsModel()->at(i)->data(ParticipantSuggestionsData::ChampionId) == championId)
                return getSuggestionsModel()->at(i)->data(Stat).value<QList<QObject*> >();

        return QList<QObject*>();
    }
};

Q_DECLARE_METATYPE(SuggestionsFilderModel*)

#endif // SUGGESTIONSFILDERMODEL_H
