/*
* This file is part of the Glove distribution (https://github.com/piallai/glove).
* Copyright (C) 2024 - 2025 Pierre Allain.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "GlvListDialog.h"

#include <QLabel>
#include "glv_QComboBox.h"
#include "glv_QStandardItemModelMaker_spec_std_container.h"

GlvListDialog::GlvListDialog(const std::vector<std::string>& _names, const std::string _list_name, QWidget* _parent, bool _l_dialog) :GlvListDialog_base(_parent, _l_dialog) {

    list_name_widget->setText(glv::toQString(_list_name + " :"));
    glv::toQComboBox(combo_list, _names);

}

GlvListDialog::~GlvListDialog() {

}
