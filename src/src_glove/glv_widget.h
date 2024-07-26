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

class QWidget;
class QLayout;
class QScrollArea;

/*! Contains functions for the Glv framework.*/
namespace glv {
	/*! Usefull functions for widget handling.*/
	namespace widget {
		/*! \p _widget_scroll: widget containing elements to be scrolled. \p _widget_over : final widget.*/
		QScrollArea* make_scrollable(QWidget* _widget_scroll, QWidget* _widget_over);
		QScrollArea* make_scrollable(QLayout* _layout_scroll, QWidget* _widget_over);

		/*! Clear the layout of \p _widget.*/
		void clear(QWidget* _widget);
		/*! Delete layout items from \p _start_index. If \p _l_recursive is true, layout of items are also being cleared.*/
		void clear(QLayout* _layout, unsigned int _start_index = 0, bool _l_recursive = false);
		/*! Remove \p _widget in \p _layout. Delete \p _widget if \p _l_delete is true.*/
		void remove_widget(QLayout* _layout, QWidget* _widget, bool _l_delete = true);
		/*! Remove widget indexed \p _index in \p _layout. Delete \p _widget if \p _l_delete is true.*/
		void remove_widget(QLayout* _layout, int _index, bool _l_delete = true);

		/*! Performs dynamic_cast of type Tcast on \p _arg. Pops up a critical message on \p _parent if casting fails */
		template <class Tcast, class Targ>
		Tcast dynamic_cast_message_box(Targ* _arg, QWidget* _parent = 0);
	}
};

#include <QMessageBox>

template <class Tcast, class Targ>
Tcast glv::widget::dynamic_cast_message_box(Targ* _arg, QWidget* _parent) {

	Tcast result = dynamic_cast<Tcast>(_arg);
	if (!result) {
		QMessageBox::critical(_parent, QMessageBox::tr(""), QMessageBox::tr("dynamic_cast error from type ") + typeid(Targ*).name() + QMessageBox::tr(" to ") + typeid(Tcast).name());
	}
	return result;
}
