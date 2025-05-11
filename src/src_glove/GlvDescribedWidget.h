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

#include "GlvDescribedWidget_base.h"

template <class Tvalue>
class GlvWidget;

/*! Widget displaying data interface with name and tool tip description.*/
template <class Tdata>
class GlvDescribedWidget : public GlvDescribedWidget_base {

protected:

    /*! Widget managing the data interface.*/
    GlvWidget<Tdata>* data_widget;

public:

    /*! \p _data_name : object name and displayed named of the data
    * \p _description : description in tool tip.
    * 'what's this' is the static name of Tdata according to SlvDataName<Tdata>.*/
    GlvDescribedWidget(Tdata _value = Tdata(), std::string _data_name = "", std::string _description = "", bool l_editable = true, QWidget* _parent = 0);
    ~GlvDescribedWidget();

    Tdata get_value() const;
    void set_value(const Tdata& _value);

    /*! Return data interface widget.*/
    const GlvWidget<Tdata>* get_widget() const;
    /*! Return data interface widget.*/
    GlvWidget<Tdata>* get_widget();

    /*! If \p _l_enable is true, whatsthis is set as the name of Tdata according to SlvDataName<Tdata>.
    * If false, it is set as empty. */
    void enable_data_type_info(bool _l_enable);

    /*! If member widgets were inserted in a grid layout, then the function inserts the widgets back to layout of the instance.*/
    void reclaim_widgets_ownership();

protected:

    /*! Append text on a new line to widget tool tip.*/
    void append_tool_tip(const std::string& _string);

};

#include "GlvWidget.h"
#include "glv_QString.h"
#include "slv_optional_text_str.h"
#include "misc/SlvDataName.h"

template <class Tdata>
GlvDescribedWidget<Tdata>::GlvDescribedWidget(Tdata _value, std::string _data_name, std::string _description, bool l_editable, QWidget* _parent) :GlvDescribedWidget_base(_data_name) {

    data_widget = new GlvWidget<Tdata>(_value, l_editable, _parent);
    data_widget->setEnabled(l_editable);
    data_widget->setObjectName(glv::toQString(data_name));
    data_widget->setToolTip(glv::toQString(_description));
    data_widget->setWhatsThis(glv::toQString(SlvDataName<Tdata>::name()));

    GlvDescribedWidget_base::set_data_widget(data_widget, glv::toQString(slv::ts::get_optional_text_str(_value)));

    connect(data_widget, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));

}

template <class Tdata>
GlvDescribedWidget<Tdata>::~GlvDescribedWidget() {

}

template <class Tdata>
Tdata GlvDescribedWidget<Tdata>::get_value() const {

    return data_widget->get_value();
}

template <class Tdata>
void GlvDescribedWidget<Tdata>::set_value(const Tdata& _value) {

    return data_widget->set_value(_value);
}

template <class Tdata>
const GlvWidget<Tdata>* GlvDescribedWidget<Tdata>::get_widget() const {

    return data_widget;
}

template <class Tdata>
GlvWidget<Tdata>* GlvDescribedWidget<Tdata>::get_widget() {

    return data_widget;
}

template <class Tdata>
void GlvDescribedWidget<Tdata>::enable_data_type_info(bool _l_enable) {

    if (_l_enable) {
        data_widget->setWhatsThis(glv::toQString(SlvDataName<Tdata>::name()));
    } else {
        data_widget->setWhatsThis("");
    }

}

template <class Tdata>
void GlvDescribedWidget<Tdata>::reclaim_widgets_ownership() {

    GlvDescribedWidget_base::reclaim_widgets_ownership(data_widget);

}

template <class Tdata>
void GlvDescribedWidget<Tdata>::append_tool_tip(const std::string& _string) {

    if (!_string.empty()) {
        QString string = data_widget->toolTip();
        string += "\n";
        string += glv::toQString(_string);
        data_widget->setToolTip(string);
    }

}