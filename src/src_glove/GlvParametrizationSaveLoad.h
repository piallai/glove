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
template <class Tparametrization>
class GlvParametrizationWidget;

/*! Manages save and load of Tparametrization in a binary file.
* See example sample009.*/
template <class Tparametrization>
class GlvParametrizationSaveLoad : public GlvWidgetSaveLoad_base {

private:

    GlvParametrizationWidget<Tparametrization>* parametrization_widget;

public:

    /*! \p _widget : direct integration to the GlvWidget. Nothing else to do.
    * \p _allowed_extensions : file extensions the file can read and write to. Allowed extensions contains by default the static name of the parametrization.
    * \p _orientation : Orientation of Save/Load buttons. Stacked (default) or side-by-side. */
    GlvParametrizationSaveLoad(GlvParametrizationWidget<Tparametrization>* _parametrization_widget, SlvFileExtensions _allowed_extensions = {}, Qt::Orientation _orientation = Qt::Orientation::Horizontal);
    ~GlvParametrizationSaveLoad();

    /*! Save parametrization to file \p _file_name.*/
    void save(const std::string& _file_name);
    /*! Load parametrization from file \p _file_name.*/
    SlvStatus load(const std::string& _file_name);

private :

    static SlvFileExtensions allowed_extensions_constructor(SlvFileExtensions _allowed_extensions);

    friend class GlvParametrizationWidget<Tparametrization>;
};

#include "filestream/SlvFileMgr.h"
#include "GlvParametrizationWidget.h"
#include "glv_flag.h"
#include "GloveOptions.h"
#if OPTION_USE_THIRDPARTY_JSON==1
#include "json.hpp"
#endif

template <class Tparametrization>
GlvParametrizationSaveLoad<Tparametrization>::GlvParametrizationSaveLoad(GlvParametrizationWidget<Tparametrization>* _parametrization_widget, SlvFileExtensions _allowed_extensions, Qt::Orientation _orientation) : GlvWidgetSaveLoad_base(allowed_extensions_constructor(_allowed_extensions), _orientation, Tparametrization::name()) {

    parametrization_widget = _parametrization_widget;
    parametrization_widget->set_save_load_widget(this);

}

template <class Tparametrization>
GlvParametrizationSaveLoad<Tparametrization>::~GlvParametrizationSaveLoad() {

    parametrization_widget->set_save_load_widget(NULL);

}

template <class Tparametrization>
void GlvParametrizationSaveLoad<Tparametrization>::save(const std::string& _file_name) {

    bool l_write_default_binary = true;

#if OPTION_USE_THIRDPARTY_JSON==1
    if (SlvFileMgr::get_extension(_file_name) == ".json") {
        if (slv::rw::json::ReadWrite<Tparametrization>::l_valid) {

            l_write_default_binary = false;

            std::ofstream file_stream;
            SlvStatus status = SlvFileMgr::open_file(file_stream, _file_name);
            if (status) {
                nlohmann::json json_value;
                slv::rw::json::ReadWrite<Tparametrization>::writeJson(parametrization_widget->get_value(), json_value);
                file_stream << json_value.dump(4);
                file_stream.close();
            }

        } else {
            SlvStatus status_tmp(SlvStatus::statusType::warning, "Json parser is not managed for this type.\nUsing default binary parser.");
            glv::flag::showQMessageBox(status_tmp, false, this);
        }
    }
#endif

    if (l_write_default_binary) {
        SlvFileMgr::write_binary(parametrization_widget->get_value().param_cast(), _file_name);
    }

}

template <class Tparametrization>
SlvStatus GlvParametrizationSaveLoad<Tparametrization>::load(const std::string& _file_name) {

    SlvStatus status;
    Tparametrization value;

    bool l_read_default_binary = true;

#if OPTION_USE_THIRDPARTY_JSON==1
    if (SlvFileMgr::get_extension(_file_name) == ".json") {
        if (slv::rw::json::ReadWrite<Tparametrization>::l_valid) {

            l_read_default_binary = false;

            std::ifstream file_stream;
            status = SlvFileMgr::open_file(file_stream, _file_name);
            if (status) {

                nlohmann::json json_value;
                file_stream >> json_value;
                if (!json_value.empty()) {
                    status = slv::rw::json::ReadWrite<Tparametrization>::readJson(value, json_value);
                    bool l_set_parameters = interactive_load_parameters(_file_name, status);
                    if (l_set_parameters) {
                        value.param_init();
                        parametrization_widget->set_value(value);
                    }

                }

            }

        } else {
            SlvStatus status_tmp(SlvStatus::statusType::warning, "Json parser is not managed for this type.\nUsing default binary parser.");
            glv::flag::showQMessageBox(status_tmp, false, this);
        }
    }
#endif

    if (l_read_default_binary) {

        status = SlvFileMgr::read_binary(value.param_cast(), _file_name);
        if (status) {
            value.param_init();
            parametrization_widget->set_value(value);
        }

    }

    return status;
}

template <class Tparametrization>
SlvFileExtensions GlvParametrizationSaveLoad<Tparametrization>::allowed_extensions_constructor(SlvFileExtensions _allowed_extensions) {

    SlvFileExtensions allowed_extensions = _allowed_extensions;
    allowed_extensions.add(SlvFileMgr::replace_forbidden_file_characters(Tparametrization::name(), '_', true, true));
#if OPTION_USE_THIRDPARTY_JSON==1
    if (slv::rw::json::ReadWrite<Tparametrization>::l_valid) {
        allowed_extensions.add(".json");
    }
#endif
    return allowed_extensions;

}
