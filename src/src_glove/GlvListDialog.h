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

#pragma once

#include "GlvListDialog_base.h"

/*! QDialog list of a list of names. See sample003 for example.*/
class GlvListDialog : public GlvListDialog_base {

public:
    /*! \p _names : List of names to fill the combo list.
    * \p _list_name : name of the list used for display.
    * \p _parent : If not NULL, then the widget is modal.
    * \p _l_dialog: Whether the list enables QDialog properties or not, such as button box, and related signals.*/
    GlvListDialog(const std::vector<std::string>& _names, const std::string _list_name, QWidget* _parent, bool _l_dialog = true);
    ~GlvListDialog();

};
