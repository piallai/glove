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

#include "GlvWidgetSaveLoad_base.h"
#include "GlvWidget.h"
#include <qnamespace.h>

/*! Widget to add in a GlvWidgetData specialization. Manages save and load of Tdata in a binary file.
* See example sample009.*/
template <class Tdata>
class GlvWidgetSaveLoad : public GlvWidgetSaveLoad_base {

private:

    /*! Handled widget in regular case.*/
    GlvWidget<Tdata>* widget;
    /*! Handled widget in specialization case.*/
    GlvWidgetData<Tdata>* widget_data;

public:

    /*! \p _widget : direct integration to the GlvWidget. Nothing else to do.
    * \p _allowed_extensions : file extensions the file can read and write to. Allowed extensions contains by default the static name of Tdata.
    * \p _orientation : Orientation of Save/Load buttons. Stacked or side-by-side (default). */
    GlvWidgetSaveLoad(GlvWidget<Tdata>* _widget, SlvFileExtensions _allowed_extensions = {}, const  Qt::Orientation _orientation = Qt::Orientation::Horizontal);
private:
    /*! Same, but allows integration directly in a GlvWidgetData. Recommended to use only in case of GlvWidgetData specialization.*/
    GlvWidgetSaveLoad(GlvWidgetData<Tdata>* _widget_data, SlvFileExtensions _allowed_extensions = {}, const  Qt::Orientation _orientation = Qt::Orientation::Horizontal);
public:
    ~GlvWidgetSaveLoad();

    /*! Save data to file \p _file_name.*/
    void save(const std::string& _file_name);
    /*! Load data from file \p _file_name.*/
    SlvStatus load(const std::string& _file_name);

private:

    /*! Friend class for specific case manaing GlvWidgetData.*/
    template <class T, typename>
    friend class GlvWidgetData;

};

#include "filestream/SlvFileMgr.h"
#include "misc/SlvDataName.h"
#include "glv_flag.h"

template <class Tdata>
GlvWidgetSaveLoad<Tdata>::GlvWidgetSaveLoad(GlvWidget<Tdata>* _widget, SlvFileExtensions _allowed_extensions, Qt::Orientation _orientation) : GlvWidgetSaveLoad_base((_allowed_extensions.add(SlvFileMgr::replace_forbidden_file_characters(SlvDataName<Tdata>::name(), '_', true, true)), _allowed_extensions), _orientation, SlvDataName<Tdata>::name()) {

    widget = _widget;
    _widget->set_save_load_widget(this);
    widget_data = NULL;

}

template <class Tdata>
GlvWidgetSaveLoad<Tdata>::GlvWidgetSaveLoad(GlvWidgetData<Tdata>* _widget_data, SlvFileExtensions _allowed_extensions, Qt::Orientation _orientation) : GlvWidgetSaveLoad_base((_allowed_extensions.add(SlvFileMgr::replace_forbidden_file_characters(SlvDataName<Tdata>::name(), '_', true, true)), _allowed_extensions), _orientation, SlvDataName<Tdata>::name()) {

    widget_data = _widget_data;
    widget = NULL;

}

template <class Tdata>
GlvWidgetSaveLoad<Tdata>::~GlvWidgetSaveLoad() {

    widget->set_save_load_widget(NULL);

}

template <class Tdata>
void GlvWidgetSaveLoad<Tdata>::save(const std::string& _file_name) {

    Tdata value;
    if (widget) {
        value = widget->get_value();
    } else if (widget_data) {
        value = widget_data->get_value();
    }
    SlvFileMgr::write_binary(value, _file_name);

}

template <class Tdata>
SlvStatus GlvWidgetSaveLoad<Tdata>::load(const std::string& _file_name) {

    Tdata value;
    SlvStatus status = SlvFileMgr::read_binary(value, _file_name);
    if (status) {
        if (widget) {
            widget->set_value(value);
        } else if (widget_data) {
            widget_data->set_value(value);
        }
    }

    return status;
}
