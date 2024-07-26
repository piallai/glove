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

PROJECT(Sample010_0)

set(
	${PROJECT_NAME}_PROJECT_SRCS
    sample010_0.cpp
)

set(GLVSAMPLE_INCLUDE_DIR
			${CMAKE_BINARY_DIR} #For cmake options .h.in
			${THIRDPARTY_JSON_SOURCE_DIR}
)

if(NOT OPTION_QT6)
set(GLVSAMPLE_INCLUDE_DIR ${GLVSAMPLE_INCLUDE_DIR} ${Qt5Widgets_INCLUDE_DIRS})
endif()

if (NOT OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER)
	set(GLVSAMPLE_INCLUDE_DIR ${GLVSAMPLE_INCLUDE_DIR}
			${SLEEVE_SOURCE_DIR}
			${GLOVE_SOURCE_DIR}
			${GLOVE_ADD_SOURCE_DIR}
	)
else ()
	set(GLVSAMPLE_INCLUDE_DIR ${GLVSAMPLE_INCLUDE_DIR}
			${GLOVE_SINGLE_HEADER_SOURCE_DIR}
	)
endif ()


INCLUDE_DIRECTORIES(${GLVSAMPLE_INCLUDE_DIR})

ADD_EXECUTABLE(${PROJECT_NAME} ${${PROJECT_NAME}_PROJECT_SRCS})

if(OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER)
	target_compile_options(${PROJECT_NAME} PRIVATE -DOPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER)
endif()

set(GLVSAMPLE_LINK_LIBRARIES
	Qt${QT_VERSION_MAJOR}::Widgets
)

if(NOT OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER)
set(GLVSAMPLE_LINK_LIBRARIES
	GloveAdd
	Glove
	Sleeve
	${GLVSAMPLE_LINK_LIBRARIES}
)
else()
set(GLVSAMPLE_LINK_LIBRARIES
	GloveSingleHeader
	${GLVSAMPLE_LINK_LIBRARIES}
)
endif()

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${GLVSAMPLE_LINK_LIBRARIES})
