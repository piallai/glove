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

#include <QWidget>
#include "SlvSize2d.h"

/*! Widget for std::pair.*/
class GlvSize2dWidget_base : public QWidget {
    Q_OBJECT
protected:
    GlvSize2dWidget_base(QWidget* _parent = 0) : QWidget(_parent) {}
    virtual ~GlvSize2dWidget_base() {}
public:
    void set_editable(bool l_editable) {
        QWidget::setEnabled(l_editable);
    }
signals:
    /*! Emitted when width is modified.*/
    void valueChanged_width();
    /*! Emitted when height is modified.*/
    void valueChanged_height();
};

template <class T>
class GlvDescribedWidget;

#define _Tdata_ SlvSize2d<T>

/*! Widget for SlvSize2d.*/
template <class T>
class GlvSize2dWidget : public GlvSize2dWidget_base {

private:

    GlvDescribedWidget<T>* width_widget;
    GlvDescribedWidget<T>* height_widget;

public:

    GlvSize2dWidget(_Tdata_ _size = _Tdata_(), QWidget* _parent = 0);
    ~GlvSize2dWidget();

    void set_size(const _Tdata_ _size);
    _Tdata_ get_size() const;

};

#include <QHBoxLayout>
#include <QLabel>
#include "GlvWidget.h"

template <class T>
GlvSize2dWidget<T>::GlvSize2dWidget(_Tdata_ _size, QWidget* _parent) : GlvSize2dWidget_base(_parent) {

    QHBoxLayout* layout = new QHBoxLayout;
    setLayout(layout);

    layout->setSpacing(4);
    layout->setContentsMargins(0, 0, 0, 0);

    bool l_editable = true;
    width_widget = new GlvDescribedWidget<T>(_size.width, "", "Width", l_editable, _parent);
    connect(width_widget, SIGNAL(valueChanged()), this, SIGNAL(valueChanged_width()));
    layout->addWidget(width_widget);
    layout->addWidget(new QLabel("x"));
    height_widget = new GlvDescribedWidget<T>(_size.height, "", "Height", l_editable, _parent);
    connect(height_widget, SIGNAL(valueChanged()), this, SIGNAL(valueChanged_height()));
    layout->addWidget(height_widget);

}

template <class T>
GlvSize2dWidget<T>::~GlvSize2dWidget() {

}

template <class T>
void GlvSize2dWidget<T>::set_size(const _Tdata_ _size) {

    width_widget->set_value(_size.width);
    height_widget->set_value(_size.height);

}

template <class T>
_Tdata_ GlvSize2dWidget<T>::get_size() const {

    _Tdata_ value;
    value.width = width_widget->get_value();
    value.height = height_widget->get_value();
    return value;

}

#undef _Tdata_
