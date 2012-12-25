import QtQuick 1.1
import LeagueGuru 1.0

GridView {
    property variant roles

    /*Component.onCompleted: {
        var r = {}
        r[Enums.Top] = "top"
        r[Enums.Mid] = "mid"
        r[Enums.Support] = "support"
        r[Enums.Jungler] = "jungle"
        r[Enums.ADC] = "adc"
        roles = r
    }*/

    id: view
    clip: true
    cellHeight: 50
    cellWidth: 50
    focus: true

    highlight: Rectangle {
        width: view.cellWidth; height: view.cellHeight
        color: "transparent"; radius: 2
        x: 2
        y: 2
        z: 2
        border { width: 3; color: "white" }
        Behavior on x { SpringAnimation { spring: 3; damping: 0.2 } }
        Behavior on y { SpringAnimation { spring: 3; damping: 0.2 } }
    }

    delegate: ChampionImage{
        x: 1
        y: 1
        championId: model.championId
        sourceSize {width: 48; height: 48}

        /*Image {
            anchors { right: parent.right; bottom: parent.bottom }
            source: "qrc:/icon/" + view.roles[model.suggestedRole] + ".png"
        }*/

        MouseArea{
            anchors.fill: parent
            onClicked: {
                view.forceActiveFocus()
                view.currentIndex = index
            }
        }
    }

}
