/*
* This file is part of the Glove distribution (https://github.com/piallai/glove).
* Copyright (C) 2024 Pierre Allain.
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
#include "GlvParamListDialog_Open.h"
#endif
#include "List.h"
// Related to template selection
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvParamListDialog_Open_Templated.h"
#endif
#include "GlvParamListDialog_Filtering_spec_List2.h"
#include "GlvParamListDialog_Open_TemplateObject_spec_List.h"

template <>
struct GlvParamListDialog_Open_Spec<List> {

    /*! Creates new GlvParametrizationDialog.
    * Only replace preprocessor macro.*/
    template <class Toption>
    static bool build_parametrization_templated(GlvParametrizationDialog_base*& _configure_window, std::string _item_name, const Toption* _option, bool _l_show, QWidget* _parent) {

        bool l_created = false;

        glvm_List_instruction_name_to_type_templated_only(l_created = GlvParamListDialog_Open_Templated<,
            _item_name,
            COMMA List COMMA Toption
        >::template open(_configure_window COMMA _option COMMA _l_show COMMA _parent);)

        return l_created;
    }

    /*! Creates new GlvParametrizationDialog.
    * Only replace preprocessor macro.*/
    template <class Toption>
    static GlvParametrizationDialog_base* build_parametrization(std::string _item_name, QWidget* _parent) {

        GlvParametrizationDialog_base* parametrization_dialog = NULL;

        glvm_List_instruction_name_to_type_not_templated_only(parametrization_dialog = new GlvParametrizationDialog<,
            _item_name,
        >(_parent);)

        return parametrization_dialog;
    }

    /*! Applies optional changes to the created parametrization widget.*/
    template <class Toption>
    static void configuration(GlvParametrizationDialog_base* _configure_window, std::string _item_name, const Toption* _option) {

    }
};
