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
#include "GlvVectorWidget.h"

#include "SlvIsContainer.h"
#include "SlvIsMap.h"
// Do not enable if value_type is a container. GlvWidgetData_spec_std_container_container.h is used instead
#define Tenable typename std::enable_if<!SlvIsContainer<T>::value || SlvIsMap<T>::value || std::is_same<T, std::string>::value>::type

#define Tdata std::vector<T>
/*! GlvWidgetData specialization for template type: std::vector.*/
template <class T>
class GlvWidgetData<Tdata, Tenable> : public GlvVectorWidget<T> {

public:
    GlvWidgetData(Tdata _vector = Tdata(), QWidget* _parent = 0) :GlvVectorWidget<T>(_vector, _parent) {}
    ~GlvWidgetData() {}

};

#include "GlvWidgetMakerConnect.h"
template <class T>
struct GlvWidgetMakerConnect<Tdata, Tenable> {
    static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        QObject::connect(_widget, SIGNAL(valueChanged(int)), _widget_connector, SLOT(valueChanged_slot(int)));
    }
};

#undef Tdata
#undef Tenable
