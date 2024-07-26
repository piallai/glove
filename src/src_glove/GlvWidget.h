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

#include "GlvWidget_base.h"
#include "GlvWidgetMaker.h"

/*! Front-end of automatic widget management. GlvWidget -> GlvWidgetMaker -> GlvWidgetData.
* No text information here (unlike GlvDescribedWidget/GlvParameterWidget).*/
template <class Tvalue>
class GlvWidget : public GlvWidget_base {

public:

    /*! \p _value : Initial value.
    * \p _l_editable : editable widget or not.*/
    GlvWidget(Tvalue _value, bool _l_editable = true, QWidget* _parent = 0);
    GlvWidget(bool l_editable, QWidget* _parent = 0);
    GlvWidget(QWidget* _parent = 0);
    ~GlvWidget();

    Tvalue get_value() const;
    void set_value(const Tvalue& _value);
    void set_editable(bool _l_editable);

    /*! Get data widget. GlvWidgetData<Tvalue> unless GlvWidgetMaker specialization.*/
    const typename GlvWidgetMaker<Tvalue>::Twidget* get_widget() const;
    /*! Get data widget. GlvWidgetData<Tvalue> unless GlvWidgetMaker specialization.*/
    typename GlvWidgetMaker<Tvalue>::Twidget* get_widget();

};

template <class Tvalue>
GlvWidget<Tvalue>::GlvWidget(Tvalue _value, bool _l_editable, QWidget* _parent) :GlvWidget_base(_parent) {

    /*! Build data_widget.*/
    GlvWidgetMaker<Tvalue>::make(this, _value, _l_editable, _parent);
    /*! data_widget is set in the layout.*/
    GlvWidget_base::set_widget();

}

template <class Tvalue>
GlvWidget<Tvalue>::GlvWidget(bool l_editable, QWidget* _parent) :GlvWidget<Tvalue>(Tvalue(), l_editable, _parent) {

}

template <class Tvalue>
GlvWidget<Tvalue>::GlvWidget(QWidget* _parent) : GlvWidget<Tvalue>(Tvalue(), true, _parent) {

}

template <class Tvalue>
GlvWidget<Tvalue>::~GlvWidget() {

}

template <class Tvalue>
Tvalue GlvWidget<Tvalue>::get_value() const {

    Tvalue value = GlvWidgetMaker<Tvalue>::get(this);
    return value;
}

template <class Tvalue>
void GlvWidget<Tvalue>::set_value(const Tvalue& _value) {

    GlvWidgetMaker<Tvalue>::set(this, _value);
}

template <class Tvalue>
void GlvWidget<Tvalue>::set_editable(bool _l_editable) {
    GlvWidgetMaker<Tvalue>::set_editable(this, _l_editable);
}

template <class Tvalue>
const typename GlvWidgetMaker<Tvalue>::Twidget* GlvWidget<Tvalue>::get_widget() const {

    return dynamic_cast<typename GlvWidgetMaker<Tvalue>::Twidget*>(data_widget);
}

template <class Tvalue>
typename GlvWidgetMaker<Tvalue>::Twidget* GlvWidget<Tvalue>::get_widget() {

    return dynamic_cast<typename GlvWidgetMaker<Tvalue>::Twidget*>(data_widget);
}
