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

#include "GlvWidget_base.h"

/*! Macro to add a connected type.*/
#define glvm_pv_GlvWidgetConnector(type)\
signals:\
void valueChanged(type _value);\
public slots:\
void valueChanged_slot(type _value) {\
    emit(valueChanged(_value));/*emits same signal as original*/\
    emit(glvwidget->valueChanged());/*emits neutral signal*/\
}

/*! Class is in charge to bridge signals from GlvWidgetData to GlvWidget_base.
* Basically, any GlvWidget<T> can emit ValueChanged() for any basic type
* The connector is here to bridge signals of particular types to slots of this class. Ex: void valueChanged_slot(double _value).
* Each time valueChanged_slot is called by connectionn it emits the corresponding (type wise) signal valueChanged(xxx), and emits glvwidget's valueChanged() signal.
* Work in progress to add other types.*/
class GlvWidget_base::GlvWidgetConnector : public QObject {

    Q_OBJECT

private:

    GlvWidget_base* glvwidget;

public:
    GlvWidgetConnector(GlvWidget_base* _glvwidget);
    GlvWidgetConnector();
    ~GlvWidgetConnector();

signals:

    void valueChanged(double _value);
    void valueChanged(int _value);
    void valueChanged(std::string _value);
    void valueChanged(const QString& _value);
    void valueChanged(const std::vector<int>& _coordinates);
    void sizeChanged();

private slots:
    void valueChanged_slot();
    void valueChanged_slot(double _value);
    void valueChanged_slot(int _value);
    void valueChanged_slot(std::string _value);
    void valueChanged_slot(const QString& _value);
    void valueChanged_slot(const std::vector<int>& _coordinates);

};
