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

#include "GlvParametersWidget_base.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include "GlvWidgetSaveLoad_base.h"
#include "glv_widget.h"
#include <QScrollArea>
#include <QScrollBar>
#include <QApplication>
#include <QStyle>
#include <QScreen>
#include <QResizeEvent>

glvm_staticVariable_impl(const, int, GlvParametersWidget_base, layout_margin, QApplication::style()->pixelMetric(QStyle::PM_LayoutLeftMargin));

class GlvParametersWidget_base::ScrollArea : public QScrollArea {
public:
	bool eventFilter(QObject* object, QEvent* event) {
		if (object == widget() && event->type() == QEvent::Resize) {

			int min_width = widget()->sizeHint().width();
			int max_width = QGuiApplication::primaryScreen()->geometry().width() - 100;
			if (min_width > max_width) {
				min_width = max_width;
			}
			if (widget()->size().height() > QScrollArea::size().height()) {
				min_width += QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent);
			}
			QScrollArea::setMinimumWidth(min_width);
		}
		return false;
	}
	bool is_expanded_vertically() const {
		return widget()->size().height() > QScrollArea::size().height();
	}
};

GlvParametersWidget_base::GlvParametersWidget_base() {

	main_layout = new QVBoxLayout;
	main_layout->setContentsMargins(layout_margin(), layout_margin(), 0, layout_margin());
	this->setLayout(main_layout);

	parameters_widget = new QWidget;
	parameters_widget->installEventFilter(this);
	vertical_layout = new QVBoxLayout;
	parameters_widget->setLayout(vertical_layout);
	parameters_widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);//here

	l_scrollable = false;
	scroll_area = NULL;
	main_layout->addWidget(parameters_widget);

	set_scrollable(true);

	l_height_decreased = false;
	l_adapt_max_height = false;

	save_load_widget = NULL;
}

GlvParametersWidget_base::~GlvParametersWidget_base() {

}

void GlvParametersWidget_base::set_layout_vertical() {

	set_layout_type(LayoutType::Vertical);

}

void GlvParametersWidget_base::set_layout_grid() {

	set_layout_type(LayoutType::Grid);

}

bool GlvParametersWidget_base::is_fully_visible() const {

	return !l_scrollable || !scroll_area->is_expanded_vertically();

}

void GlvParametersWidget_base::set_save_load_widget(GlvWidgetSaveLoad_base* _save_load_widget) {

	save_load_widget = _save_load_widget;
	if (save_load_widget) {
		save_load_widget->layout()->setContentsMargins(0, 0, layout_margin() - QApplication::style()->pixelMetric(QStyle::QStyle::PM_DefaultFrameWidth), 0);
		main_layout->addWidget(save_load_widget, 0, Qt::AlignRight | Qt::AlignBottom);
	}

}

void GlvParametersWidget_base::set_layout_type_protected(LayoutType _layout_type) {

	bool l_update_layout = false;
	if (layout_type != _layout_type) {
		l_update_layout = true;
	}
	layout_type = _layout_type;

	if (l_update_layout) {
		delete parameters_widget->layout();
		if (layout_type == LayoutType::Vertical) {
			vertical_layout = new QVBoxLayout;
			parameters_widget->setLayout(vertical_layout);
		} else if (layout_type == LayoutType::Grid) {
			grid_layout = new QGridLayout;
			grid_layout->setContentsMargins(0, 0, layout_margin(), 0);
			grid_layout->setHorizontalSpacing(grid_horizontal_spacing());
			parameters_widget->setLayout(grid_layout);
		}
	}

}

void GlvParametersWidget_base::add_parameter_widget_to_vertical_layout(QWidget* _parameter_widget) {

	vertical_layout->addWidget(_parameter_widget);

}

void GlvParametersWidget_base::add_parameter_widget_to_grid_layout(QWidget* _dataname_label, QWidget* _data_widget, QWidget* _optional_text_label, int i) {

	if (_dataname_label) {
		grid_layout->addWidget(_dataname_label, i, 0);
	}
	grid_layout->addWidget(_data_widget, i, 1);
	if (_optional_text_label) {
		grid_layout->addWidget(_optional_text_label, i, 2);
	}

}

void GlvParametersWidget_base::set_checkable_collapse(bool _l_checkable) {

	if (_l_checkable) {
		QGroupBox::setCheckable(true);
		connect(this, SIGNAL(toggled(bool)), this, SLOT(show_parameters(bool)));
		setChecked(false);
		this->setToolTip(tr("Show/hide nested parameters"));
	} else {
		setChecked(true);
		disconnect(this, SIGNAL(toggled(bool)));
		QGroupBox::setCheckable(false);
		this->setToolTip(tr(""));
	}
	

}

void GlvParametersWidget_base::set_scrollable(bool _l_scrollable) {

	if (!_l_scrollable && l_scrollable) {

		main_layout->insertWidget(0, parameters_widget);
		delete scroll_area;
		scroll_area = NULL;

	} else if (_l_scrollable && !l_scrollable) {

		scroll_area = new ScrollArea;
		scroll_area->setWidgetResizable(true);
		scroll_area->setWidget(parameters_widget);
		scroll_area->setFrameShape(QFrame::NoFrame);
		main_layout->addWidget(scroll_area, 0);

	}

	l_scrollable = _l_scrollable;


}

void GlvParametersWidget_base::set_adapt_max_height(bool _l_adapt) {

	l_adapt_max_height = _l_adapt;

}

void GlvParametersWidget_base::show_parameters(bool _l_show) {

	parameters_widget->setVisible(_l_show);

	if (save_load_widget) {
		save_load_widget->setVisible(_l_show);
	}

}

bool GlvParametersWidget_base::has_height_decreased() const {

	return l_height_decreased;

}

bool GlvParametersWidget_base::eventFilter(QObject* object, QEvent* _event) {

	if (object == parameters_widget && _event->type() == QEvent::Resize) {

		QResizeEvent* resize_event = dynamic_cast<QResizeEvent*>(_event);
		if (resize_event->size().height() < resize_event->oldSize().height()) {
			l_height_decreased = true;
			emit heightChanged();
		} else if (resize_event->size().height() > resize_event->oldSize().height()) {
			l_height_decreased = false;
			emit heightChanged();
		} else if (l_adapt_max_height) {
			l_height_decreased = false;
		}

	}
	return false;

}
