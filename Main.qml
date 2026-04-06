import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "components"
import "pages"

ApplicationWindow {
    visible: true
    width: 1100
    height: 700
    title: "CarbonQt"
    flags: Qt.Window

    color: "#DEF0DE"

    property int currentIndex: 0

    RowLayout {
        anchors.fill: parent

        // Sidebar
        Rectangle {
            Layout.minimumWidth: 180
            Layout.preferredWidth: 220
            Layout.maximumWidth: 260
            Layout.fillHeight: true
            color: "#A5D6A7"

            Column {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 16

                Text {
                    text: "🌱 CarbonQt"
                    font.pixelSize: 22
                    font.bold: true
                    color: "#163117"
                }

                Rectangle { height: 1; width: parent.width; color: "#428F44" }

                SidebarButton { text: "Dashboard"; active: currentIndex === 0; onClicked: currentIndex = 0 }
                SidebarButton { text: "Processes"; active: currentIndex === 1; onClicked: currentIndex = 1 }
                SidebarButton { text: "Energy Estimator"; active: currentIndex === 2; onClicked: currentIndex = 2 }
            }
        }

        // Main content
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#DEF0DE"

            Loader {
                anchors.fill: parent
                sourceComponent: currentIndex === 0 ? dashboard :
                                 currentIndex === 1 ? processes :
                                 threads
            }

            Component { id: dashboard; Dashboard {} }
            Component { id: processes; Processes {} }
            Component { id: threads; EnergyEstimator {} }
        }
    }
}


