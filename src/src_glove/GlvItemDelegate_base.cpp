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

#include "GlvItemDelegate_base.h"
#include <QLineEdit>
#include "slv_flag.h"
#include <QAbstractItemView>
#include "GlvAbstractItemView.h"
#include "glv_QStandardItemModel.h"

GlvItemDelegate_base::GlvItemDelegate_base(GlvAbstractItemView* _abstract_view, QObject* _parent) :QStyledItemDelegate(_parent) {

    abstract_view = _abstract_view;
    l_dynamically_update_data = true;

}

GlvItemDelegate_base::~GlvItemDelegate_base() {

}

void GlvItemDelegate_base::resize_text_editor() {

    QLineEdit* text_editor = dynamic_cast<QLineEdit*>(sender());

    if (text_editor) {

        QString text = text_editor->text();
        QFontMetrics fm = text_editor->fontMetrics();
        int w = fm.boundingRect(text).width();
        w += 10;
        text_editor->setFixedSize(w, text_editor->height());

    } else {
        slv::flag::ISSUE(slv::flag::Critical, "Should not happen");
    }

}

void GlvItemDelegate_base::item_changed_slot(const QString& _text) {

    QWidget* editor_sending = dynamic_cast<QWidget*>(sender());
    if (editor_sending) {
        emit commitData(editor_sending);//triggers model writing
        editor_size_changed(editor_sending);//messes up resizing because resize_fit pb with QRect for basic QLineEdit
    }

}


void GlvItemDelegate_base::item_changed_slot() {

    QWidget* editor_sending = dynamic_cast<QWidget*>(sender());

    if (editor_sending) {
        editor_size_changed(editor_sending);
    }

}

void GlvItemDelegate_base::editor_size_changed(QWidget* _editor) const {

    if (_editor) {

        _editor->adjustSize();//to refresh editor's size
        QRect rect = _editor->geometry();
        QSize offset = abstract_view->get_view_offset();
        QPoint point(offset.width(), offset.height());
        QRect rect2(_editor->geometry().topLeft() + point, _editor->geometry().bottomRight() + point);
        abstract_view->item_delegate_changed(rect2, current_index, false);

    } else {
        abstract_view->item_delegate_changed(QRect(), QModelIndex(), false);
    }

    abstract_view->emit_sizeChanged();

}

void GlvItemDelegate_base::set_dynamically_update_data(bool _l_dynamically_update_data) {

    l_dynamically_update_data = _l_dynamically_update_data;

}

bool GlvItemDelegate_base::is_dynamically_updating_data() const {

    return l_dynamically_update_data;

}

void GlvItemDelegate_base::value_changed_slot_dynamic_check() {

    if (l_dynamically_update_data) {
        value_changed_slot();
    }

}

void GlvItemDelegate_base::value_changed_slot() {

    QWidget* editor_sending = dynamic_cast<QWidget*>(sender());

    if (editor_sending) {
        emit commitData(editor_sending);//triggers model writing
    }

}

bool GlvItemDelegate_base::is_mismatch_type(const QModelIndex& _index) {
    
    return static_cast<const QStandardItemModel*>(_index.model())->itemFromIndex(_index)->flags() & glv::tdata::type_mismatch_flag;

}