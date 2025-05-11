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
#include "GlvParametrizationWidget.h"

/*! GlvWidgetData for type SlvParametrization*/
template <class Tparametrization>
class GlvWidgetData<Tparametrization, typename std::enable_if<std::is_base_of<SlvParametrization_base, Tparametrization>::value>::type> : public GlvParametrizationWidget<Tparametrization> {

public:
    GlvWidgetData(Tparametrization _value = Tparametrization(), QWidget* _parent = 0) :GlvParametrizationWidget<Tparametrization>(_value, true, _parent) {
        this->set_checkable_collapse(true);
        this->set_scrollable(false);
    }
    ~GlvWidgetData() {}

};

#include "GlvWidgetMakerConnect.h"
template <class Tparametrization>
struct GlvWidgetMakerConnect<Tparametrization, typename std::enable_if<std::is_base_of<SlvParametrization_base, Tparametrization>::value>::type> {
    static void connect(GlvWidgetData<Tparametrization>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        QObject::connect(_widget, SIGNAL(parameterChanged(std::string)), _widget_connector, SLOT(valueChanged_slot(std::string)));
    }
};

