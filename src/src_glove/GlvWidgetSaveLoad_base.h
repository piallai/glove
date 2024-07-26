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

#pragma once

#include <QWidget>
class GlvOpenFile;
#include <QIODevice>
class QBoxLayout;
#include "filestream/SlvFileExtensions.h"
#include "SlvStatus.h"

/*! Base widget managing save/load (pure virtual).*/
class GlvWidgetSaveLoad_base : public QWidget {

	Q_OBJECT

private:

	QBoxLayout* layout;
	GlvOpenFile* open_file;
	SlvFileExtensions allowed_extensions;

	void paintEvent(QPaintEvent* _event);

protected:
	/* \p _orientation : Orientation of Save/Load buttons. Stacked or side-by-side.*/
	GlvWidgetSaveLoad_base(const SlvFileExtensions& _allowed_extensions, Qt::Orientation _orientation, std::string _data_name);
public:
	virtual ~GlvWidgetSaveLoad_base();

	/* \p _orientation : Orientation of Save/Load buttons. Stacked or side-by-side.*/
	void set_orientation(Qt::Orientation _orientation);

	/*! Return the allowed extensions for saving/loading the file.*/
	SlvFileExtensions get_allowed_extensions() const;
	/*! Set the allowed extensions for saving/loading the file.*/
	void set_allowed_extensions(const SlvFileExtensions& _allowed_extensions);

protected:
	/*! Methods to avoid template GlvWidgetSaveLoad class to include GlvOpenFile.*/
	void open_file_save();
	bool open_file_load();
	bool is_ready(QIODevice::OpenMode _mode);
	std::string get_file_name() const;
	void delete_open_file();

private:

	virtual void save() = 0;
	virtual SlvStatus load() = 0;

private slots:

	void save_slot();
	void load_slot();

};
