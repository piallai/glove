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

//#include "GlvItemDelegate.h"
#include <QLineEdit>
#include "glv_QStandardItem.h"

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview>
GlvItemDelegate<Tdata, Tview, GlvLineEdit, false, Tenable_GlvItemDelegateGeneral>::GlvItemDelegate(GlvAbstractItemView* _abstract_view, QObject* _parent) :GlvItemDelegate_base(_abstract_view, _parent) {

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview>
GlvItemDelegate<Tdata, Tview, GlvLineEdit, false, Tenable_GlvItemDelegateGeneral>::~GlvItemDelegate() {

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview>
QWidget* GlvItemDelegate<Tdata, Tview, GlvLineEdit, false, Tenable_GlvItemDelegateGeneral>::createEditor(QWidget* _parent, const QStyleOptionViewItem& _option, const QModelIndex& _index) const {

    QWidget* editor = QStyledItemDelegate::createEditor(_parent, _option, _index);

    QLineEdit* text_editor = dynamic_cast<QLineEdit*>(editor);
    connect(text_editor, SIGNAL(textChanged(const QString&)), this, SLOT(resize_text_editor()));
    connect(text_editor, SIGNAL(textChanged(const QString&)), this, SLOT(item_changed_slot(const QString&)));

    return editor;

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview>
void GlvItemDelegate<Tdata, Tview, GlvLineEdit, false, Tenable_GlvItemDelegateGeneral>::destroyEditor(QWidget* _editor, const QModelIndex& _index) const {

    QStyledItemDelegate::destroyEditor(_editor, _index);
    editor_size_changed(NULL);// readjusts view and manages dummies

}

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview>
void GlvItemDelegate<Tdata, Tview, GlvLineEdit, false, Tenable_GlvItemDelegateGeneral>::setEditorData(QWidget* _editor, const QModelIndex& _index) const {

    QStyledItemDelegate::setEditorData(_editor, _index);

}

#define GENERAL_DELEGATE_USE_TYPE

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview>
void GlvItemDelegate<Tdata, Tview, GlvLineEdit, false, Tenable_GlvItemDelegateGeneral>::setModelData(QWidget* _editor, QAbstractItemModel* _model, const QModelIndex& _index) const {

#ifndef GENERAL_DELEGATE_USE_TYPE
    QStyledItemDelegate::setModelData(_editor, _model, _index);
#else
    Tdata data;
    std::istringstream iss(static_cast<QLineEdit*>(_editor)->text().toStdString());
    iss >> data;
    if (_model != _index.model()) {
        slv::flag::ISSUE(slv::flag::Critical, "Should not happen");
    }
    glv::tdata::toQStandardItem(data, dynamic_cast<QStandardItemModel*>(_model)->itemFromIndex(_index));
#endif

}

#undef GENERAL_DELEGATE_USE_TYPE

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview>
void GlvItemDelegate<Tdata, Tview, GlvLineEdit, false, Tenable_GlvItemDelegateGeneral>::updateEditorGeometry(QWidget* _editor, const QStyleOptionViewItem& _option, const QModelIndex& _index) const {

    QStyledItemDelegate::updateEditorGeometry(_editor, _option, _index);
}

#undef Tenable_GlvItemDelegateGeneral
