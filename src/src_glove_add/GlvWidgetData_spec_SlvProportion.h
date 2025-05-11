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
#include "GlvProportionWidget.h"

#define Tdata SlvProportion

/*! GlvWidgetData for type SlvProportion.*/
template <>
class GlvWidgetData<Tdata> : public GlvProportionWidget {

public:
    GlvWidgetData(Tdata _ratio = Tdata(), QWidget* _parent = 0);
    ~GlvWidgetData();

};

#include "GlvWidgetMakerConnect.h"
template <>
struct GlvWidgetMakerConnect<Tdata> {
    static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        QObject::connect(_widget, SIGNAL(valueChanged(double)), _widget_connector, SLOT(valueChanged_slot(double)));
    }
};

#undef Tdata
