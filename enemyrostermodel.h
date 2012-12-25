#ifndef ENEMYROSTERMODEL_H
#define ENEMYROSTERMODEL_H

#include "basicitemmodel.hpp"

enum class EnemyRosterData{
    ChampionId = Qt::UserRole + 1
};

class EnemyRosterItem : public BasicItem<EnemyRosterData>
{
public:
    EnemyRosterItem(){}

    EnemyRosterItem(InitList init) :
        BasicItem(init)
    {}
};

class EnemyRosterModel : public BasicItemModel<EnemyRosterItem>
{
    Q_OBJECT
public:
    explicit EnemyRosterModel(QObject *parent = 0) :
        BasicItemModel(parent)
    {
        QHash<int, QByteArray> r;
        r[(int)EnemyRosterData::ChampionId] = "championId";
        setRoleNames(r);
    }
};

#endif // ENEMYROSTERMODEL_H
