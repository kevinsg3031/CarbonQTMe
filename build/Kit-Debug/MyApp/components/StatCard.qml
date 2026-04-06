import QtQuick 2.15
import QtQuick.Layouts 1.15

// Rectangle {
//     id: card

//     radius: 14
//     color: highlight ? "#428F44" : "#A5D6A7"
//     border.color: "#428F44"

//     // ===== PUBLIC API =====
//     property string title: ""
//     property string value: ""

//     // NEW properties (THIS FIXES YOUR ERROR)
//     property bool highlight: false
//     property bool wide: false

//     Column {
//         anchors.centerIn: parent
//         spacing: wide ? 12 : 8

//         Text {
//             text: title
//             font.pixelSize: wide ? 16 : 14
//             color: highlight ? "white" : "#163117"
//         }

//         Text {
//             text: value
//             font.pixelSize: wide ? 30 : 24
//             font.bold: true
//             color: highlight ? "white" : "#163117"
//         }
//     }
// }

Rectangle {
    radius: 14
    color: "#A5D6A7"
    border.color: "#428F44"

    implicitWidth: 240
    implicitHeight: 120

    property string title
    property string value

    Column {
        anchors.centerIn: parent
        spacing: 8

        Text {
            text: title
            font.pixelSize: 14
            color: "#163117"
        }

        Text {
            text: value
            font.pixelSize: 26
            font.bold: true
            color: "#163117"
        }
    }
}


