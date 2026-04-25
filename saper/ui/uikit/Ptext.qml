import QtQuick

Text {
    id: root

    property int size: 6

    FontLoader {
        id: fontLoader

        source: "fonts/PixelizerBold.ttf"
    }

    font {
        pixelSize: root.size * settingsInteractor.guiMultiply
        family: fontLoader.font.family
    }

    color: "#131e21"
}
