cmake_minimum_required(VERSION 3.16)

project(TelemetryAndDiagnosticsProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp



)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TelemetryAndDiagnosticsProject
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        qcguagewidget.h
        qcguagewidget.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        Battery.cpp
        common.cpp
        Diagnostics.cpp
        Ecu.cpp
        Logger.cpp
        RadarSensor.cpp
        Rpi_Connection.cpp
        Rpm.cpp
        SpeedSensor.cpp
        TempSesnor.cpp
        Battery.hpp
        common.hpp
        Diagnostics.hpp
        Ecu.hpp
        Logger.hpp
        RadarSensor.hpp
        Rpi_Connection.hpp
        Rpm.hpp
        Sensor.hpp
        SpeedSensor.hpp
        TempSesnor.hpp

        temperror.h temperror.cpp temperror.ui
        distanceerror.h distanceerror.cpp distanceerror.ui
        batteryerror.h batteryerror.cpp batteryerror.ui
        speederror.h speederror.cpp speederror.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TelemetryAndDiagnosticsProject APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TelemetryAndDiagnosticsProject SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TelemetryAndDiagnosticsProject
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TelemetryAndDiagnosticsProject PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TelemetryAndDiagnosticsProject)
endif()
set_target_properties(TelemetryAndDiagnosticsProject PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TelemetryAndDiagnosticsProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TelemetryAndDiagnosticsProject)
endif()
