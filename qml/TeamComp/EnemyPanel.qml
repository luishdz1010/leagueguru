import QtQuick 1.1
import LeagueGuru 1.0

FocusScope {
    width: 440
    height: 600

    property alias bansModel: suggestedBansView.model
    property alias rosterModel: rosterView.model
    property alias enemyChampionCount: rosterView.count

    DarkFrame {
        id: suggestedBansDarkFrame
        anchors { top: parent.top; left: parent.left}
        height: 118

        SectionTitle {
            id: suggestedBansTitle
            text: qsTr("Suggested bans")
        }

        GridView {
            id: suggestedBansView
            anchors { left: parent.left; top: suggestedBansTitle.bottom; right: parent.right; bottom: parent.bottom;
                leftMargin: 5; rightMargin: 5; topMargin: 3}
            clip: true
            cellHeight: 51
            cellWidth: suggestedBansView.width / 3 - 6

            delegate: Item {
                Image {
                    id: championImage
                    anchors { left: parent.left; top: parent.top; }
                    source: championData.imageSource
                    sourceSize { width: 48; height: 48 }
                }

                Text {
                    id: championName
                    anchors.left: championImage.right
                    anchors.leftMargin: 5
                    anchors.top: parent.top
                    text: championData.name
                    color: "white"
                }

                Image {
                    id: winrateIcon
                    anchors{ left:  championImage.right; top: championName.bottom; topMargin: 3; leftMargin: 5; }
                    source: "qrc:/icon/wins.png"
                }

                Text {
                    id: winrateText
                    anchors { left: winrateIcon.right; top: championName.bottom; topMargin: 3; leftMargin: 3; }
                    text: model.winPercent.toFixed(2) + "%"
                    font.bold: true
                    color: "white"
                }

                ChampionData{
                    id: championData
                    championId: model.championId
                }

                /*Column {
                   anchors.left: championName.right
                   //anchors.horizontalCenter: parent.horizontalCenter
                   anchors.leftMargin: 5
                   spacing: 5

                   Row {
                       spacing: 3
                       width: childrenRect.width
                       height: childrenRect.height
                   }

                   Row {
                       spacing: 3
                       Image{
                           source: "img/popularity.png"
                       }

                       Text{
                           text: {
                               if(model.popularity > 40)
                                   return qsTr("Extremely High")
                               if(model.popularity > 30)
                                   return qsTr("Very High")
                               else if(model.popularity > 20)
                                   return qsTr("High")
                               else if(model.popularity > 10)
                                   return qsTr("Normal")
                               else if(model.popularity > 5)
                                   return qsTr("Low")
                               else if(model.popularity > 1)
                                   return qsTr("Very Low")
                               else
                                   return qsTr("Extremely Low")
                           }
                       }
                    }    */
            }
        }
    }

    ChampionFilterControls {
        anchors { top: suggestedBansDarkFrame.bottom; topMargin: 10; leftMargin: 5; rightMargin: 5;
                  left: parent.left; right: parent.right}
        id: championFilter
        height: 20
        championModel: rosterView.model
        focus: true
    }

    DarkFrame {
        anchors { top: championFilter.bottom; bottom: parent.bottom; topMargin: 10; }

        SectionTitle {
            id: enemyRosterText
            text: qsTr("Enemy roster")
        }

        GridView {
            id: rosterView
            anchors { top: enemyRosterText.bottom; bottom: parent.bottom; left: parent.left; right: parent.right;
                      margins: 5; topMargin: 5}
            cellWidth: 50; cellHeight: 50
            clip: true
            delegate: Image{
                x: 1
                y: 1
                source: rChampionData.imageSource
                sourceSize {width: 48; height: 48}

                ChampionData{
                    id: rChampionData
                    championId: model.championId
                }
            }
        }
    }

    states: [
        State {
            name: "afterBanPhase"
        }
    ]
}
