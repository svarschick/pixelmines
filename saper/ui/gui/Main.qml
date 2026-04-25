import QtQuick
import uikit as UiKit

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("saper")

    Image {
        id: bg

        anchors.fill: parent
        source: textureInteractor.bg01
        fillMode: Image.PreserveAspectCrop

        Rectangle {
            id: darkness

            color: "black"
            anchors.fill: parent
            opacity: 0.5
        }
    }

    Loader {
        anchors.fill: parent

        source: "pages/MainPage.qml"
    }
}
