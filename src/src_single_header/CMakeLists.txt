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

PROJECT(GLOVE_SINGLE_HEADER)

set(GLOVE_SINGLE_HEADER_INCLUDE_DIR
	${THIRDPARTY_JSON_SOURCE_DIR}
	${Qt${QT_VERSION_MAJOR}Widgets_INCLUDE_DIRS}
)

INCLUDE_DIRECTORIES(${GLOVE_SINGLE_HEADER_INCLUDE_DIR})

SET(GLOVE_SINGLE_HEADER_SOURCES
	glove.h
)

ADD_LIBRARY(GloveSingleHeader OBJECT ${GLOVE_SINGLE_HEADER_SOURCES})

