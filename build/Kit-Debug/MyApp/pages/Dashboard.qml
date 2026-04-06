import QtQuick 2.15
import QtQuick.Layouts 1.15
import "../components"

Item {
    anchors.fill: parent

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 32
        spacing: 24

        // ===== Header =====
        Text {
             text: "System Overview"
             font.pixelSize: 26
             font.bold: true
             color: "#163117"
             Layout.alignment: Qt.AlignLeft
         }

        // RingChart {
        //     width: 180
        //     height: 180
        //     cpuValue: energyBackend.cpuWatts
        //     ramValue: energyBackend.ramWatts
        //     Layout.alignment: Qt.AlignHCenter
        // }
    }
}


