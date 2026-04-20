qt_add_executable(${PROJECT_NAME}
    main.cpp
    app/managers/sql_manager/sql_manager.h
    app/managers/sql_manager/sql_handler.h
    app/managers/sql_manager/sql_query.h
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::Gui
        Qt6::Quick
        UiKitLib
        GUILib
        sqlite
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

add_subdirectory(third_party)
add_subdirectory(app)
add_subdirectory(ui)
