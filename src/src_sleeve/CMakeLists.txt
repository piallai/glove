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

PROJECT(SLEEVE)

set(SLEEVE_INCLUDE_DIR
	${CMAKE_BINARY_DIR} #For cmake options .h.in
	${THIRDPARTY_JSON_SOURCE_DIR}
)

# Add Qt include directories (optional, used for signal management only)
if(OPTION_ENABLE_SLV_QT_PROGRESS)
if (OPTION_QT6)
set(SLEEVE_INCLUDE_DIR ${SLEEVE_INCLUDE_DIR} ${Qt6Widgets_INCLUDE_DIRS})
else()
set(SLEEVE_INCLUDE_DIR ${SLEEVE_INCLUDE_DIR} ${Qt5Widgets_INCLUDE_DIRS})
endif()
endif()

INCLUDE_DIRECTORIES(${SLEEVE_INCLUDE_DIR})

set(FILESTREAM_SOURCES

    filestream/slv_read.h
    filestream/slv_rw.h
    filestream/slv_write.h
    filestream/SlvDirectory.h
    filestream/SlvDirectory.cpp
    filestream/SlvFile.h
    filestream/SlvFile.cpp
    filestream/SlvFileName.h
    filestream/SlvFileName.cpp
    filestream/SlvFileExtensions.h
    filestream/SlvFileExtensions.cpp
    filestream/SlvFileMgr.h
    filestream/SlvFileMgr.cpp
    filestream/SlvFileTypedefs.h
	filestream/SlvReadText.h
    filestream/SlvReadText.cpp
	filestream/SlvReadBinary.h
    filestream/SlvReadBinary.cpp
	filestream/SlvWriteText.h
    filestream/SlvWriteText.cpp
	filestream/SlvWriteBinary.h
    filestream/SlvWriteBinary.cpp
    filestream/SlvReadWriteText.h
    filestream/SlvReadWriteBinary.h
	filestream/SlvWriteBinaryNamed.h
	filestream/SlvWriteTextNamed.h
	
	filestream/spec/slv_read_spec_AT.h
	filestream/spec/slv_read_spec_AT.cpp
	filestream/spec/slv_read_spec_AT_ptr.h
	filestream/spec/slv_read_spec_AT_ptr.cpp
	filestream/spec/slv_write_spec_AT.h
	filestream/spec/slv_write_spec_AT.cpp
	filestream/spec/slv_write_spec_AT_ptr.h
	filestream/spec/slv_write_spec_AT_ptr.cpp
	filestream/spec/slv_rw_spec_AT.h
	filestream/spec/slv_rw_spec_std_string.h
	filestream/spec/slv_rw_spec_std_string.cpp
	filestream/spec/slv_rw_spec_std_vector.h
	filestream/spec/slv_rw_spec_std_vector_decl.h
	filestream/spec/slv_rw_spec_std_vector_impl.h
	filestream/spec/slv_rw_spec_std_vector.cpp
	filestream/spec/slv_rw_spec_std_array.h
	filestream/spec/slv_rw_spec_std_array_decl.h
	filestream/spec/slv_rw_spec_std_array_impl.h
	filestream/spec/slv_rw_spec_std_list.h
	filestream/spec/slv_rw_spec_std_list_decl.h
	filestream/spec/slv_rw_spec_std_list_impl.h
	filestream/spec/slv_rw_spec_std_deque.h
	filestream/spec/slv_rw_spec_std_deque_decl.h
	filestream/spec/slv_rw_spec_std_deque_impl.h
	filestream/spec/slv_rw_spec_std_pair.h
	filestream/spec/slv_rw_spec_std_pair_decl.h
	filestream/spec/slv_rw_spec_std_pair_impl.h
	filestream/spec/slv_rw_spec_std_map.h
	filestream/spec/slv_rw_spec_std_map_decl.h
	filestream/spec/slv_rw_spec_std_map_impl.h
	filestream/spec/slv_rw_spec_std_unordered_map.h
	filestream/spec/slv_rw_spec_std_unordered_map_decl.h
	filestream/spec/slv_rw_spec_std_unordered_map_impl.h
	filestream/spec/slv_rw_spec_STL.h
	filestream/spec/slv_rw_spec_std_filesystem_path.h
	filestream/spec/slv_rw_spec_std_filesystem_path.cpp
	filestream/spec/slv_rw_spec_boost_container_vector.h
	filestream/spec/slv_rw_spec_boost_container_vector_decl.h
	filestream/spec/slv_rw_spec_boost_container_vector_impl.h
	filestream/spec/slv_rw_spec_boost_unordered_map.h
	filestream/spec/slv_rw_spec_boost_unordered_map_decl.h
	filestream/spec/slv_rw_spec_boost_unordered_map_impl.h
	filestream/spec/slv_rw_spec_multi.h
	
	filestream/slv_rw_json.h
)

set(IO_SOURCES
	iostream/spec/iostream_spec_boost_container_vector.h
	iostream/spec/iostream_spec_boost_container_vector_decl.h
	iostream/spec/iostream_spec_boost_container_vector_impl.h
	iostream/spec/iostream_spec_boost_unordered_map.h
	iostream/spec/iostream_spec_boost_unordered_map_decl.h
	iostream/spec/iostream_spec_boost_unordered_map_impl.h
	iostream/spec/iostream_spec_multi.h
	iostream/spec/iostream_spec_pointer.h
	iostream/spec/iostream_spec_std_map.h
	iostream/spec/iostream_spec_std_map_decl.h
	iostream/spec/iostream_spec_std_map_impl.h
	iostream/spec/iostream_spec_std_pair.h
	iostream/spec/iostream_spec_std_pair_decl.h
	iostream/spec/iostream_spec_std_pair_impl.h
	iostream/spec/iostream_spec_std_unordered_map.h
	iostream/spec/iostream_spec_std_unordered_map_decl.h
	iostream/spec/iostream_spec_std_unordered_map_impl.h
	iostream/spec/iostream_spec_std_vector.h
	iostream/spec/iostream_spec_std_vector_decl.h
	iostream/spec/iostream_spec_std_vector_impl.h
	iostream/spec/iostream_spec_std_list.h
	iostream/spec/iostream_spec_std_list_decl.h
	iostream/spec/iostream_spec_std_list_impl.h
	iostream/spec/iostream_spec_std_deque.h
	iostream/spec/iostream_spec_std_deque_decl.h
	iostream/spec/iostream_spec_std_deque_impl.h
	iostream/spec/iostream_spec_std_array.h
	iostream/spec/iostream_spec_std_array_decl.h
	iostream/spec/iostream_spec_std_array_impl.h
)

set(MISC_SOURCES
	misc/slv_misc.h
	misc/SlvIsSameFilter.h
	misc/SlvTimer.cpp
	misc/SlvTimer.h
	misc/SlvDataName.h
	misc/spec/SlvDataName_spec_AT.h
	misc/spec/SlvDataName_spec_std_string.h
	misc/spec/SlvDataName_spec_std_vector.h
	misc/spec/SlvDataName_spec_std_array.h
	misc/spec/SlvDataName_spec_std_list.h
	misc/spec/SlvDataName_spec_std_deque.h
	misc/spec/SlvDataName_spec_std_vector_vector.h
	misc/spec/SlvDataName_spec_std_pair.h
	misc/spec/SlvDataName_spec_std_map.h
	misc/spec/SlvDataName_spec_std_unordered_map.h
	misc/spec/SlvDataName_spec_STL.h
	misc/spec/SlvDataName_spec_SlvPool.h
	misc/spec/SlvDataName_spec_All.h
)

file(
	GLOB
	PARAM_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/param/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/param/*.h"
)

SET(SLEEVE_SOURCES

	SlvMacros.h
	SlvIsType.h
	SlvIsContainer.h
	SlvIsMap.h
	SlvHasMethod.h
	SlvHasOstreamOperator.h
	SlvHasIstreamOperator.h
	SlvLblName.h
	SlvLblName.cpp
	SlvLblIdentifier.h
	SlvLblIdentifier.cpp
	slv_lbl.h
	SlvLabeling.h
	SlvPool.h
	SlvPoolFactory.h
	SlvName.h
	SlvName.cpp

	SlvParameterRuleValidation.h
	SlvParameterRuleValidation_spec_Files.h
	SlvParameterRuleValidation_spec_Files.cpp
	SlvParameterRuleValue.h
	SlvParameterRuleT.h
	SlvParameterRuleT_impl.h
	SlvParameterRuleT_spec_Arithmetic.h
	SlvParameterRuleT_spec_SlvParametrization.h
	SlvParameterRuleT_spec_Parameter.h
	SlvParameterRuleT_spec_ParameterArithmetic.h
	SlvParameter_base.h
	SlvParameter_base.cpp
	SlvParameter.h
	SlvParametrization_base.h
	SlvParametrization_base.cpp
			
	SlvIsParametrization.h

	std_vector.h
	std_list.h
	std_deque.h
	std_map.h
	std_unordered_map.h
	std_array.h
	std_pair.h

	SlvMacrosDeclarations.h
	SlvVirtualGetName.h
			
	SlvStatus.h
	SlvStatus.cpp
			
	SlvOS.h
	SlvOS.cpp
	SlvIS.h
	SlvIS.cpp
	SlvIOS.h
	
	SlvOFS.h
	SlvOFS.cpp
	SlvIFS.h
	SlvIFS.cpp
	SlvIOFS.h
	
	SlvCombo.h
	SlvComboFunc.h

	slv_string.h
	slv_string.cpp
	slv_flag.h
	slv_flag.cpp
	slv_is_arithmetic.h
	slv_vector.h
	slv_optional_text_str.h
			
	SlvSort.h
			
	SlvSize2d.h
	
	SlvProgression.h
	SlvProgression.cpp
			
	##### Parameter classes #########
	SlvProportion.h
	SlvProportion.cpp
	#Also filestream/SlvFile
	SlvEnum.h
	SlvEnum_macros.h
	SlvEnum_macros_var.h
	SlvEnum_macros_msvc.h
	SlvEnum_macros_var_msvc.h
	#################################
)

SET(SLEEVE_SUB_SOURCES 
	${FILESTREAM_SOURCES}
	${IO_SOURCES}
	${MISC_SOURCES}
	${PARAM_SOURCES}
)

SET(SLEEVE_SOURCES ${SLEEVE_SOURCES}
	SlvProgressionQt.h
	SlvProgressionQt.cpp
)

ADD_LIBRARY(Sleeve STATIC ${SLEEVE_SOURCES} ${SLEEVE_SUB_SOURCES})

set_target_properties(Sleeve PROPERTIES DEBUG_POSTFIX "d")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SLEEVE_SUB_SOURCES})
SOURCE_GROUP(Headers REGULAR_EXPRESSION "[.]h$")
SOURCE_GROUP(Implementations REGULAR_EXPRESSION "_impl[.]h$")
