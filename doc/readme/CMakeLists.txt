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

add_custom_target(_Readme_md ALL 
    SOURCES
    ../../README.md
    SlvEnum.md
    GlvOpenFile.md
    GlvOpenDirectory.md
    GlvProportionWidget.md
    GlvEnumWidget.md
    GlvMapWidget.md
    GlvVectorWidget.md
    GlvPairWidget.md
    Parametrization/Parametrization_basic.md
    Parametrization/Parametrization_nested.md
    Parametrization/Parametrization_rules.md
    Parametrization/Parametrization_list.md
    GlvWidgetData_specs.md
    GlvWidgetData_spec.md
    SaveLoad/SaveLoad_binary.md
    SaveLoad/SaveLoad_json.md
    SlvDataName.md
    ModelView/ModelView_basic.md
    ModelView/ModelView_widget_editor.md
    ModelView/ModelView_std_map.md
    ModelView/ModelView_SlvPool.md
    ModelView/ModelView_multiple.md
    ModelView/ModelView_dialog.md
    ModelView/ModelView_specs.md
    Progress/Progress_basic.md
    Progress/Progress_class_method.md
    Progress/Progress_class_multiple.md
    Progress/Progress_class_multiple.md
    ReadWriteFile/ReadWriteFile_opening.md
    ReadWriteFile/ReadWriteFile_class_binary.md
    ReadWriteFile/ReadWriteFile_class_binary2.md
    ReadWriteFile/ReadWriteFile_class_IO.md
    ReadWriteFile/ReadWriteFile_class_text.md
    ReadWriteFile/ReadWriteFile_specs.md
    Specializations.md
    CLI/CLI.md
)
