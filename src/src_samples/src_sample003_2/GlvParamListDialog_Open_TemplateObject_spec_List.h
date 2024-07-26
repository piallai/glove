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
#include "GlvParamListDialog_Open_TemplateObject.h"
#endif
#include "List.h"
#include "List2Filter.h"
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvParamListDialog_Open_TemplatedTemplated.h"
#endif
#include "GlvParamListDialog_Open_TemplateTemplateObject_spec_List2.h"

#define Tspec List

template <>
struct GlvParamListDialog_Open_TemplateObject_Spec<Tspec> {

    template <class Tbase, class Toption>
    static bool build_parametrization_templated(GlvParametrizationDialog_base*& _configure_window, std::string _item_name, const Toption* _option, bool _l_show, QWidget* _parent) {
        
        bool l_created = false;

        glvm_List_instruction_name_to_type_templated_only(l_created = GlvParamListDialog_Open_TemplatedTemplated<Tbase::template Tderived COMMA, \
            _item_name, \
            COMMA List2 COMMA Toption\
        >::template open<List2Filter>(_configure_window COMMA _option COMMA _l_show COMMA _parent);)

        return l_created;

    }

    template <class Tbase, class Toption>
    static GlvParametrizationDialog_base* cast_check(std::string _item_name, const GlvParamListDialog_Open_TemplateObject<Tbase, Tspec, Toption>* _list) {

        GlvParametrizationDialog_base* parametrization_dialog = NULL;

        glvm_List_instruction_name_to_type_not_templated_only(\
            parametrization_dialog = _list->template cast_check<\
            , _item_name, >();)

        return parametrization_dialog;
    }

    template <class Tbase, class Toption>
    static GlvParametrizationDialog_base* build_parametrization(std::string _item_name, QWidget* _parent) {

        GlvParametrizationDialog_base* parametrization_dialog = NULL;

        glvm_List_instruction_name_to_type_not_templated_only(\
            parametrization_dialog = new GlvParametrizationDialog<typename Tbase::template Tderived<\
            , _item_name, COMMA Toption> >(_parent);)

        return parametrization_dialog;
    }

    template <class Tbase, class Toption>
    static void configuration(std::string _item_name, const GlvParamListDialog_Open_TemplateObject<Tbase, Tspec, Toption>* _list) {
        // Do nothing in particular
    }

};

#undef Tspec
