import QtQuick 2.15
import QtQuick.Layouts 1.15
import "../components"

Item {
    anchors.fill: parent

    Timer {
        interval: 3000
        running: true
        repeat: true
        onTriggered: {
            backend.updateStats()
            if (processModel)
                processModel.refresh()
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: parent.width < 700 ? 16 : 40
        spacing: parent.width < 700 ? 12 : 20

        RowLayout {
            Layout.fillWidth: true
            spacing: 16

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredWidth: 1
                height: 150
                radius: 12
                color: "#A5D6A7"
                border.color: "#428F44"

                Column {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 6

                    Text { text: "System Info"; font.bold: true; font.pixelSize: 18; color: "#163117" }
                    Text { text: "OS: Fedora Linux Asahi Remix"; color: "#163117" }
                    Text { text: "Kernel: 6.18.15-400"; color: "#163117" }
                    Text { text: "CPU: Apple Blizzard M2"; color: "#163117" }
                    Text { text: "Cores: " + backend.coreCount; color: "#163117" }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredWidth: 1
                height: 150
                radius: 12
                color: "#A5D6A7"
                border.color: "#428F44"

                property var tips: [
                    "Close unused apps to save energy",
                    "Dim your screen to reduce power draw",
                    "Fewer browser tabs = less RAM usage",
                    "Restart weekly to clear memory leaks"
                ]
                property int tipIndex: 0

                Timer {
                    interval: 4000
                    running: true
                    repeat: true
                    onTriggered: parent.tipIndex = (parent.tipIndex + 1) % parent.tips.length
                }

                Column {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 8

                    Text {
                        text: "💡 Tips"
                        font.bold: true
                        font.pixelSize: 18
                        color: "#163117"
                    }

                    Text {
                        id: tipText
                        width: parent.width - 32
                        text: parent.parent.tips[parent.parent.tipIndex]
                        wrapMode: Text.WordWrap
                        color: "#163117"
                        font.pixelSize: 15
                        font.family: "Georgia"
                        font.italic: true

                        Behavior on opacity {
                            NumberAnimation { duration: 300; easing.type: Easing.InOutQuad }
                        }

                        property int watchIndex: parent.parent.tipIndex
                        onWatchIndexChanged: {
                            opacity = 0
                            opacity = 1
                        }
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 190
            radius: 12
            color: "#A5D6A7"
            border.color: "#428F44"

            RowLayout {
                spacing: 40
                anchors.fill: parent
                anchors.margins: 20

                DoughnutStat {
                    Layout.fillWidth: true
                    Layout.maximumWidth: 160
                    Layout.maximumHeight: 160
                    Layout.alignment: Qt.AlignVCenter
                    title: "CPU"
                    value: backend.cpuUsage
                    maxValue: 100
                    unit: "%"
                    color: "#163117"
                }

                DoughnutStat {
                    Layout.fillWidth: true
                    Layout.maximumWidth: 160
                    Layout.maximumHeight: 160
                    Layout.alignment: Qt.AlignVCenter
                    title: "RAM"
                    value: backend.ramUsage
                    maxValue: 100
                    unit: "%"
                    color: "#163117"
                }

                DoughnutStat {
                    Layout.fillWidth: true
                    Layout.maximumWidth: 160
                    Layout.maximumHeight: 160
                    Layout.alignment: Qt.AlignVCenter
                    title: "Processes"
                    value: processModel.pidValues.length
                    maxValue: 500
                    unit: ""
                    color: "#163117"
                }

                DoughnutStat {
                    Layout.fillWidth: true
                    Layout.maximumWidth: 160
                    Layout.maximumHeight: 160
                    Layout.alignment: Qt.AlignVCenter
                    title: "Threads"
                    value: processModel.totalThreads
                    maxValue: 2000
                    unit: ""
                    color: "#163117"
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 12
            color: "#A5D6A7"
            border.color: "#428F44"

            Column {
                anchors.fill: parent
                anchors.margins: 20
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
                    height: parent.height - 44
                    clip: true
                    contentWidth: chart.width
                    contentHeight: chart.height

                    PidThreadsChart {
                        id: chart
                        height: flick.height
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
