#include "summonerstatsprovider.h"
#include <QWebFrame>
#include <QWebElement>
#include <QWebHistory>
#include <QTimer>
#include "qslog/QsLog.h"

LolKingSummonerStatsProvider::LolKingSummonerStatsProvider(QObject *parent) :
    SummonerStatsProvider(parent)
{
    for(int i = 0; i < 5; ++i)
        addWebPage();
}

LolKingSummonerStatsProvider::~LolKingSummonerStatsProvider()
{
    qDeleteAll(webPageCache);
}

void LolKingSummonerStatsProvider::addWebPage()
{
    auto profile = new QWebPage();

    connect(profile, SIGNAL(loadFinished(bool)), this, SLOT(profileLoaded(bool)));

    profile->history()->setMaximumItemCount(0);
    profile->settings()->setAttribute(QWebSettings::AutoLoadImages, false);
    profile->settings()->setAttribute(QWebSettings::JavascriptEnabled, false);
    profile->settings()->setAttribute(QWebSettings::PrivateBrowsingEnabled, true);

    webPageCache.enqueue(profile);
}

void LolKingSummonerStatsProvider::lookupSummonerStats(Enums::ServerRegion region, int summonerId)
{
    if(webPageCache.empty())
        addWebPage();

    auto profile = webPageCache.dequeue();
    activeLookups[profile] = {summonerId, 0};

    QString regionPath;
    switch(region){
    case Enums::NorthAmerica:
        regionPath = "na";
        break;
    case Enums::EuropeWest:
        regionPath = "euw";
        break;
    case Enums::EuropeNordicEast:
        regionPath = "eune";
        break;
    default:
        QLOG_ERROR() << "LolKingSummonerStatsProvider unknown region" << region;
        break;
    }

    QString url = "http://www.lolking.net/summoner/" + regionPath + "/" + QString::number(summonerId);
    profile->mainFrame()->setUrl(url);
}

void LolKingSummonerStatsProvider::profileLoaded(bool ok)
{
    auto profile = qobject_cast<QWebPage*>(sender());

    if(profile->mainFrame()->requestedUrl() == QUrl("about:blank"))
        return;

    if(!ok){
        QLOG_ERROR() << "LolKingSummonerStatsProvider load finished with error on" << activeLookups.value(profile);
        return triggerError();
    }

    SummonerStats stats;

    auto container = profile->mainFrame()->findFirstElement("div.tabs2_container.pane");

    if(container.isNull()){
        QLOG_ERROR() << "LolKingSummonerStatsProvider can't find container element \"div.tabs2_container.pane\" on"
                     << activeLookups.value(profile);
        return triggerError();
    }

    // profile
    auto ratings = container.findFirst("ul.personal_ratings > li:nth-child(2)");

    if(!ratings.isNull()){
        auto solo5TopRating = ratings.findFirst("div:nth-child(3)");

        if(solo5TopRating.isNull()){
            QLOG_WARN() << "LolKingSummonerStatsProvider failed to retrieve Solo 5x5 top rating element "
                           "\"div:nth-child(3)\" on" << activeLookups.value(profile) << "- Rating set to 0";
            stats.solo5TopRating = 0;
        } else if(solo5TopRating.toPlainText().trimmed().toLower() == "unranked"){
            stats.solo5TopRating = 0;
        } else {
            stats.solo5TopRating = solo5TopRating.toPlainText().toInt(&ok);

            if(!ok){
                QLOG_ERROR() << "LolKingSummonerStatsProvider failed to obtain an integer from  Solo 5x5"
                                " top rating element \"div:nth-child(3)\", content was"
                             << solo5TopRating.toPlainText() << "on" << activeLookups.value(profile);
                return triggerError();
            }
        }

        auto solo5Rating = ratings.findFirst("div:nth-child(6) > span");

        if(solo5Rating.isNull()){
            QLOG_WARN() << "LolKingSummonerStatsProvider failed to retrieve Solo 5x5 current rating "
                           "element \"div:nth-child(6) > span\" on" << activeLookups.value(profile)
                        << "- Rating set to 0";
            stats.solo5Rating = 0;
        } else {
            stats.solo5Rating = solo5Rating.toPlainText().toInt(&ok);

            if(!ok){
                QLOG_ERROR() << "LolKingSummonerStatsProvider failed to obtain an integer from Solo 5x5"
                                " current rating element \"div:nth-child(6)\", content was "
                             << solo5Rating.toPlainText() << "on" << activeLookups.value(profile);
                return triggerError();
            }
        }

    } else {
        QLOG_WARN() << "LolKingSummonerStatsProvider failed to retrieve ratings container "
                       "\"ul.personal_ratings > li:nth-child(2)\" on" << activeLookups.value(profile)
                    << "- All ratings set to 0.";
        stats.solo5TopRating = 0;
        stats.solo5Rating = 0;
    }

    // ranked stats
    //auto statsEl = container.findAll("#ranked_stats tbody tr");
    //todo: avg stats (kda) are only taken into account for season 2, we need to rethink our approach
    auto statsEl = container.findAll(".season_3_ranked_stats tbody tr, .season_2_ranked_stats tbody tr");

    if(statsEl.count() == 0){
        QLOG_ERROR() << "LolKingSummonerStatsProvider failed to retrieve player champion stats elements"
                        "\"#ranked_stats tbody tr\" on" << activeLookups.value(profile);
        return triggerError();
    }

    ok = getSesonStats(container.findAll(".season_2_ranked_stats tbody tr"), stats.s2ChampionStats);
    ok = getSesonStats(container.findAll(".season_3_ranked_stats tbody tr"), stats.s3ChampionStats) || ok;

    if(!ok)
        return triggerError();

    auto state = activeLookups.value(profile);
    QLOG_INFO() << "LolKingSummonerStatsProvider lookup succeed on" << state;
    clearLookup(profile);

    emit lookupSucceed(state.summonerId, stats);
}

void LolKingSummonerStatsProvider::retryLookup()
{
    auto profile = *retryQueue.begin();
    QLOG_TRACE() << "LolKingSummonerStatsProvider retrying lookup on" << activeLookups.value(profile);
    auto url = profile->mainFrame()->requestedUrl();
    profile->mainFrame()->setUrl(QUrl("about:blank"));
    profile->mainFrame()->setUrl(url);
    retryQueue.erase(retryQueue.begin());
}

void LolKingSummonerStatsProvider::triggerError()
{
    auto profile = qobject_cast<QWebPage*>(sender());
    auto state = activeLookups.value(profile);

    if(state.retry < 2){
        int ms = state.retry == 0? 2000 : 5000;
        QLOG_INFO() << "LolKingSummonerStatsProvider retrying lookup in" << ms << "ms from now on" << state;
        ++activeLookups[profile].retry;

        int idx = QDateTime::currentMSecsSinceEpoch() + ms;
        while(retryQueue.contains(idx))
            ++idx;

        retryQueue[idx] = profile;
        QTimer::singleShot(ms, this, SLOT(retryLookup()));

    } else {
        QLOG_INFO() << "LolKingSummonerStatsProvider lookup of summoner stopped after 3 tries on"
                     << activeLookups.value(profile);
        clearLookup(profile);
        emit lookupFailed(state.summonerId);
    }
}

bool LolKingSummonerStatsProvider::getSesonStats(QWebElementCollection statsEl, QHash<int, SummonerChampionStats>& stats)
{
    auto profile = qobject_cast<QWebPage*>(sender());
    foreach(QWebElement tr, statsEl){
        auto champIdEl = tr.findFirst("td:nth-child(1) div div");

        if(champIdEl.isNull()){
            QLOG_ERROR() << "LolKingSummonerStatsProvider failed to retrieve champion id element"
                            "\"td:nth-child(1) div div\" on" << activeLookups.value(profile);
            return false;
        }

        QString style = champIdEl.attribute("style");

        if(style.isEmpty()){
            QLOG_ERROR() << "LolKingSummonerStatsProvider failed to retrieve 'style' attribute from"
                            "champion id element \"td:nth-child(1) div div\" on"
                         << activeLookups.value(profile);
            return false;
        }

        int leftIdx = style.indexOf("champions/") + 10;

        if(leftIdx == -1){
            QLOG_ERROR() << "LolKingSummonerStatsProvider string \"champions/\" not found in 'style' "
                            "attribute from champion id element \"td:nth-child(1) div div\" on"
                         << activeLookups.value(profile);
            return false;
        }

        int rightIdx = style.indexOf("_icon_") - leftIdx;

        if(leftIdx <= 0){
            QLOG_ERROR() << "LolKingSummonerStatsProvider string \"_icon_/\" not found in 'style' "
                            "attribute from champion id element \"td:nth-child(1) div div\" on"
                         << activeLookups.value(profile);
            return false;
        }

        style = style.mid(leftIdx, rightIdx);
        bool ok;
        int champId = style.toInt(&ok);

        if(!ok){
            QLOG_ERROR() << "LolKingSummonerStatsProvider failed to obtain an integer from sliced 'style' "
                            "attribute in champion id element \"td:nth-child(1) div div\" image url, content was"
                         << style << "on" << activeLookups.value(profile);
            return false;
        }

        auto& s = stats[champId];

        auto m = getStatTdInt(tr.findFirst("td:nth-child(2)"), &s.wins);
        if(!m.isEmpty()){
            QLOG_ERROR() << m.arg("wins").arg("td:nth-child(2)").data() << activeLookups.value(profile);
            return false;
        }

        m = getStatTdInt(tr.findFirst("td:nth-child(3)"), &s.loses);
        if(!m.isEmpty()){
            QLOG_ERROR() << m.arg("loses").arg("td:nth-child(3)").data() << activeLookups.value(profile);
            return false;
        }

        m = getStatTdFloat(tr.findFirst("td:nth-child(5)"), &s.kills);
        if(!m.isEmpty()){
            QLOG_WARN() << m.arg("kills").arg("td:nth-child(5)").data() << activeLookups.value(profile);
        }


        m = getStatTdFloat(tr.findFirst("td:nth-child(6)"), &s.deaths);
        if(!m.isEmpty()){
            QLOG_WARN() << m.arg("deaths").arg("td:nth-child(6)").data() << activeLookups.value(profile);
        }


        m = getStatTdFloat(tr.findFirst("td:nth-child(7)"), &s.assists);
        if(!m.isEmpty()){
            QLOG_WARN() << m.arg("assists").arg("td:nth-child(7)").data() << activeLookups.value(profile);
        }
    }

    return true;
}

QString LolKingSummonerStatsProvider::getStatTdInt(QWebElement e, int* i)
{
    if(e.isNull())
        return "LolKingSummonerStatsProvider failed to retrieve player champion  %1 element \"%2\" on";

    bool ok;
    *i = e.toPlainText().toInt(&ok);
    return ok? "":
           QString("LolKingSummonerStatsProvider failed to obtain integer from player champion %1 element"
                   "\"%2\", content was \"") + e.toPlainText() + "\" on";
}

QString LolKingSummonerStatsProvider::getStatTdFloat(QWebElement e, float* i)
{
    if(e.isNull())
        return "LolKingSummonerStatsProvider failed to retrieve player champion %1 element \"%2\" on";

    auto txt = e.toPlainText();
    int floatEnd = txt.indexOf('/');

    if(floatEnd == -1)
        return "LolKingSummonerStatsProvider character '/' not found in player champion %1 element"
                "\"%2\", content was \"" + txt + "\" on";

    bool ok;
    *i = txt.mid(0, floatEnd).toFloat(&ok);

    return ok? "":
           QString("LolKingSummonerStatsProvider failed to obtain float from player champion %1 element"
                   "\"%2\", content was \"") + txt.mid(0, floatEnd) + "\" on";
}

void LolKingSummonerStatsProvider::clearLookup(QWebPage* wp)
{
    activeLookups.remove(wp);

    if(webPageCache.size() >= 5){
        wp->deleteLater();
    } else{
        wp->mainFrame()->setUrl(QUrl("about:blank"));
        webPageCache.enqueue(wp);
    }
}

