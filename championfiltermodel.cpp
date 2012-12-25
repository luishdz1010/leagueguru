#include "championfiltermodel.h"
#include "championdata.h"

SingleChampionFilterModel::SingleChampionFilterModel(int championIdRole, QObject *parent) :
    QSortFilterProxyModel(parent),
    modelChampionIdRole(championIdRole)
{
}

void SingleChampionFilterModel::filterByRole(int role)
{
    championRoleQuery = role;
    setFilterRegExp("[");
}

void SingleChampionFilterModel::filterByName(QString name)
{
    setFilterRegExp(QRegExp(name, Qt::CaseInsensitive, QRegExp::FixedString));
}

bool SingleChampionFilterModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
    if(!filterRegExp().isValid()){ // by role
        if(championRoleQuery == 0)
            return true;

        bool ok;
        int cId = sourceModel()->data(sourceModel()->index(source_row, 0, source_parent), modelChampionIdRole).toInt(&ok);
        Q_ASSERT(ok);
        return ChampionDataProvider::instance()->getChampionData(cId)->roles.indexOf(championRoleQuery) != -1;

    } else { // by name
        bool ok;
        int cId = sourceModel()->data(sourceModel()->index(source_row, 0, source_parent), modelChampionIdRole).toInt(&ok);
        Q_ASSERT(ok);
        return ChampionDataProvider::instance()->getChampionData(cId)->name.contains(filterRegExp());
    }
}

bool SingleChampionFilterModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    return ChampionDataProvider::instance()->getChampionData(sourceModel()->data(left, modelChampionIdRole).toInt())->name <
            ChampionDataProvider::instance()->getChampionData(sourceModel()->data(right, modelChampionIdRole).toInt())->name;
}
