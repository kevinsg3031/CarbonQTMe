import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../components"

Item {
    anchors.fill: parent
    property int colPid: 80
    property int colName: 1        // flexible column
    property int colCpu: 100
    property int colMem: 120
    property int colThreads: 100


    ColumnLayout {
        anchors.fill: parent
        anchors.margins: width < 700 ? 16 : 32
        spacing: 20

        // ===== Page Title =====
        Text {
            text: "Processes"
            font.pixelSize: 26
            font.bold: true
            color: "#163117"
        }

        // ===== Toolbar =====
        RowLayout {
            Layout.fillWidth: true
            spacing: 12

            TextField {
                id: searchField
                Layout.fillWidth: true
                height: 46
                font.pixelSize: 16

                leftPadding: 14
                rightPadding: 14
                topPadding: 10
                bottomPadding: 10

                placeholderText: "Search process..."
                placeholderTextColor: "#7A9A7A"
                color: "#163117"

                onTextChanged: processModel.setFilter(text)

                background: Rectangle {
                    radius: 8
                    color: "white"
                }
            }

            Button {
                id: refreshButton
                width: 46
                height: 46

                leftPadding: 10
                rightPadding: 10
                topPadding: 10
                bottomPadding: 10

                icon.source: "qrc:/qt/qml/MyApp/assets/icons/refresh.svg"
                icon.width: 18
                icon.height: 18

                onClicked: processModel.refresh()

                background: Rectangle {
                    radius: width/2
                    color: refreshButton.hovered ? "white" : "transparent"
                }
            }
        }

        // ===== Table Card =====
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 14
            color: "white"
            border.color: "#DEF0DE"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 0

                // ===== Table Header =====
                Rectangle {
                    Layout.fillWidth: true
                    height: 40
                    color: "#F3FBF3"

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 8
                        spacing: 12

                        TableHeader { text: "PID"; Layout.preferredWidth: colPid }
                        TableHeader { text: "Name"; Layout.fillWidth: true }
                        TableHeader { text: "CPU %"; Layout.preferredWidth: colCpu; horizontalAlignment: Text.AlignRight }
                        TableHeader { text: "Memory"; Layout.preferredWidth: colMem; horizontalAlignment: Text.AlignRight }
                        TableHeader { text: "Threads"; Layout.preferredWidth: colThreads; horizontalAlignment: Text.AlignRight }
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    height: 1
                    color: "#DEF0DE"
                }

                // ===== List =====
                ListView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true
                    model: processModel

                    delegate: Rectangle {
                        width: ListView.view.width
                        height: 44
                        color: mouse.containsMouse ? "#F4FBF4" : "transparent"

                        MouseArea {
                            id: mouse
                            anchors.fill: parent
                            hoverEnabled: true
                        }

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 8
                            spacing: 12

                            Text { text: pid; Layout.preferredWidth: colPid }

                            Text {
                                text: name
                                Layout.fillWidth: true
                                elide: Text.ElideRight
                            }

                            Text {
                                text: cpu.toFixed(1)
                                Layout.preferredWidth: colCpu
                                horizontalAlignment: Text.AlignRight
                            }

                            Text {
                                text: memory.toFixed(0) + " MB"
                                Layout.preferredWidth: colMem
                                horizontalAlignment: Text.AlignRight
                            }

                            Text {
                                text: threads
                                Layout.preferredWidth: colThreads
                                horizontalAlignment: Text.AlignRight
                            }
                        }

                        Rectangle {
                            anchors.bottom: parent.bottom
                            height: 1
                            width: parent.width
                            color: "#EEF6EE"
                        }
                    }
                }
            }
        }
    }
}

