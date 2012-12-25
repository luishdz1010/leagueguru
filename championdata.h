#ifndef CHAMPIONDATA_H
#define CHAMPIONDATA_H

#include <QDeclarativeImageProvider>
#include <QVector>
#include <QHash>
#include <QUrl>

struct ChampionData{
    QVector<int> roles;
    QString name;
    int id;
};


class ChampionDataProvider{
public:
    static ChampionDataProvider* instance()
    {
        static ChampionDataProvider d;
        return &d;
    }

    ~ChampionDataProvider()
    {
        qDeleteAll(championMap.values());
    }

    bool addFromFile(QString filepath);

    ChampionData* getChampionData(int id)
    {
        auto c = championMap.find(id);
        return c != championMap.end()? *c : getDefaultChampionData();
    }

    ChampionData* getDefaultChampionData()
    {
        return &defaultChampion;
    }

    static QString championDebugString(int championId)
    {
        return "[" + instance()->getChampionData(championId)->name + ", " + QString::number(championId) + "]";
    }

private:
    ChampionDataProvider() :
        defaultChampion({{}, {"Unknown"}, 0})
    {}

    ChampionData defaultChampion;
    QHash<int, ChampionData*> championMap;
};


class DeclarativeChampion : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int championId READ getId WRITE setId NOTIFY championIdChanged)
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged)
    Q_PROPERTY(QUrl imageSource READ getImageSource NOTIFY imageSourceChanged)
public:
    DeclarativeChampion()
    {
        d = ChampionDataProvider::instance()->getDefaultChampionData();
    }

    DeclarativeChampion(int id)
    {
        d = ChampionDataProvider::instance()->getChampionData(id);
    }

    void setId(int id)
    {
        if(id == d->id)
            return;

        d = ChampionDataProvider::instance()->getChampionData(id);
        emit championIdChanged();
        emit nameChanged();
        emit imageSourceChanged();
    }

    int getId() const
    {
        return d->id;
    }

    const QString& getName() const
    {
        return d->name;
    }

    const QVector<int>& getRoles() const
    {
        return d->roles;
    }

    QUrl getImageSource() const
    {
        return "image://champions/" + QString::number(d->id);
    }

signals:
    void championIdChanged();
    void nameChanged();
    void imageSourceChanged();
    
private:
    DeclarativeChampion(ChampionData* d_) :
        d(d_)
    {}

    ChampionData* d;
};

class ChampionImageProvider : public QDeclarativeImageProvider{
public:
    ChampionImageProvider();

    QImage requestImage(const QString &idStr, QSize *size, const QSize &requestedSize);

    struct ChampionImage{
        int id;
        QSize size;

        bool operator ==(const ChampionImage& o) const
        {
            return id == o.id && size == o.size;
        }
    };

private:
    QImage invalidImage;
    QHash<ChampionImage, QImage> imgCache;
};

inline uint qHash(const ChampionImageProvider::ChampionImage& cimg)
{
    return (((cimg.id * 33) ^ cimg.size.width()) * 17) ^ cimg.size.width();
}

#endif // CHAMPIONDATA_H
