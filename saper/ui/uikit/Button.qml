import QtQuick
import QtQuick.Controls

Item {
    id: root

    required property string texturePlash
    required property string textureLeftBorder
    required property string textureRightBorder

    property real guiMultiply: 1.0

    readonly property real plashWidth: 30 * guiMultiply
    readonly property real minButtonWidth: 20 * guiMultiply
    readonly property real buttonHeight: 10 * guiMultiply
    property real buttonWidth: 20 * guiMultiply

    signal tapped()

    width: Math.max(minButtonWidth, buttonWidth)
    height: buttonHeight

    clip: true

    Image {
        id: leftBorder

        width: buttonHeight
        height: buttonHeight

        anchors.left: parent.left
        anchors.top: parent.top

        source: textureLeftBorder
        smooth: false
        antialiasing: true
    }

    Repeater {
        id: plashBorder

        anchors.left: leftBorder.left
        anchors.top: parent.top

        model: Math.max(0, Math.floor(width - buttonHeight * 2)) / plashWidth + 1
        delegate: Image {
            width: plashWidth
            height: buttonHeight

            source: textureRightBorder
            smooth: false
            antialiasing: true
        }
    }

    Image {
        id: rightBorder

        width: buttonHeight
        height: buttonHeight

        anchors.right: parent.right
        anchors.top: parent.top

        source: textureRightBorder
        smooth: false
        antialiasing: true
    }

    Rectangle {
        id: interact

        color: "white"
        opacity: 0
    }

    TapHandler {
        id: tapHandler

        onPressedChanged: updateInteractOpacity()
        onTapped: root.tapped()
    }

    HoverHandler {
        id: hoverHandler

        onHoveredChanged: updateInteractOpacity()
    }

    function updateInteractOpacity()
    {
        if (tapHandler.pressed)
        {
            interact.opacity = 0.4
        }
        else if (hoverHandler.hovered)
        {
            interact.opacity = 0.2
        }
        else
        {
            interact.opacity = 0
        }
    }
}
