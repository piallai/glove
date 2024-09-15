# 
# This file is part of the Glove distribution (https://github.com/piallai/glove).
# Copyright (C) 2024 Pierre Allain.
# 
# This program is free software: you can redistribute it and/or modify  
# it under the terms of the GNU General Public License as published by  
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License 
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.0.0)

PROJECT(Glove VERSION 0.7.2
        DESCRIPTION "A Qt C++ library for simple GUI")

message(STATUS "Glove " ${PROJECT_VERSION})

# Configure Glove options header
option(OPTION_ENABLE_SLV_QT_PROGRESS "Needed to enable qt in Sleeve library and provide progress management classes. Setting OFF will disable tracking of progress. Disabled if Qt is not found." ON)
option(OPTION_USE_THIRDPARTY_JSON "Use json library." ON)
option(OPTION_USE_BOOST "Enable default management of boost containers with GCC and Clang (nested containers management)." OFF)
option(OPTION_STD_BREAK_THROW_EXCEPTION "Throws std::runtime_error when using slv::flag::BREAK" ON)
option(OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER "Examples to be compiled with the merged library as a single header." OFF)
option(OPTION_QT6 "Use Qt6. If ON, minimal C++ version is 17" OFF)
set(OPTION_CXX "11" CACHE STRING "C++ version.")
set_property(CACHE OPTION_CXX PROPERTY STRINGS 11 14 17 20)

if (OPTION_QT6)
set(QT_VERSION_MAJOR "6")
else()
set(QT_VERSION_MAJOR "5")
endif()

# Find the QtWidgets library
find_package(Qt${QT_VERSION_MAJOR}Widgets)

if (Qt${QT_VERSION_MAJOR}Widgets_FOUND)
set(USE_QT ON)
find_package(Qt${QT_VERSION_MAJOR}PrintSupport REQUIRED)
else()
set(USE_QT OFF)
set(OPTION_ENABLE_SLV_QT_PROGRESS OFF)
endif()

include("${${PROJECT_NAME}_SOURCE_DIR}/CMake/options.txt")

configure_file (
  "src/GloveOptions.h.in"
  "${PROJECT_BINARY_DIR}/GloveOptions.h"
)

configure_file (
  "src/GloveVersion.h.in"
  "${PROJECT_BINARY_DIR}/GloveVersion.h"
)

###QT####
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
IF(UNIX)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
ENDIF()
#########

if (OPTION_QT6 AND (${OPTION_CXX} STREQUAL "11" OR ${OPTION_CXX} STREQUAL "14"))
message(STATUS "Using Qt6 : C++ is set to 17 instead of " ${OPTION_CXX})
set(OPTION_CXX "17")
endif()
set(CMAKE_CXX_STANDARD ${OPTION_CXX})

# For examples
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
	add_definitions(-DUSE_OMP)
endif()

if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

IF(MSVC)
add_definitions(/bigobj)
add_definitions(/MP4)#parallel compilation of files
add_compile_options(/wd4250)#Ignore inheritance via dominance warning
add_compile_options(/wd4100)#Ignore unreferenced formal parameter
add_compile_options(/W4)#Ignore inheritance via dominance warning
add_compile_options(/Zc:__cplusplus)#Enable __cplusplus macro
#add_compile_options(/Zc:preprocessor)#Set _MSVC_TRADITIONAL to 0
if (OPTION_QT6)
add_compile_options(/permissive-)
endif()
ENDIF()

if(UNIX AND NOT CMAKE_BUILD_TYPE)
SET(CMAKE_BUILD_TYPE Release)#set default build tpye to release
endif()
message(STATUS "CMAKE_BUILD_TYPE " ${CMAKE_BUILD_TYPE})

SET(CMAKE_VERBOSE_MAKEFILE True)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/samples)

if(OPTION_USE_THIRDPARTY_JSON)
add_subdirectory(thirdParty/json)
endif()
add_subdirectory(src)

add_subdirectory(doc/readme)

add_custom_target(_Config ALL 
    SOURCES
	CMake/options.txt
    src/GloveVersion.h.in
    src/GloveOptions.h.in
)

if(Qt5Widgets_FOUND)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sample001)
endif()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if(WIN32)
        set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation directory" FORCE)
    else()
        set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Installation directory" FORCE)
    endif()
endif()

message(STATUS "CMAKE_INSTALL_PREFIX " ${CMAKE_INSTALL_PREFIX})

##############################################################################
install(TARGETS Sleeve CONFIGURATIONS Release DESTINATION "lib/glove")
if(USE_QT)
install(TARGETS Glove CONFIGURATIONS Release DESTINATION "lib/glove")
install(TARGETS GloveAdd CONFIGURATIONS Release DESTINATION "lib/glove")
endif()

install(TARGETS Sleeve CONFIGURATIONS Debug DESTINATION "lib/glove")
if(USE_QT)
install(TARGETS Glove CONFIGURATIONS Debug DESTINATION "lib/glove")
install(TARGETS GloveAdd CONFIGURATIONS Debug DESTINATION "lib/glove")
endif()

install(DIRECTORY "${CMAKE_SOURCE_DIR}/src/src_sleeve/"
    DESTINATION "include/glove/sleeve"
    FILES_MATCHING
    PATTERN "*.h")

if(USE_QT)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/src/src_glove/"
    DESTINATION "include/glove/glove"
    FILES_MATCHING
    PATTERN "*.h")

install(DIRECTORY "${CMAKE_SOURCE_DIR}/src/src_glove_add/"
    DESTINATION "include/glove/glove_add"
    FILES_MATCHING
    PATTERN "*.h")
endif()
	
install(FILES "${PROJECT_BINARY_DIR}/GloveOptions.h"
    DESTINATION "include/glove/sleeve"
	)

install(FILES "${PROJECT_BINARY_DIR}/GloveVersion.h"
    DESTINATION "include/glove/sleeve"
	)

if(OPTION_USE_THIRDPARTY_JSON)
install(FILES "${CMAKE_SOURCE_DIR}/thirdParty/json/json.hpp"
    DESTINATION "include/glove/thirdParty"
	)
endif()
##############################################################################

