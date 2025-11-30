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

#include "GlvParametersWidget.h"
template <class Tparametrization>
class GlvParametrizationSaveLoad;

/*! Widget managing SlvParametrization to widget, and vice versa.
* Tparametrization is a class inheriting from SlvParametrization.
* Member values not belonging to SlvParametrization are ignored here (constructor values).
* This is the main widget (with GlvParametrizationDialog) to use for parametrization management in the framework.*/
template <class Tparametrization>
class GlvParametrizationWidget : public GlvParametersWidget<typename Tparametrization::Tparametrization> {

public:

    GlvParametrizationWidget(const Tparametrization _parametrization = Tparametrization(), bool l_editable = true, QWidget* _parent = 0);
    ~GlvParametrizationWidget();

    /*! Get parametrization.*/
    Tparametrization get_parametrization() const;
    /*! Set parametrization.*/
    void set_parametrization(const Tparametrization& _parametrization);

    /*! Same as get_parametrization(), to be compliant with GlvWidgetMaker.*/
    Tparametrization get_value() const;
    /*! Same as set_parametrization(), to be compliant with GlvWidgetMaker.*/
    void set_value(const Tparametrization& _parametrization);

private:

    /*! \p _l_explicit_bool_arg : whether bool argument must be defined with 0/1 value.*/
    SlvStatus parse_arguments(const std::string& _arguments, const bool _l_explicit_bool_arg, const bool _l_reset_default);

    friend class GlvParametrizationSaveLoad<Tparametrization>;
};

#include "SlvCLI.h"

/*! Convenience macro to access widget (GlvWidgetData) of parameter number 'parameter_index'.
* See example in sample001.cpp.*/
#define glvm_get_parameter_GlvWidgetData(glv_parametrization_widget, parameter_index) glv_parametrization_widget->get_parameter##parameter_index()->get_widget()->get_widget()
/*! Convenience macro to access widget (GlvWidget) of parameter number 'parameter_index'.*/
#define glvm_get_parameter_GlvWidget(glv_parametrization_widget, parameter_index) glv_parametrization_widget->get_parameter##parameter_index()->get_widget()

template <class Tparametrization>
GlvParametrizationWidget<Tparametrization>::GlvParametrizationWidget(const Tparametrization _parametrization, bool l_editable, QWidget* _parent) :GlvParametersWidget<typename Tparametrization::Tparametrization>(_parametrization, l_editable) {

    this->setTitle(QString(Tparametrization::name().c_str()));
    // Set grid layout by default. More ergonomic.
    GlvParametersWidget_base::set_layout_grid();

}

template <class Tparametrization>
GlvParametrizationWidget<Tparametrization>::~GlvParametrizationWidget() {

}

template <class Tparametrization>
Tparametrization GlvParametrizationWidget<Tparametrization>::get_parametrization() const {

    return this->template get<Tparametrization>();

}

template <class Tparametrization>
void GlvParametrizationWidget<Tparametrization>::set_parametrization(const Tparametrization& _parametrization) {

    return this->set(_parametrization);
}

template <class Tparametrization>
Tparametrization GlvParametrizationWidget<Tparametrization>::get_value() const {
    return get_parametrization();
}

template <class Tparametrization>
void GlvParametrizationWidget<Tparametrization>::set_value(const Tparametrization& _parametrization) {
    set_parametrization(_parametrization);
}

template <class Tparametrization>
SlvStatus GlvParametrizationWidget<Tparametrization>::parse_arguments(const std::string& _arguments, const bool _l_explicit_bool_arg, const bool _l_reset_default) {

    Tparametrization parametrization;
    if (!_l_reset_default) {
        parametrization = get_parametrization();
    }
    std::vector<std::string> arg_names;
    std::vector<std::string> solo_arg_names;
    if (!_l_explicit_bool_arg) {// If not explicit bool arg (ie: 0/1 value), then it is necessary to know the mapping of the parameters
        std::pair< std::vector< std::pair<std::string, std::string> >, std::vector< std::pair<std::string, bool> > > serialization = parametrization.get_string_serialization_bool();
        for (auto it = serialization.first.begin(); it != serialization.first.end(); ++it) {
            arg_names.push_back(it->first);
        }
        for (auto it = serialization.second.begin(); it != serialization.second.end(); ++it) {
            solo_arg_names.push_back(it->first);
        }
    }
    SlvCLI::Arguments arguments(_arguments, arg_names, solo_arg_names);
    SlvStatus status = arguments.get_status();
    if (status) {
        std::vector<std::string> CLI_parameters = arguments.get_arguments_name();// Done before SlvCLI::parse because of arguments filtering
        status = SlvCLI::parse(parametrization, arguments);
        if (status) {
            GlvParametersWidget_base::CLI_parameters = CLI_parameters;
            set_parametrization(parametrization);
            //GlvParametersWidget_base::CLI_arguments_line = SlvCLI::get_CLI(parametrization, _l_explicit_bool_arg);
        }
    }
    return status;
}
