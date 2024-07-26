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

#include "GlvWidgetSaveLoad_base.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include "GlvOpenFile.h"
#include "glv_flag.h"
#include "glv_QString.h"

GlvWidgetSaveLoad_base::GlvWidgetSaveLoad_base(const SlvFileExtensions& _allowed_extensions, Qt::Orientation _orientation, std::string _data_name) {

	allowed_extensions = _allowed_extensions;

	if (_orientation == Qt::Orientation::Horizontal) {
		layout = new QHBoxLayout;
	} else if (_orientation == Qt::Orientation::Vertical) {
		layout = new QVBoxLayout;
	}
	layout->setContentsMargins(0, 0, 0, 0);
	QPushButton* save_button = new QPushButton(QString(tr("Save")));
	save_button->setToolTip(tr("Save ") + glv::toQString(_data_name) + tr(" in a file."));
	layout->addWidget(save_button);
	QPushButton* load_button = new QPushButton(QString(tr("Load")));
	load_button->setToolTip(tr("Load ") + glv::toQString(_data_name) + tr(" from a file."));
	layout->addWidget(load_button);
	this->setLayout(layout);

	connect(save_button, SIGNAL(clicked()), this, SLOT(save_slot()));
	connect(load_button, SIGNAL(clicked()), this, SLOT(load_slot()));

	open_file = NULL;
}

GlvWidgetSaveLoad_base::~GlvWidgetSaveLoad_base() {

}

void GlvWidgetSaveLoad_base::set_orientation(Qt::Orientation _orientation) {

	QBoxLayout* new_layout = NULL;
	if (_orientation == Qt::Orientation::Vertical && dynamic_cast<QHBoxLayout*>(layout)) {
		new_layout = new QVBoxLayout;
		while (layout->count() > 0) {
			new_layout->addWidget(layout->itemAt(0)->widget());
		}
	} else if (_orientation == Qt::Orientation::Horizontal && dynamic_cast<QVBoxLayout*>(layout)) {
		new_layout = new QHBoxLayout;
		while (layout->count() > 0) {
			new_layout->addWidget(layout->itemAt(0)->widget());
		}
	}
	new_layout->setContentsMargins(0, 0, 0, 0);

	if (new_layout) {
		delete layout;
		layout = new_layout;
		setLayout(layout);
	}

}

SlvFileExtensions GlvWidgetSaveLoad_base::get_allowed_extensions() const {

	return allowed_extensions;

}

void GlvWidgetSaveLoad_base::set_allowed_extensions(const SlvFileExtensions& _allowed_extensions) {

	allowed_extensions = _allowed_extensions;

}

void GlvWidgetSaveLoad_base::paintEvent(QPaintEvent* _event) {

	QPainter painter(this);
	QWidget::paintEvent(_event);

}

void GlvWidgetSaveLoad_base::open_file_save() {

	if (!open_file) {
		open_file = new GlvOpenFile("", allowed_extensions);
	}
	open_file->getSaveFileName();

}

bool GlvWidgetSaveLoad_base::open_file_load() {

	if (!open_file) {
		open_file = new GlvOpenFile("", allowed_extensions);
	}
	return open_file->getOpenFileName();

}

bool GlvWidgetSaveLoad_base::is_ready(QIODevice::OpenMode _mode) {

	if (open_file) {
		return open_file->is_ready(_mode);
	} else {
		/*! open_file should be null is is_ready is called.*/
		return false;
	}

}

std::string GlvWidgetSaveLoad_base::get_file_name() const {

	if (open_file) {
		return open_file->get_file().get_path();
	} else {
		return "";
	}
}

void GlvWidgetSaveLoad_base::delete_open_file() {

	if (open_file) {
		delete open_file;
		open_file = NULL;
	}

}

void GlvWidgetSaveLoad_base::save_slot() {

	GlvWidgetSaveLoad_base::open_file_save();
	if (GlvWidgetSaveLoad_base::is_ready(QIODevice::WriteOnly)) {
		save();
	}
	GlvWidgetSaveLoad_base::delete_open_file();

}

void GlvWidgetSaveLoad_base::load_slot() {

	if (GlvWidgetSaveLoad_base::open_file_load()) {
		if (GlvWidgetSaveLoad_base::is_ready(QIODevice::ReadOnly)) {
			SlvStatus status = load();
			glv::flag::showQMessageBox(status, true, this);
		}
	}
	GlvWidgetSaveLoad_base::delete_open_file();

}
