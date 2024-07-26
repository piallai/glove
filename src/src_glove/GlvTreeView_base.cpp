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

#include "GlvTreeView_base.h"
#include "slv_flag.h"
#include <QScrollBar>
#include <QApplication>

GlvTreeView_base::GlvTreeView_base(QWidget* _parent) :QTreeView(_parent), GlvAbstractItemView(this) {

    setHeaderHidden(true);

    delegate_rect = QRect();

    connect(this, SIGNAL(cell_changed()), this, SIGNAL(valueChanged()));
}

GlvTreeView_base::~GlvTreeView_base() {

}

void GlvTreeView_base::setModel(QAbstractItemModel* _model) {

    if (model()) {
        disconnect(model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SIGNAL(cell_changed()));
    }
    QTreeView::setModel(_model);
    connect(model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SIGNAL(cell_changed()));

    resize_fit(true);
}

void GlvTreeView_base::select(const QModelIndex& _index) const {

}

void GlvTreeView_base::emit_sizeChanged() {

    emit sizeChanged();
}

void GlvTreeView_base::resize_fit(bool l_emit) {

    GlvAbstractItemView::resize_fit(l_emit);
}

void GlvTreeView_base::resize_fit(const QModelIndex& _index) {

    GlvAbstractItemView::resize_fit(_index);
}

QSize GlvTreeView_base::get_total_size(bool l_manage_dummy) const {

    QSize total_size;

    total_size.setWidth(300);
    total_size.setHeight(300);

    return total_size;
}

QSize GlvTreeView_base::get_delegate_corner(const QRect& _delegate_rect) const {

    QSize delegate_corner;

    int delegate_corner_x = _delegate_rect.x() + _delegate_rect.width();
    int delegate_corner_y = _delegate_rect.y() + _delegate_rect.height();
    delegate_corner.setWidth(delegate_corner_x);
    delegate_corner.setHeight(delegate_corner_y);

    return delegate_corner;
}

bool GlvTreeView_base::manage_dummy_column(int _delegate_offset_x, int _default_size_x, const QModelIndex& _delegate_index) {

    return true;
}

bool GlvTreeView_base::manage_dummy_row(int _delegate_offset_y, int _default_size_y, const QModelIndex& _delegate_index) {

    return true;
}

void GlvTreeView_base::manage_dummy_remove(bool l_remove_dummy_row, bool l_remove_dummy_column) {

}

QSize GlvTreeView_base::get_view_offset() {

    return QSize(QTreeView::horizontalOffset(), QTreeView::verticalOffset());

}
