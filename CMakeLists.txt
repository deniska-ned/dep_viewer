cmake_minimum_required(VERSION 3.5)

project(dep_viewer LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)


add_subdirectory(
        libs/pugixml/
)


add_executable(dep_viewer
        src/main.cpp

        src/base_classes/base_manager.h
        src/base_classes/base_loader.h
        src/base_classes/base_command.h
        src/base_classes/base_command.cpp

        src/cmdhistory/cmdhistory_manager.h
        src/cmdhistory/cmdhistory_manager.cpp
        src/cmdhistory/cmdhistory_manager_creator.h
        src/cmdhistory/cmdhistory_manager_creator.cpp

        src/cmds/new_file_command.h
        src/cmds/new_file_command.cpp
        src/cmds/load_command.h
        src/cmds/load_command.cpp
        src/cmds/update_command.h
        src/cmds/update_command.cpp
        src/cmds/save_command.h
        src/cmds/save_command.cpp
        src/cmds/save_as_command.h
        src/cmds/save_as_command.cpp
        src/cmds/undo_command.h
        src/cmds/undo_command.cpp
        src/cmds/redo_command.h
        src/cmds/redo_command.cpp
        src/cmds/showdata_command.h
        src/cmds/showdata_command.cpp

        src/dep/employment.h
        src/dep/employment.cpp
        src/dep/department.hpp
        src/dep/department.cpp
        src/dep/department_manager.h
        src/dep/department_manager.cpp
        src/dep/department_manager_creator.h
        src/dep/department_manager_creator.cpp

        src/exceptions/errors.hpp

        src/gui/i_tableowner.h
        src/gui/mainwindow.h
        src/gui/mainwindow.cpp
        src/gui/mainwindow.ui
        src/gui/treeitem.h
        src/gui/treeitem.cpp
        src/gui/treemodel.h
        src/gui/treemodel.cpp

        src/loading/load_manager.h
        src/loading/load_manager.cpp
        src/loading/load_manager_creator.h
        src/loading/load_manager_creator.cpp
        src/loading/pugixml_loader_adapter.h
        src/loading/pugixml_loader_adapter.cpp
        )

target_include_directories(dep_viewer PUBLIC
        src/
        src/base_classes/
        src/cmdhistory/
        src/cmds/
        src/dep/
        src/exceptions/
        src/gui/
        src/loading/
        )

target_link_libraries(dep_viewer PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        pugixml
        )
