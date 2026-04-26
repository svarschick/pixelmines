import QtQuick
import uikit as UiKit

Item {
    id: root

    property real dragThreshold: 4

    Item {
        id: viewport

        anchors.fill: parent

        onWidthChanged: minefieldModel.viewportWidth = viewport.width
        onHeightChanged: minefieldModel.viewportHeight = viewport.height

        MouseArea {
            id: mouseArea

            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            preventStealing: true

            property real lastMouseX: 0
            property real lastMouseY: 0
            property real pressX: 0
            property real pressY: 0
            property bool dragged: false
            property int pressedButton: Qt.NoButton

            onPressed: (mouse) => {
                mouseArea.lastMouseX = mouse.x
                mouseArea.lastMouseY = mouse.y
                mouseArea.dragged = false
                mouseArea.pressedButton = mouse.button
            }

            onPositionChanged: (mouse) => {
                if (!(mouse.buttons & Qt.LeftButton))
                {
                    return
                }

                const dx = mouse.x - mouseArea.lastMouseX
                const dy = mouse.y - mouseArea.lastMouseY

                if (!mouseArea.dragged)
                {
                    const travelX = mouse.x - mouseArea.lastMouseX
                    const travelY = mouse.y - mouseArea.lastMouseY
                    mouseArea.dragged = Math.hypot(travelX, travelY) >= root.dragThreshold
                }

                minefieldModel.moveCameraBy(-dx, -dy)

                mouseArea.lastMouseX = mouse.x
                mouseArea.lastMouseY = mouse.y
            }

            onReleased: (mouse) => {
                if (mouseArea.dragged && mouseArea.pressedButton === Qt.LeftButton)
                {
                    mouseArea.pressedButton = Qt.NoButton
                    return
                }

                if (mouseArea.pressedButton === Qt.LeftButton)
                {
                    minefieldModel.leftClickAt(mouse.x, mouse.y)
                }
                else if (pressedButton === Qt.RightButton)
                {
                    minefieldModel.rightClickAt(mouse.x, mouse.y)
                }

                mouseArea.pressedButton = Qt.NoButton
            }
        }

        Item {
            id: board

            x: -minefieldModel.cameraX
            y: -minefieldModel.cameraY
            width: minefieldModel.boardWidth
            height: minefieldModel.boardHeight

            Item {
                id: playground

                anchors.centerIn: parent
                width: minefieldModel.minefieldWidth
                height: minefieldModel.minefieldHeight

                Repeater {
                    model: minefieldModel

                    delegate: Item {
                        required property int xPos
                        required property int yPos
                        required property bool isOpen
                        required property bool isFlagged
                        required property string value
                        required property string textureIndex

                        x: xPos * minefieldModel.cellSize
                        y: yPos * minefieldModel.cellSize
                        width: minefieldModel.cellSize
                        height: minefieldModel.cellSize

                        Rectangle {
                            anchors.fill: parent
                            color: {
                                if (!isOpen)
                                    return isFlagged ? "#c28b39" : "#8b8b8b"
                                if (isMine)
                                    return "#b64a4a"
                                return cellValue === 0 ? "#cfcfcf" : "#dcdcdc"
                            }
                        }

                        Rectangle {
                            anchors.fill: parent

                            border.width: 1
                            border.color: "#131e21"
                        }

                        // Image {
                        //     anchors.fill: parent
                        //     source: textureSource
                        //     fillMode: Image.Stretch
                        //     asynchronous: true
                        //     cache: true
                        // }

                        Text {
                            anchors.centerIn: parent
                            visible: true
                            text: value
                            color: "black"
                            font.pixelSize: Math.max(12, minefieldModel.cellSize * 0.5)
                            font.bold: true
                        }
                    }
                }
            }
        }
    }

    Connections {
        target: settingsInteractor
        function onGuiMultiplyChanged()
        {
            minefieldModel.cellSize = 10 * settingsInteractor.guiMultiply
        }
    }

    Connections {
        target: minefieldModel

        function onFieldGeometryChanged()
        {
            minefieldModel.clampCamera()
        }
    }
}
