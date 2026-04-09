qt_add_executable(${PROJECT_NAME}
    main.cpp
    app/managers/resource_manager/file_collector/file_hierarchy.h
    app/managers/resource_manager/file_collector/file_hierarchy.cpp
    app/managers/resource_manager/i_update_interactor.h
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::Gui
        Qt6::Quick
        UiKitLib
        GUILib
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

add_subdirectory(app)
add_subdirectory(ui)
