import QtQuick 1.1
import QtDesktop 0.1
import LeagueGuru 1.0

FocusScope {
    id: root
    property variant championModel
    property int currentRole: 0
    property int currentIndex
    property alias filters: rolesRow
    property alias searchBox: championSearch

    property bool __filtering: false

    width: 420
    height: 20

    function resetFilter()
    {
        currentRole = 0
        filterByRole(0)
    }

    function filterByRole(role){
        if(role === 0 && __filtering)
            return

        __filtering = true
        championSearch.text = ""
        __filtering = false
        championModel.filterByRole(role)
    }

    onCurrentIndexChanged: currentRole = rolesRow.children[currentIndex].role

    onCurrentRoleChanged: filterByRole(currentRole)

    Item{
        id: roleButtons
        height: parent.height
        anchors { left: parent.left; right: championSearch.left; rightMargin: 30; }

        Row {
            id: rolesRow
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            KeyNavigation.tab: championSearch

            Keys.onLeftPressed: currentIndex = (currentIndex + roles.count - 1) % roles.count
            Keys.onRightPressed: currentIndex = (currentIndex + 1) % roles.count

            ListModel{
                id: roles
            }

            Repeater{
                model: roles
                delegate: Text{
                    property int role: roles.get(index).role

                    text: tag
                    width: roleButtons.width / roles.count
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: currentRole === role? "white" : "#00d683"
                    font.pixelSize: currentRole === role? 14 : 12
                    font.bold: currentRole === role

                    MouseArea {
                        anchors.fill: parent
                        anchors.topMargin: -4
                        anchors.bottomMargin: -4
                        onClicked: {
                            rolesRow.forceActiveFocus()
                            currentIndex = index
                        }
                    }
                }

                Component.onCompleted: {
                    roles.append({tag: "All", role: Enums.AnyRole})
                    roles.append({tag: "Top", role: Enums.Top})
                    roles.append({tag: "ADC", role: Enums.ADC})
                    roles.append({tag: "Mid", role: Enums.Mid})
                    roles.append({tag: "Jungler", role: Enums.Jungler})
                    roles.append({tag: "Support", role: Enums.Support})
                }
            }

        }
    }

    // name search
    TextField{
        id: championSearch
        width: 95
        height: 19
        anchors.right: parent.right
        styleHint: "focuswidget"
        //background: Rectangle{ color: "red" }

        KeyNavigation.backtab: rolesRow

        onTextChanged:{
            if(text == "" && __filtering)
                return;

            __filtering = true
            currentRole = 0
            __filtering = false
            championModel.filterByName(text);
        }
    }
}
