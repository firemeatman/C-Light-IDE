cmake_minimum_required(VERSION 3.5)

project(C_Light_IDE VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(THIRD_DIR src/third/CodeEditor/codeEditor/)
set(THIRD_CODE_FILES)
file(GLOB THIRD_CODE_FILES ${THIRD_DIR}/*.cpp ${THIRD_DIR}/*.h)


set(Common_Code_Files
    src/common/forceAccess.h src/common/forceAccess.cpp
    src/common/global_data.h src/common/global_data.cpp
    src/common/blockingQueue.h
    src/common/usefulTool.h src/common/usefulTool.cpp

)

set(GUI_Code_Files

    # GUI/component/

    src/GUI/window/mainWindow/mainwindow.h src/GUI/window/mainWindow/mainwindow.cpp src/GUI/window/mainWindow/mainwindow.ui
    src/GUI/window/mainWindow/sideMenu/sideMenuWidget.h src/GUI/window/mainWindow/sideMenu/sideMenuWidget.cpp src/GUI/window/mainWindow/sideMenu/sideMenuWidget.ui
    src/GUI/window/actionWindow/createProjectDialog.h src/GUI/window/actionWindow/createProjectDialog.cpp src/GUI/window/actionWindow/createProjectDialog.ui
    src/GUI/window/actionWindow/createFileDialog.h src/GUI/window/actionWindow/createFileDialog.cpp src/GUI/window/actionWindow/createFileDialog.ui
    src/GUI/window/infoWindow/terminalWidget.h src/GUI/window/infoWindow/terminalWidget.cpp
    src/GUI/window/infoWindow/makeInfoWidget.h src/GUI/window/infoWindow/makeInfoWidget.cpp src/GUI/window/infoWindow/makeInfoWidget.ui

    src/GUI/page/startPage/startPageWidget.h src/GUI/page/startPage/startPageWidget.cpp src/GUI/page/startPage/startPageWidget.ui
    src/GUI/page/startPage/historyListWidget.h src/GUI/page/startPage/historyListWidget.cpp
    src/GUI/page/startPage/historyItemForm.h src/GUI/page/startPage/historyItemForm.cpp src/GUI/page/startPage/historyItemForm.ui

    src/GUI/page/codePage/codePage.h src/GUI/page/codePage/codePage.cpp
    src/GUI/page/codePage/codePageEditWidget.h src/GUI/page/codePage/codePageEditWidget.cpp src/GUI/page/codePage/codePageEditWidget.ui
    src/GUI/page/codePage/codeFileListWidget.h src/GUI/page/codePage/codeFileListWidget.cpp src/GUI/page/codePage/codeFileListWidget.ui
    src/GUI/page/codePage/codeTreeSideWidget.h src/GUI/page/codePage/codeTreeSideWidget.cpp src/GUI/page/codePage/codeTreeSideWidget.ui

)

set(Main_Code_Files
    src/project/projectManager.h src/project/projectManager.cpp
    src/project/project.h src/project/project.cpp
    src/file/editCodeManager.cpp src/file/editCodeManager.h
)

set(PROJECT_SOURCES
        src/main.cpp
        ${Common_Code_Files}
        ${GUI_Code_Files}
        ${Main_Code_Files}

        src/system/codeFileSys.h src/system/codeFileSys.cpp
        src/system/projectSys.h src/system/projectSys.cpp
        src/system/projectConfig.h src/system/projectConfig.cpp
        src/externProcesses/makeProcess.h src/externProcesses/makeProcess.cpp
        src/externProcesses/debuggerProcess.h src/externProcesses/debuggerProcess.cpp
        src/externProcesses/externProcessThread.h src/externProcesses/externProcessThread.cpp
        src/externProcesses/cmakeProcess.h src/externProcesses/cmakeProcess.cpp
        ${THIRD_CODE_FILES}

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(C_Light_IDE
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resource.qrc
        # src/model/historyProjectListModel.h src/model/historyProjectListModel.cpp
        src/model/modelDataDef.h src/model/modelDataDef.cpp
        src/GUI/page/configPage/configerPage.h src/GUI/page/configPage/configerPage.cpp
        src/GUI/page/configPage/buildConfigerForm.h src/GUI/page/configPage/buildConfigerForm.cpp src/GUI/page/configPage/buildConfigerForm.ui

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
