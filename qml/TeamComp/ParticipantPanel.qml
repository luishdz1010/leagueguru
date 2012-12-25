import QtQuick 1.1
import LeagueGuru 1.0
import QtDesktop 0.1

FocusScope {
    property int participantIndex
    property alias filterModel : filterControls.championModel    
    property alias suggestionsModel: suggestionsGrid.model
    property variant s2RosterModel
    property variant s3RosterModel

    property bool __selecting: false

    function setCurrentChampion(championId){
        currentChamp.championId = championId

        var championStats = rosterView.model.getChampionStats(championId)
        currentChamp.wins = championStats.wins
        currentChamp.loses = championStats.loses
        currentChamp.kills = championStats.kills
        currentChamp.deaths = championStats.deaths
        currentChamp.assists = championStats.assists
        currentChamp.weakVs = suggestionsModel.getWeakVs(championId)
        currentChamp.strongVs = suggestionsModel.getStrongVs(championId)
        currentChamp.goodWith = suggestionsModel.getGoodWith(championId)

        focusActiveChampion()
    }

    function focusActiveChampion()
    {
        if(currentChamp.championId !== 0){
            __selecting = true
            suggestionsGrid.currentIndex = suggestionsModel.championIndex(currentChamp.championId)
            rosterView.currentIndex = rosterView.model.championIndex(currentChamp.championId)
             __selecting = false
        }
    }

    Keys.onPressed: {
        switch(event.key){
        case Qt.Key_R:
            if(event.modifiers & Qt.ControlModifier){
                filterControls.resetFilter()
                event.accepted = true
            }
        };
    }

    Connections{
        target: suggestionsModel
        onModelReset: focusActiveChampion()
    }

    // holds the data for the current champion
    QtObject{
        id: currentChamp

        property alias championId: championData.championId
        property alias name: championData.name
        property alias imageSource: championData.imageSource

        property int wins: -1
        property int loses: -1
        property real kills: -1
        property real deaths: -1
        property real assists: -1

        property alias goodWith: goodWithView.model
        property alias strongVs: strongVsView.model
        property alias weakVs: weakVsView.model

        property ChampionData championData: ChampionData{
            id: championData
            championId: 0
        }
    }

    DarkFrame{
        id: championDisplay
        anchors.left: parent.left
        anchors.right: parent.right
        height: 105//125

        Item {
            anchors.fill: parent
            anchors.margins: 5

            Image {
                id: championImage
                anchors {top: parent.top; left: parent.left }
                source: currentChamp.imageSource
                sourceSize { width: 32; height: 32 }
            }

            Text {
                anchors { top: parent.top; left: championImage.right; leftMargin: 5 }
                id: championNameLabel
                text: currentChamp.name
                color: "white"
                font.pointSize: 12
                font.letterSpacing: -1
                height: 15
            }

            Row {
                anchors { top: parent.top; left:parent.left; right: parent.right; topMargin: 2; leftMargin: 150}
                height: 16
                spacing: 10

                Row{
                    width: Math.max(30, 18 + cdT1.paintedWidth) ; height: 16; spacing: 2
                    Image{ source: "qrc:/icon/wins.png" }
                    Text { id: cdT1; y: -2; color: "#3daf2c"; font.bold: true;
                        text: currentChamp.wins < 0? "0" : currentChamp.wins }
                }

                Row{
                    width: Math.max(30, 18 + cdT2.paintedWidth); height: 16; spacing: 2
                    Image{ source: "qrc:/icon/loses.png" }
                    Text { id: cdT2; y: -2; color: "#e83c3c"; font.bold: true;
                        text: currentChamp.loses < 0? "0" : currentChamp.loses}
                }

                Row{
                    width: Math.max(30, 18 + cdT3.paintedWidth); height: 16; spacing: 2
                    Image{ source: "qrc:/icon/kills.png" }
                    Text { id: cdT3; y: -2; color: "white"; font.bold: true;
                        text: currentChamp.kills < 0? "0.0" : currentChamp.kills.toFixed(1)}
                }

                Row{
                    width: Math.max(30, 18 + cdT4.paintedWidth); height: 16; spacing: 2
                    Image{ source: "qrc:/icon/deaths.png" }
                    Text { id: cdT4; y: -2; color: "white"; font.bold: true;
                        text: currentChamp.deaths < 0? "0.0" : currentChamp.deaths.toFixed(1)}
                }

                Row{
                    width: Math.max(30, 18 + cdT5.paintedWidth); height: 16; spacing: 2
                    Image{ source: "qrc:/icon/assists.png" }
                    Text { id: cdT5; y: -2; color: "white"; font.bold: true;
                        text: currentChamp.assists < 0? "0.0" : currentChamp.assists.toFixed(1)}
                }
            }

            Row{
                anchors {top: parent.top; topMargin: 24; left: parent.left; right: parent.right; bottom: parent.bottom;
                    bottomMargin: 5}

                MatchupDetailsBox {
                    id: strongVsView
                    title: "Strong vs"
                    titleLeftMargin.leftMargin: 38
                    width: (parent.width - 2) / 3
                    height: parent.height
                }

                VerticalLineSeparator{ height: parent.height; }

                MatchupDetailsBox {
                    id: weakVsView
                    title: "Weak vs"
                    width: (parent.width - 2) / 3
                    height: parent.height
                }

                VerticalLineSeparator{ height: parent.height; }

                MatchupDetailsBox {
                    id: goodWithView
                    title: "Good with"
                    width: (parent.width - 2) / 3
                    height: parent.height
                }
            }

            /*Text{
                id: roleLabel
                anchors {bottom: parent.bottom; left: parent.left; bottomMargin: 3}
                text: "\"XXX or I feed\"? Set fixed role:"
                color: "white"
                font.pointSize: 6.5
            }

            ListModel{
                id: roles
            }

            ComboBox{
                id: roleCombobox
                anchors { left: roleLabel.right; leftMargin: 5; verticalCenter: roleLabel.verticalCenter }
                width: 100
                height: roleLabel.height + 6
                model: roles
                activeFocusOnPress: true

                onSelectedIndexChanged: controller.setParticipantRole(participantIndex, roles.get(selectedIndex).role)

                KeyNavigation.backtab: rosterView
                Keys.onTabPressed: filterControls.filters.forceActiveFocus() // workaround

                Component.onCompleted: {
                    roles.append({text: "Any", role: Enums.AnyRole})
                    roles.append({text: "Top", role: Enums.Top})
                    roles.append({text: "ADC", role: Enums.ADC})
                    roles.append({text: "Mid", role: Enums.Mid})
                    roles.append({text: "Jungler", role: Enums.Jungler})
                    roles.append({text: "Support", role: Enums.Support})
                }
            }*/
        }
    }

    ChampionFilterControls {
        id: filterControls
        anchors{ top: championDisplay.bottom; left: parent.left; right: parent.right; topMargin:  10; leftMargin:
                5; rightMargin: 5}
        height: 20

        //KeyNavigation.backtab: roleCombobox
        KeyNavigation.backtab: rosterView
        KeyNavigation.tab: suggestionsGrid
        KeyNavigation.down: suggestionsGrid
    }

    // pick suggestions
    DarkFrame{
        id: suggestionsDarkFrame
        anchors {top: filterControls.bottom; left: parent.left; right: parent.right; topMargin: 10}
        height: season2Label.height + 50*3

        SectionTitle {
            id: suggestionsLabel
            anchors{ top: parent.top; left: parent.left; right: parent.right }
            text: "Suggestions"
        }

        ChampionGridView{
            id: suggestionsGrid
            model: suggestionsModel
            anchors { top: suggestionsLabel.bottom; bottom: parent.bottom; left: parent.left;
                right: parent.right; leftMargin: 5; rightMargin: 5; topMargin: 3 }

            Keys.onBacktabPressed: filterControls.searchBox.forceActiveFocus()
            KeyNavigation.tab: rosterView
            KeyNavigation.up: filterControls
            KeyNavigation.down: rosterView

            onCurrentIndexChanged:  {
                if(suggestionsGrid.currentIndex == -1 || __selecting)
                    return

                setCurrentChampion(suggestionsGrid.currentItem.championId)
            }
        }
    }

    // participan champion roster
    DarkFrame {
        anchors { top: suggestionsDarkFrame.bottom; bottom: parent.bottom; left: parent.left;
            right: parent.right; topMargin: 5 }

        SectionTitle{
            id: season2Label
            anchors { top: parent.top; right: seasonSep.left; left: parent.left; rightMargin: 8; topMargin: 2 }
            text: "Season 2"
            horizontalAlignment: Text.AlignRight

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    var ch = currentChamp.championId
                    season3Label.font.bold = false
                    season2Label.font.bold = true
                    s2RosterModel.sort(rosterView.sortColumn, rosterView.sortIndicatorDirection)
                    rosterView.model = s2RosterModel

                    if(ch > 0)
                        setCurrentChampion(ch)
                }
            }
        }

        VerticalLineSeparator{
            id: seasonSep
            y: 4
            width: 1
            anchors.horizontalCenter: parent.horizontalCenter
            height: Math.max(season2Label.height, season3Label.height) - 4
        }

        SectionTitle{
            id: season3Label
            anchors { top: parent.top; left: seasonSep.right; right: parent.right; leftMargin: 8; topMargin: 2 }
            text: "Season 3"
            horizontalAlignment: Text.AlignLeft

            MouseArea{
                anchors.fill: parent

                function switchToSeason3Stats(){
                    var ch = currentChamp.championId
                    season2Label.font.bold = false
                    season3Label.font.bold = true
                    s3RosterModel.sort(rosterView.sortColumn, rosterView.sortIndicatorDirection)
                    rosterView.model = s3RosterModel

                    if(ch > 0)
                        setCurrentChampion(ch)
                }

                Component.onCompleted: switchToSeason3Stats()
                onClicked: switchToSeason3Stats()
            }
        }

        // note: we horribly hacked table view to work here (usage of list.contentY is 200% broken), if we
        // use it anywhere else, we will have to copy it into our project and restore the original version
        TableView{
            id: rosterView

            property int currentChampionId

            anchors { top: season2Label.bottom; bottom: parent.bottom; left: parent.left; right: parent.right;
                leftMargin: 5; rightMargin: 5 }
            cacheBuffer: 3600
            backgroundColor: "transparent"
            highlightOnFocus: true
            sortIndicatorVisible: true
            frame: false
            alternateRowColor: false
            sortColumn: 1
            focus: true

            KeyNavigation.backtab: suggestionsGrid
            //KeyNavigation.tab: roleCombobox
            Keys.onTabPressed: filterControls.filters.forceActiveFocus()
            KeyNavigation.up: suggestionsGrid

            onSortColumnChanged: model.sort(sortColumn, sortIndicatorDirection);
            onSortIndicatorDirectionChanged: model.sort(sortColumn, sortIndicatorDirection);

            headerDelegate: Item{
                clip: true
                Text {
                    id: rHeaderText
                    anchors.centerIn: parent
                    text: itemValue
                    color: itemContainsMouse? "white": "#a3c9e4"
                    elide: Text.ElideRight
                    font.bold: itemPressed
                }
                Rectangle{
                    color: itemSort.length > 0? (itemSort == "up"? "red":"green") : "#0b4276"
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: 2
                }
            }

            itemDelegate: Item {
                height: 36
                clip: true
                property int implicitWidth: rosterItemDelegateSizehint.paintedWidth + 4
                Text {
                    id: rosterItemDelegateLabel
                    width: parent.width
                    anchors.margins: 6
                    anchors.left: parent.left
                    anchors.right: parent.right
                    horizontalAlignment: Text.AlignHCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: itemValue >= 0? itemValue : ""
                    color: "white"
                }
                Text {
                    id: rosterItemDelegateSizehint
                    font: rosterItemDelegateLabel.font
                    text: itemValue >= 0? itemValue : ""
                    visible: false
                }
            }



            onCurrentIndexChanged: {
                if(rosterView.currentIndex == -1 || __selecting)
                    return

                setCurrentChampion(currentChampionId)
            }

            TableColumn{
                id: championColumn
                role: "championId"
                title: "Champion"
                width: rViewChampionColumnSizeHint.paintedWidth + 36 + 5 // text + icon + margin

                delegate: Item{
                    height: 36
                    clip:true

                    Image {
                        id: rChampionPortrait
                        source: rChampionData.imageSource
                        sourceSize { width: 36; height: 36 }
                    }

                    property bool isSelected: itemSelected

                    onIsSelectedChanged: if(isSelected) rosterView.currentChampionId = itemValue

                    Text{
                        anchors { left: rChampionPortrait.right; verticalCenter: rChampionPortrait.verticalCenter;
                            leftMargin: 5 }
                        text: rChampionData.name
                        color: "white"
                    }

                    ChampionData { id: rChampionData; championId: itemValue }
                }
            }

            TableColumn{
                role: "wins"; title: "Wins";  width: (rosterView.width - championColumn.width - 24) / 6
            }

            TableColumn{
                role: "loses"; title: "Loses"; width: (rosterView.width - championColumn.width - 24) / 6
            }

            TableColumn{
                role: "winrate"; title: "Win %"; width: (rosterView.width - championColumn.width - 24) / 6
                delegate: Item {
                    height: 36
                    property int implicitWidth: rosterWinrateItemDelegateSizehint.paintedWidth + 4
                    Text {
                        id: rosterWinrateItemDelegate
                        width: parent.width
                        anchors.margins: 6
                        anchors.left: parent.left
                        anchors.right: parent.right
                        horizontalAlignment: Text.AlignHCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: itemValue >= 0 ? itemValue.toFixed(2) + "%" : "?"
                        color: "white"
                    }
                    Text {
                        id: rosterWinrateItemDelegateSizehint
                        font: rosterWinrateItemDelegate.font
                        text: itemValue >= 0? itemValue.toFixed(2) + "%" : "?"
                        visible: false
                    }
                }
            }

            TableColumn{
                role: "kills"; title: "Kills"; width: (rosterView.width - championColumn.width - 24) / 6
                delegate: rfloatDelegate
            }

            TableColumn{
                role: "deaths"; title: "Deaths"; width: (rosterView.width - championColumn.width - 24) / 6
                delegate: rfloatDelegate
            }

            TableColumn{
                role: "assists"; title: "Assists"; width: (rosterView.width - championColumn.width - 24) / 6
                delegate: rfloatDelegate
            }
        }

        Component{
            id: rfloatDelegate
            Item {
                height: 36
                property int implicitWidth: rFloatDelegateSizehint.paintedWidth + 4
                Text {
                    id: rFloatItemDelegate
                    width: parent.width
                    anchors.margins: 6
                    anchors.left: parent.left
                    anchors.right: parent.right
                    horizontalAlignment: Text.AlignHCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: itemValue >= 0 ? itemValue.toFixed(1) : "?"
                    color: "white"
                }
                Text {
                    id: rFloatDelegateSizehint
                    font: rFloatItemDelegate.font
                    text: itemValue >= 0? itemValue.toFixed(1) : "?"
                    visible: false
                }
            }
        }

        Text{
            id: rViewChampionColumnSizeHint
            text: "Twisted Fate" // the largest name (along with 2 others)
            visible: false
        }
    }
}
