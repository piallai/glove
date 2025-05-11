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

#include "GlvParamListDialog_Open_TemplateTemplateObject.h"

/*! In charge of opening a tertiary list to select a tertiary type. Target type is sort of: Tclass<Tbase<Tsublist-pick>>.
* Not supposed to be specialized.*/
template < template <class Tbase_derived, class _Toption> class Tclass, class Tbase, class Tsublist, class Toption>
struct GlvParamListDialog_Open_TemplatedTemplated {

    template <template <class _Tlist_item, class _Toption, class _Tenable> class Tfiltering = GlvListFilterDefault>
    static bool open(GlvParametrizationDialog_base*& _parametrization_dialog, const Toption* _option, bool _l_show_parametrization_dialog, QWidget* _parent) {

        GlvParamListDialog_Open_TemplateTemplateObject<Tclass, Tbase, Tsublist, Toption>* sublist;
        sublist = new GlvParamListDialog_Open_TemplateTemplateObject<Tclass, Tbase, Tsublist, Toption>(_parent, _parametrization_dialog, _option, _l_show_parametrization_dialog);
        sublist->template filter_list<Tfiltering, Toption>();

        sublist->set_text(glv::toQString("Select " + Tbase::name() + "'s " + Tsublist::item_description()));

        if (_l_show_parametrization_dialog) {
            sublist->exec();
        } else {
            sublist->accept();
        }
        bool l_created = sublist->l_created;

        delete sublist;

        return l_created;

    }

};
