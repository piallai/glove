# 
# This file is part of the Glove distribution (https://github.com/xxxx or http://xxx.github.io).
# Copyright (C) 2022 Pierre Allain.
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

# Locates the GLOVE library and include directories.

include(FindPackageHandleStandardArgs)
unset(GLOVE_FOUND)

if(WIN32)
if(DEFINED ENV{GLOVE_ROOT})
set(GLOVE_PATH $ENV{GLOVE_ROOT})
message(STATUS "GLOVE_ROOT is set to " $ENV{GLOVE_ROOT})
else()
message(FATAL_ERROR "GLOVE_ROOT environment variable was not set")
endif()
elseif(UNIX)
if(DEFINED ENV{GLOVE_ROOT})
set(GLOVE_PATH $ENV{GLOVE_ROOT})
message(STATUS "GLOVE_ROOT is set to " $ENV{GLOVE_ROOT})
else()
set(GLOVE_PATH "/usr/local")
endif()
endif()

find_path(GLOVE_INCLUDE_DIR
        NAMES
        sleeve
        HINTS
		${GLOVE_PATH}/include/glove)

if(WIN32)
find_library(GLOVE_LIBRARY
		NAMES
		Glove.lib
		Gloved.lib
        HINTS
		${GLOVE_PATH}/lib/glove
		${GLOVE_PATH}/lib/glove
		)
elseif(UNIX)
find_library(GLOVE_LIBRARY
		NAMES
		libGlove.a
		libGloved.a
        HINTS
		${GLOVE_PATH}/lib/glove
		${GLOVE_PATH}/lib/glove
		)
endif()
		
# set GLOVE_FOUND
find_package_handle_standard_args(Glove DEFAULT_MSG GLOVE_INCLUDE_DIR GLOVE_LIBRARY)

# set external variables for usage in CMakeLists.txt
if(GLOVE_FOUND)
if(WIN32)
    set(GLOVE_LIBRARIES
    ${GLOVE_PATH}/lib/glove/GloveAdd.lib
	${GLOVE_PATH}/lib/glove/Glove.lib
	${GLOVE_PATH}/lib/glove/Sleeve.lib
	)
	set(GLOVE_LIBRARIES_DEBUG
	${GLOVE_PATH}/lib/glove/GloveAddd.lib
	${GLOVE_PATH}/lib/glove/Gloved.lib
	${GLOVE_PATH}/lib/glove/Sleeved.lib
	)
elseif(UNIX)
    set(GLOVE_LIBRARIES
	${GLOVE_PATH}/lib/glove/libGloveAdd.a
	${GLOVE_PATH}/lib/glove/libGlove.a
	${GLOVE_PATH}/lib/glove/libSleeve.a
	)
	set(GLOVE_LIBRARIES_DEBUG
	${GLOVE_PATH}/lib/glove/libGloveAddd.a
	${GLOVE_PATH}/lib/glove/libGloved.a
	${GLOVE_PATH}/lib/glove/libSleeved.a
	)
endif()
    set(GLOVE_INCLUDE_DIRS
	${GLOVE_INCLUDE_DIR}/sleeve
	${GLOVE_INCLUDE_DIR}/glove
	${GLOVE_INCLUDE_DIR}/glove_add
	${GLOVE_INCLUDE_DIR}/thirdParty)
endif()

mark_as_advanced(GLOVE_INCLUDE_DIR GLOVE_LIBRARY)
