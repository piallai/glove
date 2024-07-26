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

#include "GlvListDialog.h"

/*! QDialog list of Tlist type.
* Tlist must have:
* - static const std::vector<std::string>& list() method
* - static const std::string& name() method
* No GlvParametrizationDialog management as compared to GlvParamListDialog.*/
template <class Tlist>
class GlvListDialogTlist : public GlvListDialog {

public:

    GlvListDialogTlist(QWidget* _parent, bool _l_dialog = true);
    ~GlvListDialogTlist() {}

    /*! Enables or disables items in QComboBox depending on whether types of the list are compatible with T1 according to Tfiltering.*/
    template < template <class T1, class T2, class Tenable> class Tfiltering, class T1 >
    void filter_list();// This method is also in GlvParamListDialog. Factorization is not straightfoward because it is impossible to virtually inherit QObject.

};

#include "GlvParamListDialog_Filtering.h"

template <class Tlist>
GlvListDialogTlist<Tlist>::GlvListDialogTlist(QWidget* _parent, bool _l_dialog) :GlvListDialog(Tlist::list(), Tlist::name(), _parent, _l_dialog) {

}

template <class Tlist>
template < template <class T1, class T2, class Tenable> class Tfiltering, class T1 >
void GlvListDialogTlist<Tlist>::filter_list() {

    int Nitems;
    GlvParamListDialog_Filtering::filter_list<Tlist, Tfiltering, T1>(combo_list, &Nitems);

    if (Nitems == 0) {
        setOkButtonEnabled(false);
    } else {
        setOkButtonEnabled(true);
    }

}
