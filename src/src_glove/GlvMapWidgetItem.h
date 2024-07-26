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

#include "GlvMapWidgetItem_base.h"

template <class T>
class GlvWidget;
template <class Tkey, class Tvalue, class Tcompare>
class GlvMapWidget;

/*! Item widget for GlvMapWidget.*/
template <class Tkey, class Tvalue, class Tcompare>
class GlvMapWidgetItem : public GlvMapWidgetItem_base {

private:

    /*! Widget of the key.*/
    GlvWidget<Tkey>* key_widget;
    /*! Widget of the data.*/
    GlvWidget<Tvalue>* value_widget;
    /*! Map widget the item belongs to.*/
    GlvMapWidget<Tkey, Tvalue, Tcompare>* parent;

private:

    /*! \p _key : Key.
    * \p _value : Initialization value.
    * \p _index : index in GlvMapWidget.*
    * \p _parent : Vector widget the item belongs to.*/
    GlvMapWidgetItem(const Tkey& _key, const Tvalue& _value, const unsigned int _index, GlvMapWidget<Tkey, Tvalue, Tcompare>* _parent);
    ~GlvMapWidgetItem();

    Tkey get_key() const;
    void set_key(const Tkey _key);
    Tvalue get_value() const;
    void set_value(const Tvalue _value);
    GlvWidget<Tkey>* get_key_widget() const;
    GlvWidget<Tvalue>* get_value_widget() const;
    void increment_index();
    void decrement_index();

    /*! Remove in GlvMapWidget at index contained in the instance.*/
    void remove();

    friend class GlvMapWidget<Tkey, Tvalue, Tcompare>;
};

#include <QLabel>
#include <QPushButton>
#include "glv_QString.h"

template <class Tkey, class Tvalue, class Tcompare>
GlvMapWidgetItem<Tkey, Tvalue, Tcompare>::GlvMapWidgetItem(const Tkey& _key, const Tvalue& _value, const unsigned int _index, GlvMapWidget<Tkey, Tvalue, Tcompare>* _parent) {

    key_widget = new GlvWidget<Tkey>(_key);
    value_widget = new GlvWidget<Tvalue>(_value);
    index = _index;
    parent = _parent;

    remove_button = new QPushButton(tr("Remove"));
    layout->addWidget(key_widget);
    layout->addWidget(value_widget);
    layout->addWidget(remove_button);

    connect(remove_button, SIGNAL(clicked()), this, SLOT(remove()));
    connect(value_widget, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));

}

template <class Tkey, class Tvalue, class Tcompare>
GlvMapWidgetItem<Tkey, Tvalue, Tcompare>::~GlvMapWidgetItem() {

}

template <class Tkey, class Tvalue, class Tcompare>
Tkey GlvMapWidgetItem<Tkey, Tvalue, Tcompare>::get_key() const {

    return key_widget->get_value();

}

template <class Tkey, class Tvalue, class Tcompare>
void GlvMapWidgetItem<Tkey, Tvalue, Tcompare>::set_key(const Tkey _key) {

    key_widget->set_value(_key);

}

template <class Tkey, class Tvalue, class Tcompare>
Tvalue GlvMapWidgetItem<Tkey, Tvalue, Tcompare>::get_value() const {

    return value_widget->get_value();

}

template <class Tkey, class Tvalue, class Tcompare>
void GlvMapWidgetItem<Tkey, Tvalue, Tcompare>::set_value(const Tvalue _value) {

    value_widget->set_value(_value);

}

template <class Tkey, class Tvalue, class Tcompare>
GlvWidget<Tkey>* GlvMapWidgetItem<Tkey, Tvalue, Tcompare>::get_key_widget() const {
    return key_widget;
}

template <class Tkey, class Tvalue, class Tcompare>
GlvWidget<Tvalue>* GlvMapWidgetItem<Tkey, Tvalue, Tcompare>::get_value_widget() const {
    return value_widget;
}

template <class Tkey, class Tvalue, class Tcompare>
void GlvMapWidgetItem<Tkey, Tvalue, Tcompare>::increment_index() {
    index++;
}

template <class Tkey, class Tvalue, class Tcompare>
void GlvMapWidgetItem<Tkey, Tvalue, Tcompare>::decrement_index() {
    index--;
}

template <class Tkey, class Tvalue, class Tcompare>
void GlvMapWidgetItem<Tkey, Tvalue, Tcompare>::remove() {
    parent->removeWidget(index);
}
