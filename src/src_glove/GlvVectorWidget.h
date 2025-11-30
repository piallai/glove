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

#include "GlvVectorWidget_base.h"

#define _Tdata_ std::vector<T>

class QVBoxLayout;
template <class T>
class GlvVectorWidgetItem;
template <class Tvalue>
class GlvWidget;

/*! Widget to manage interface of std::vector.*/
template <class T>
class GlvVectorWidget : public GlvVectorWidget_base {

protected:

    std::vector<GlvVectorWidgetItem<T>*> widgets;

public:

    GlvVectorWidget(_Tdata_ _vector = _Tdata_(), QWidget* _parent = 0);
    ~GlvVectorWidget();

    /*! Set vector.*/
    void set_value(const _Tdata_& _vector);
    /*! Get vector.*/
    _Tdata_ get_value() const;

    void pushValue(T _value);
    /*! Reimplementation of virtual method.*/
    void pushValue();
    void popValue();
    /*! New value at index \p i.*/
    void insertValue(const unsigned int i);
    /*! Resize vector at size \p i.*/
    void resizeVector(const unsigned int i);
    /*! Get widget of index \p i.*/
    GlvWidget<T>* operator[] (const unsigned int i);

private:

    void valueChanged_slot();
    void removeWidget(const unsigned int i);

    friend class GlvVectorWidgetItem<T>;
};

#include <QVBoxLayout>
#include "GlvWidget.h"
#include "GlvVectorWidgetItem.h"

template <class T>
GlvVectorWidget<T>::GlvVectorWidget(_Tdata_ _vector, QWidget* _parent) : GlvVectorWidget_base(_parent) {

    set_value(_vector);

}

template <class T>
GlvVectorWidget<T>::~GlvVectorWidget() {

}

template <class T>
void GlvVectorWidget<T>::set_value(const _Tdata_& _vector) {

    if (_vector.size() > Nelements_max) {
        set_Nelements_max((int)_vector.size());
    }

    int N = (int)std::min(widgets.size(), _vector.size());

    for (int i = 0; i < N; i++) {
        widgets[i]->set_value(_vector[i]);
    }

    if (widgets.size() < _vector.size()) {
        for (int i = N; i < _vector.size(); i++) {
            pushValue(_vector[i]);
        }
    } else if (widgets.size() > _vector.size()) {
        for (int i = N; i < widgets.size(); i++) {
            layout_items->removeWidget(widgets[i]);
            delete widgets[i];
        }
        widgets.resize(_vector.size());
        resize_spinbox->setValue((int)widgets.size());
        insert_spinbox->setMaximum((int)widgets.size());
    }

    if (_vector.empty()) {// If no vector item exists, then the vector is indicated as fully displayed for reading convenience
        set_checked(true);
    } else if (!QWidget::isVisible()) {// If a value is set before the widget is visible, and the vector widget is checkable, then the default display hides the vector items
        set_checked(false);
    }

}

template <class T>
_Tdata_ GlvVectorWidget<T>::get_value() const {

    _Tdata_ value(widgets.size());
    for (int i = 0; i < widgets.size(); i++) {
        value[i] = widgets[i]->get_value();
    }
    return value;

}

template <class T>
void GlvVectorWidget<T>::pushValue(T _value) {

    if (widgets.size() < Nelements_max) {

        GlvVectorWidgetItem<T>* widget = new GlvVectorWidgetItem<T>(_value, (int)widgets.size(), this);
        widgets.push_back(widget);
        layout_items->insertWidget((int)widgets.size() - 1, widget);
        connect(widget, SIGNAL(valueChanged()), this, SLOT(valueChanged_slot()));
        button_pop->setEnabled(true);

        if (widgets.size() == Nelements_max) {
            button_push->setEnabled(false);
            button_insert->setEnabled(false);
        }

        resize_spinbox->setValue((int)widgets.size());
        insert_spinbox->setMaximum((int)widgets.size());
    }
}

template <class T>
void GlvVectorWidget<T>::insertValue(const unsigned int i) {

    if (widgets.size() < Nelements_max) {

        unsigned int j = i;
        if (j > (unsigned int)widgets.size()) {
            j = (unsigned int)widgets.size();
        }
        GlvVectorWidgetItem<T>* widget = new GlvVectorWidgetItem<T>(T(), j, this);
        layout_items->insertWidget(j, widget);
        widgets.insert(widgets.begin() + j, widget);
        connect(widget->get_widget(), SIGNAL(valueChanged()), this, SLOT(valueChanged_slot()));
        button_pop->setEnabled(true);

        for (unsigned int k = j + 1; k < widgets.size(); k++) {
            widgets[k]->increment_index();
        }

        if (widgets.size() == Nelements_max) {
            button_push->setEnabled(false);
            button_insert->setEnabled(false);
            resize_spinbox->setValue((int)widgets.size());
            insert_spinbox->setMaximum((int)widgets.size());
        }

    }

}

template <class T>
void GlvVectorWidget<T>::resizeVector(const unsigned int i) {

    if (i != widgets.size()) {

        _Tdata_ vector_ = get_value();
        vector_.resize(std::min(i, Nelements_max));
        set_value(vector_);

        bool l_max = (widgets.size() == Nelements_max);
        button_push->setEnabled(!l_max);
        button_insert->setEnabled(!l_max);
        resize_spinbox->setValue((int)widgets.size());
        insert_spinbox->setMaximum((int)widgets.size());
    }

    if (widgets.empty()) {
        set_checked(true);// If no vector item exists, then the vector is indicated as fully displayed for reading convenience
    }

}

template <class T>
GlvWidget<T>* GlvVectorWidget<T>::operator[] (const unsigned int i) {
    return widgets[i]->get_widget();
}

template <class T>
void GlvVectorWidget<T>::pushValue() {

    pushValue(T());

}

template <class T>
void GlvVectorWidget<T>::popValue() {

    if (!widgets.empty()) {
        removeWidget((int)widgets.size() - 1);

        if (widgets.size() < Nelements_max) {
            button_push->setEnabled(true);
            button_insert->setEnabled(true);
        }

        resize_spinbox->setValue((int)widgets.size());
        insert_spinbox->setMaximum((int)widgets.size());
    }

}

template <class T>
void GlvVectorWidget<T>::valueChanged_slot() {

    GlvVectorWidgetItem<T>* item = dynamic_cast<GlvVectorWidgetItem<T>*>(QObject::sender());
    if (item) {
        emit valueChanged(item->index);
    }

}

template <class T>
void GlvVectorWidget<T>::removeWidget(const unsigned int i) {

    if (!widgets.empty()) {

        layout_items->removeWidget(widgets[i]);
        delete widgets[i];
        widgets.erase(widgets.begin() + i);

        for (unsigned int j = i; j < widgets.size(); j++) {
            widgets[j]->decrement_index();
        }
    }

    if (widgets.empty()) {
        button_pop->setEnabled(false);
        set_checked(true);// If no vector item exists, then the vector is indicated as fully displayed for reading convenience
    }

}

#undef _Tdata_
