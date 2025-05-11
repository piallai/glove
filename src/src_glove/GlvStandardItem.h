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

#include <QStandardItem>
#include "glv_QString.h"

/*! Simple QStandardItem containing a template value and its expression in QString. If no specialization of glv::toQString<T>, slv::string::to_string<T> is used.*/
template <class T>
class GlvStandardItem : public QStandardItem {

protected:

    T value;

public:

    GlvStandardItem();
    GlvStandardItem(const T& _value);
    /*! Text can be explicitly set.*/
    GlvStandardItem(const QString& text);
    GlvStandardItem(const QString& text, const T& _value);
    GlvStandardItem(const QIcon& icon, const QString& text, const T& _value);

    ~GlvStandardItem();

    const T& get_value() const;
    void set_value(const T& _value);

};

template <class T>
GlvStandardItem<T>::GlvStandardItem() :QStandardItem(), value(T()) {

}

template <class T>
GlvStandardItem<T>::GlvStandardItem(const T& _value) : QStandardItem(glv::toQString(_value)), value(_value) {

}

template <class T>
GlvStandardItem<T>::GlvStandardItem(const QString& text) : QStandardItem(text), value(T()) {

}

template <class T>
GlvStandardItem<T>::GlvStandardItem(const QString& text, const T& _value) : QStandardItem(text), value(_value) {

}

template <class T>
GlvStandardItem<T>::GlvStandardItem(const QIcon& icon, const QString& text, const T& _value) : QStandardItem(icon, text), value(_value) {

}

template <class T>
GlvStandardItem<T>::~GlvStandardItem() {

}

template <class T>
const T& GlvStandardItem<T>::get_value() const {

    return value;

}

template <class T>
void GlvStandardItem<T>::set_value(const T& _value) {

    value = _value;

}