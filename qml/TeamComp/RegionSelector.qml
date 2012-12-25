import QtQuick 1.1
import QtDesktop 0.1
import LeagueGuru 1.0

FocusScope {
    property alias text: label.text
    property alias comboboxOpacity: regionCombo.opacity

    Text {
        id: label
        anchors {left: parent.left; right: parent.right}
        text: "Waiting for the league of legends client to start. Select your region: "
        color: "white"
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
    }    

    ListModel{
        id: regions
    }

    ComboBox{
        id: regionCombo
        width: 164
        anchors { top: label.bottom; horizontalCenter: parent.horizontalCenter; topMargin: 5}
        model: regions
        focus: true

        onSelectedIndexChanged: controller.setServerRegion(regions.get(selectedIndex).region)

        Component.onCompleted: {
            regions.append({ text: "North America", region: Enums.NorthAmerica})
            regions.append({ text: "Europe West", region: Enums.EuropeWest})
            regions.append({ text: "Europe Nordic East", region: Enums.EuropeNordicEast})
        }

        Behavior on opacity { PropertyAnimation{} }
    }    
}
