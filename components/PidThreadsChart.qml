import QtQuick 2.15

Item {
    id: root

    property var pids: []
    property var threads: []
    property var names: []

    property int hoveredIndex: -1

    // padding for chart area
    property int leftPadding: 10
    property int rightPadding: 10
    property int topPadding: 20
    property int bottomPadding: 30

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {

            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)

            if (!threads || threads.length === 0)
                return

            var usableWidth = width - leftPadding - rightPadding
            var usableHeight = height - topPadding - bottomPadding

            var maxThreads = Math.max(...threads)
            var stepX = usableWidth / Math.max(threads.length, 1)

            // draw baseline axis
            // ctx.strokeStyle = "#cccccc"
            ctx.strokeStyle = "black"
            ctx.lineWidth = 1
            ctx.beginPath()
            ctx.moveTo(leftPadding, height - bottomPadding)
            ctx.lineTo(width - rightPadding, height - bottomPadding)
            ctx.stroke()

            for (var i = 0; i < threads.length; i++) {

                var normalized = threads[i] / Math.max(maxThreads, 1)

                var x = leftPadding + i * stepX + stepX / 2

                var y = topPadding + usableHeight -
                        (normalized * usableHeight)

                // vertical line
                ctx.strokeStyle = "#4CAF50"
                ctx.lineWidth = 2

                ctx.beginPath()
                ctx.moveTo(x, height - bottomPadding)
                ctx.lineTo(x, y)
                ctx.stroke()

                // point
                ctx.beginPath()
                ctx.fillStyle = (i === hoveredIndex)
                                ? "#FF5722"
                                : "#2E7D32"

                ctx.arc(x, y, 4, 0, Math.PI * 2)
                ctx.fill()
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onPositionChanged: {
            if (!threads || threads.length === 0)
                return

            var usableWidth = width - leftPadding - rightPadding
            var stepX = usableWidth / Math.max(threads.length, 1)

            var index = Math.floor(
                (mouse.x - leftPadding) / stepX
            )

            if (index >= 0 && index < threads.length)
                root.hoveredIndex = index
            else
                root.hoveredIndex = -1
            canvas.requestPaint()
        }

        onExited: {
            root.hoveredIndex = -1
            canvas.requestPaint()
        }
    }

    // TOOLTIP
    Rectangle {
        id: tooltip
        visible: root.hoveredIndex >= 0
        color: "#333333"
        radius: 6
        opacity: 0.95
        border.color: "#555"
        border.width: 1

        property real usableWidth: root.width - root.leftPadding - root.rightPadding
        property real usableHeight: root.height - root.topPadding - root.bottomPadding
        property real stepX: usableWidth / Math.max(root.threads.length, 1)

        property real pointX:
            root.leftPadding +
            root.hoveredIndex * stepX +
            stepX / 2

        property real maxThreads:
            root.threads.length > 0
            ? Math.max(...root.threads)
            : 1

        property real normalized:
            root.hoveredIndex >= 0
            ? root.threads[root.hoveredIndex] / maxThreads
            : 0

        property real pointY:
            root.topPadding +
            usableHeight -
            (normalized * usableHeight)

        width: tooltipText.width + 16
        height: tooltipText.height + 12

        x: Math.max(
               0,
               Math.min(
                   pointX - width / 2,
                   root.width - width
               )
           )

        y: {
            var preferred = pointY - height - 8
            if (preferred < 0)
                return pointY + 8
            return preferred
        }

        Text {
            id: tooltipText
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: 12

            text:
                root.hoveredIndex >= 0 ?
                "Name: " + root.names[root.hoveredIndex] +
                "\nPID: " + root.pids[root.hoveredIndex] +
                "\nThreads: " + root.threads[root.hoveredIndex]
                : ""
        }
    }

    onThreadsChanged: canvas.requestPaint()
    Component.onCompleted: canvas.requestPaint()
}
