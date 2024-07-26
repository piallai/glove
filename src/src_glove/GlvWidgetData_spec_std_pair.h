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
#include "iostream/spec/iostream_spec_std_pair.h"
#include "GlvPairWidget.h"

#define Tdata std::pair<T1, T2>
/*! GlvWidgetData specialization for template type: std::pair.*/
template <class T1, class T2>
class GlvWidgetData<Tdata> : public GlvPairWidget<T1, T2> {

public:
    GlvWidgetData(Tdata _pair = Tdata(), QWidget* _parent = 0) :GlvPairWidget<T1, T2>(_pair, _parent) {}
    ~GlvWidgetData() {}

    Tdata get_value() const {
        return GlvPairWidget<T1, T2>::get_pair();
    }
    void set_value(const Tdata& _value) {
        return GlvPairWidget<T1, T2>::set_pair(_value);
    }

};

#include "GlvWidgetMakerConnect.h"
template <class T1, class T2>
struct GlvWidgetMakerConnect<Tdata> {
    static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        QObject::connect(_widget, SIGNAL(valueChanged_first()), _widget_connector, SLOT(valueChanged_slot()));
        QObject::connect(_widget, SIGNAL(valueChanged_second()), _widget_connector, SLOT(valueChanged_slot()));
    }
};

#undef Tdata
