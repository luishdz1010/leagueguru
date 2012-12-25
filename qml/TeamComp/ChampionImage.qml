import QtQuick 1.1
import LeagueGuru 1.0

Image {
    property alias championId: championData.championId

    source: championData.imageSource

    ChampionData{ id: championData }
}
