import QtQuick 1.1
import QtDesktop 0.1
import LeagueGuru 1.0

FocusScope {
    id: matchupView
    property alias bansModel: enemyPanel.bansModel
    property alias enemyRosterModel: enemyPanel.rosterModel
    property variant participantsModel
    property int currentTab: -1

    signal requestClose()

    function matchupDisbanded(){
        closeMatchupMessage.state = "SHOWN"
    }

    function switchTab(){
        for(var i = 0; i < panels.children.length; ++i)
            panels.children[i].visible = currentTab==i

        panels.children[currentTab].forceActiveFocus()
    }    

    function tabEnabled(n){
        return tabsRow.children[n].tabEnabled
    }

    function setCurrentTab(n){
        if(tabEnabled(n))
            currentTab = n
    }

    Component.onCompleted: {
        if(!enemyTab.tabEnabled){
            for(var i = 0; i < repeater.count; ++i){
                if(tabEnabdled(i)){
                    currentTab = i
                    break;
                }
            }
        } else {
            currentTab = 0
        }
    }

    onCurrentTabChanged: switchTab()

    Keys.onPressed: {
        switch(event.key){
        case Qt.Key_0: case Qt.Key_1: case Qt.Key_2: case Qt.Key_3: case Qt.Key_4:
        case Qt.Key_5: case Qt.Key_6: case Qt.Key_7: case Qt.Key_8: case Qt.Key_9:
            var n = parseInt(event.text);
            if(n < repeater.count){
                setCurrentTab(n)
                event.accepted = true
            }
            break

        case Qt.Key_Space:
            var nextPickingTab = currentTab
            var skippedTabs = 0;

            do{
                if(skippedTabs == repeater.count){
                    nextPickingTab = 0
                    break
                }

                nextPickingTab = (nextPickingTab+1) % (repeater.count+1)
                if(nextPickingTab > 0)
                    skippedTabs += 1
            }while(!tabsRow.children[nextPickingTab].picking)

            setCurrentTab(nextPickingTab)
            event.accepted = true
            break

        case Enums.ControlTabKey:
            var nextTab = currentTab
            do{ nextTab = (nextTab+1) % (repeater.count+1) } while(!tabEnabled(nextTab))
            setCurrentTab(nextTab)
            event.accepted = true
            break

        case Enums.ControlShiftTabKey:
            var prevTab = currentTab
            do{ prevTab = (prevTab + repeater.count) % (repeater.count + 1) } while(!tabEnabled(prevTab))
            setCurrentTab(prevTab)
            event.accepted = true
            break
        }; // ; needed, qml bug
    }

    width: 420
    height: 600
    opacity: 0

    Behavior on opacity { PropertyAnimation{} }

    // tabs
    Rectangle{
        id: tabsHeader
        width: parent.width
        height: 62
        color: "#000d20"

        Row {
            id: tabsRow
            anchors.fill: parent

            // enemy tab
            TabComponent{
                id: enemyTab
                tabIndex: 0
                // theres nothing useful to show for this tab on normal games, roster is never set on normals
                // so we take advantage of that to disable the tab
                tabEnabled: enemyPanel.enemyChampionCount > 0

                onTabEnabledChanged: {
                    if(tabEnabled)
                        currentTab = tabIndex;
                }

                Image {
                    source: "qrc:/icon/enemy.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 6
                    width: 36
                    height: 36
                }

                Text {
                    text: "Enemy"
                    color: currentTab === 0? "white" : "#88e8f5"
                    anchors.topMargin: 14
                    anchors.top: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 10
                }
            }

            // match participants tabs
            Repeater {
                id: repeater
                model: participantsModel
                delegate: TabComponent {
                    property bool picking: model.pickState == Enums.Picking

                    id: tab
                    tabIndex: index + 1
                    tabEnabled: model.ranking >= 0
                    featured: model.selfSummoner

                    onTabEnabledChanged: {
                        if(tabEnabled && currentTab == -1)
                            currentTab = tabIndex
                    }

                    Item {
                        id: championImgContainer
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        anchors.topMargin: 6
                        width: 36
                        height: 36
                        opacity: 0

                        ChampionImage {
                            id: championImg
                            anchors.fill: parent
                            championId: model.championId
                            sourceSize { height: 36; width: 36 }
                            opacity: model.championId > 0? 1:0

                            Behavior on opacity { PropertyAnimation{} }
                        }

                        AnimatedImage {
                            id: loadingChampionImg
                            anchors.fill: parent
                            anchors.margins: 2
                            source: "qrc:/img/loading.gif"
                            opacity: model.pickState === Enums.LockedIn? 0 : .4

                            Behavior on opacity { PropertyAnimation{ } }
                        }

                        Behavior on opacity { PropertyAnimation{} }
                    }

                    Text {
                        id: playerName
                        anchors.bottom: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: currentTab === tabIndex || !tab.tabEnabled? "white" : "#88e8f5"
                        font.pixelSize: 10
                        text: model.summonerName
                    }

                    Text {
                        id: playerRanking
                        anchors.top: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: currentTab === tabIndex? "white" : "#88e8f5"
                        font.bold: true
                        font.pixelSize: 14
                        opacity: 0
                        text: model.ranking || "< 1200"

                        Behavior on opacity { PropertyAnimation{} }

                    }

                    property variant rankingBind: model.ranking
                    onRankingBindChanged: if(rankingBind >= 0 && state == "") state = "A"

                    property variant pickStateBind: model.pickState
                    onPickStateBindChanged:{
                        if((pickStateBind == Enums.Picking || pickStateBind == Enums.LockedIn) && state == "A")
                            state = "B"
                        if(pickStateBind == Enums.LockedIn)
                            panels.children[tabIndex].setCurrentChampion(model.championId);
                    }

                    states: [
                        State {
                            name: "A"
                            PropertyChanges { target: playerRanking; opacity: 1;}
                            AnchorChanges { target: playerRanking; anchors.top: parent.verticalCenter;}
                        },

                        State {
                            name: "B"
                            PropertyChanges { target: playerName; anchors.topMargin: 14;}
                            AnchorChanges { target: playerName; anchors.top: parent.verticalCenter;}
                            PropertyChanges { target: championImgContainer; opacity: 1 }
                        }
                    ]

                    transitions: Transition {
                        AnchorAnimation {}
                    }
                }
            }
        }
    }


    // pages
    Item {
        id: panels
        anchors {top: tabsHeader.bottom; left: parent.left; right: parent.right; bottom: closeMatchupMessage.top }
        clip: true

        EnemyPanel{
            anchors {topMargin: 5; bottomMargin: 5 }
            id: enemyPanel
            anchors.fill: parent
            visible: false
        }

        Repeater{
            model: participantsModel
            delegate: ParticipantPanel{
                visible: false
                anchors {fill: parent; topMargin: 5; bottomMargin: 5 }
                participantIndex: model.participantIndex
                filterModel: model.filterModel
                s2RosterModel: model.s2RosterModel
                s3RosterModel: model.s3RosterModel
                suggestionsModel: model.suggestionsModel
            }
        }
    }

    // "close matchup" when matchup is over
    Item {
        id: closeMatchupMessage
        anchors { top: parent.bottom; left: parent.left; right: parent.right }
        height: closeMatchupText.height + closeMatchupRow.height + 10

        Image {
            id: closeMatchupIcon
            anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 5 }
            source: "qrc:/icon/info.png"
        }

        Text {
            id: closeMatchupText
            anchors { left: closeMatchupIcon.right; right: parent.right; leftMargin: 5; rightMargin: 5}
            text: qsTr("This matchup has already ended. As soon as you enter a new game this view will be refreshed.")
            wrapMode: Text.Wrap
            color: "white"
        }

        Row{
            id: closeMatchupRow
            anchors { horizontalCenter: parent.horizontalCenter; top: closeMatchupText.bottom; topMargin: 5}
            height: closeMatchupOkButton.implicitHeight

            Button {
                id: closeMatchupOkButton
                text: "Ok"
                onClicked: closeMatchupMessage.state = ""
            }

            Button{
                text: "Close now"
                onClicked: requestClose()
            }
        }

        states: State {
            name: "SHOWN"
            AnchorChanges {
                target: closeMatchupMessage
                anchors.top: undefined
                anchors.bottom: matchupView.bottom
            }
        }

        transitions: Transition { AnchorAnimation{ duration: 500 } }
    }
}
