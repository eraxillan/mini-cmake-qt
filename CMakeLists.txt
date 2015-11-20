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

option( UPDATE_TRANSLATIONS "Update translations on compile" OFF )
message( STATUS "Update translations on compile: ${UPDATE_TRANSLATIONS}" )

# Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
fix_project_version()

# Set additional project information
set( COMPANY "Example" )
set( COPYRIGHT "Copyright (c) 2014 Vincent Lee. All rights reserved." )
set( IDENTIFIER "com.example.Example" )

###############################################################################

# Find required libraries
# Qt5 Widgets module
find_package( Qt5Widgets REQUIRED )
# TODO: other Qt5 modules goes here

message( STATUS "Found Qt ${Qt5Widgets_VERSION_STRING}" )

# FIX: Qt was built with -reduce-relocations
if( Qt5_POSITION_INDEPENDENT_CODE )
    set( CMAKE_POSITION_INDEPENDENT_CODE ON )
endif()

# Localization stuff
find_package( Qt5LinguistTools )
if( UPDATE_TRANSLATIONS )
    if( NOT Qt5_LUPDATE_EXECUTABLE )
        message( FATAL_ERROR "Qt's lupdate utility not found! Aborting" )
    endif()
endif()

if( NOT Qt5_LRELEASE_EXECUTABLE )
    message( FATAL_ERROR "Qt's lrelease utility not found! Aborting" )
endif()

###############################################################################

# Set project files
# Sources
set( SOURCE_FILES
     src/main.cc
     src/mainwindow.cc
)

# Translations
if( UPDATE_TRANSLATIONS )
    file( GLOB_RECURSE translate_SRCS ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.cc ${CMAKE_SOURCE_DIR}/src/*.cxx
                                      ${CMAKE_SOURCE_DIR}/src/*.h ${CMAKE_SOURCE_DIR}/src/*.hpp ${CMAKE_SOURCE_DIR}/src/*.hxx )
    file( GLOB_RECURSE translate_UIS  ${CMAKE_SOURCE_DIR}/src/*.ui )
    set( translate_SRCS ${translate_SRCS} ${translate_UIS} )

    # TODO: other languages goes here
    set( TRANSLATION_FILES "${CMAKE_CURRENT_SOURCE_DIR}/translations/example_en.ts"
                           "${CMAKE_CURRENT_SOURCE_DIR}/translations/example_ru.ts" )
    qt5_create_translation( TRANSLATION_BINARY_FILES ${translate_SRCS} ${TRANSLATION_FILES} )
else()
    file( GLOB TRANSLATION_FILES "${CMAKE_CURRENT_SOURCE_DIR}/translations/*.ts" )
    qt5_add_translation( TRANSLATION_BINARY_FILES ${TRANSLATION_FILES})
endif()

# TODO: Headers
# Other files
add_project_meta( META_FILES_TO_INCLUDE )
# Resources
set( RESOURCE_FILES example.qrc )

# source_group("UI Files" FILES ${UI_FILES})

# Add executable target
# NOTE: OS_BUNDLE expands to WIN32 or MACOS_BUNDLE depending on OS
add_executable( ${PROJECT_NAME} ${OS_BUNDLE}
    ${SOURCE_FILES}
    ${META_FILES_TO_INCLUDE}
    ${RESOURCE_FILES}
    ${TRANSLATION_BINARY_FILES}
)

qt5_use_modules( ${PROJECT_NAME} Widgets )
