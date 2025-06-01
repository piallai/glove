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
#include "GlvWidgetMakerConnect.h"
#include <QLineEdit>

#define Tdata std::nullptr_t
/*! GlvWidgetData specialization for type: std::nullptr_t.
* Default type to 'disable' a parameter.*/
template <>
class GlvWidgetData<Tdata> : public QWidget {
public:
    GlvWidgetData(QWidget* _parent = 0) :QWidget(_parent) {}
    GlvWidgetData(const Tdata& _value, QWidget* _parent = 0) {}
    ~GlvWidgetData() {}
    void set_editable(bool l_editable) {}
    Tdata get_value() const {
        return nullptr;
    }
    void set_value(const Tdata& _value) {}
};

template <>
struct GlvWidgetMakerConnect<Tdata> {
    static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {}
};
#undef Tdata
