import QtQuick 1.1
import LeagueGuru 1.0

Rectangle {
    width: childrenRect.width
    height: childrenRect.height

    property alias championId: championData.championId
    property alias showName: championName.visible
    property string size: "small"

    Component.onCompleted: {
    }

    ChampionData{
        id: championData
    }

    Column{
        spacing: 3

        Image{
            id: championImage
            anchors.horizontalCenter: parent.horizontalCenter
            source: championData.imageSource
        }

        Text{
            id: championName
            font.pixelSize: 10
            anchors.horizontalCenter: parent.horizontalCenter
            visible: false
            text: championData.name
        }
    }
}
