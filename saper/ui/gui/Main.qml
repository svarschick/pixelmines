import QtQuick
import uikit as UiKit

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("saper")

    UiKit.Button {
        textureLeftBorder: textureInteractor.textureButtonLeftBorder
        texturePlash: textureInteractor.textureButtonPlashBorder
        textureRightBorder: textureInteractor.textureButtonRightBorder
    }
}
