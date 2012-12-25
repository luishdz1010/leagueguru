#ifndef ROSTERFILTERMODEL_H
#define ROSTERFILTERMODEL_H

#include "championfiltermodel.h"
#include "participantrostermodel.hpp"

class ParticipantChampionStats : public QObject{
    Q_OBJECT
    Q_PROPERTY(int wins READ wins)
    Q_PROPERTY(int loses READ loses)
    Q_PROPERTY(qreal kills READ kills)
    Q_PROPERTY(qreal deaths READ deaths)
    Q_PROPERTY(qreal assists READ assists)
public:
    ParticipantChampionStats()
    {}

    ParticipantChampionStats(const ParticipantRosterItem* it) :
        w(it->data(ParticipantRosterData::Wins).toInt()),
        l(it->data(ParticipantRosterData::Loses).toInt()),
        k(it->data(ParticipantRosterData::Kills).toReal()),
        d(it->data(ParticipantRosterData::Deaths).toReal()),
        a(it->data(ParticipantRosterData::Assists).toReal())
    {}

    int wins(){ return w; }
    int loses(){ return l; }
    qreal kills(){ return k; }
    qreal deaths(){ return d; }
    qreal assists(){ return a; }

private:
    int w = -1;
    int l = -1;
    qreal k = -1;
    qreal d = -1;
    qreal a = -1;
};

class RosterFilterModel : public SingleChampionFilterModel
{
    Q_OBJECT
public:
    using SingleChampionFilterModel::sort;

    explicit RosterFilterModel(QObject *parent = 0);

    ParticipantRosterModel* getRosterModel() const;

    Q_INVOKABLE int championIndex(int championId);
    Q_INVOKABLE QObject* getChampionStats(int championId);

    Q_INVOKABLE void filterByRole(int role);
    Q_INVOKABLE void filterByName(QString name);

    Q_INVOKABLE void sort(int sortColumn, const QString& order);

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    ParticipantRosterData sortColumn;
    Qt::SortOrder sortOrder;
};

Q_DECLARE_METATYPE(RosterFilterModel*)

#endif // ROSTERFILTERMODEL_H
