// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: parent.width
    color: "#000d20"
    //clip: true

    Rectangle{ anchors {top: parent.top; left: parent.left; right: parent.right; leftMargin: -2; rightMargin: -2}
        height: 1;  border.color: "white"; z: 100
    }
    Rectangle{
        anchors {bottom: parent.bottom; left: parent.left; right: parent.right; leftMargin: -2; rightMargin: -2}
        height: 1;  border.color: "white"; z: 100
    }

}
