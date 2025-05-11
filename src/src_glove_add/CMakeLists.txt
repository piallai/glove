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

PROJECT(GLOVE_ADD)

set(GLOVE_ADD_INCLUDE_DIR
			${CMAKE_BINARY_DIR} #For cmake options .h.in
			${SLEEVE_SOURCE_DIR}
			${THIRDPARTY_JSON_SOURCE_DIR}
			${GLOVE_SOURCE_DIR}
)

if(OPTION_QT6)
set(GLOVE_ADD_INCLUDE_DIR ${GLOVE_ADD_INCLUDE_DIR} ${Qt6Widgets_INCLUDE_DIRS})
else()
set(GLOVE_ADD_INCLUDE_DIR ${GLOVE_ADD_INCLUDE_DIR} ${Qt5Widgets_INCLUDE_DIRS})
endif()

INCLUDE_DIRECTORIES(${GLOVE_ADD_INCLUDE_DIR})

ADD_LIBRARY(GloveAdd STATIC  

    GlvProportionWidget.h
    GlvProportionWidget.cpp

	GlvEnumWidget.h
	
	GlvSize2dWidget.h

	GlvWidgetData_spec_SlvEnum.h
    GlvWidgetData_spec_SlvParametrization.h

    GlvWidgetData_spec_SlvDirectory.h
    GlvWidgetData_spec_SlvDirectory.cpp
    GlvWidgetData_spec_SlvFile.h
    GlvWidgetData_spec_SlvFile.cpp
    GlvWidgetData_spec_SlvProportion.h
    GlvWidgetData_spec_SlvProportion.cpp
	GlvWidgetData_spec_SlvSize2d.h

	GlvWidgetData_spec_All.h
	GlvParametrizationIncludes.h

	glv_QStandardItemModelMaker_spec_SlvPool.h
)

set_target_properties(GloveAdd PROPERTIES DEBUG_POSTFIX "d")

SOURCE_GROUP(Headers REGULAR_EXPRESSION "[.]h$")
SOURCE_GROUP(Implementations REGULAR_EXPRESSION "_impl[.]h$")
