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
#include "GlvEnumWidget.h"

/*! GlvWidgetData for enum type.*/
template <class Tdata>
class GlvWidgetData<Tdata, typename std::enable_if<std::is_enum<Tdata>::value>::type> : public GlvEnumWidget<Tdata> {

public:
    GlvWidgetData(Tdata _enum = Tdata(), QWidget* _parent = 0) :GlvEnumWidget<Tdata>(_enum, _parent) {}
    ~GlvWidgetData() {}

};

#include "GlvWidgetMakerConnect.h"
template <class Tdata>
struct GlvWidgetMakerConnect<Tdata, typename std::enable_if<std::is_enum<Tdata>::value>::type> {
    static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        QObject::connect(_widget, SIGNAL(currentIndexChanged(int)), _widget_connector, SLOT(valueChanged_slot(int)));
    }
};
