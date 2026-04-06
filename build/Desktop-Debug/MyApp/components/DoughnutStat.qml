import QtQuick 2.15

Item {
    id: root

    property string title: ""
    property real value: 0
    property real maxValue: 100
    property string unit: "%"
    property color color: "#4CAF50"

    width: 150
    height: 150

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {

            var ctx = getContext("2d")
            ctx.clearRect(0,0,width,height)

            var centerX = width/2
            var centerY = height/2
            var radius = width/2 - 10

            var start = -Math.PI/2
            var end = start + (value/maxValue) * Math.PI * 2

            // background ring
            ctx.beginPath()
            // ctx.strokeStyle = "#e0e0e0"
            ctx.strokeStyle = "#DEF0DE"
            ctx.lineWidth = 12
            ctx.arc(centerX, centerY, radius, 0, Math.PI*2)
            ctx.stroke()

            // value arc
            ctx.beginPath()
            ctx.strokeStyle = root.color
            ctx.lineWidth = 12
            ctx.arc(centerX, centerY, radius, start, end)
            ctx.stroke()
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 2

        Text {
            text: Math.round(root.value) + root.unit
            font.pixelSize: 20
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            text: root.title
            font.pixelSize: 12
            // color: "#555"
            color: "black"
            horizontalAlignment: Text.AlignHCenter
        }
    }

    onValueChanged: canvas.requestPaint()
    Component.onCompleted: canvas.requestPaint()
}
