cmake_minimum_required(VERSION 3.16)

project(CarMaintenanceScheduler VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include Qt Widgets, SQL, and Network modules
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Network)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    animatedbackground.cpp
    animatedbackground.h

    smtp.cpp
    smtp.h

    loginwindow.cpp        # <-- ADDED
    loginwindow.h          # <-- ADDED
    loginwindow.ui         # <-- ADDED

    signupwindow.cpp       # <-- ADDED
    signupwindow.h         # <-- ADDED
    signupwindow.ui        # <-- ADDED
)

# Create executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CarMaintenanceScheduler
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(CarMaintenanceScheduler
        ${PROJECT_SOURCES}
    )
endif()

# Link Widgets, SQL, Network
target_link_libraries(CarMaintenanceScheduler
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    PRIVATE Qt${QT_VERSION_MAJOR}::Sql
    PRIVATE Qt${QT_VERSION_MAJOR}::Network
)

# Bundle settings
set_target_properties(CarMaintenanceScheduler PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CarMaintenanceScheduler
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Required for Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CarMaintenanceScheduler)
endif()



