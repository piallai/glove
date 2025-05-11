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

#include "GlvParametrizationWidget.h"

/*! Convenience methods to make Glv widgets out of Tdata.*/
class GlvWidgetAuto {

public:

    template <class Tdata>
    static GlvWidget<Tdata>* make(const Tdata _value = Tdata(), bool l_editable = true, QWidget* _parent = 0);

    template <class Tdata>
    static GlvDescribedWidget<Tdata>* make_described(const Tdata _value = Tdata(), std::string _data_name = "", std::string _description = "", bool l_editable = true, QWidget* _parent = 0);

    template <class Tparametrization>
    static GlvParametrizationWidget<Tparametrization>* make_parametrization(const Tparametrization _parametrization = Tparametrization(), bool l_editable = true, QWidget* _parent = 0);

};

template <class Tdata>
GlvWidget<Tdata>* GlvWidgetAuto::make(const Tdata _value, bool l_editable, QWidget* _parent) {

    GlvWidget<Tdata>* widget = new GlvWidget<Tdata>(_value, l_editable, _parent);
    return widget;
}

template <class Tdata>
GlvDescribedWidget<Tdata>* GlvWidgetAuto::make_described(const Tdata _value, std::string _data_name, std::string _description, bool l_editable, QWidget* _parent) {

    GlvDescribedWidget<Tdata>* widget = new GlvDescribedWidget<Tdata>(_value, _data_name, _description, l_editable, _parent);
    return widget;
}

template <class Tparametrization>
GlvParametrizationWidget<Tparametrization>* GlvWidgetAuto::make_parametrization(const Tparametrization _parametrization, bool l_editable, QWidget* _parent) {

    GlvParametrizationWidget<Tparametrization>* widget = new GlvParametrizationWidget<Tparametrization>(_parametrization, l_editable, _parent);
    return widget;
}
