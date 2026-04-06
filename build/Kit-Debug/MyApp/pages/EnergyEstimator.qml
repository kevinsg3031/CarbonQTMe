import QtQuick 2.15
import QtQuick.Layouts 1.15
import "../components"

Item {
    anchors.fill: parent

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 32
        spacing: 32

        Text {
            text: "Energy Estimator"
            font.pixelSize: 26
            font.bold: true
            color: "#163117"
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 24

            ColumnLayout {
                Layout.preferredWidth: parent.width * 0.25
                spacing: 20

                StatCard {
                    title: "CPU Power"
                    value: energyBackend.cpuWatts.toFixed(2) + " W"
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 180
                }

                StatCard {
                    title: "RAM Power"
                    value: energyBackend.ramWatts.toFixed(2) + " W"
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 180
                }
            }

            Rectangle {
                radius: 16
                color: "#A5D6A7"
                border.color: "#428F44"

                Layout.fillWidth: true
                Layout.fillHeight: true

                ColumnLayout {
                    anchors.centerIn: parent
                    spacing: 16

                    Text {
                        text: "Total Power"
                        font.pixelSize: 16
                        color: "#163117"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: energyBackend.totalWatts.toFixed(2) + " W"
                        font.pixelSize: 32
                        font.bold: true
                        color: "#163117"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    RingChart {
                        width: 180
                        height: 180
                        cpuValue: energyBackend.cpuWatts
                        ramValue: energyBackend.ramWatts
                        Layout.alignment: Qt.AlignHCenter
                    }

                    RowLayout {
                        spacing: 16
                        Layout.alignment: Qt.AlignHCenter

                        RowLayout {
                            spacing: 6
                            Rectangle { width: 10; height: 10; radius: 5; color: "#163117" }
                            Text { text: "CPU"; font.pixelSize: 12 }
                        }

                        RowLayout {
                            spacing: 6
                            Rectangle { width: 10; height: 10; radius: 5; color: "#428F44" }
                            Text { text: "RAM"; font.pixelSize: 12 }
                        }
                    }
                }
            }

        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 24

            StatCard {
                title: "Energy Used"
                value: energyBackend.energyJoules.toFixed(3) + " J"
                Layout.fillWidth: true
                Layout.preferredHeight: 150
                // wide: true
            }

            StatCard {
                title: "CO₂ Emissions"
                value: energyBackend.co2.toFixed(6) + " kg"
                Layout.fillWidth: true
                Layout.preferredHeight: 150
                // wide: true
            }
        }
    }
}


