#ifndef SUGGESTIONMODELPICKFILTER_H
#define SUGGESTIONMODELPICKFILTER_H

#include <QSortFilterProxyModel>

/// Used in QML for splitting counter picks/overall picks
class SuggestionModelPickFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString filter READ filter WRITE setFilter)
    Q_PROPERTY(QAbstractItemModel* sourceModel READ sourceModel WRITE setSourceModel)
public:
    explicit SuggestionModelPickFilter(QObject *parent = 0);
    
    const QString& filter();
    void setFilter(const QString& str);

    Q_INVOKABLE int championIndex(int championId);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    enum FilterMode{
        CounterPicks,
        OverallPicks
    };

    FilterMode filterMode;
};

#endif // SUGGESTIONMODELPICKFILTER_H
