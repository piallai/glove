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

#include <QTableView>
#include "GlvAbstractItemView.h"

/*! Base class of GlvTableView.*/
class GlvTableView_base : public QTableView, public GlvAbstractItemView {

    Q_OBJECT

private:
    /*! Edit triggers savec when switching from editable to not editable.*/
    QAbstractItemView::EditTriggers edit_triggers;

protected:

    /*! Whether a row is added to make space for delegate widget.*/
    bool l_dummy_row;
    /*! Whether a column is added to make space for delegate widget.*/
    bool l_dummy_column;

protected://could be public, but there is not real reason for GlvTableView to be

    GlvTableView_base(QWidget* _parent = 0);
    ~GlvTableView_base();

public:

    /*! Reimplementation of QTableView::setModel.*/
    void setModel(QAbstractItemModel* _model);

    /*! Allow edition or not.*/
    void set_editable(bool _l_edit);

    /*! Reimplementation to save editable triggers.*/
    void setEditTriggers(QAbstractItemView::EditTriggers _triggers);

protected:

    /*! Resize table to fit content. \p _l_emit : whether to emit sizeChanged or not.*/
    void resize_fit(bool _l_emit);

    /*! Set dummy row/column status to false.*/
    void reset_dummies();

    void showEvent(QShowEvent* _event);

private:

    /*! Get total size of table, including dummy row/column or not.*/
    QSize get_total_size(bool _l_manage_dummy) const;
    /*! Get the position of the corner of the delegate.*/
    QSize get_delegate_corner(const QRect& _delegate_rect) const;
    /*! Emits size_Changed() signal. Reimplementation of pure virtual method.*/
    void emit_sizeChanged();

    /*! Manage view enlargement when delegate is opened.*/
    bool manage_dummy_column(int _delegate_offset_x, int _default_size_x, const QModelIndex& _delegate_index);
    /*! Manage view enlargement when delegate is opened.*/
    bool manage_dummy_row(int _delegate_offset_y, int _default_size_y, const QModelIndex& _delegate_index);
    /*! Manage view enlargement when delegate is opened.*/
    void manage_dummy_remove(bool l_remove_dummy_row, bool l_remove_dummy_column);

    QSize get_view_offset();

private slots:

    void resize_fit(const QModelIndex& _index);//for click connection

    /*! Select index \p _index.*/
    void select(const QModelIndex& _index) const;

    /*! Emit the coordinates corresponding to \p _index accord to data dimension.*/
    virtual void cell_changed_slot(const QModelIndex& _index) = 0;

protected slots:
    /*! Reimplementation. Recursivity only is dynamic update of data is false, in order to appl a full commit when closing the editor.
    * See: set_dynamically_update_data() */
    void commitData(QWidget* editor);
private:
    void commitData();


signals:

    /*! Emitted whenever model value changes. \p _coordinates are the coordinates of the cell which changed.*/
    void cell_changed(const std::vector<int>& _coordinates);
    /*! Same as cell_changed(). Allow to keep 'cell_changed' for better IDE tracking.*/
    void valueChanged(const std::vector<int>& _coordinates);
    /*! Emitted whenever the size of the widget changes.*/
    void sizeChanged();

};

