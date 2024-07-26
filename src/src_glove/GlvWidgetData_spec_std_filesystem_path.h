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

#if __cplusplus > 201402L

#include "GlvWidgetData.h"
#include "GlvOpenFile.h"
#include <filesystem>

#define Tdata std::filesystem::path
/*! GlvWidgetData specialization for template type: std::filesystem::path.*/
template <>
class GlvWidgetData<Tdata> : public GlvOpenFile {

public:
    GlvWidgetData(Tdata _path = Tdata(), QWidget* _parent = 0) :GlvOpenFile(_path.generic_string(), _parent) {}
    ~GlvWidgetData() {}


    Tdata get_value() const {
        return GlvOpenFile::get_file().get_path();
    }
    void set_value(const Tdata& _value) {
        return GlvOpenFile::set_file(SlvFile(_value.generic_string()));
    }
};

#include "GlvWidgetMakerConnect.h"
template <>
struct GlvWidgetMakerConnect<Tdata> {
    static void connect(GlvWidgetData<Tdata>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        QObject::connect(_widget, SIGNAL(file_changed(const QString&)), _widget_connector, SLOT(valueChanged_slot(const QString&)));
    }
};

#undef Tdata
#endif
