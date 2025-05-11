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

#include <QLineEdit>
#include "glv_QStandardItem.h"

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateWidget>::GlvItemDelegate(GlvAbstractItemView* _abstract_view, QObject* _parent) :GlvItemDelegate_base(_abstract_view, _parent) {

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateWidget>::~GlvItemDelegate() {

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
QWidget* GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateWidget>::createEditor(QWidget* _parent, const QStyleOptionViewItem& _option, const QModelIndex& _index) const {

    if (!is_mismatch_type(_index)) {
        Twidget<Tdata>* editor;

        editor = new Twidget<Tdata>(_parent);
        connect(editor, SIGNAL(sizeChanged()), this, SLOT(item_changed_slot()));
        connect(editor, SIGNAL(valueChanged()), this, SLOT(value_changed_slot()));
        const_cast<GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateWidget>*>(this)->current_index = _index;
        editor->setAutoFillBackground(true);

        return editor;
    } else {
        QWidget* editor = QStyledItemDelegate::createEditor(_parent, _option, _index);

        QLineEdit* text_editor = dynamic_cast<QLineEdit*>(editor);
        connect(text_editor, SIGNAL(textChanged(const QString&)), this, SLOT(resize_text_editor()));
        connect(text_editor, SIGNAL(textChanged(const QString&)), this, SLOT(item_changed_slot(const QString&)));

        return editor;
    }

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
void GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateWidget>::destroyEditor(QWidget* _editor, const QModelIndex& _index) const {

    QStyledItemDelegate::destroyEditor(_editor, _index);
    _editor = 0;
    editor_size_changed(_editor);
    const_cast<GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateWidget>*>(this)->current_index = QModelIndex();

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
void GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateWidget>::paint(QPainter* _painter, const QStyleOptionViewItem& _option, const QModelIndex& _index) const {

    QStyledItemDelegate::paint(_painter, _option, _index);

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
void GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateWidget>::setEditorData(QWidget* _editor, const QModelIndex& _index) const {

    if (!is_mismatch_type(_index)) {
        const QStandardItemModel* model = dynamic_cast<const QStandardItemModel*>(_index.model());
        Tdata data = glv::tdata::fromQStandardItem<Tdata>(model->itemFromIndex(_index));
        static_cast<Twidget<Tdata>*>(_editor)->set_value(data);
    } else {
        QStyledItemDelegate::setEditorData(_editor, _index);
    }

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
void GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateWidget>::setModelData(QWidget* _editor, QAbstractItemModel* _model, const QModelIndex& _index) const {

    //used when editor is closed
    //Warning : modifying _model at _index triggers setEditorData. So, glv::tdata::toQStandardItemModel must modify at index last after anything

    if (!is_mismatch_type(_index)) {
        Tdata data = static_cast<Twidget<Tdata>*>(_editor)->get_value();
        if (_model != _index.model()) {
            slv::flag::ISSUE(slv::flag::Critical, "Should not happen");
        }
        glv::tdata::toQStandardItem(data, dynamic_cast<QStandardItemModel*>(_model)->itemFromIndex(_index));//something here triggers setEditorData
    } else {
        QStyledItemDelegate::setModelData(_editor, _model, _index);
    }

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
QSize GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateWidget>::sizeHint(const QStyleOptionViewItem& _option, const QModelIndex& _index) const {

    return QStyledItemDelegate::sizeHint(_option, _index);

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
void GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateWidget>::updateEditorGeometry(QWidget* _editor, const QStyleOptionViewItem& _option, const QModelIndex& _index) const {

    QRect rect = _option.rect;
    QSize size = _editor->sizeHint();
    rect.setSize(size);

    _editor->setGeometry(rect);//warning, triggers sizeChanged() of editor

}

#undef Tenable_GlvItemDelegateWidget
