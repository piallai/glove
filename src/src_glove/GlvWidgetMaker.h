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

/*! First layer of template specialization possibility.
* GlvWidgetMaker is also in charge of signals connection through GlvWidgetMakerConnect provided corresponding specialization is defined.
* GlvWidgetData must have get_value(), set_value() and set_editable() methods.*/
template <class Tvalue>
struct GlvWidgetMaker {
	typedef GlvWidgetData<Tvalue> Twidget;
	static void make(GlvWidget_base* _glvwidget, const Tvalue& _value, bool _l_editable = true, QWidget* _parent = 0);
	static void set(GlvWidget_base* _glvwidget, const Tvalue& _value);
	static Tvalue get(const GlvWidget_base* _glvwidget);
	static void set_editable(GlvWidget_base* _glvwidget, bool _l_editable);
};

#include "GlvWidget_base.h"
#include "GlvWidgetMakerConnect.h"

template <class Tvalue>
void GlvWidgetMaker<Tvalue>::make(GlvWidget_base* _glvwidget, const Tvalue& _value, bool _l_editable, QWidget* _parent) {
	Twidget* widget = new Twidget(_value);
	GlvWidgetMakerConnect<Tvalue>::connect(widget, _glvwidget->connector);

	/*! Options to set layout of widgets.*/
	//widget->layout()->setSpacing(0);
	//widget->layout()->setContentsMargins(4, 2, 4, 2);

	_glvwidget->data_widget = widget;
	set_editable(_glvwidget, _l_editable);
}

template <class Tvalue>
void GlvWidgetMaker<Tvalue>::set(GlvWidget_base* _glvwidget, const Tvalue& _value) {
	dynamic_cast<Twidget*>(_glvwidget->data_widget)->set_value(_value);
}

template <class Tvalue>
Tvalue GlvWidgetMaker<Tvalue>::get(const GlvWidget_base* _glvwidget) {
	return dynamic_cast<const Twidget*>(_glvwidget->data_widget)->get_value();
}

template <class Tvalue>
void GlvWidgetMaker<Tvalue>::set_editable(GlvWidget_base* _glvwidget, bool _l_editable) {
	dynamic_cast<Twidget*>(_glvwidget->data_widget)->set_editable(_l_editable);
}

/*! Macro to easily declare a GlvWidgetMaker. Deprecated.*/
#define glvm_pv_GlvWidgetMaker_spec_declaration(Tvalue, _Twidget)\
template <>\
struct GlvWidgetMaker<Tvalue, void> {\
    typedef _Twidget Twidget;\
    static void make(GlvWidget_base* _glvwidget, const Tvalue& _value, bool l_editable=true, QWidget* _parent=0);\
    static void set(GlvWidget_base* _glvwidget, const Tvalue& _value);\
    static Tvalue get(const GlvWidget_base* _glvwidget);\
    static void set_editable(GlvWidget_base* _glvwidget, bool l_editable);\
};
