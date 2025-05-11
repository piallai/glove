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
#include "GlvVectorWidget.h"
#include "GloveOptions.h"
#if OPTION_WIDGET_DATA_CONTAINER_TABLE==1
// Do not enable if value_type is a container. GlvWidgetData_spec_std_container_container.h is used instead
#include "SlvIsContainer.h"
#include "SlvIsMap.h"
#define Tenable typename std::enable_if<!SlvIsContainer<T>::value || SlvIsMap<T>::value || std::is_same<T, std::string>::value>::type
#else
#define Tenable typename std::enable_if<true>::type
#endif

#define Tdata std::vector<T>
/*! GlvWidgetData specialization for template type: std::vector.*/
template <class T>
class GlvWidgetData<Tdata, Tenable> : public GlvVectorWidget<T> {

public:
    GlvWidgetData(Tdata _vector = Tdata(), QWidget* _parent = 0) :GlvVectorWidget<T>(_vector, _parent) {
        this->set_checkable(true);
        if (!_vector.empty()) {
            this->set_checked(false);
        } else {
            // If empty, leave checked so that it's easier to see that the vector widget is empty
        }
        this->set_items_top_aligment(true);
    }
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
