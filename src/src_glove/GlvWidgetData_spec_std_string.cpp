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

#include "GlvWidgetData_spec_std_string.h"
#include "glv_QString.h"

#define Tdata std::string
GlvWidgetData<Tdata>::GlvWidgetData(QWidget* _parent) :QLineEdit(_parent) {

}
GlvWidgetData<Tdata>::GlvWidgetData(const Tdata& _value, QWidget* _parent) : GlvWidgetData(_parent) {
    set_value(_value);
}
GlvWidgetData<Tdata>::~GlvWidgetData() {

}
void GlvWidgetData<Tdata>::set_editable(bool l_editable) {
    QLineEdit::setReadOnly(!l_editable);
}
Tdata GlvWidgetData<Tdata>::get_value() const {
    return QLineEdit::displayText().toStdString();
}
void GlvWidgetData<Tdata>::set_value(const Tdata& _value) {
    QLineEdit::setText(glv::toQString(_value));
}

#undef Tdata
