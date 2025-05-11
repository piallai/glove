# 
# This file is part of the Glove distribution (https://github.com/piallai/glove).
# Copyright (C) 2024 - 2025 Pierre Allain.
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

PROJECT(Example)

cmake_minimum_required(VERSION 3.0.0)

option(OPTION_SINGLE_HEADER "Use single header (ON) or installed library (OFF)." ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake/CMakeModules")

if(COMMAND cmake_policy)
   cmake_policy(SET CMP0074 NEW)
endif(COMMAND cmake_policy)

SET(CMAKE_VERBOSE_MAKEFILE True)

set(PROJECT_SOURCES
	main.cpp
)

if(OPTION_SINGLE_HEADER)
add_compile_options(-DOPTION_SINGLE_HEADER)
set(PROJECT_SOURCES ${PROJECT_SOURCES} glove.h)
else()
find_package(Glove REQUIRED)
endif()

if (NOT OPTION_SINGLE_HEADER AND NOT GLOVE_FOUND)
message(WARNING "Glove was not found.")
else()
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}Widgets REQUIRED)
endif()

set(EXAMPLE_INCLUDE_DIRECTORIES ${Qt${QT_VERSION_MAJOR}Widgets_INCLUDE_DIRS})

if(NOT OPTION_SINGLE_HEADER)
list(APPEND EXAMPLE_INCLUDE_DIRECTORIES ${GLOVE_INCLUDE_DIRS})
endif()

INCLUDE_DIRECTORIES(${EXAMPLE_INCLUDE_DIRECTORIES})

ADD_EXECUTABLE(${PROJECT_NAME} ${PROJECT_SOURCES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Widgets)

if(NOT OPTION_SINGLE_HEADER)
	glove_link(${PROJECT_NAME})
endif()
