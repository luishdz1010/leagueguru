import QtQuick 1.1
import LeagueGuru 1.0

Item{
    property alias model: grid.model
    property alias title: titleLabel.text
    property alias titleLeftMargin: titleLabel.anchors

    id: root

    Text{
        anchors { top: parent.top; left: parent.left; leftMargin: 10; topMargin: -4 }
        id: titleLabel
        color: "#69e6eb"
        font.pointSize: 6
    }

    GridView {
        id: grid
        anchors { top: parent.top; left: parent.left; right: parent.right; bottom: parent.bottom; topMargin: 10 }
        cellHeight: 30
        cellWidth: (root.width/2) - 1
        interactive: false
        delegate: Item{
            Image {
                id: championImage
                anchors.left: parent.left
                anchors.top: parent.top
                source: championData.imageSource
                sourceSize { width: 28; height: 28 }
            }

            Text {
                anchors.left: championImage.right
                anchors.leftMargin: 2
                anchors.verticalCenter: championImage.verticalCenter
                color: "white"
                text: model.modelData.percentPositive.toFixed(2) + "<font size=\"1\">%</font>"
                font.pixelSize: 11
                textFormat: Text.RichText
            }

            ChampionData{
                id: championData
                championId: model.modelData.championId
            }
        }
    }
}
