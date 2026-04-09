qt_add_library(UiKitLib STATIC)

set_target_properties(UiKitLib PROPERTIES AUTOMOC ON)
target_link_libraries(UiKitLib PRIVATE Qt6::Gui Qt6::Quick)

list(APPEND UIKIT_QML_FILES
    Button.qml
)

qt_add_qml_module(UiKitLib
    URI uikit
    VERSION 1.0
    RESOURCE_PREFIX /uikit/qml
    NO_PLUGIN
    TYPEINFO UiKit.qmltypes
    QML_FILES
        ${UIKIT_QML_FILES}
)
