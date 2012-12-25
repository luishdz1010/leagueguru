import QtQuick 1.1

// used only in MatchupTabWidget
Item {
    property int tabIndex
    property bool tabEnabled: false
    property bool featured: false
    default property alias content: clippingRect.children

    width: tabsHeader.width / (repeater.count + 1)
    height: tabsHeader.height
    clip: true

    BorderImage {
        source: !tabEnabled? "qrc:/img/tab_disabled.png" :
                          (currentTab === tabIndex?
                               (featured? "qrc:/img/highlight_tab_active.png" : "qrc:/img/tab_active.png"):
                               (featured? "qrc:/img/highlight_tab.png" : "qrc:/img/tab.png"))
        anchors.fill: parent
        border.left: 11;
        border.top: 10
        border.right:11;

        Item{
            id: clippingRect
            anchors { fill: parent; topMargin: 4; leftMargin: 4; rightMargin: 4 }
            clip: true
        }
    }

    BorderImage {
        width: parent.width
        source: "qrc:/img/tab_div.png"
        height: 4
        anchors.bottom: parent.bottom
        visible: currentTab !== tabIndex
    }

    MouseArea {
        id: tabMouseArea
        anchors.fill: parent
        enabled: parent.tabEnabled
        onClicked: currentTab = tabIndex
    }
}
