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

#include "GlvWidgetData_spec_AT.h"
#include "slv_flag.h"
#include "glv_QString.h"
#include "misc/slv_misc.h"

#define Tdata int
GlvWidgetData<Tdata>::GlvWidgetData(QWidget* _parent) :QSpinBox(_parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    setMaximum(std::numeric_limits<int>::max());
    setMinimum(std::numeric_limits<int>::lowest());
}
GlvWidgetData<Tdata>::GlvWidgetData(const Tdata& _value, QWidget* _parent) : GlvWidgetData(_parent) {
    set_value(_value);
}
GlvWidgetData<Tdata>::~GlvWidgetData() {

}
void GlvWidgetData<Tdata>::set_editable(bool l_editable) {
    QSpinBox::setReadOnly(!l_editable);
}
Tdata GlvWidgetData<Tdata>::get_value() const {
    return QSpinBox::value();
}
void GlvWidgetData<Tdata>::set_value(const Tdata& _value) {
    QSpinBox::setValue(_value);
}

#undef Tdata
#define Tdata unsigned int
GlvWidgetData<Tdata>::GlvWidgetData(QWidget* _parent) :QSpinBox(_parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    setMaximum(std::numeric_limits<int>::max());
    setMinimum(0);
}
GlvWidgetData<Tdata>::GlvWidgetData(const Tdata& _value, QWidget* _parent) : GlvWidgetData(_parent) {
    set_value(_value);
}
GlvWidgetData<Tdata>::~GlvWidgetData() {

}
void GlvWidgetData<Tdata>::set_editable(bool l_editable) {
    QSpinBox::setReadOnly(!l_editable);
}
Tdata GlvWidgetData<Tdata>::get_value() const {
    return QSpinBox::value();
}
void GlvWidgetData<Tdata>::set_value(const Tdata& _value) {
    Tdata value = _value;
    if (value > (unsigned int)std::numeric_limits<int>::max()) {
        value = (unsigned int)std::numeric_limits<int>::max();
        slv::flag::WARNING("GlvWidgetData<unsigned int> : value is too high to be set in QSpinBox");
    }
    QSpinBox::setValue(value);
}

#undef Tdata
#define Tdata float
GlvWidgetData<Tdata>::GlvWidgetData(QWidget* _parent) :QDoubleSpinBox(_parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    setMaximum(std::numeric_limits<float>::max());
    setMinimum(std::numeric_limits<float>::lowest());
}
GlvWidgetData<Tdata>::GlvWidgetData(const Tdata& _value, QWidget* _parent) : GlvWidgetData(_parent) {
    unsigned int Ndecimals = slv::misc::get_Ndecimals(_value);
    Ndecimals = std::max((unsigned int)2, Ndecimals);
    setDecimals(Ndecimals);
    set_value(_value);
}
GlvWidgetData<Tdata>::~GlvWidgetData() {

}
void GlvWidgetData<Tdata>::set_editable(bool l_editable) {
    QDoubleSpinBox::setReadOnly(!l_editable);
}
Tdata GlvWidgetData<Tdata>::get_value() const {
    return QDoubleSpinBox::value();
}
void GlvWidgetData<Tdata>::set_value(const Tdata& _value) {
    QDoubleSpinBox::setValue(_value);
}

#undef Tdata
#define Tdata double
GlvWidgetData<Tdata>::GlvWidgetData(QWidget* _parent) :QDoubleSpinBox(_parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    setMaximum(std::numeric_limits<double>::max());
    setMinimum(std::numeric_limits<double>::lowest());
}
GlvWidgetData<Tdata>::GlvWidgetData(const Tdata& _value, QWidget* _parent) : GlvWidgetData(_parent) {
    unsigned int Ndecimals = slv::misc::get_Ndecimals(_value);
    Ndecimals = std::max((unsigned int)2, Ndecimals);
    setDecimals(Ndecimals);
    set_value(_value);
}
GlvWidgetData<Tdata>::~GlvWidgetData() {

}
void GlvWidgetData<Tdata>::set_editable(bool l_editable) {
    QDoubleSpinBox::setReadOnly(!l_editable);
}
Tdata GlvWidgetData<Tdata>::get_value() const {
    return QDoubleSpinBox::value();
}
void GlvWidgetData<Tdata>::set_value(const Tdata& _value) {
    QDoubleSpinBox::setValue(_value);
}

#undef Tdata
#define Tdata bool
GlvWidgetData<Tdata>::GlvWidgetData(QWidget* _parent) :QCheckBox(_parent) {

}
GlvWidgetData<Tdata>::GlvWidgetData(const Tdata& _value, QWidget* _parent) : GlvWidgetData(_parent) {
    set_value(_value);
}
GlvWidgetData<Tdata>::~GlvWidgetData() {

}
void GlvWidgetData<Tdata>::set_editable(bool l_editable) {
    QCheckBox::setEnabled(l_editable);
}
Tdata GlvWidgetData<Tdata>::get_value() const {
    return QCheckBox::isChecked();
}
void GlvWidgetData<Tdata>::set_value(const Tdata& _value) {
    QCheckBox::setChecked(_value);
}

#undef Tdata

