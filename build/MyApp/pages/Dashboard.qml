import QtQuick 2.15
import QtQuick.Layouts 1.15
import "../components"

Item {
    anchors.fill: parent

    Timer {
        interval: 2000
        running: true
        repeat: true
        onTriggered: {
            backend.updateStats()
            if (processModel)
                processModel.refresh()
        }
    }

    Column {
        // width: 900
        // anchors.horizontalCenter: parent.horizontalCenter
        anchors.fill: parent
        anchors.margins: parent.width < 700 ? 16 : 40
        spacing: parent.width < 700 ? 12 : 20

        Rectangle {
                width: 320
                height: 150
                radius: 12
                color: "#A5D6A7"
                border.color: "#428F44"

                Column {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 6

                    Text { text: "System Info"; font.bold: true; font.pixelSize: 18 }

                    Text { text: "OS: Ubuntu 22.04" }
                    Text { text: "Kernel: 6.5.0" }
                    Text { text: "CPU: Intel i7-1165G7" }
                    Text { text: "Cores: " + backend.coreCount }
                }
            }

        Rectangle {
            width: 800
            height: 190
            radius: 12
            color: "#A5D6A7"
            border.color: "#428F44"
            // anchors.horizontalCenter: parent.horizontalCenter

            RowLayout {
                spacing: 40
                anchors.fill: parent
                anchors.margins: 20

                DoughnutStat {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignVCenter
                    title: "CPU"
                    value: backend.cpuUsage
                    maxValue: 100
                    unit: "%"
                    // color: "#4CAF50"
                    color: "#163117"
                }

                DoughnutStat {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignVCenter
                    title: "RAM"
                    value: backend.ramUsage
                    maxValue: 100
                    unit: "%"
                    // color: "#2196F3"
                    color: "#163117"
                }

                DoughnutStat {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignVCenter
                    title: "Processes"
                    value: processModel.pidValues.length
                    maxValue: 500
                    unit: ""
                    // color: "#FF9800"
                    color: "#163117"
                }

                DoughnutStat {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignVCenter
                    title: "Threads"
                    value: processModel.totalThreads
                    maxValue: 2000
                    unit: ""
                    // color: "#9C27B0"
                    color: "#163117"
                }
            }
        }

        Rectangle {
            width: parent.width
            height: 380
            radius: 12
            color: "#A5D6A7"
            border.color: "#428F44"

            Column {
                anchors.fill: parent
                anchors.margins: 20
                width: 800
                spacing: 12

                Text {
                    text: "PID vs Threads"
                    font.pixelSize: 20
                    font.bold: true
                    color: Theme.text
                }

                Flickable {
                    id: flick
                    width: parent.width
                    height: 300
                    clip: true

                    contentWidth: chart.width
                    contentHeight: chart.height

                    PidThreadsChart {
                        id: chart
                        height: 280
                        width: processModel ? processModel.pidValues.length * 20 : 0

                        pids: processModel ? processModel.pidValues : []
                        threads: processModel ? processModel.threadValues : []
                        names: processModel ? processModel.processNames : []
                    }
                }
            }
        }
    }
}
