import QtQuick
import QtQuick.Controls

Item {
    id: root

    property int from: 0
    property int to: 100
    property int value: 50
    property int stepSize: 1

    property real size: 20

    signal tapped()

    readonly property string leftSliderBorder: textureInteractor.leftSliderBorder
    readonly property string sliderPlash: textureInteractor.sliderPlash
    readonly property string rightSliderBorder: textureInteractor.rightSliderBorder
    readonly property string slider: textureInteractor.slider

    readonly property real plashWidth: 30 * settingsInteractor.guiMultiply
    readonly property real minSliderWidth: 20 * settingsInteractor.guiMultiply
    readonly property real plashHeight: 2 * settingsInteractor.guiMultiply
    readonly property real borderWidth: 10 * settingsInteractor.guiMultiply
    readonly property real sliderHeight: 4 * settingsInteractor.guiMultiply

    readonly property real interestedSliderWidth: root.width - root.borderWidth
    readonly property real position: (root.value - root.from) / (root.to - root.from)

    width: Math.max(root.minSliderWidth, root.size * settingsInteractor.guiMultiply)
    height: root.plashHeight

    Repeater {
        id: plashBorder

        anchors.left: leftBorder.left
        anchors.top: parent.top

        model: Math.max(0, Math.floor(width - root.plashHeight * 2)) / root.plashWidth + 1
        delegate: Image {
            width: root.plashWidth
            height: root.plashHeight

            source: root.sliderPlash
            smooth: false
            antialiasing: true
        }
    }

    Image {
        id: leftBorder

        width: root.borderWidth
        height: root.plashHeight

        anchors.left: parent.left
        anchors.top: parent.top

        source: root.leftSliderBorder
        smooth: false
        antialiasing: true
    }

    Image {
        id: rightBorder

        width: root.borderWidth
        height: root.plashHeight

        anchors.right: parent.right
        anchors.top: parent.top

        source: root.rightSliderBorder
        smooth: false
        antialiasing: true
    }

    Image {
        id: slider

        width: root.borderWidth
        height: root.sliderHeight

        x: clamp(root.position * root.interestedSliderWidth, 0, root.interestedSliderWidth)
        y: (Math.min(root.height, height) - Math.max(root.height, height)) / 2

        source: root.slider
        smooth: false
        antialiasing: true

        Rectangle {
            id: interact

            anchors.fill: parent
            color: "white"
            opacity: 0
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        hoverEnabled: true

        onPressed: (mouse) => {
            updateInteractOpacity()
            root.value = root.valueFromX(mouse.x);
        }

        onPositionChanged: (mouse) => {
            updateInteractOpacity()
            if (pressed)
            {
                root.value = root.valueFromX(mouse.x)
            }
        }

        onReleased: {
            updateInteractOpacity()
            root.tapped()
        }
    }

    HoverHandler {
        id: hoverHandler

        onHoveredChanged: updateInteractOpacity()
    }

    function updateInteractOpacity()
    {
        if (mouseArea.pressed)
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

    function clamp(value, min, max)
    {
        return Math.max(min, Math.min(value, max))
    }

    function valueFromX(x)
    {
        let xClamped = root.clamp(x, root.borderWidth / 2, root.width - root.borderWidth / 2)
        let p = root.clamp((xClamped - root.borderWidth / 2) / root.interestedSliderWidth, 0, 1)
        let raw = root.from + p * (root.to - root.from)

        if (root.stepSize > 0)
        {
            raw = Math.round(raw / root.stepSize) * root.stepSize
        }

        return root.clamp(raw, root.from, root.to)
    }
}
