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
#include "GlvParamListDialog_Open_TemplateObject.h"
#endif
#include "List2.h"

template <>
struct GlvParamListDialog_Open_TemplateObject_Spec<List2> {

    template <class Tbase, class Toption>
    static bool build_parametrization_templated(GlvParametrizationDialog_base*& _configure_window, std::string _item_name, const Toption* _option, bool _l_show, QWidget* _parent) {
        return false;
    }

    template <class Tbase, class Toption>
    static GlvParametrizationDialog_base* cast_check(std::string _item_name, const GlvParamListDialog_Open_TemplateObject<Tbase, List2, Toption>* _list) {

        GlvParametrizationDialog_base* parametrization_dialog = NULL;

        glvm_List2_instruction_name_to_type(\
            parametrization_dialog = _list->template cast_check<\
            , _item_name, >();)

        return parametrization_dialog;

    }

    template <class Tbase, class Toption>
    static GlvParametrizationDialog_base* build_parametrization(std::string _item_name, QWidget* _parent) {

        GlvParametrizationDialog_base* parametrization_dialog = NULL;

        glvm_List2_instruction_name_to_type(\
            parametrization_dialog = new GlvParametrizationDialog<typename Tbase::template Tderived<\
            , _item_name, COMMA Toption> >(_parent);)

        return parametrization_dialog;
    }

    template <class Tbase, class Toption>
    static void configuration(std::string _item_name, const GlvParamListDialog_Open_TemplateObject<Tbase, List2, Toption>* _list) {
        // Do nothing in particular
    }

};
