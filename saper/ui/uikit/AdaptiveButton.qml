import QtQuick
import QtQuick.Controls
import uikit as UiKit

Item {
    id: root

    property int  size: 20
    property bool selectedMode: false
    property bool selected: true
    property string text: ""

    readonly property string leftBorder: selected ? textureInteractor.buttonLeft : textureInteractor.unselectedButtonLeftBorder
    readonly property string plash: selected ? textureInteractor.buttonPlash : textureInteractor.unselectedButtonPlash
    readonly property string rightBorder: selected ? textureInteractor.buttonRight : textureInteractor.unselectedButtonRightBorder

    readonly property real plashWidth: 30
    readonly property real minButtonWidth: 20
    readonly property real buttonHeight: 10
    property real buttonWidth: root.size * settingsInteractor.guiMultiply

    signal tapped()

    width: Math.max(minButtonWidth, buttonWidth)
    height: buttonHeight * settingsInteractor.guiMultiply

    clip: true

    Repeater {
        id: plashBorder

        anchors.left: leftBorder.left
        anchors.top: parent.top

        model: Math.max(0, Math.floor(root.width - buttonHeight * 2)) / plashWidth + 1
        delegate: UiKit.PImage {
            pWidth: root.plashWidth
            pHeight: root.buttonHeight
            source: root.plash
        }
    }

    UiKit.PImage {
        id: leftBorder

        pWidth: root.buttonHeight
        pHeight: root.buttonHeight

        anchors.left: parent.left
        anchors.top: parent.top

        source: root.leftBorder
    }

    UiKit.PImage {
        id: rightBorder

        pWidth: root.buttonHeight
        pHeight: root.buttonHeight

        anchors.right: parent.right
        anchors.top: parent.top

        source: root.rightBorder
    }

    UiKit.PText {
        anchors.centerIn: parent
        text: root.text
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
        onTapped: {
            if (selectedMode)
            {
                selected = !selected
            }

            root.tapped()
        }
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
}
