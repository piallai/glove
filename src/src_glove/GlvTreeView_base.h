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

#include <QTreeView>
#include "GlvAbstractItemView.h"

/*! Base class of GlvTreeView.*/
class GlvTreeView_base : public QTreeView, public GlvAbstractItemView {

    Q_OBJECT

private:

    QRect delegate_rect;
    QModelIndex delegate_index;

protected:

    GlvTreeView_base(QWidget* _parent = 0);
    ~GlvTreeView_base();

public:

    void setModel(QAbstractItemModel* _model);

protected:

    void resize_fit(bool l_emit);

private:

    /*! Emits size_Changed() signal. Reimplementation of pure virtual method.*/
    void emit_sizeChanged();

    /*! Get total size of table, including dummy row/column or not.*/
    QSize get_total_size(bool l_manage_dummy) const;
    /*! Get the position of the corner of the delegate.*/
    QSize get_delegate_corner(const QRect& _delegate_rect) const;

    /*! Not operational for now. Manage view enlargement when delegate is opened.*/
    bool manage_dummy_column(int _delegate_offset_x, int _default_size_x, const QModelIndex& _delegate_index);
    /*! Not operational for now. Manage view enlargement when delegate is opened.*/
    bool manage_dummy_row(int _delegate_offset_y, int _default_size_y, const QModelIndex& _delegate_index);
    /*! Not operational for now. Manage view enlargement when delegate is opened.*/
    void manage_dummy_remove(bool l_remove_dummy_row, bool l_remove_dummy_column);

    QSize get_view_offset();

public slots:

    void resize_fit(const QModelIndex& _index);//for click connection

private slots:

    /*! Select index \p _index.*/
    void select(const QModelIndex& _index) const;

signals:

    /*! Emitted whenever model value changes.*/
    void cell_changed();
    /*! Same as cell_changed(). Allow to keep 'cell_changed' for better IDE tracking.*/
    void valueChanged();
    /*! Emitted whenever the size of the widget changes.*/
    void sizeChanged();
};
