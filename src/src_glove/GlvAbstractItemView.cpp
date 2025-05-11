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

#include "GlvAbstractItemView.h"
#include <QAbstractItemView>
#include <QApplication>
#include "slv_flag.h"
#include "glv_flag.h"//for BREAK

GlvAbstractItemView::GlvAbstractItemView(QAbstractItemView* _item_view) {

    l_fixed_size = false;
    item_view = _item_view;

    max_size = QSize(400, 300);

    delegate_rect = QRect();
    delegate_index = QModelIndex();

    l_check_dummy = false;

}

GlvAbstractItemView::~GlvAbstractItemView() {

}

QAbstractItemView* GlvAbstractItemView::get_item_view() {

    return item_view;
}

void GlvAbstractItemView::set_max_size(const QSize& _max_size) {

    max_size = _max_size;
}

void GlvAbstractItemView::set_fixed_size(bool _l_fixed_size) {

    l_fixed_size = _l_fixed_size;
}

void GlvAbstractItemView::item_delegate_changed(const QRect& _delegate_rect, const QModelIndex& _delegate_index, bool l_emit) {

    resize_fit(_delegate_rect, _delegate_index, l_emit);
}

void GlvAbstractItemView::item_delegate_changed(bool l_emit) {

    resize_fit(l_emit);
}

QSize GlvAbstractItemView::get_size(const QSize& _table_size, const QSize& _max_size, bool& l_scrollbar_vertical_x, bool& l_scrollbar_horizontal_y) {

    QSize new_size;

    int table_size_x = _table_size.width();
    int table_size_y = _table_size.height();

    int base_Max_x = _max_size.width();
    int base_Max_y = _max_size.height();
    int Max_x;
    int Max_y;

    int scrollbar_width_x = QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent);//is minored by 1 after a scrollbar is actually created, I don't know why
    int scrollbar_height_y = QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent);

    //stands for widget size
    int basic_size_x = table_size_x + mini_offset_x();//adds a little offset so that a scrollbar doesn't appear if not needed
    int basic_size_y = table_size_y + mini_offset_y();

    Max_x = base_Max_x;
    Max_y = base_Max_y;

    int basic_remain_x = basic_size_x - Max_x;
    if (basic_size_x > Max_x) {
        basic_size_x = Max_x;
        l_scrollbar_horizontal_y = true;
    } else {
        l_scrollbar_horizontal_y = false;
    }

    int basic_remain_y = basic_size_y - Max_y;
    if (basic_size_y > Max_y) {
        basic_size_y = Max_y;
        l_scrollbar_vertical_x = true;
    } else {
        l_scrollbar_vertical_x = false;
    }

    if (l_scrollbar_vertical_x) {
        basic_size_x += std::min(scrollbar_width_x, std::max(-scrollbar_width_x, -basic_remain_x));
    }

    if (l_scrollbar_horizontal_y) {
        basic_size_y += std::min(scrollbar_height_y, std::max(-scrollbar_height_y, -basic_remain_y));
    }

    if (basic_size_x > Max_x) {
        slv::flag::ISSUE(slv::flag::Critical, "Max_x = ", Max_x, ", basic_size_x = ", basic_size_x);
    }
    if (basic_size_y > Max_y) {
        slv::flag::ISSUE(slv::flag::Critical, "Max_y = ", Max_y, ", basic_size_y = ", basic_size_y);
    }

    new_size.setWidth(basic_size_x);
    new_size.setHeight(basic_size_y);

    return new_size;
}

QSize GlvAbstractItemView::get_size_with_delegate(const QSize& _tab_size, const QRect& _delegate_geometry, bool _l_scrollbar_vertical_x, bool _l_scrollbar_horizontal_y) {

    QSize delegate_offset;

    QSize delegate_corner;

    delegate_corner = get_delegate_corner(_delegate_geometry);

    QSize view_offset = get_view_offset();

    int usable_x = _tab_size.width();
    int usable_y = _tab_size.height();

    if (_l_scrollbar_vertical_x) {
        usable_x -= QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent);
    }

    if (_l_scrollbar_horizontal_y) {
        usable_y -= QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent);
    }

    int offset_x = delegate_corner.width() - usable_x;
    int offset_y = delegate_corner.height() - usable_y;

    delegate_offset.setWidth(offset_x);
    delegate_offset.setHeight(offset_y);

    return delegate_offset;
}

QSize GlvAbstractItemView::new_size_after_delegate_if_still_needs_scrollbars(const QSize& _new_size, const bool _l_scrollbar_vertical_x, const bool _l_scrollbar_horizontal_y) {

    //if doesn't need scrollbar anymore, then crop size

    QSize new_size = _new_size;

#define set_scrollbar_mode_blocked 1//should be 1

#if set_scrollbar_mode_blocked==0

    if (_l_scrollbar_vertical_x) {
        if (_new_size.width() > horizontalHeader()->length() + verticalHeader()->width()) {

            new_size.setWidth(new_size.width() - QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent));
        }
    }

    if (_l_scrollbar_horizontal_y) {
        if (_new_size.height() > verticalHeader()->length() + horizontalHeader()->height()) {

            new_size.setHeight(new_size.height() - QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent));
        }
    }

#elif set_scrollbar_mode_blocked==1

    if (_l_scrollbar_vertical_x) {
        if (new_size.height() > get_total_size(false).height()) {
            new_size.setWidth(new_size.width() - QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent));
        }
    }

    if (_l_scrollbar_horizontal_y) {
        if (new_size.width() > get_total_size(false).width()) {
            new_size.setHeight(new_size.height() - QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent));
        }
    }

#else

    if (_l_scrollbar_vertical_x) {
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    } else {
        setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }
    if (_l_scrollbar_horizontal_y) {
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    } else {
        setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }

#endif

    return new_size;
}

void GlvAbstractItemView::resize_fit(bool _l_emit) {

    resize_fit(delegate_rect, delegate_index, _l_emit);

}

void GlvAbstractItemView::resize_fit(const QModelIndex& _index, bool _l_emit) {


    resize_fit(_l_emit);
}

void GlvAbstractItemView::resize_fit(const QModelIndex& _index) {

    resize_fit(QRect(), QModelIndex(), true);
}

void GlvAbstractItemView::resize_fit(const QRect& _delegate_rect, const QModelIndex& _delegate_index, bool _l_emit) {

    delegate_rect = _delegate_rect;
    delegate_index = _delegate_index;

    //_rect comes from delegate's geometry
    //whole method is designed so setFixedSize is called only once (avoid glitches)

    if (!l_check_dummy) {
        l_check_dummy = true;
        QSize table_size;
        table_size = get_total_size(true);

        QSize new_size;
        bool l_scrollbar_vertical_x;
        bool l_scrollbar_horizontal_y;
        new_size = get_size(table_size, max_size, l_scrollbar_vertical_x, l_scrollbar_horizontal_y);

        QSize delegate_offset;
        bool l_remove_dummy_column = false;
        bool l_remove_dummy_row = false;

        if (_delegate_rect != QRect()) {

            delegate_offset = get_size_with_delegate(new_size, _delegate_rect, l_scrollbar_vertical_x, l_scrollbar_horizontal_y);

            if (delegate_offset.width() > 0) {

                int usable_size_x = new_size.width();
                if (l_scrollbar_vertical_x) {
                    usable_size_x -= QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent);
                }
                l_remove_dummy_column = manage_dummy_column(delegate_offset.width(), usable_size_x, delegate_index);
                new_size.setWidth(new_size.width() + delegate_offset.width());
                if (!l_remove_dummy_column) {
                    new_size.setWidth(new_size.width() + mini_offset_with_delegate_x());
                }

            } else {

                l_remove_dummy_column = true;
            }

            if (delegate_offset.height() > 0) {

                int usable_size_y = new_size.height();
                if (l_scrollbar_horizontal_y) {
                    usable_size_y -= QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent);
                }
                l_remove_dummy_row = manage_dummy_row(delegate_offset.height(), usable_size_y, delegate_index);
                new_size.setHeight(new_size.height() + delegate_offset.height());
                if (!l_remove_dummy_row) {
                    new_size.setHeight(new_size.height() + mini_offset_with_delegate_y());
                }
            } else {

                l_remove_dummy_row = true;
            }

            new_size = new_size_after_delegate_if_still_needs_scrollbars(new_size, l_scrollbar_vertical_x, l_scrollbar_horizontal_y);

        } else {

            l_remove_dummy_column = true;
            l_remove_dummy_row = true;
        }

        manage_dummy_remove(l_remove_dummy_row, l_remove_dummy_column);

        if (l_fixed_size) {
            item_view->setFixedSize(new_size);
        }

        item_view->repaint();

        l_check_dummy = false;
        if (_l_emit) {
            emit_sizeChanged();
        }

    } else {
        glv::flag::BREAK("GlvTableView::resize_fit is runned twice at the same time, can cause problem with dummy management", item_view);
    }

}

void GlvAbstractItemView::reset() {

    if (delegate_rect == QRect()) {
        item_view->reset();
    }

}
