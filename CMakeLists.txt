# Reference: http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html

cmake_minimum_required( VERSION 3.0 )

# Add folder where are supportive functions
set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# Include our self-made Qt basic functions
include( QtCommon )

# Basic info about project
# FIXME: make version user-changeable
project( example VERSION 1.0 )

# Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
fix_project_version()

# Set additional project information
set( COMPANY "Example" )
set( COPYRIGHT "Copyright (c) 2014 Vincent Lee. All rights reserved." )
set( IDENTIFIER "com.example.Example" )

# Set project files
# Sources
set( SOURCE_FILES
     src/main.cc
     src/mainwindow.cc
)
# TODO: Headers
# Other files
add_project_meta( META_FILES_TO_INCLUDE )
# Resources
set( RESOURCE_FILES example.qrc )

# Find required libraries
# Qt5 Widgets module
find_package( Qt5Widgets REQUIRED )

# source_group("UI Files" FILES ${UI_FILES})

# Add executable target
# NOTE: OS_BUNDLE expands to WIN32 or MACOS_BUNDLE depending on OS
add_executable( ${PROJECT_NAME} ${OS_BUNDLE}
    ${SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES}
)

qt5_use_modules( ${PROJECT_NAME} Widgets )
