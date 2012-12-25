#ifndef SUMMONERSTATSPROVIDER_H
#define SUMMONERSTATSPROVIDER_H

#include <QWebPage>
#include <QQueue>
#include <QMap>
#include <QWebElementCollection>
#include <QDebug>
#include "summonerstats.h"
#include "enums.h"



/// Base class for every provider.
/// At the moment we take our stats from 3rd party websites, this may change in the future
class SummonerStatsProvider : public QObject
{
    Q_OBJECT
public:
    SummonerStatsProvider(QObject* parent = 0) :
        QObject(parent)
    {}

    virtual ~SummonerStatsProvider(){}

    virtual void lookupSummonerStats(Enums::ServerRegion region, int summonerId) = 0;

signals:
    void lookupSucceed(int summonerId, SummonerStats stats);
    void lookupFailed(int summonerId);
};


class LolKingSummonerStatsProvider : public SummonerStatsProvider{
    Q_OBJECT
public:
    struct LookupState{
        int summonerId;
        int retry;
    };

    LolKingSummonerStatsProvider(QObject* parent = 0);

    ~LolKingSummonerStatsProvider();

    void lookupSummonerStats(Enums::ServerRegion region, int summonerId);

private slots:
    void profileLoaded(bool ok);
    void retryLookup();

private:
    void addWebPage();
    void triggerError();

    bool getSesonStats(QWebElementCollection statsEl, QHash<int, SummonerChampionStats>& stats);
    QString getStatTdInt(QWebElement e, int* i);
    QString getStatTdFloat(QWebElement e, float* i);
    void clearLookup(QWebPage* wp);


    QHash<QWebPage*, LookupState> activeLookups;
    QMap<qint64, QWebPage*> retryQueue;
    QQueue<QWebPage*> webPageCache;
};

inline QDebug& operator<<(QDebug& dbg, const LolKingSummonerStatsProvider::LookupState& s)
{
    dbg.nospace() << "[summonerId:" << s.summonerId << ", retry:" << s.retry << ']';
    return dbg;
}

#endif // SUMMONERSTATSPROVIDER_H
