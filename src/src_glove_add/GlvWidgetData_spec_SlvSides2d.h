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

#pragma once

#include "GlvWidgetData.h"
#include "GlvSides2dWidget.h"

#define Tdata SlvSides2d<T>
/*! GlvWidgetData specialization for template type: SlvSides2d.*/
template <class T>
class GlvWidgetData<Tdata> : public GlvSides2dWidget<T> {

public:
    GlvWidgetData(Tdata _sides = Tdata(), QWidget* _parent = 0) :GlvSides2dWidget<T>(_sides, _parent) {}
    ~GlvWidgetData() {}

    Tdata get_value() const {
        return GlvSides2dWidget<T>::get_sides();
    }
    void set_value(const Tdata& _value) {
        return GlvSides2dWidget<T>::set_sides(_value);
    }

};

#include "GlvWidgetMakerConnect.h"
template <class T>
struct GlvWidgetMakerConnect<Tdata> {
    static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        QObject::connect(_widget, SIGNAL(valueChanged_left()), _widget_connector, SLOT(valueChanged_slot()));
        QObject::connect(_widget, SIGNAL(valueChanged_right()), _widget_connector, SLOT(valueChanged_slot()));
        QObject::connect(_widget, SIGNAL(valueChanged_up()), _widget_connector, SLOT(valueChanged_slot()));
        QObject::connect(_widget, SIGNAL(valueChanged_bottom()), _widget_connector, SLOT(valueChanged_slot()));
    }
};

#undef Tdata
