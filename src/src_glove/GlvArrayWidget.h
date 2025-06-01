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

#include "GlvVectorWidget.h"
#include "std_array.h"

#define _Tdata_ std::array<T, N>

/*! Widget to manage interface of std::vector.*/
template <class T, size_t N>
class GlvArrayWidget : public GlvVectorWidget<T> {


public:

    GlvArrayWidget(_Tdata_ _array = _Tdata_(), QWidget* _parent = 0);
    ~GlvArrayWidget();

    /*! Set vector.*/
    void set_value(const _Tdata_& _array);
    /*! Get vector.*/
    _Tdata_ get_value() const;

private:
    using GlvVectorWidget<T>::pushValue;
    using GlvVectorWidget<T>::popValue;
    using GlvVectorWidget<T>::insertValue;

};

#include <QVBoxLayout>
#include "GlvWidget.h"
#include "GlvVectorWidgetItem.h"

template <class T, size_t N>
GlvArrayWidget<T, N>::GlvArrayWidget(_Tdata_ _array, QWidget* _parent) : GlvVectorWidget<T>({}, _parent) {

    this->buttons_group_widget->hide();

    for (int i = 0; i < N; i++) {
        pushValue();
        this->widgets[i]->show_remove_button(false);
    }

    set_value(_array);

}

template <class T, size_t N>
GlvArrayWidget<T, N>::~GlvArrayWidget() {

}

template <class T, size_t N>
void GlvArrayWidget<T, N>::set_value(const _Tdata_& _array) {

    for (int i = 0; i < N; i++) {
        this->widgets[i]->set_value(_array[i]);
    }

}

template <class T, size_t N>
_Tdata_ GlvArrayWidget<T, N>::get_value() const {

    _Tdata_ value;
    for (int i = 0; i < N; i++) {
        value[i] = this->widgets[i]->get_value();
    }
    return value;

}

#undef _Tdata_
