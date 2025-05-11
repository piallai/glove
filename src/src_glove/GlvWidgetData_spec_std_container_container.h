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

#include "GloveOptions.h"
#if OPTION_WIDGET_DATA_CONTAINER_TABLE==1

#include "GlvWidgetData.h"
#include "GlvTableView.h"
#include "glv_QStandardItemModelMaker_spec_std_container.h"

// Container of container, except std::map, std::unordered_map and std::string
#define Tenable typename std::enable_if<SlvIsContainer<Tcontainer>::value && SlvIsContainer<typename Tcontainer::value_type>::value && !std::is_same<typename Tcontainer::value_type, std::string>::value && !SlvIsMap<Tcontainer>::value && !std::is_same<Tcontainer, std::string>::value>::type

/*! GlvWidgetData specialization for template type: .*/
template <class Tcontainer>
class GlvWidgetData<Tcontainer, Tenable> : public GlvTableView<Tcontainer> {

public:
    GlvWidgetData(Tcontainer _container = Tcontainer(), QWidget* _parent = 0) :GlvTableView<Tcontainer>(_container, _parent) {
        GlvTableView_base::set_fixed_size(true);
    }
    ~GlvWidgetData() {}

};

#include "GlvWidgetMakerConnect.h"
template <class Tcontainer>
struct GlvWidgetMakerConnect<Tcontainer, Tenable> {
    static void connect(GlvWidgetData<Tcontainer>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        QObject::connect(_widget, SIGNAL(valueChanged(const std::vector<int>&)), _widget_connector, SLOT(valueChanged_slot(const std::vector<int>&)));
    }
};

#undef Tenable
#endif
