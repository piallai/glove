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

#include "glv_widget.h"
#include <QScrollArea>
#include <QHBoxLayout>
#include "slv_flag.h"

QScrollArea* glv::widget::make_scrollable(QWidget* _widget_scroll, QWidget* _widget_over) {

	QScrollArea* scroll_area = new QScrollArea;
	scroll_area->setWidgetResizable(true);
	QBoxLayout* layout = new QHBoxLayout;

	scroll_area->setWidget(_widget_scroll);
	layout->addWidget(scroll_area);

	_widget_over->setLayout(layout);

	return scroll_area;
}

QScrollArea* glv::widget::make_scrollable(QLayout* _layout_scroll, QWidget* _widget_over) {

	QWidget* widget_scroll = new QWidget;
	widget_scroll->setLayout(_layout_scroll);

	return make_scrollable(widget_scroll, _widget_over);

}

void glv::widget::clear(QWidget* _widget) {

	QLayout* layout = _widget->layout();
	if (layout) {
		clear(layout);
		delete layout;
	}

}

void glv::widget::clear(QLayout* _layout, unsigned int _start_index, bool _l_recursive) {

	if (_layout) {
		QLayoutItem* item;
		while ((item = _layout->takeAt(_start_index))) {
			if (_l_recursive && item->layout()) {
				clear(item->layout(), 0);
				delete item->layout();
			}
			if (item->widget()) {
				delete item->widget();
			}
			delete item;
		}
	}

}

void glv::widget::remove_widget(QLayout* _layout, QWidget* _widget, bool _l_delete) {

	if (_widget) {
		_layout->removeWidget(_widget);
		if (_l_delete) {
			delete _widget;
		} else {
			_widget->setParent(NULL);
		}
	} else {
		slv::flag::ISSUE(slv::flag::Critical, "no _widget");
	}

}

void glv::widget::remove_widget(QLayout* _layout, int _index, bool _l_delete) {

	QLayoutItem* item = _layout->takeAt(_index);
	if (item) {
		glv::widget::remove_widget(_layout, item->widget(), _l_delete);
		if (_l_delete) {
			delete item;
		}
	} else {
		slv::flag::ISSUE(slv::flag::Critical, "no item");
	}

}
