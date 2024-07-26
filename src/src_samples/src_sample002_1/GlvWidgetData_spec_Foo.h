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

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvWidgetData.h"
#endif
#include "FooWidget.h"

#define Tdata Foo

template <>
class GlvWidgetData<Tdata> : public FooWidget {

public:
	GlvWidgetData(Tdata _value = Tdata(), QWidget* _parent = 0):FooWidget(_value, _parent) {}
	~GlvWidgetData() {}

	Tdata get_value() const {
		return FooWidget::get_foo();
	}
	void set_value(const Tdata& _value) {
		return FooWidget::set_foo(_value);
	}
	void set_editable(bool _l_editable) {
		return FooWidget::allow_edition(_l_editable);
	}

};

// Manage connections related to FooWidget
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvWidgetMakerConnect.h"
#endif
template <>
struct GlvWidgetMakerConnect<Tdata> {
	static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
		QObject::connect(_widget, SIGNAL(foo_changed(int)), _widget_connector, SLOT(valueChanged_slot(int)));
	}
};

#undef Tdata
