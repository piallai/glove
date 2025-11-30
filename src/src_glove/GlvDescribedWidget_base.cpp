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

#include "GlvDescribedWidget_base.h"
#include <QGridLayout>
#include <QLabel>
#include "glv_QString.h"

GlvDescribedWidget_base::GlvDescribedWidget_base(const std::string& _data_name) :data_name(_data_name) {

	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);

	if (!data_name.empty()) {
		data_name_label = new QLabel(glv::toQString(data_name));
		layout->addWidget(data_name_label, 0, 0);
	} else {
		data_name_label = NULL;
	}

	optional_text_label = NULL;

	this->setLayout(layout);

}

GlvDescribedWidget_base::~GlvDescribedWidget_base() {

}

void GlvDescribedWidget_base::set_alias(const std::string& _alias) {

	if (data_name_label && !_alias.empty()) {
		data_name_label->setToolTip(glv::toQString(_alias));
	}

}

const std::string& GlvDescribedWidget_base::get_data_name() const {

	return data_name;

}

std::string GlvDescribedWidget_base::get_data_alias() const {

	if (data_name_label) {
		return data_name_label->toolTip().toStdString();
	} else {
		return std::string();
	}

}

void GlvDescribedWidget_base::set_data_widget(QWidget* _data_widget, const QString& _optional_text_str) {

	layout->addWidget(_data_widget, 1, 0);
	if (!_optional_text_str.isEmpty()) {
		if (!optional_text_label) {
			optional_text_label = new QLabel;
			layout->addWidget(optional_text_label, 1, 1);
		}
		optional_text_label->setText(_optional_text_str);
	} else {
		delete optional_text_label;
		optional_text_label = NULL;
	}

}

void GlvDescribedWidget_base::reclaim_widgets_ownership(QWidget* _data_widget) {

	if (!data_name.empty()) {
		layout->addWidget(data_name_label, 0, 0);
	}
	layout->addWidget(_data_widget, 1, 0);
	if (optional_text_label) {
		layout->addWidget(optional_text_label, 1, 1);
	}

}
