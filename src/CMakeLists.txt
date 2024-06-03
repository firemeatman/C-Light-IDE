cmake_minimum_required(VERSION 3.5)

project(C_Light_IDE VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(THIRD_RESOURCES_FILE

)

set(THIRD_SOURCE_FILES
    third/TreeMenu.h
    third/TreeMenu.cpp
    third/newBulidFile.h third/newBulidFile.cpp
    third/newBuildfolder.h third/newBuildfolder.cpp
)

set(Common_Code_Files
    common/forceAccess.h common/forceAccess.cpp
    common/global_data.h common/global_data.cpp
    common/blockingQueue.h
    common/usefulTool.h common/usefulTool.cpp

)

set(GUI_Code_Files
    GUI/mainwindow.cpp
    GUI/mainwindow.h
    GUI/mainwindow.ui
    GUI/commonWidget/terminalWidget.h GUI/commonWidget/terminalWidget.cpp
    GUI/commonWidget/codeEditor.h GUI/commonWidget/codeEditor.cpp
    GUI/commonWidget/editorSideArea.h GUI/commonWidget/editorSideArea.cpp
    GUI/commonWidget/createProjectDialog.h GUI/commonWidget/createProjectDialog.cpp GUI/commonWidget/createProjectDialog.ui
    GUI/codePage/codeTreeSideWidget.h GUI/codePage/codeTreeSideWidget.cpp GUI/codePage/codeTreeSideWidget.ui
    GUI/codePage/codeFileListWidget.h GUI/codePage/codeFileListWidget.cpp GUI/codePage/codeFileListWidget.ui
    GUI/codePage/codePageEditWidget.h GUI/codePage/codePageEditWidget.cpp GUI/codePage/codePageEditWidget.ui
    GUI/sideMenu/sideMenuWidget.h GUI/sideMenu/sideMenuWidget.cpp GUI/sideMenu/sideMenuWidget.ui
    GUI/startPage/startPageWidget.h GUI/startPage/startPageWidget.cpp GUI/startPage/startPageWidget.ui
    GUI/projectConfigPage/projectConfigSideMenu.h GUI/projectConfigPage/projectConfigSideMenu.cpp GUI/projectConfigPage/projectConfigSideMenu.ui
    GUI/projectConfigPage/projectConfigWidget.h GUI/projectConfigPage/projectConfigWidget.cpp GUI/projectConfigPage/projectConfigWidget.ui
    GUI/projectConfigPage/genBuildConfigWidget.h GUI/projectConfigPage/genBuildConfigWidget.cpp GUI/projectConfigPage/genBuildConfigWidget.ui
    GUI/projectConfigPage/debugConfigWidget.h GUI/projectConfigPage/debugConfigWidget.cpp GUI/projectConfigPage/debugConfigWidget.ui
    GUI/infoWindow/makeInfoWidget.h GUI/infoWindow/makeInfoWidget.cpp GUI/infoWindow/makeInfoWidget.ui
)

set(Model_Code_Files
    project/projectManager.h project/projectManager.cpp
    project/project.h project/project.cpp
)

set(PROJECT_SOURCES
        main.cpp
        ${Common_Code_Files}
        ${GUI_Code_Files}
        ${Model_Code_Files}

        system/codeFileSys.h system/codeFileSys.cpp
        system/projectSys.h system/projectSys.cpp
        system/projectConfig.h system/projectConfig.cpp
        externProcesses/makeProcess.h externProcesses/makeProcess.cpp
        externProcesses/debuggerProcess.h externProcesses/debuggerProcess.cpp
        externProcesses/externProcessThread.h externProcesses/externProcessThread.cpp
        externProcesses/cmakeProcess.h externProcesses/cmakeProcess.cpp
        ${THIRD_RESOURCES_FILE}
        ${THIRD_SOURCE_FILES}

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(C_Light_IDE
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET C_Light_IDE APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(C_Light_IDE SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(C_Light_IDE
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(C_Light_IDE PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(C_Light_IDE PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS C_Light_IDE
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(C_Light_IDE)
endif()
