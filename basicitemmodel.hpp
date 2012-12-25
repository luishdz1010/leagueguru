#ifndef BASICITEMMODEL_H
#define BASICITEMMODEL_H

#include <QAbstractListModel>
#include <QMap>
#include <QVariant>
#include <initializer_list>

class BasicItemMoc : public QObject{
    Q_OBJECT
public:
    explicit BasicItemMoc(QObject* parent = 0) :
        QObject(parent)
    {}

signals:
    void dataChanged();
};

template <class Field>
class BasicItem : public BasicItemMoc{
public:
    typedef std::initializer_list<QPair<Field, QVariant> > InitList;
    typedef Field FieldType;

    BasicItem(){}

    BasicItem(InitList init)
    {
        for(auto it = init.begin(); it != init.end(); ++it)
            values[(int)it->first] = it->second;
    }

    void setData(Field field, const QVariant& value)
    {
        auto& v = values[static_cast<int>(field)];
        if(v != value){
            v = value;
            emit dataChanged();
        }
    }

    QVariant data(Field field) const
    {
        return values.value(static_cast<int>(field));
    }

private:
    QMap<int, QVariant> values;
};


class BasicItemModelMoc : public QAbstractListModel{
    Q_OBJECT
public:
    explicit BasicItemModelMoc(QObject* parent) :
        QAbstractListModel(parent)
    {}

protected slots:
    virtual void itemDataChanged() = 0;
};

// Takes ownership of all the items
template <class Item>
class BasicItemModel : public BasicItemModelMoc
{
public:
    typedef typename Item::FieldType FieldType;

    explicit BasicItemModel(QObject *parent = 0) :
        BasicItemModelMoc(parent)
    {}

    ~BasicItemModel()
    {
        qDeleteAll(items);
    }

    int size() const
    {
        return items.size();
    }

    bool isEmpty()
    {
        return items.isEmpty();
    }

    const Item* at(int i) const
    {
        return items.at(i);
    }

    int indexOf(Item* item)
    {
        return items.indexOf(item);
    }

    void append(Item* item)
    {
        insert(size(), item);
    }

    void append(const QList<Item*>& items_)
    {
        beginInsertRows(QModelIndex(), size(), size() + items_.size());

        internalAppend(items_);

        endInsertRows();
    }
    
    void insert(int i, Item* value)
    {
        beginInsertRows(QModelIndex(), i, i);

        items.insert(i, value);
        connect(items[i], SIGNAL(dataChanged()), this, SLOT(itemDataChanged()));

        endInsertRows();
    }

    void removeAt(int i)
    {
        beginRemoveRows(QModelIndex(), i, i);

        items.takeAt(i)->deleteLater();

        endRemoveRows();
    }

    void clear()
    {
        beginResetModel();

        qDeleteAll(items);
        items.clear();

        endResetModel();
    }

    void reset(QList<Item*>& newItems)
    {
        beginResetModel();

        qDeleteAll(items);
        items.clear();
        internalAppend(newItems);

        endResetModel();
    }

    Item* operator[](int i)
    {
        Q_ASSERT(at(i));
        return items[i];
    }

    // QAbstractItemModel
    int rowCount(const QModelIndex& = QModelIndex()) const
    {
        return size();
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        if(index.row() < 0 || index.row() > size())
            return QVariant();

        return items[index.row()]->data(static_cast<FieldType>(role));
    }

    QVariant data(const QModelIndex &index, FieldType role) const
    {
        return data(index, (int)role);
    }

protected:
    void itemDataChanged()
    {
        auto i = index(indexOf(static_cast<Item*>(sender())));
        emit dataChanged(i, i);
    }

    void internalAppend(const QList<Item*>& items_)
    {
        items.append(items_);
        for(int i = size() - items_.size(); i < size(); ++i)
            connect(items[i], SIGNAL(dataChanged()), this, SLOT(itemDataChanged()));
    }

private:
    QList<Item*> items;
};

#endif // BASICITEMMODEL_H
