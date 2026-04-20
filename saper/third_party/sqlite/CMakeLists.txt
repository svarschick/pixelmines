cmake_minimum_required(VERSION 3.16)
project(sqlite)

add_library(${PROJECT_NAME} SHARED sqlite3.c)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME sqlite3)
