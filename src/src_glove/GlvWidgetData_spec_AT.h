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

// AT: Arithmetic Types.
// GlvWidgetData for arithemtic types such as int, unsigned int, float, double, bool

#include "GlvWidgetData.h"
#include "GlvWidgetMakerConnect.h"

#include <QSpinBox>
#define Tdata int
/*! GlvWidgetData specialization for type: int.*/
template <>
class GlvWidgetData<Tdata> : public QSpinBox {
public:
    GlvWidgetData(QWidget* _parent = 0);
    GlvWidgetData(const Tdata& _value, QWidget* _parent = 0);
    ~GlvWidgetData();
    void set_editable(bool l_editable);
    Tdata get_value() const;
    void set_value(const Tdata& _value);
};

template <>
struct GlvWidgetMakerConnect<Tdata> {
    static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        QObject::connect(_widget, SIGNAL(valueChanged(int)), _widget_connector, SLOT(valueChanged_slot(int)));
    }
};

#undef Tdata
#define Tdata unsigned int
/*! GlvWidgetData specialization for type: unsigned int.*/
template <>
class GlvWidgetData<Tdata> : public QSpinBox {
public:
    GlvWidgetData(QWidget* _parent = 0);
    GlvWidgetData(const Tdata& _value, QWidget* _parent = 0);
    ~GlvWidgetData();
    void set_editable(bool l_editable);
    Tdata get_value() const;
    void set_value(const Tdata& _value);
};

template <>
struct GlvWidgetMakerConnect<Tdata> {
    static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        QObject::connect(_widget, SIGNAL(valueChanged(int)), _widget_connector, SLOT(valueChanged_slot(int)));
    }
};

#include <QDoubleSpinBox>
#undef Tdata
#define Tdata float
/*! GlvWidgetData specialization for type: float.*/
template <>
class GlvWidgetData<Tdata> : public QDoubleSpinBox {
public:
    GlvWidgetData(QWidget* _parent = 0);
    GlvWidgetData(const Tdata& _value, QWidget* _parent = 0);
    ~GlvWidgetData();
    void set_editable(bool l_editable);
    Tdata get_value() const;
    void set_value(const Tdata& _value);
};

template <>
struct GlvWidgetMakerConnect<Tdata> {
    static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        QObject::connect(_widget, SIGNAL(valueChanged(double)), _widget_connector, SLOT(valueChanged_slot(double)));
    }
};

#undef Tdata
#define Tdata double
/*! GlvWidgetData specialization for type: double.*/
template <>
class GlvWidgetData<Tdata> : public QDoubleSpinBox {
public:
    GlvWidgetData(QWidget* _parent = 0);
    GlvWidgetData(const Tdata& _value, QWidget* _parent = 0);
    ~GlvWidgetData();
    void set_editable(bool l_editable);
    Tdata get_value() const;
    void set_value(const Tdata& _value);
};

template <>
struct GlvWidgetMakerConnect<Tdata> {
    static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        QObject::connect(_widget, SIGNAL(valueChanged(double)), _widget_connector, SLOT(valueChanged_slot(double)));
    }
};

#include <QCheckBox>
#undef Tdata
#define Tdata bool
/*! GlvWidgetData specialization for type: bool.*/
template <>
class GlvWidgetData<Tdata> : public QCheckBox {
public:
    GlvWidgetData(QWidget* _parent = 0);
    GlvWidgetData(const Tdata& _value, QWidget* _parent = 0);
    ~GlvWidgetData();
    void set_editable(bool l_editable);
    Tdata get_value() const;
    void set_value(const Tdata& _value);
};

template <>
struct GlvWidgetMakerConnect<Tdata> {
    static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        QObject::connect(_widget, SIGNAL(stateChanged(int)), _widget_connector, SLOT(valueChanged_slot(int)));
    }
};



#undef Tdata
