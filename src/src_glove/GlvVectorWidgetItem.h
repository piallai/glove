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

#include "GlvVectorWidgetItem_base.h"

template <class T>
class GlvWidget;
template <class T>
class GlvVectorWidget;

/*! Item widget for GlvVectorWidget.*/
template <class T>
class GlvVectorWidgetItem : public GlvVectorWidgetItem_base {

private:

    /*! Widget of the data.*/
    GlvWidget<T>* widget;
    /*! Vector widget the item belongs to.*/
    GlvVectorWidget<T>* parent;

private:

    /*! \p _value : Initialization value.
    * \p _index : index in GlvVectorWidget.*
    * \p _parent : Vector widget the item belongs to.*/
    GlvVectorWidgetItem(const T& _value, const unsigned int _index, GlvVectorWidget<T>* _parent);
    ~GlvVectorWidgetItem();

public:
    T get_value() const;
    void set_value(const T _value);
private:
    GlvWidget<T>* get_widget() const;
    void increment_index();
    void decrement_index();
    void update_label_index();

    /*! Remove in GlvVectorWidget at index contained in the instance.*/
    void remove();

    friend class GlvVectorWidget<T>;

};

#include <QLabel>
#include <QPushButton>
#include "glv_QString.h"

template <class T>
GlvVectorWidgetItem<T>::GlvVectorWidgetItem(const T& _value, const unsigned int _index, GlvVectorWidget<T>* _parent) {

    widget = new GlvWidget<T>(_value);
    index = _index;
    parent = _parent;

    label_index = new QLabel;
    update_label_index();
    remove_button = new QPushButton(tr("Remove"));
    layout->addWidget(label_index);
    layout->addWidget(widget);
    layout->addWidget(remove_button);

    connect(remove_button, SIGNAL(clicked()), this, SLOT(remove()));
    connect(widget, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));

}

template <class T>
GlvVectorWidgetItem<T>::~GlvVectorWidgetItem() {

}

template <class T>
T GlvVectorWidgetItem<T>::get_value() const {

    return widget->get_value();

}

template <class T>
void GlvVectorWidgetItem<T>::set_value(const T _value) {

    widget->set_value(_value);

}

template <class T>
GlvWidget<T>* GlvVectorWidgetItem<T>::get_widget() const {
    return widget;
}

template <class T>
void GlvVectorWidgetItem<T>::increment_index() {
    index++;
    update_label_index();
}

template <class T>
void GlvVectorWidgetItem<T>::decrement_index() {
    index--;
    update_label_index();
}

template <class T>
void GlvVectorWidgetItem<T>::update_label_index() {
    label_index->setText(glv::toQString(index));
}

template <class T>
void GlvVectorWidgetItem<T>::remove() {
    parent->removeWidget(index);
}