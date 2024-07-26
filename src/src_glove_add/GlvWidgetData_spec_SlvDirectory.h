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

#include "GlvWidgetData.h"
#include "GlvOpenDirectory.h"

#define Tdata SlvDirectory

/*! GlvWidgetData for type SlvDirectory.*/
template <>
class GlvWidgetData<Tdata> : public GlvOpenDirectory {

public:
	GlvWidgetData(Tdata _file = Tdata(), QWidget* _parent = 0);
	~GlvWidgetData();

	Tdata get_value() const {
		return GlvOpenDirectory::get_directory();
	}
	void set_value(const Tdata& _value) {
		return GlvOpenDirectory::set_directory(_value);
	}

};

#include "GlvWidgetMakerConnect.h"
template <>
struct GlvWidgetMakerConnect<Tdata> {
	static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
		QObject::connect(_widget, SIGNAL(directory_changed(const QString&)), _widget_connector, SLOT(valueChanged_slot(const QString&)));
	}
};

#undef Tdata
