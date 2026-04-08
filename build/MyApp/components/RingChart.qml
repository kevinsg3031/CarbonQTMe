import QtQuick 2.15

Item {
    id: root
    width: 160
    height: 160

    property real cpuValue: 0
    property real ramValue: 0

    readonly property real total: cpuValue + ramValue

    onCpuValueChanged: canvas.requestPaint()
    onRamValueChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)

            if (root.total <= 0)
                return

            var centerX = width / 2
            var centerY = height / 2
            var lineWidth = 18
            var padding = lineWidth / 2 + 6
            var radius = Math.min(width, height) / 2 - padding

            var startAngle = -Math.PI / 2
            var cpuAngle = (cpuValue / total) * Math.PI * 2
            var ramAngle = (ramValue / total) * Math.PI * 2

            ctx.lineWidth = lineWidth
            ctx.lineCap = "round"

            // CPU
            ctx.beginPath()
            ctx.strokeStyle = "#163117"
            ctx.arc(centerX, centerY, radius, startAngle, startAngle + cpuAngle)
            ctx.stroke()

            // RAM
            ctx.beginPath()
            ctx.strokeStyle = "#428F44"
            ctx.arc(centerX, centerY, radius,
                    startAngle + cpuAngle,
                    startAngle + cpuAngle + ramAngle)
            ctx.stroke()
        }
    }
}
