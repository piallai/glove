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

#include "GlvItemDelegate_spec_Modeled.h"
#include "slv_flag.h"
#include <QEvent>

#define delegate_completely_inside_cell 0

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateModeled>::GlvItemDelegate(GlvAbstractItemView* _abstract_view, QObject* _parent) :GlvItemDelegate_base(_abstract_view, _parent) {

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateModeled>::~GlvItemDelegate() {

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
QWidget* GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateModeled>::createEditor(QWidget* _parent, const QStyleOptionViewItem& _option, const QModelIndex& _index) const {

    //bool l_type_mismatch = static_cast<const QStandardItemModel*>(_index.model())->itemFromIndex(_index)->flags() & glv::tdata::type_mismatch_flag;
    if (!is_mismatch_type(_index)) {
        Tview<Tdata, Twidget, IsPersistent>* editor;

        editor = new Tview<Tdata, Twidget, IsPersistent>(_parent);
        editor->set_fixed_size(true);
        editor->set_dynamically_update_data(l_dynamically_update_data);
        connect(editor, SIGNAL(sizeChanged()), this, SLOT(item_changed_slot()));
        connect(editor, SIGNAL(valueChanged(const std::vector<int>&)), this, SLOT(value_changed_slot_dynamic_check()));
        const_cast<GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateModeled>*>(this)->current_index = _index;

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
void GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateModeled>::destroyEditor(QWidget* _editor, const QModelIndex& _index) const {

    QStyledItemDelegate::destroyEditor(_editor, _index);
    editor_size_changed(NULL);// readjusts view and manages dummies
    const_cast<GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateModeled>*>(this)->current_index = QModelIndex();

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
void GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateModeled>::paint(QPainter* _painter, const QStyleOptionViewItem& _option, const QModelIndex& _index) const {

    QStyledItemDelegate::paint(_painter, _option, _index);

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
void GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateModeled>::setEditorData(QWidget* _editor, const QModelIndex& _index) const {

    if (!is_mismatch_type(_index)) {
        //used when editor is opened
        const QStandardItemModel* model = dynamic_cast<const QStandardItemModel*>(_index.model());
        Tdata data = glv::tdata::fromQStandardItemModel<Tdata>(model, _index);
        static_cast<Tview<Tdata, Twidget, IsPersistent>*>(_editor)->set_value(data);
    } else {
        QStyledItemDelegate::setEditorData(_editor, _index);
    }

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
void GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateModeled>::setModelData(QWidget* _editor, QAbstractItemModel* _model, const QModelIndex& _index) const {

    //used when editor is closed
    //Warning : modifying _model at _index triggers setEditorData. So, glv::tdata::toQStandardItemModel must modify at index last after anything

    if (!is_mismatch_type(_index)) {
        Tdata data = static_cast<Tview<Tdata, Twidget, IsPersistent>*>(_editor)->get_value();
        if (_model != _index.model()) {
            slv::flag::ISSUE(slv::flag::Critical, "Should not happen");
        }
        glv::tdata::toQStandardItemModel(data, dynamic_cast<QStandardItemModel*>(_model), _index);//something here triggers setEditorData
    } else {
        QStyledItemDelegate::setModelData(_editor, _model, _index);
    }

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
QSize GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateModeled>::sizeHint(const QStyleOptionViewItem& _option, const QModelIndex& _index) const {

#if delegate_completely_inside_cell==1
    if (persistent_editors.find(_index) != persistent_editors.end()) {
        persistent_editors.at(_index)->adjustSize();
        QSize size = persistent_editors.at(_index)->sizeHint();
        size.setWidth(size.width() - 20);
        size.setHeight(size.height() - 10);
        return size;
    } else {
        return QStyledItemDelegate::sizeHint(_option, _index);
    }
#else
    return QStyledItemDelegate::sizeHint(_option, _index) + QSize(0, 0);
#endif

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
void GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateModeled>::updateEditorGeometry(QWidget* _editor, const QStyleOptionViewItem& _option, const QModelIndex& _index) const {

    QRect rect = _option.rect;
    QSize size = _editor->sizeHint();
    rect.setSize(size);
#if delegate_completely_inside_cell==1
    rect.setX(rect.x() - 10);
    rect.setY(rect.y() - 5);
#endif

    _editor->setGeometry(rect);//warning, triggers sizeChanged() of editor

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
bool GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateModeled>::eventFilter(QObject* _editor, QEvent* _event) {

    if (_event->type() == QEvent::FocusOut) {
        return true;
    } else {
        return QStyledItemDelegate::eventFilter(_editor, _event);
    }

}

#undef Tenable_GlvItemDelegateModeled
