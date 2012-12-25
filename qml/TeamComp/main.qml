import QtQuick 1.1
import QtDesktop 0.1

Window {
    id: window
    title: "League Guru"
    minimumWidth: 420
    maximumWidth: 516
    minimumHeight: 200
    visible: true

    width: 420
    height: 200

    Behavior on height { PropertyAnimation{ duration: 500; easing.type: Easing.OutExpo} }

    Rectangle{
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.33; color: "#031634" }
            GradientStop { position: 1; color: "#000d20" }
        }
    }

    function closeMatchupView()  {
        if(matchupViewLoader.item)
            matchupViewLoader.item.opacity = 0
        status.opacity = 1
    }

    Connections{
        target: controller

        onInjectionSucceed: {
            status.text = "Client is ready. Select your region if you haven't done that already:"
        }

        onInjectionFailed: {
            status.text = "League of Legends is already open, League Guru can only work if you open it before logging in PVP.net. Please restart both the LoL client and Guru and try again."
            status.state = "UNSELECTABLE"
        }

        onSummonerLoggedIn: {
            status.text = "Waiting for a 5v5 Summoner's Rift match."
            status.state = "UNSELECTABLE"
        }

        onConnectionError: {
            var text = "A network error ocurred, please verify you selected the correct server region. If the problem persists, contact us at http://leagueguru.net/contact."

            if(matchupViewLoader.item){
                dialog.text = text;
                dialog.visible = true;
            } else {
                status.text = text;
                status.state = "UNSELECTABLE"
            }
        }

        onMatchupCreated: {
            matchupViewLoader.source = ""
            matchupViewLoader.source = "MatchupView.qml"
            matchupViewLoader.item.opacity = 1;
            matchupViewLoader.item.bansModel = bansModel
            matchupViewLoader.item.enemyRosterModel = enemyRosterModel
            matchupViewLoader.item.participantsModel = participantsModel
            matchupViewLoader.item.focus = true

            if(window.height == 200)
                window.height = 620

            status.opacity = 0
        }

        onMatchupDisbanded: matchupViewLoader.item.matchupDisbanded()
        onMatchupDestroyed: closeMatchupView()
    }

    Connections{
        target: matchupViewLoader.item
        onRequestClose: {
            if(window.height == 620)
                window.height = 200
            closeMatchupView()
        }
    }

    Loader{
        id: matchupViewLoader
        anchors.fill: parent
    }

    RegionSelector{
        id: status
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.verticalCenterOffset: -40
        anchors.margins: 5

        Behavior on anchors.verticalCenterOffset { PropertyAnimation{} }
        Behavior on opacity { PropertyAnimation{ duration: 500 } }

        states: State{
            name: "UNSELECTABLE"
            PropertyChanges {
                target: status
                anchors.verticalCenterOffset: -18
                comboboxOpacity: 0
            }
        }
    }

    Dialog{
        property alias text: label.text

        id: dialog
        width: 300
        height: 150
        title: "League Guru"
        buttons: ok
        modal: true
        visible: false

        Text{
            id: label
            anchors.fill: parent
            anchors.margins: 5
            wrapMode: Text.WordWrap
        }
    }
}
