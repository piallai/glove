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

#include "GlvParamListDialog_base.h"
template <class Tparametrization>
class GlvParametrizationDialog;

#include "GlvParamListDialog_fwd.h"

/*! Configuration list of Tlist type.
* Tlist must have:
* - static const std::vector<std::string>& list() method
* - static const std::string& name() method
* Toption is the type of the optional data provided for the parametrization windows. See GlvParamListDialog_Open::open.
* The optional data is not stored in the GlvParamListDialog instance.*/
template <class Tlist, class Toption>
class GlvParamListDialog : public GlvParamListDialog_base {

private:

    const Toption* optional_data;

public:

    /*! \p _list : Instance to convert to list.
    * \p _optional_data : pointer to optional data to be managed by all the parametrizations.
    * \p _l_dialog: Whether QDialog functionalities are activated or not (buttons, accept/reject).
    * \p _l_visible_config : If true, configure button is displayed. Otherwise, parametrization is triggered when changing QComboBox item.*/
    GlvParamListDialog(QWidget* _parent, const Toption* _optional_data, bool _l_dialog = true, bool _l_visible_config = true);
    GlvParamListDialog(QWidget* _parent = NULL, bool _l_dialog = true, bool _l_visible_config = true);
    ~GlvParamListDialog();

    /*! Get parametrization widget. The parametrization type must match the type currently selected/configured. Otherwise returns NULL.*/
    template <class Tparametrization>
    GlvParametrizationDialog<Tparametrization>* get_parametrization_dialog();

    /*! Set optional data for parametrization windows.*/
    void set_optional_data(const Toption* _optional_data);

public:

    /*! Applies default parametrization (if none is configured yet) and accepts QDialog.*/
    void accept();

    /*! Enables or disables items in QComboBox depending on whether types of the list are compatible with T1 according to Tfiltering.*/
    template < template <class T1, class T2, class Tenable> class Tfiltering, class T1 = Toption>
    void filter_list();//this method is also GlvListDialogTlist. I didn't restructred inheritance yet (can't virtual inherit QWidget)

private:

    /*! Implements pure virtual slot of GlvParamListDialog_base.*/
    void make_parametrization_dialog();
    /*! Implements pure virtual slot of GlvParamListDialog_base.*/
    void make_parametrization_dialog(const QString& _item_name);

    /*! Creates new parametrization window. \p _parametrization_name is the name of the parametrization type.
    * The parametrization window can be displayed or not using \p _l_show.*/
    void new_parametrization_dialog(const QString& _parametrization_name, bool l_show);

};

#include "GlvParametrizationDialog.h"
#include <QComboBox>
#include "GlvParamListDialog_Filtering.h"
#include "GlvParamListDialog_Open.h"

template <class Tlist, class Toption>
GlvParamListDialog<Tlist, Toption>::GlvParamListDialog(QWidget* _parent, const Toption* _optional_data, bool _l_dialog, bool _l_visible_config) :\
GlvParamListDialog_base(Tlist::list(), Tlist::name(), _parent, _l_dialog, _l_visible_config) {

    set_optional_data(_optional_data);

}

template <class Tlist, class Toption>
GlvParamListDialog<Tlist, Toption>::GlvParamListDialog(QWidget* _parent, bool _l_dialog, bool _l_visible_config) :\
GlvParamListDialog<Tlist, Toption>(_parent, (Toption*)(NULL), _l_dialog, _l_visible_config) {

}

template <class Tlist, class Toption>
GlvParamListDialog<Tlist, Toption>::~GlvParamListDialog() {

}

template <class Tlist, class Toption>
template <class Tparametrization>
GlvParametrizationDialog<Tparametrization>* GlvParamListDialog<Tlist, Toption>::get_parametrization_dialog() {

    return dynamic_cast<GlvParametrizationDialog<Tparametrization>*>(parametrization_dialog);//ddynamic_cast

}

template <class Tlist, class Toption>
void GlvParamListDialog<Tlist, Toption>::set_optional_data(const Toption* _optional_data) {

    optional_data = _optional_data;
}

template <class Tlist, class Toption>
void GlvParamListDialog<Tlist, Toption>::accept() {

    // Do not call new_parametrization_dialog if a parametrization widget already exists.
    // Avoids getting list items value that are by default not the ones that may be configured
    // Call it if combo item name differs from the current parametrization (ex: combo item has changed and direct 'ok') 
    if (!parametrization_dialog || parametrization_dialog->get_parametrization_base()->get_name() != combo_list->currentText().toStdString()) {
        bool l_show = false;
        new_parametrization_dialog(combo_list->currentText(), l_show);
    }

    GlvListDialog::accept();

}

template <class Tlist, class Toption>
template < template <class T1, class T2, class Tenable> class Tfiltering, class T1 >
void GlvParamListDialog<Tlist, Toption>::filter_list() {

    int Nitems;
    GlvParamListDialog_Filtering::filter_list<Tlist, Tfiltering, T1>(combo_list, &Nitems);

    if (Nitems == 0) {
        setOkButtonEnabled(false);
    } else {
        setOkButtonEnabled(true);
    }

}

template <class Tlist, class Toption>
void GlvParamListDialog<Tlist, Toption>::make_parametrization_dialog(const QString& _item_name) {

    bool l_show = true;
    new_parametrization_dialog(_item_name, l_show);

}

template <class Tlist, class Toption>
void GlvParamListDialog<Tlist, Toption>::make_parametrization_dialog() {

    make_parametrization_dialog(combo_list->currentText());

}

template <class Tlist, class Toption>
void GlvParamListDialog<Tlist, Toption>::new_parametrization_dialog(const QString& _parametrization_name, bool l_show) {

    /*! This is where specialization occurs.*/
    bool l_created = GlvParamListDialog_Open<Tlist, Toption>::open(parametrization_dialog, _parametrization_name.toStdString(), optional_data, l_show, this);

    if (l_created) emit configure(_parametrization_name);
}

// Needed most of the time when using glv lists
#include "GlvParamListMacros.h"
