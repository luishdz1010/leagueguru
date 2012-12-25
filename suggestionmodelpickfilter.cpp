#include "suggestionmodelpickfilter.h"
#include <QDeclarativeContext>
#include "participantsuggestionsmodel.h"

SuggestionModelPickFilter::SuggestionModelPickFilter(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

const QString& SuggestionModelPickFilter::filter()
{
    static QString s[] = {"counter", "overall}"};
    return filterMode == CounterPicks? s[0] : s[1];
}

void SuggestionModelPickFilter::setFilter(const QString& str)
{
    filterMode = str == "counter"? CounterPicks : OverallPicks;
}

int SuggestionModelPickFilter::championIndex(int championId)
{
    for(int i = 0; i < rowCount(); ++i)
        if(data(index(i, 0), (int)ParticipantSuggestionsData::ChampionId) == championId)
            return i;

    return -1;
}

bool SuggestionModelPickFilter::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
    auto v = sourceModel()->data(sourceModel()->index(source_row, 0, source_parent),
                                 (int)ParticipantSuggestionsData::StrongAgainst).value<QList<QObject*> >();

    return filterMode == CounterPicks? !v.isEmpty() : v.isEmpty();
}

