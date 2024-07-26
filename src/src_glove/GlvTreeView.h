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

#include "GlvTreeView_base.h"
#include "GlvTreeView_fwd.h"

/*! Makes a table view from a template data. Caution: work in progress for proper management of delegates size.
* If a glv::tdata::QStandardItemModelMaker specialization exists, each delegate item is a GlvTreeView.
* Can manage delegate's editor space by adding temporary header sections.
* Edition mode is forced to double click if delegate is modeled.
* It prevents clicking on temporary sections.*/
template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
class GlvTreeView : public GlvTreeView_base {

public:

    GlvTreeView(QWidget* _parent = 0);
    GlvTreeView(const Tdata& _value, QWidget* _parent = 0);
    ~GlvTreeView();

    Tdata get_value() const;
    void set_value(const Tdata& _data);

    /*! Whether to update model data when value changes.*/
    void set_dynamically_update_data(bool _l_dynamically_update_data);
    /*! Return whether data is dynamically updated or not.*/
    bool is_dynamically_upating_data() const;

};

#include "glv_QStandardItemModel.h"
#include "GlvItemDelegate.h"

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
GlvTreeView<Tdata, Twidget_final, IsPersistent>::GlvTreeView(QWidget* _parent) :GlvTreeView(Tdata(), _parent) {

}

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
GlvTreeView<Tdata, Twidget_final, IsPersistent>::GlvTreeView(const Tdata& _value, QWidget* _parent) : GlvTreeView_base(_parent) {

    GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTreeView, Twidget_final, IsPersistent>* delegate = dynamic_cast<GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTreeView, Twidget_final, IsPersistent>*>(this->itemDelegate());

    //check existing self made delegate (unlikely)
    if (!delegate) {
        GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTreeView, Twidget_final, IsPersistent>* delegate = new GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTreeView, Twidget_final, IsPersistent>(this);
        this->setItemDelegate(delegate);
    }

    set_value(_value);
}

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
GlvTreeView<Tdata, Twidget_final, IsPersistent>::~GlvTreeView() {

}

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
Tdata GlvTreeView<Tdata, Twidget_final, IsPersistent>::get_value() const {

    Tdata value;
    QStandardItemModel* model_ = dynamic_cast<QStandardItemModel*>(model());
    value = glv::tdata::fromQStandardItemModel<Tdata>(model_);
    return value;

}

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
void GlvTreeView<Tdata, Twidget_final, IsPersistent>::set_value(const Tdata& _data) {

    if (!model()) {
        setModel(glv::tdata::toQStandardItemModel(_data));
    } else {
        QStandardItemModel* _model = dynamic_cast<QStandardItemModel*>(model());
        //reset_dummies();//must be set before, because model modification can trigger 'parent' of this if this is delegate
        _model->blockSignals(true);//block signals so cell_changed() is not emitted each time an item of model is changed
        glv::tdata::toQStandardItemModel(_data, _model);
        _model->blockSignals(false);
        emit _model->layoutChanged();//to refresh view automatically
    }

}

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
void GlvTreeView<Tdata, Twidget_final, IsPersistent>::set_dynamically_update_data(bool _l_dynamically_update_data) {

    GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTreeView, Twidget_final, IsPersistent>* item_delegate = dynamic_cast<GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTreeView, Twidget_final, IsPersistent>*>(this->itemDelegate());

    if (item_delegate) {
        item_delegate->set_dynamically_update_data(_l_dynamically_update_data);
    }

}

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
bool GlvTreeView<Tdata, Twidget_final, IsPersistent>::is_dynamically_upating_data() const {

    GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTreeView, Twidget_final, IsPersistent>* item_delegate = dynamic_cast<GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTreeView, Twidget_final, IsPersistent>*>(this->itemDelegate());
    return item_delegate->is_dynamically_updating_data();

}

/*! Convenience alias for a GlvTreeView with regular line edit.*/
template <class Tdata>
using GlvTreeViewLineEdit = GlvTreeView<Tdata>;
/*! Convenience alias for a GlvTreeView with end editor as GlvWidget.*/
template <class Tdata>
using GlvTreeViewWidget = GlvTreeView<Tdata, GlvWidget>;
/*! Convenience alias for a GlvTreeView with end editor as persistent GlvWidget.*/
template <class Tdata>
using GlvTreeViewWidgetPersistent = GlvTreeView<Tdata, GlvWidget, true>;
