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

#include "GlvItemDelegate_spec_General.h"
#include "glv_QStandardItemModel.h"

#define Tenable_GlvItemDelegateModeled typename std::enable_if<glv::tdata::QStandardItemModelMaker<Tdata>::is_specialized>::type

/*! Item delegate for template data for which model maker is known.
* Important: each delegate has to be closed in order to apply the edited values.*/
template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent>
class GlvItemDelegate<Tdata, Tview, Twidget, IsPersistent, Tenable_GlvItemDelegateModeled> : public GlvItemDelegate_base {

public:

    /*! Static const boolean to check if the delegate is modeled or not. Here, true.
    * Usefull to avoid specialization in some cases.*/
    static bool is_modeled() { return true; }
    /*! Whether persistent editor is possible or not.*/
    static bool is_persistent() { return false; }

    GlvItemDelegate(GlvAbstractItemView* _abstract_view, QObject* _parent = 0);
    ~GlvItemDelegate();

private:
    /*! Reimplementation of QStyledItemDelegate.*/
    QWidget* createEditor(QWidget* _parent, const QStyleOptionViewItem& _option, const QModelIndex& _index) const;
    /*! Reimplementation of QStyledItemDelegate.*/
    void destroyEditor(QWidget* _editor, const QModelIndex& _index) const;
    /*! Reimplementation of QStyledItemDelegate.*/
    void paint(QPainter* _painter, const QStyleOptionViewItem& _option, const QModelIndex& _index) const;
    /*! Reimplementation of QStyledItemDelegate.*/
    void setEditorData(QWidget* _editor, const QModelIndex& _index) const;
    /*! Reimplementation of QStyledItemDelegate.*/
    void setModelData(QWidget* _editor, QAbstractItemModel* _model, const QModelIndex& _index) const;
    /*! Reimplementation of QStyledItemDelegate.*/
    QSize sizeHint(const QStyleOptionViewItem& _option, const QModelIndex& _index) const;
    /*! Reimplementation of QStyledItemDelegate.*/
    void updateEditorGeometry(QWidget* _editor, const QStyleOptionViewItem& _option, const QModelIndex& _index) const;
    /*! Reimplementation of QStyledItemDelegate.*/
    bool eventFilter(QObject* _editor, QEvent* _event);
};

#include "GlvItemDelegate_spec_Modeled_impl.h"
