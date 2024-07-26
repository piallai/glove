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

#include "GlvWidgetConnector.h"

GlvWidget_base::GlvWidgetConnector::GlvWidgetConnector(GlvWidget_base* _glvwidget) {
    glvwidget = _glvwidget;
    connect(this, SIGNAL(sizeChanged()), glvwidget, SIGNAL(sizeChanged()));
}

GlvWidget_base::GlvWidgetConnector::GlvWidgetConnector() {

}

GlvWidget_base::GlvWidgetConnector::~GlvWidgetConnector() {

}

void GlvWidget_base::GlvWidgetConnector::valueChanged_slot() {
    emit(glvwidget->valueChanged());/*emits neutral signal*/ /*Responsible of emit parameterChanged(std::string)*/
}

void GlvWidget_base::GlvWidgetConnector::valueChanged_slot(double _value) {
    emit(valueChanged(_value));/*emits same signal as original*/
    valueChanged_slot();
}

void GlvWidget_base::GlvWidgetConnector::valueChanged_slot(int _value) {
    emit(valueChanged(_value));/*emits same signal as original*/
    valueChanged_slot();
}

void GlvWidget_base::GlvWidgetConnector::valueChanged_slot(std::string _value) {
    emit(valueChanged(_value));/*emits same signal as original*/
    valueChanged_slot();
}

void GlvWidget_base::GlvWidgetConnector::valueChanged_slot(const QString& _value) {
    emit(valueChanged(_value));/*emits same signal as original*/
    valueChanged_slot();
}

void GlvWidget_base::GlvWidgetConnector::valueChanged_slot(const std::vector<int>& _coordinates) {
    emit(valueChanged(_coordinates));/*emits same signal as original*/
    valueChanged_slot();
}
