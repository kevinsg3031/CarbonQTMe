import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: parent.width
    height: 42
    radius: 8

    property string text: ""
    property bool active: false
    signal clicked()

    color: active ? "#428F44" : "transparent"
    border.color: "#428F44"

    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked()
    }

    Text {
        anchors.centerIn: parent
        text: parent.text
        color: active ? "white" : "#163117"
        font.pixelSize: 14
        font.bold: active
    }
}

