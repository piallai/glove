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

PROJECT(GLOVE)

set(GLOVE_INCLUDE_DIR
			${CMAKE_BINARY_DIR} #For cmake options .h.in
			${SLEEVE_SOURCE_DIR}
            ${THIRDPARTY_JSON_SOURCE_DIR}
)

if (OPTION_QT6)
set(GLOVE_INCLUDE_DIR ${GLOVE_INCLUDE_DIR} ${Qt6Widgets_INCLUDE_DIRS})
else()
set(GLOVE_INCLUDE_DIR ${GLOVE_INCLUDE_DIR} ${Qt5Widgets_INCLUDE_DIRS})
endif()

INCLUDE_DIRECTORIES(${GLOVE_INCLUDE_DIR})

SET(GLOVE_SOURCES  
    
	glv_widget.h
	glv_widget.cpp
	glv_flag.h
	glv_flag.cpp
	glv_QComboBox.h
	glv_QStandardItem.h
	glv_QStandardItemModel.h
	glv_QStandardItemModel.cpp
	glv_QStandardItemModelMaker_spec_std_map.h
	glv_QStandardItemModelMaker_spec_std_container.h
	glv_QString.h
	glv_QString.cpp
	glv_QTableView.h
	glv_QTableView.cpp
	glv_QTreeView.h
	glv_QTreeView.cpp
    
    GlvDescribedWidget.h
    GlvDescribedWidget_base.h
    GlvDescribedWidget_base.cpp

    GlvWidget_base.h
    GlvWidget_base.cpp
    GlvWidget.h

    GlvWidgetMakerConnect.h
    GlvWidgetMaker.h
    GlvWidgetConnector.h
    GlvWidgetConnector.cpp

    GlvWidgetAuto.h

    GlvWidgetData.h
    GlvWidgetData_spec_AT.h
    GlvWidgetData_spec_AT.cpp
	GlvWidgetData_spec_std_string.h
	GlvWidgetData_spec_std_string.cpp

	GlvSaveLoad.h
	GlvSaveLoad.cpp
    GlvWidgetSaveLoad_base.h
    GlvWidgetSaveLoad_base.cpp
	GlvWidgetSaveLoad.h
	GlvParametrizationSaveLoad.h

    GlvItemDelegate_base.h
    GlvItemDelegate_base.cpp
    GlvItemDelegate_spec_General.h
    GlvItemDelegate_spec_General_impl.h
	GlvItemDelegate_spec_Widget.h
    GlvItemDelegate_spec_Widget_impl.h
    GlvItemDelegate_spec_Modeled.h
    GlvItemDelegate_spec_Modeled_impl.h
    GlvItemDelegate.h

    GlvAbstractItemView.h
    GlvAbstractItemView.cpp

    GlvTableView_base.h
    GlvTableView_base.cpp
    GlvTableView_fwd.h
    GlvTableView.h
	GlvTableDialog.h

    GlvTreeView_base.h
    GlvTreeView_base.cpp
    GlvTreeView_fwd.h
    GlvTreeView.h
	GlvTreeDialog.h

	GlvStandardItem.h

    GlvListDialog_base.h
    GlvListDialog_base.cpp
    GlvListDialog.h
    GlvListDialog.cpp
	GlvListDialogTlist.h

    GlvParameterRuleAbiding.h
	GlvParameterRuleAbiding_spec_ParameterArithmetic.h
    GlvParameterRuleAbiding_spec_Arithmetic.h
    GlvParameterRuleAbiding_spec_bool.h
    GlvParameterRuleAbiding_specs.h
    GlvParameterWidget.h
	GlvParametersWidget_base.h
	GlvParametersWidget_base.cpp
    GlvParametersWidget.h
    GlvParametersWidget_specs.h
    GlvParametrizationWidget.h

    GlvParametrizationDialog_base.h
    GlvParametrizationDialog_base.cpp
    GlvParametrizationDialog.h
	GlvParamListDialog_base.h
	GlvParamListDialog_base.cpp
    GlvParamListDialog.h
    GlvParamListDialog_fwd.h
    GlvParamListMacros.h

    GlvParamListDialog_Open.h
	GlvParamListDialog_Open_Templated.h
    GlvParamListDialog_Open_TemplateObject.h
	GlvParamListDialog_Open_TemplatedTemplated.h
    GlvParamListDialog_Open_TemplateTemplateObject.h

    GlvParamListDialog_Filtering.h
    GlvParamListDialog_Filtering.cpp

    GlvWidgetData_spec_std_pair.h
	GlvPairWidget.h
	
	GlvWidgetData_spec_std_vector.h
	GlvVectorWidget.h
	GlvVectorWidget_base.h
	GlvVectorWidget_base.cpp
	GlvVectorWidgetItem.h
	GlvVectorWidgetItem_base.h
	GlvVectorWidgetItem_base.cpp

    GlvWidgetData_spec_std_map.h
    GlvMapWidget.h
	GlvMapWidget_base.h
	GlvMapWidget_base.cpp
	GlvMapWidgetItem.h
	GlvMapWidgetItem_base.h
	GlvMapWidgetItem_base.cpp

	GlvArrayWidget.h
	GlvWidgetData_spec_std_array.h
	
	GlvWidgetData_spec_std_container_container.h

	GlvWidgetData_spec_std_filesystem_path.h

	GlvOpenFile.h
	GlvOpenFile.cpp
	GlvOpenDirectory.h
	GlvOpenDirectory.cpp

    GlvProgression.h
    GlvProgression.cpp
    GlvProgressMgr.h
    GlvProgressMgr.cpp

	GlvDialog.h
	GlvDialogData.h
	
	GlvCLI.h
	GlvCLI.cpp

)

SET(GLOVE_SUB_SOURCES 
    iostream/spec/iostream_spec_QVector.h
    iostream/spec/iostream_spec_QModelIndex.h
    iostream/spec/iostream_spec_QModelIndex.cpp
	filestream/spec/slv_rw_spec_QVector.h
    filestream/spec/slv_rw_spec_QVector.cpp
    filestream/spec/slv_rw_spec_QModelIndex.h
    filestream/spec/slv_rw_spec_QModelIndex.cpp
)

ADD_LIBRARY(Glove STATIC ${GLOVE_SOURCES} ${GLOVE_SUB_SOURCES})

set_target_properties(Glove PROPERTIES DEBUG_POSTFIX "d")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${GLOVE_SUB_SOURCES})
SOURCE_GROUP(Headers REGULAR_EXPRESSION "[.]h$")
SOURCE_GROUP(Implementations REGULAR_EXPRESSION "_impl[.]h$")
