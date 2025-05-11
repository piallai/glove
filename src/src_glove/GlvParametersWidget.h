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

#include "GlvParameterWidget.h"
#include "param/SlvParametrization0.h"
#include "GlvParametersWidget_base.h"

template <class T>
class GlvParametersWidget;

/*! Widget managing the parameters of classes SlvParametrization**.*/
template <>
class GlvParametersWidget<SlvParametrization0> : public GlvParametersWidget_base {

public:
    GlvParametersWidget(const SlvParametrization0& _parametered_object, bool l_editable);
    ~GlvParametersWidget();
    /*! Set parametrization.*/
    void set(const SlvParametrization0& _parametered_object);
    /*! Get parametrization. Tparametrization is the class inheriting from SlvParametrization.*/
    template <class Tparametrization>
    Tparametrization get() const;
    /*! Set the parameters as editable or not.*/
    void set_editable(bool l_editable);
protected:
    void assign_recursive(SlvParametrization0& _parametrization) const;
    /*! Set the layout of parameters as either
    * Vertical : stack of widgets
    * Grid : parameters name are in the first column, their respective interaction widget on the second one.*/
    void set_layout_type(LayoutType _layout_type);
    /*! Enable or not display of parameter types in WhatsThis.*/
    void enable_data_type_info(bool _l_enable);
private:
    int get_Nparameters() const;
};

inline GlvParametersWidget<SlvParametrization0>::GlvParametersWidget(const SlvParametrization0& _parametered_object, bool l_editable) {

}

inline GlvParametersWidget<SlvParametrization0>::~GlvParametersWidget() {

}

inline void GlvParametersWidget<SlvParametrization0>::set(const SlvParametrization0& _parametered_object) {}

template <class Tparametrization>
Tparametrization GlvParametersWidget<SlvParametrization0>::get() const {
    return Tparametrization();
}

inline void GlvParametersWidget<SlvParametrization0>::set_editable(bool l_editable) {}

inline void GlvParametersWidget<SlvParametrization0>::assign_recursive(SlvParametrization0& _parametrization) const {}

inline void GlvParametersWidget<SlvParametrization0>::set_layout_type(LayoutType _layout_type) {
    GlvParametersWidget_base::set_layout_type_protected(_layout_type);
}

inline void GlvParametersWidget<SlvParametrization0>::enable_data_type_info(bool _l_enable) {}

inline int GlvParametersWidget<SlvParametrization0>::get_Nparameters() const {
    return 0;
}


#define glvm_pv_GlvParametersWidget_make_parameter(i) \
parameter##i = new GlvParameterWidget<Tparam##i>(_parametered_object.get_parameter##i(), l_editable);\
this->connect(static_cast<GlvParameterWidget_base*>(parameter##i), SIGNAL(parameterChanged(std::string)), this, SIGNAL(parameterChanged(std::string)));\
GlvParametersWidget_base::add_parameter_widget_to_vertical_layout(parameter##i);

#define glvm_pv_GlvParametersWidget_get_parameter(i) \
GlvParameterWidget<Tparam##i>* parameter_widget##i = dynamic_cast<GlvParameterWidget<Tparam##i>*>(this->layout()->itemAt(i-1)->widget());\
Tparam##i parameter_value##i;\
parameter_value##i = parameter_widget##i->get_value();

/*! Macro in charge of defining the template class parameter widget for i parameters.*/
#define glvm_pv_GlvParametersWidget(i, meta_Tparameters_current, spec_Tparameters_current)\
template <meta_Tparameters_current>\
class GlvParametersWidget< SlvParametrization##i<spec_Tparameters_current> > : public GlvParametersWidget<typename SlvParametrization##i<spec_Tparameters_current>::Tparametrization_lower> {\
    private:\
    GlvParameterWidget<Tparam##i>* parameter##i;\
    protected:\
    Tparam##i get_value##i() const {\
        return parameter##i->get_value();\
    }\
    public:\
    GlvParametersWidget(const SlvParametrization##i<spec_Tparameters_current>& _parametered_object, bool l_editable):GlvParametersWidget<typename SlvParametrization##i<spec_Tparameters_current>::Tparametrization_lower>(_parametered_object, l_editable) {\
        glvm_pv_GlvParametersWidget_make_parameter(i)\
    }\
    ~GlvParametersWidget() {}\
    const GlvParameterWidget<Tparam##i>* get_parameter##i() const {return parameter##i;}\
	GlvParameterWidget<Tparam##i>* get_parameter##i() {return parameter##i;}\
    void set(const SlvParametrization##i<spec_Tparameters_current>& _parametered_object) {\
        GlvParametersWidget<typename SlvParametrization##i<spec_Tparameters_current>::Tparametrization_lower>::set(_parametered_object);\
        parameter##i->set(_parametered_object.get_parameter##i());\
    }\
    protected:\
    void assign_recursive(SlvParametrization##i<spec_Tparameters_current>& _parametrization) const {\
        GlvParametersWidget<typename SlvParametrization##i<spec_Tparameters_current>::Tparametrization_lower>::assign_recursive(_parametrization);\
        const_cast<SlvParameter<Tparam##i>*>(&const_cast<const SlvParametrization##i<spec_Tparameters_current>*>(&_parametrization)->get_parameter##i())->set_value(get_value##i());\
    }\
    public:\
    template <class Tparametrization>\
    Tparametrization get() const {\
        Tparametrization parametrization;\
        assign_recursive(parametrization);\
        static_cast<SlvParametrization_base*>(&parametrization)->param_init();\
        return parametrization;\
    }\
    void set_editable(bool l_editable) {\
        GlvParametersWidget<typename SlvParametrization##i<spec_Tparameters_current>::Tparametrization_lower>::set_editable(l_editable);\
        parameter##i->set_editable(l_editable);\
    }\
    void set_layout_type(GlvParametersWidget_base::LayoutType _layout_type) {\
        GlvParametersWidget<typename SlvParametrization##i<spec_Tparameters_current>::Tparametrization_lower>::set_layout_type(_layout_type);\
        if (_layout_type == GlvParametersWidget_base::LayoutType::Vertical) {\
            GlvParametersWidget_base::add_parameter_widget_to_vertical_layout(parameter##i);\
            parameter##i->reclaim_widgets_ownership();\
        } else if (_layout_type == GlvParametersWidget_base::LayoutType::Grid) {\
            GlvParametersWidget_base::set_parameter_widget_to_grid_layout(parameter##i, i - 1);\
        }\
    }\
    void enable_data_type_info(bool _l_enable) {\
        GlvParametersWidget<typename SlvParametrization##i<spec_Tparameters_current>::Tparametrization_lower>::enable_data_type_info(_l_enable);\
        parameter##i->enable_data_type_info(_l_enable);\
    }\
private:\
    int get_Nparameters() const {\
        return i;\
    }\
};

#include "GlvParametersWidget_specs.h"

