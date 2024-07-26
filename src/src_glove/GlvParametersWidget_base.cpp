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

GlvParametersWidget_base::GlvParametersWidget_base() {

	vertical_layout = new QVBoxLayout;
	this->setLayout(vertical_layout);

	save_load_widget = NULL;
}

GlvParametersWidget_base::~GlvParametersWidget_base() {

}

void GlvParametersWidget_base::set_layout_vertical() {

	set_layout_type(LayoutType::Vertical);
	if (save_load_widget) {
		this->vertical_layout->addWidget(save_load_widget);
	}

}

void GlvParametersWidget_base::set_layout_grid() {

	set_layout_type(LayoutType::Grid);
	if (save_load_widget) {
		grid_layout->addWidget(save_load_widget, getNparameters(), 0, 1, 2, Qt::AlignCenter);
	}

}

void GlvParametersWidget_base::set_save_load_widget(GlvWidgetSaveLoad_base* _save_load_widget) {

	save_load_widget = _save_load_widget;
	if (save_load_widget) {
		if (layout_type == LayoutType::Vertical) {
			this->vertical_layout->addWidget(save_load_widget);
		} else {
			grid_layout->addWidget(save_load_widget, getNparameters(), 1, 1, 1, Qt::AlignRight);
		}
	}

}

void GlvParametersWidget_base::set_layout_type_pv(LayoutType _layout_type) {

	bool l_update_layout = false;
	if (layout_type != _layout_type) {
		l_update_layout = true;
	}
	layout_type = _layout_type;

	if (l_update_layout) {
		delete QWidget::layout();
		if (layout_type == LayoutType::Vertical) {
			vertical_layout = new QVBoxLayout;
			this->setLayout(vertical_layout);
		} else if (layout_type == LayoutType::Grid) {
			grid_layout = new QGridLayout;
			grid_layout->setHorizontalSpacing(grid_horizontal_spacing());
			this->setLayout(grid_layout);
		}
	}

}

void GlvParametersWidget_base::add_parameter_widget_to_vertical_layout(QWidget* _parameter_widget) {

	this->vertical_layout->addWidget(_parameter_widget);

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

void GlvParametersWidget_base::show_parameters(bool _l_show) {

	QLayout* layout = NULL;
	if (layout_type == LayoutType::Vertical) {
		layout = vertical_layout;
	} else if (layout_type == LayoutType::Grid) {
		layout = grid_layout;
	}
	for (int i = 0; i < layout->count(); i++) {
		QWidget* widget = layout->itemAt(i)->widget();
		widget->setVisible(_l_show);
	}

}
