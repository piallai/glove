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

#include "GlvTableView_base.h"
#include "GlvTableView_fwd.h"

/*! Makes a table view from a template data.
* If a glv::tdata::QStandardItemModelMaker specialization exists, each delegate item is a GlvTableView.
* Can manage delegate's editor space by adding temporary header sections.
* Edition mode is forced to double click if delegate is modeled.
* It prevents clicking on temporary sections.*/
template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
class GlvTableView : public GlvTableView_base {

public:

    GlvTableView(QWidget* _parent = 0);
    GlvTableView(const Tdata& _value, QWidget* _parent = 0);
    ~GlvTableView();

    Tdata get_value() const;
    void set_value(const Tdata& _data);

    /*! Reimplementation to force to double click if delegate is modeled.*/
    void setEditTriggers(EditTriggers _triggers);

    /*! Whether to update model data when value changes. Default value is true.
    * If false, then the model data is updated only when closing the main editor.*/
    void set_dynamically_update_data(bool _l_dynamically_update_data);
    /*! Return whether data is dynamically updated or not.*/
    bool is_dynamically_upating_data() const;

private:
    /*! Emit the coordinates corresponding to \p _index accord to data dimension.*/
    void cell_changed_slot(const QModelIndex& _index);

};

#include "glv_QStandardItemModel.h"
#include "GlvItemDelegate.h"
#include <QStandardItemModel>
#include <QHeaderView>//to resize columns to content

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
GlvTableView<Tdata, Twidget_final, IsPersistent>::GlvTableView(QWidget* _parent) :GlvTableView(Tdata(), _parent) {

}

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
GlvTableView<Tdata, Twidget_final, IsPersistent>::GlvTableView(const Tdata& _value, QWidget* _parent) : GlvTableView_base(_parent) {

    GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTableView, Twidget_final, IsPersistent>* item_delegate = dynamic_cast<GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTableView, Twidget_final, IsPersistent>*>(this->itemDelegate());

    //check existing self made delegate (unlikely)
    if (!item_delegate) {
        item_delegate = new GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTableView, Twidget_final, IsPersistent>(this);
        this->setItemDelegate(item_delegate);
    }

    set_value(_value);
    GlvTableView_base::setEditTriggers(EditTrigger::DoubleClicked);

    if (GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTableView, Twidget_final, IsPersistent>::is_modeled()) {
        GlvTableView_base::setEditTriggers(EditTrigger::DoubleClicked);
    }

}

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
GlvTableView<Tdata, Twidget_final, IsPersistent>::~GlvTableView() {

}

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
Tdata GlvTableView<Tdata, Twidget_final, IsPersistent>::get_value() const {

    Tdata value;
    QStandardItemModel* model_ = dynamic_cast<QStandardItemModel*>(model());
    int Mrows = model_->rowCount();
    int Ncols = model_->columnCount();
    if (l_dummy_row) {
        Mrows--;
    }
    if (l_dummy_column) {
        Ncols--;
    }
    value = glv::tdata::fromQStandardItemModel<Tdata>(model_, QModelIndex(), Mrows, Ncols);

    return value;
}

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
void GlvTableView<Tdata, Twidget_final, IsPersistent>::set_value(const Tdata& _data) {

    if (!model()) {
        setModel(glv::tdata::toQStandardItemModel(_data));
    } else {

        this->setCurrentIndex(QModelIndex());// Close delegate editor if opened. Prevents overwriting of model when closing the editor after value is set.

        QStandardItemModel* _model = dynamic_cast<QStandardItemModel*>(model());
        reset_dummies();//must be set before, because model modification can trigger 'parent' of this if this is delegate
        _model->blockSignals(true);//block signals so cell_changed() is not emitted each time an item of model is changed
        glv::tdata::toQStandardItemModel(_data, _model);
        _model->blockSignals(false);
        resize_fit(true);
        emit _model->layoutChanged();//to refresh view automatically
    }

    if (GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTableView, Twidget_final, IsPersistent>::is_persistent()) {
        int Mrows = model()->rowCount();
        int Ncols = model()->columnCount();
        QModelIndex index;
        //setUpdatesEnabled(false);
        for (int i = 0; i < Mrows; ++i) {
            for (int j = 0; j < Ncols; ++j) {
                index = model()->index(i, j);
                bool l_type_mismatch = static_cast<QStandardItemModel*>(model())->itemFromIndex(index)->flags() & glv::tdata::type_mismatch_flag;
                if (!QTableView::isPersistentEditorOpen(index) && !l_type_mismatch && IsPersistent) {
                    QTableView::openPersistentEditor(index);
                }

                // If type mismatch : disable editing. Using a type dedicated widget is not possible
                if (l_type_mismatch && !std::is_same<Twidget_final<void>, GlvLineEdit<void>>::value) {//Twidget_final comparison is actually redundant with is_persistent() for now
                    if (!glv::tdata::l_allow_type_mismatch_edit) {
                        Qt::ItemFlags flags = static_cast<QStandardItemModel*>(model())->itemFromIndex(index)->flags();
                        static_cast<QStandardItemModel*>(model())->itemFromIndex(index)->setFlags(flags ^ Qt::ItemIsEditable);
                    }
                }
            }
        }
        //setUpdatesEnabled(true);
    }


    if (GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTableView, Twidget_final, IsPersistent>::is_persistent() && IsPersistent) {
        //horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        int rowCount = model()->rowCount();
        int columnCount = model()->columnCount();
        if (rowCount > 0) {
            for (int j = 0; j < columnCount; j++) {
                QModelIndex index = model()->index(0, j);
                bool l_type_mismatch = static_cast<QStandardItemModel*>(model())->itemFromIndex(index)->flags() & glv::tdata::type_mismatch_flag;
                if (!l_type_mismatch) {
                    horizontalHeader()->setSectionResizeMode(j, QHeaderView::ResizeToContents);
                } else {
                    //horizontalHeader()->setSectionResizeMode(j, QHeaderView::Interactive);
                }
            }
        } else {
            //horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        }

        verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }

}

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
void GlvTableView<Tdata, Twidget_final, IsPersistent>::setEditTriggers(EditTriggers _triggers) {

    if (!GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTableView, Twidget_final, IsPersistent>::is_modeled()) {
        GlvTableView::setEditTriggers(_triggers);
    }

}

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
void GlvTableView<Tdata, Twidget_final, IsPersistent>::set_dynamically_update_data(bool _l_dynamically_update_data) {

    GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTableView, Twidget_final, IsPersistent>* item_delegate = dynamic_cast<GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTableView, Twidget_final, IsPersistent>*>(this->itemDelegate());

    if (item_delegate) {
        item_delegate->set_dynamically_update_data(_l_dynamically_update_data);
    }

}

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
bool GlvTableView<Tdata, Twidget_final, IsPersistent>::is_dynamically_upating_data() const {

    GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTableView, Twidget_final, IsPersistent>* item_delegate = dynamic_cast<GlvItemDelegate<typename glv::tdata::QStandardItemModelMaker<Tdata>::Tdata_sub, GlvTableView, Twidget_final, IsPersistent>*>(this->itemDelegate());
    return item_delegate->is_dynamically_updating_data();

}

template <class Tdata, template <class _Tdata> class Twidget_final, bool IsPersistent>
void GlvTableView<Tdata, Twidget_final, IsPersistent>::cell_changed_slot(const QModelIndex& _index) {

    std::vector<int> coordinates = glv::tdata::get_coordinates<Tdata>(_index);
    emit cell_changed(coordinates);

}

/*! Convenience alias for a GlvTableView with regular line edit.*/
template <class Tdata>
using GlvTableViewLineEdit = GlvTableView<Tdata>;
/*! Convenience alias for a GlvTableView with end editor as GlvWidget.*/
template <class Tdata>
using GlvTableViewWidget = GlvTableView<Tdata, GlvWidget>;
/*! Convenience alias for a GlvTableView with end editor as persistent GlvWidget.*/
template <class Tdata>
using GlvTableViewWidgetPersistent = GlvTableView<Tdata, GlvWidget, true>;
