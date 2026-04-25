import QtQuick

Item {
    id: root

    enum Direction
    {
        Left,
        Right
    }

    readonly property real buttonSize: 10 * settingsInteractor.guiMultiply
    property int direction: DirectionButton.Direction.Left

    signal tapped()

    width: buttonSize
    height: buttonSize
    clip: true

    Image {
        width: buttonSize
        height: buttonSize

        anchors.left: parent.left
        anchors.top: parent.top

        source: root.getCurrentTexture()
        smooth: false
        antialiasing: true
    }

    Rectangle {
        id: interact

        anchors.fill: parent
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
            interact.opacity = 0.2
        }
        else if (hoverHandler.hovered)
        {
            interact.opacity = 0.1
        }
        else
        {
            interact.opacity = 0
        }
    }

    function getCurrentTexture()
    {
        switch(root.direction)
        {
        case DirectionButton.Direction.Left:
            return textureInteractor.leftButton;
        case DirectionButton.Direction.Right:
            return textureInteractor.rightButton;
        }
    }
}
