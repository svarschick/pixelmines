qt_add_library(GUILib STATIC)

set_target_properties(GUILib PROPERTIES AUTOMOC ON)
target_link_libraries(GUILib PRIVATE Qt6::Gui Qt6::Quick)

list(APPEND GUI_QML_FILES
    Main.qml
)

qt_add_qml_module(GUILib
    URI gui
    VERSION 1.0
    RESOURCE_PREFIX /gui/qml
    NO_PLUGIN
    TYPEINFO GUI.qmltypes
    QML_FILES
        ${GUI_QML_FILES}
)
