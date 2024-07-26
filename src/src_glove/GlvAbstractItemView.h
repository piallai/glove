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

class QAbstractItemView;
#include <QRect>
#include <QWidget>
#include <QModelIndex>
#include "SlvMacrosDeclarations.h"

/*! Management of resize of QAbstractItemView due to delegate.*/
class GlvAbstractItemView {

private:

    // Can't diamond virtual inherit QAbstractItemView (qt forbids it). So a pointer can make it
    QAbstractItemView* item_view;
    bool l_fixed_size;

    bool l_check_dummy;//to check if runned twice and problem with add/Remove dummy
    QRect delegate_rect;
    QModelIndex delegate_index;

    /*! Max size of instance. Limits global size in case delegate editor is too large.
    * Used only if l_fixed_size is true.*/
    QSize max_size;

    //mini_offset is used if table_view is itself a delegate. Needed for some reason, otherwise unnecessary scrollbars can appear
    //Tweak parameters. Best case would be not to need them (ie = 0)
    glvm_staticVariable(const, int, mini_offset_x, 2);
    glvm_staticVariable(const, int, mini_offset_y, 2);
    glvm_staticVariable(const, int, mini_offset_with_delegate_x, 2);
    glvm_staticVariable(const, int, mini_offset_with_delegate_y, 2);

public:

    GlvAbstractItemView(QAbstractItemView* _item_view);
    ~GlvAbstractItemView();

    /*! Get QAbstractItemView.*/
    QAbstractItemView* get_item_view();

    /*! Reset QAbstractItemView.*/
    void reset();

    /*! Set max size of instance. Limits global size in case delegate editor is too large.
    * Used only if l_fixed_size is true.*/
    void set_max_size(const QSize& _max_size);
    /*! Set fixed size mode as true or false.
    * If true, the widget will have a fixed size up to max size property.
    * If false, the widget will have a free size for manual resizing.*/
    void set_fixed_size(bool _l_fixed_size);

    /*! Whether to update model data when value changes.*/
    virtual void set_dynamically_update_data(bool _l_dynamically_update_data) = 0;
    /*! Return whether data is dynamically updated or not.*/
    virtual bool is_dynamically_upating_data() const = 0;

private:

    virtual QSize get_view_offset() = 0;

    /*! Get total size of table, including dummy row/column or not.*/
    virtual QSize get_total_size(bool l_manage_dummy) const = 0;
    /*! Get the position of the corner of the delegate.*/
    virtual QSize get_delegate_corner(const QRect& _delegate_rect) const = 0;

    // Every resize_fit is supposed to be used only by GlvTreeView/GlvTableView.
    void resize_fit(bool _l_emit);
    void resize_fit(const QModelIndex& _index, bool _l_emit);
    void resize_fit(const QModelIndex& _index);//for click connection
    void resize_fit(const QRect& _delegate_rect, const QModelIndex& _delegate_index, bool _l_emit);

    /*! To be called only by GlvItemDelegate_base.*/
    void item_delegate_changed(const QRect& _delegate_rect, const QModelIndex& _delegate_index, bool _l_emit = true);
    void item_delegate_changed(bool _l_emit = true);
    /*! Emits sizeChanged() signal of inheriting classes.*/
    virtual void emit_sizeChanged() = 0;

    friend class GlvTableView_base;
    friend class GlvTreeView_base;
    friend class GlvItemDelegate_base;

    QSize get_size(const QSize& _table_size, const QSize& _max_size, bool& l_scrollbar_vertical_x, bool& l_scrollbar_horizontal_y);
    QSize get_size_with_delegate(const QSize& _tab_size, const QRect& _delegate_geometry, bool _l_scrollbar_vertical_x, bool _l_scrollbar_horizontal_y);
    QSize new_size_after_delegate_if_still_needs_scrollbars(const QSize& _new_size, const bool _l_scrollbar_vertical_x, const bool _l_scrollbar_horizontal_y);

    virtual bool manage_dummy_column(int _delegate_offset_x, int _default_size_x, const QModelIndex& _delegate_index) = 0;
    virtual bool manage_dummy_row(int _delegate_offset_y, int _default_size_y, const QModelIndex& _delegate_index) = 0;
    virtual void manage_dummy_remove(bool l_remove_dummy_row, bool l_remove_dummy_column) = 0;

};
