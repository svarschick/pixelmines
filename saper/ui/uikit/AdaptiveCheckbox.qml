import QtQuick
import QtQuick.Controls

Item {
    id: root

    property real size: 10
    property bool selected: false

    readonly property string selectedCheckbox: textureInteractor.selectedCheckbox
    readonly property string unselectedCheckbox: textureInteractor.unselectedCheckbox

    readonly property real buttonHeight: root.size * settingsInteractor.guiMultiply

    width: root.buttonHeight
    height: root.buttonHeight

    Image {
        id: image

        width: buttonHeight
        height: buttonHeight

        anchors.left: parent.left
        anchors.top: parent.top

        source: root.selected ? root.selectedCheckbox : root.unselectedCheckbox
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
        onTapped: root.selected = !root.selected
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
