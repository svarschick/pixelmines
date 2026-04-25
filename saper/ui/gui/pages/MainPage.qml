import QtQuick
import uikit as UiKit

Item {
    id: root

    anchors.fill: parent
    anchors.margins: 5 * settingsInteractor.guiMultiply

    Item {
        id: menuSection

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width / 2

        UiKit.PImage  {
            id: logo

            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            source: textureInteractor.logo
            pWidth: 50
            pHeight: 30
        }

        Item {
            id: buttonBlock

            anchors {
                top: logo.bottom
                topMargin: 2 * settingsInteractor.guiMultiply
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }

            Column {
                anchors.centerIn: parent
                spacing: 2 * settingsInteractor.guiMultiply

                UiKit.AdaptiveButton {
                    id: playButton

                    size: 35
                    text: "играть"
                }
                UiKit.AdaptiveButton {
                    id: settingsButton

                    size: 35
                    text: "настройки"
                }
                UiKit.AdaptiveButton {
                    id: exitButton

                    size: 35
                    text: "выход"
                }
            }
        }
    }

    Item {
        id: recordsSection
    }
}
