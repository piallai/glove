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

#include <QWidget>
#include "SlvSides2d.h"

/*! Widget for std::pair.*/
class GlvSides2dWidget_base : public QWidget {
    Q_OBJECT
protected:
    GlvSides2dWidget_base(QWidget* _parent = 0) : QWidget(_parent) {}
    virtual ~GlvSides2dWidget_base() {}
public:
    void set_editable(bool l_editable) {
        QWidget::setEnabled(l_editable);
    }
signals:
    /*! Emitted when left is modified.*/
    void valueChanged_left();
    /*! Emitted when right is modified.*/
    void valueChanged_right();
    /*! Emitted when up is modified.*/
    void valueChanged_up();
    /*! Emitted when bottom is modified.*/
    void valueChanged_bottom();
};

template <class T>
class GlvDescribedWidget;

#define _Tdata_ SlvSides2d<T>

/*! Widget for SlvSides2d.*/
template <class T>
class GlvSides2dWidget : public GlvSides2dWidget_base {

private:

    GlvDescribedWidget<T>* left_widget;
    GlvDescribedWidget<T>* right_widget;
    GlvDescribedWidget<T>* up_widget;
    GlvDescribedWidget<T>* bottom_widget;

public:

    GlvSides2dWidget(_Tdata_ _sides = _Tdata_(), QWidget* _parent = 0);
    ~GlvSides2dWidget();

    void set_sides(const _Tdata_ _sides);
    _Tdata_ get_sides() const;

};

#include <QGridLayout>
#include <QLabel>
#include "GlvWidget.h"

template <class T>
GlvSides2dWidget<T>::GlvSides2dWidget(_Tdata_ _sides, QWidget* _parent) : GlvSides2dWidget_base(_parent) {

    QGridLayout* layout = new QGridLayout;
    setLayout(layout);

    layout->setSpacing(4);
    layout->setContentsMargins(0, 0, 0, 0);

    bool l_editable = true;

    up_widget = new GlvDescribedWidget<T>(_sides.up, "", "Up", l_editable, _parent);
    connect(up_widget, SIGNAL(valueChanged()), this, SIGNAL(valueChanged_up()));
    layout->addWidget(up_widget, 0, 1);

    left_widget = new GlvDescribedWidget<T>(_sides.left, "", "Left", l_editable, _parent);
    connect(left_widget, SIGNAL(valueChanged()), this, SIGNAL(valueChanged_left()));
    layout->addWidget(left_widget, 1, 0);

    right_widget = new GlvDescribedWidget<T>(_sides.right, "", "Right", l_editable, _parent);
    connect(right_widget, SIGNAL(valueChanged()), this, SIGNAL(valueChanged_right()));
    layout->addWidget(right_widget, 1, 2);

    bottom_widget = new GlvDescribedWidget<T>(_sides.bottom, "", "Bottom", l_editable, _parent);
    connect(bottom_widget, SIGNAL(valueChanged()), this, SIGNAL(valueChanged_bottom()));
    layout->addWidget(bottom_widget, 2, 1);

}

template <class T>
GlvSides2dWidget<T>::~GlvSides2dWidget() {

}

template <class T>
void GlvSides2dWidget<T>::set_sides(const _Tdata_ _sides) {

    left_widget->set_value(_sides.left);
    right_widget->set_value(_sides.right);
    up_widget->set_value(_sides.up);
    bottom_widget->set_value(_sides.bottom);

}

template <class T>
_Tdata_ GlvSides2dWidget<T>::get_sides() const {

    _Tdata_ value;
    value.left = left_widget->get_value();
    value.right = right_widget->get_value();
    value.up = up_widget->get_value();
    value.bottom = bottom_widget->get_value();
    return value;

}

#undef _Tdata_
