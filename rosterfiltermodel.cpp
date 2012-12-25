#include "rosterfiltermodel.h"
#include <QDebug>

RosterFilterModel::RosterFilterModel(QObject *parent) :
    SingleChampionFilterModel((int)ParticipantRosterData::ChampionId, parent),
    sortColumn(ParticipantRosterData::ChampionId)
{
}

ParticipantRosterModel* RosterFilterModel::getRosterModel() const
{
    return static_cast<ParticipantRosterModel*>(sourceModel());
}

int RosterFilterModel::championIndex(int championId)
{
    for(int i = 0; i < rowCount(); ++i)
        if(data(index(i, 0), (int)ParticipantRosterData::ChampionId) == championId)
            return i;

    return -1;
}

QObject* RosterFilterModel::getChampionStats(int championId)
{
    auto sm = getRosterModel();
    for(int i = 0; i < sm->rowCount(); ++i){
        if(sm->at(i)->data(ParticipantRosterData::ChampionId) == championId)
            return new ParticipantChampionStats(sm->at(i));
    }

    return new ParticipantChampionStats();
}

void RosterFilterModel::filterByRole(int role)
{
    SingleChampionFilterModel::filterByRole(role);
    SingleChampionFilterModel::sort(0, sortOrder);
}

void RosterFilterModel::filterByName(QString name)
{
    SingleChampionFilterModel::filterByName(name);
    SingleChampionFilterModel::sort(0, sortOrder);
}

void RosterFilterModel::sort(int column, const QString &order)
{
    this->sortColumn = (ParticipantRosterData) ((int)ParticipantRosterData::ChampionId + column);
    sortOrder = order == "up"? Qt::AscendingOrder : Qt::DescendingOrder;
    SingleChampionFilterModel::sort(0, sortOrder);
}

bool RosterFilterModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if(sortColumn == ParticipantRosterData::ChampionId)
        return SingleChampionFilterModel::lessThan(left, right); // sort by champion name

    return getRosterModel()->data(left, sortColumn).toFloat() < getRosterModel()->data(right, sortColumn).toFloat();
}
