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
#include "GlvSize2dWidget.h"

#define Tdata SlvSize2d<T>
/*! GlvWidgetData specialization for template type: std::vector.*/
template <class T>
class GlvWidgetData<Tdata> : public GlvSize2dWidget<T> {

public:
    GlvWidgetData(Tdata _size = Tdata(), QWidget* _parent = 0) :GlvSize2dWidget<T>(_size, _parent) {}
    ~GlvWidgetData() {}

    Tdata get_value() const {
        return GlvSize2dWidget<T>::get_size();
    }
    void set_value(const Tdata& _value) {
        return GlvSize2dWidget<T>::set_size(_value);
    }

};

#include "GlvWidgetMakerConnect.h"
template <class T>
struct GlvWidgetMakerConnect<Tdata> {
    static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        QObject::connect(_widget, SIGNAL(valueChanged_width()), _widget_connector, SLOT(valueChanged_slot()));
        QObject::connect(_widget, SIGNAL(valueChanged_height()), _widget_connector, SLOT(valueChanged_slot()));
    }
};

#undef Tdata
