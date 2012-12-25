#ifndef BANSMODEL_H
#define BANSMODEL_H

#include "basicitemmodel.hpp"

enum class BanSuggestionsData{
    ChampionId = Qt::UserRole + 1,
    WinPercent,
    TotalGames,
    Popularity
};

class BanSuggestionItem : public BasicItem<BanSuggestionsData>{
public:
    BanSuggestionItem(){}

    BanSuggestionItem(InitList init) :
        BasicItem(init)
    {}
};

class BanSuggestionsModel : public BasicItemModel<BanSuggestionItem>
{
public:
    explicit BanSuggestionsModel(QObject *parent = 0) :
        BasicItemModel(parent)
    {
        QHash<int, QByteArray> r;
        r[(int)BanSuggestionsData::ChampionId] = "championId";
        r[(int)BanSuggestionsData::WinPercent] = "winPercent";
        r[(int)BanSuggestionsData::TotalGames] = "totalGames";
        r[(int)BanSuggestionsData::Popularity] = "popularity";
        setRoleNames(r);
    }
};

Q_DECLARE_METATYPE(BanSuggestionsModel*)

#endif // BANSMODEL_H
