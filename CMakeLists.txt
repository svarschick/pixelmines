cmake_minimum_required(VERSION 3.16)

project(saper)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

add_subdirectory(saper)

set(QML_IMPORT_PATH
    ${CMAKE_BINARY_DIR}/saper/ui
    ${CMAKE_BINARY_DIR}/saper/gui
    CACHE STRING "QML import paths for Qt Creator"
)
