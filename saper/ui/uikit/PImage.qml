import QtQuick

Image {
    id: root

    property int pWidth: 0
    property int pHeight: 0

    width: root.pWidth * settingsInteractor.guiMultiply
    height: root.pHeight * settingsInteractor.guiMultiply

    smooth: false
    antialiasing: true
}
