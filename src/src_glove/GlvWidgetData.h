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

#include <QWidget>

class GlvWidgetData_base : public QWidget {

    Q_OBJECT

protected:
    GlvWidgetData_base(QWidget* _parent) :QWidget(_parent) {}
    virtual ~GlvWidgetData_base() {}

signals:

    void sizeChanged();
};

/* Key widget to specialize depending on Tdata. Different from GlvWidget (deal with any type).
* Not supposed to be manipulated directly. Use GlvWidget publicly.
* In short GlvWidgetData is at the end of GlvWidget's chain.
* Must have methods: get_value(), set_value() and set_editable() methods.
* These methods can be directly available if the inherited widget contains them, or the methods can be implemented in the class.*/
template <class Tdata, typename = void>
class GlvWidgetData;
