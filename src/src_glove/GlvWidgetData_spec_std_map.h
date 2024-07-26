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
#include "GlvMapWidget.h"

#define Tdata std::map<Tkey, Tvalue>
/*! GlvWidgetData specialization for template type: std::map.*/
template <class Tkey, class Tvalue>
class GlvWidgetData<Tdata> : public GlvMapWidget<Tkey, Tvalue> {

public:
    GlvWidgetData(Tdata _map = Tdata(), QWidget* _parent = 0) :GlvMapWidget<Tkey, Tvalue>(_map, _parent) {}
    ~GlvWidgetData() {}

};

#include "GlvWidgetMakerConnect.h"
template <class Tkey, class Tvalue>
struct GlvWidgetMakerConnect<Tdata> {
    static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        QObject::connect(_widget, SIGNAL(valueChanged(int)), _widget_connector, SLOT(valueChanged_slot(int)));
    }
};

#undef Tdata
