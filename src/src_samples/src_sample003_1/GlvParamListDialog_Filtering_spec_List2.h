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

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvParamListDialog_Filtering.h"
#endif
#include "List2.h"

template <>
struct GlvParamListDialog_Filtering::Spec<List2> {
    template <template <class Tlist_item, class Toption, class Tenable> class Tfiltering, class Toption>
    static bool filter(const std::string& _item_name, QComboBox* _combo_list, int i) {

        bool l_enabled = false;

        /*! Simply specify the lookup preprocessor macro here.*/
        glvm_List2_instruction_name_to_type(
            l_enabled = GlvParamListDialog_Filtering::filter<Tfiltering COMMA,
            _item_name
            , COMMA Toption>(_combo_list COMMA i);
        )

        return l_enabled;
    }
};
