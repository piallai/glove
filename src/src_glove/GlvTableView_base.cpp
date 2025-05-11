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

#include "GlvTableView_base.h"
#include <QHeaderView>
#include <QApplication>//to access scrollbar default width and height
#include "slv_flag.h"//for debug
#include <QStandardItem>//for adding dummy label

GlvTableView_base::GlvTableView_base(QWidget* _parent) :QTableView(_parent), GlvAbstractItemView(this) {


    setEditTriggers(QAbstractItemView::CurrentChanged);

    // Works but slow if large number of data //////////////////
    //horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);// Do not use QHeaderView::Stretch
    //verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);// Do not use QHeaderView::Stretch
    ////////////////////////////////////////////////////////////

    connect(this, SIGNAL(cell_changed(const std::vector<int>&)), this, SIGNAL(valueChanged(const std::vector<int>&)));

    l_dummy_column = false;
    l_dummy_row = false;

    horizontalHeader()->setMinimumSectionSize(0);
    verticalHeader()->setMinimumSectionSize(0);

}

GlvTableView_base::~GlvTableView_base() {

}

void GlvTableView_base::commitData(QWidget* _editor) {

    if (!is_dynamically_upating_data()) {
        GlvTableView_base* editor_view = dynamic_cast<GlvTableView_base*>(_editor);
        if (editor_view) {
            editor_view->commitData();
        }
    }
    QAbstractItemView::commitData(_editor);
}

void GlvTableView_base::commitData() {

    commitData(indexWidget(currentIndex()));

}

void GlvTableView_base::setModel(QAbstractItemModel* _model) {

    if (model()) {
        disconnect(model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SIGNAL(cell_changed()));
    }
    reset_dummies();
    QTableView::setModel(_model);
    connect(model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(cell_changed_slot(const QModelIndex&)));

    GlvAbstractItemView::resize_fit(true);

}

void GlvTableView_base::set_editable(bool _l_edit) {

    if (_l_edit) {
        setEditTriggers(edit_triggers);
    } else {
        setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

void GlvTableView_base::setEditTriggers(QAbstractItemView::EditTriggers _triggers) {

    if (_triggers != QAbstractItemView::NoEditTriggers) {
        edit_triggers = _triggers;
    }

    QAbstractItemView::setEditTriggers(_triggers);

}

void GlvTableView_base::select(const QModelIndex& _index) const {

    selectionModel()->select(_index, QItemSelectionModel::SelectCurrent);
}

void GlvTableView_base::reset_dummies() {

    l_dummy_row = false;
    l_dummy_column = false;
}

void GlvTableView_base::emit_sizeChanged() {

    emit sizeChanged();

}

void GlvTableView_base::showEvent(QShowEvent* _event) {

    QTableView::showEvent(_event);
    repaint();
    GlvAbstractItemView::resize_fit(true);

}

void GlvTableView_base::resize_fit(const QModelIndex& _index) {

    GlvAbstractItemView::resize_fit(_index);

}

void GlvTableView_base::resize_fit(bool _l_emit) {

    GlvAbstractItemView::resize_fit(_l_emit);

}

bool GlvTableView_base::manage_dummy_column(int _delegate_offset_x, int _default_size_x, const QModelIndex& _delegate_index) {

    //MANAGE DUMMY

    bool l_remove_dummy_column;

    //first, checks if delegate_offset is higher than headerview's size, and therefore need to create a dummy
    int column_index;
    column_index = _delegate_index.column();

    int remaining_size = 0;
    for (int i = column_index + 1; i < model()->columnCount() - l_dummy_column; i++) {
        remaining_size += horizontalHeader()->sectionSize(i);
    }

    //remaining_space is the space left on the right between selected cell and end of widget (ie visible)
    int remaining_space_right = _default_size_x - (columnViewportPosition(column_index) + horizontalHeader()->sectionSize(column_index) + verticalHeader()->width());
    remaining_space_right -= get_view_offset().width();
    remaining_size -= remaining_space_right;

    if (horizontalHeader()->length() + verticalHeader()->width() + mini_offset_with_delegate_x() < _default_size_x) {
        if (remaining_size < 0) {
            remaining_size = 0;
        }
    }

    //if needed, creates a dummy
    if (_delegate_offset_x > remaining_size) {
        if (!l_dummy_column) {
            l_dummy_column = true;
            model()->blockSignals(true);
            model()->insertColumn(model()->columnCount());
            model()->blockSignals(false);
            dynamic_cast<QStandardItemModel*>(model())->setHorizontalHeaderItem(model()->columnCount() - 1, new QStandardItem(""));
            horizontalHeader()->setSectionResizeMode(model()->columnCount() - 1, QHeaderView::Fixed);
        }
        int dummy_offset = _delegate_offset_x - remaining_size;
        horizontalHeader()->resizeSection(model()->columnCount() - 1, dummy_offset);
        l_remove_dummy_column = false;

    } else {
        l_remove_dummy_column = true;
    }

    return l_remove_dummy_column;

}

bool GlvTableView_base::manage_dummy_row(int _delegate_offset_y, int _default_size_y, const QModelIndex& _delegate_index) {

    bool l_remove_dummy_row;

    //first, checks if delegate_offset is higher than headerview's size, and therefore need to create a dummy
    int row_index;
    row_index = _delegate_index.row();

    int remaining_size = 0;
    for (int i = row_index + 1; i < model()->rowCount() - l_dummy_row; i++) {
        remaining_size += verticalHeader()->sectionSize(i);
    }

    //remaining_space is the space left on bottom between selected cell and end of widget (ie visible)
    int remaining_space_bottom = _default_size_y - (rowViewportPosition(row_index) + verticalHeader()->sectionSize(row_index) + horizontalHeader()->height());
    remaining_space_bottom -= get_view_offset().height();
    remaining_size -= remaining_space_bottom;

    if (verticalHeader()->length() + horizontalHeader()->height() + mini_offset_with_delegate_y() < _default_size_y) {
        if (remaining_size < 0) {
            remaining_size = 0;
        }
    }

    //if needed, creates a dummy
    if (_delegate_offset_y > remaining_size) {
        if (!l_dummy_row) {
            l_dummy_row = true;
            model()->blockSignals(true);
            model()->insertRow(model()->rowCount());
            model()->blockSignals(false);
            dynamic_cast<QStandardItemModel*>(model())->setVerticalHeaderItem(model()->rowCount() - 1, new QStandardItem(""));
            verticalHeader()->setSectionResizeMode(model()->rowCount() - 1, QHeaderView::Fixed);
        }
        int dummy_offset = _delegate_offset_y - remaining_size;
        verticalHeader()->resizeSection(model()->rowCount() - 1, dummy_offset);

        l_remove_dummy_row = false;

    } else {
        l_remove_dummy_row = true;
    }

    return l_remove_dummy_row;

}

void GlvTableView_base::manage_dummy_remove(bool l_remove_dummy_row, bool l_remove_dummy_column) {

    //TRIGGERS RESIZE EVENT, THUS GlvWidget_base::sizeChanged() signal is GlvTableView is inside a GlvWidgetData which is inside a GlvWidget
    if (l_remove_dummy_column) {
        if (l_dummy_column) {
            l_dummy_column = false;
            // Provided this table_view contains an item delegate opened, triggers updateEditorGeometry in GlvItemDelegate if editor is opened.*/
            model()->removeColumn(model()->columnCount() - 1);
            // Triggers GlvItemDelegate::destroyEditor, which can cause loop back here in this function
        } else {
            //slv::flag::ISSUE(slv::flag::Critical, "Should not remove dummy_column, when there is none");
        }
    }

    if (l_remove_dummy_row) {
        if (l_dummy_row) {
            l_dummy_row = false;
            // Provided this table_view contains an item delegate opened, triggers updateEditorGeometry in GlvItemDelegate if editor is opened
            model()->removeRow(model()->rowCount() - 1);
        } else {
            //slv::flag::ISSUE(slv::flag::Critical, "Should not remove dummy_row, when there is none");
        }
    }

}

QSize GlvTableView_base::get_total_size(bool _l_manage_dummy) const {

    QSize total_size;

    total_size.setWidth(horizontalHeader()->length() + verticalHeader()->sizeHint().width());//why sizeHint ??
    total_size.setHeight(verticalHeader()->length() + horizontalHeader()->sizeHint().height());

    if (_l_manage_dummy) {
        //if there are dummy column or row, need to remove their size to compute real table_size
        if (l_dummy_column) {
            total_size.setWidth(total_size.width() - horizontalHeader()->sectionSize(model()->columnCount() - 1));
        }
        if (l_dummy_row) {
            total_size.setHeight(total_size.height() - verticalHeader()->sectionSize(model()->rowCount() - 1));
        }
    }

    return total_size;
}

QSize GlvTableView_base::get_delegate_corner(const QRect& _delegate_rect) const {

    QSize delegate_corner;

    int delegate_corner_x = _delegate_rect.x() + _delegate_rect.width() + verticalHeader()->sizeHint().width();
    int delegate_corner_y = _delegate_rect.y() + _delegate_rect.height() + horizontalHeader()->sizeHint().height();
    delegate_corner.setWidth(delegate_corner_x);
    delegate_corner.setHeight(delegate_corner_y);

    return delegate_corner;

}

QSize GlvTableView_base::get_view_offset() {

    return QSize(QTableView::horizontalOffset(), QTableView::verticalOffset());

}
