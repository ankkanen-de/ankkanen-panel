cmake_minimum_required(VERSION 3.5)

project(ankkanen-panel VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(LayerShellQt REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(FOREIGN_TOPLEVEL_MANAGEMENT REQUIRED qt6-foreign-toplevel-management)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainmenu.cpp
        src/taskbutton.cpp
        src/desktopentry.cpp
        src/applicationmodel.cpp

        src/include/mainwindow.hpp
        src/include/mainmenu.hpp
        src/include/taskbutton.hpp
        src/include/desktopentry.hpp
        src/include/applicationmodel.hpp

        src/ui/mainwindow.ui
        src/ui/mainmenu.ui
)

qt_add_executable(ankkanen-panel
    ${PROJECT_SOURCES}
)

target_link_libraries(ankkanen-panel PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    LayerShellQt::Interface
    ${FOREIGN_TOPLEVEL_MANAGEMENT_LIBRARIES})

target_include_directories(ankkanen-panel PRIVATE
    src/include)

include(GNUInstallDirs)
install(TARGETS ankkanen-panel
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
