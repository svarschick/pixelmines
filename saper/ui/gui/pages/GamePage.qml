import QtQuick
import uikit as UiKit

Item {
    id: root

    Loader {
        anchors.fill: parent

        source: "../component/Board.qml"
    }
}
