import QtQuick 2.15
import QtQuick.Layouts 1.15

Text {
    property alias text: label.text

    id: label
    font.pixelSize: 14
    font.bold: true
    color: "#428F44"
}
