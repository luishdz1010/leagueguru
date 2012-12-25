#ifndef CHAMPIONFILTERMODEL_H
#define CHAMPIONFILTERMODEL_H

#include <QSortFilterProxyModel>
#include <QVector>


class ChampionFilterModel{
public:
    virtual ~ChampionFilterModel(){}

    virtual void filterByRole(int role) = 0;
    virtual void filterByName(QString name) = 0;
};


class SingleChampionFilterModel : public QSortFilterProxyModel, public ChampionFilterModel
{
    Q_OBJECT
public:
    SingleChampionFilterModel(QObject* parent = 0) :
        QSortFilterProxyModel(parent)
    {}

    SingleChampionFilterModel(int championIdRole, QObject* parent = 0);

    Q_INVOKABLE void filterByRole(int role);
    Q_INVOKABLE void filterByName(QString name);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

private:
    int modelChampionIdRole;
    int championRoleQuery;
};


class MultipleChampionFilterModel : public QObject, public ChampionFilterModel
{
    Q_OBJECT
public:
     MultipleChampionFilterModel(QObject* parent = 0) :
         QObject(parent)
     {}

     Q_INVOKABLE void filterByRole(int role)
     {
         foreach(ChampionFilterModel* m, models)
            m->filterByRole(role);
     }

     Q_INVOKABLE void filterByName(QString name)
     {
         foreach(ChampionFilterModel* m, models)
            m->filterByName(name);
     }

     void addModel(ChampionFilterModel* m)
     {
         models.append(m);
     }

private:
    QVector<ChampionFilterModel*> models;
};

Q_DECLARE_METATYPE(MultipleChampionFilterModel*)

#endif // CHAMPIONFILTERMODEL_H
