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
#include <utility>

/*! Widget for std::pair.*/
class GlvPairWidget_base : public QWidget {
    Q_OBJECT
protected:
    GlvPairWidget_base(QWidget* _parent = 0) : QWidget(_parent) {}
    virtual ~GlvPairWidget_base() {}
public:
    void set_editable(bool l_editable) {
        QWidget::setEnabled(l_editable);
    }
signals:
    /*! Emitted when first of pair is modified.*/
    void valueChanged_first();
    /*! Emitted when second of pair is modified.*/
    void valueChanged_second();
};

template <class T>
class GlvWidget;

#define _Tdata_ std::pair<T1, T2>

/*! Widget for std::pair.*/
template <class T1, class T2>
class GlvPairWidget : public GlvPairWidget_base {

private:

    GlvWidget<T1>* subwidget1;
    GlvWidget<T2>* subwidget2;

public:

    GlvPairWidget(_Tdata_ _pair = _Tdata_(), QWidget* _parent = 0);
    ~GlvPairWidget();

    void set_pair(const _Tdata_ _pair);
    _Tdata_ get_pair() const;

};

#include <QHBoxLayout>
#include "GlvWidget.h"

template <class T1, class T2>
GlvPairWidget<T1, T2>::GlvPairWidget(_Tdata_ _pair, QWidget* _parent) : GlvPairWidget_base(_parent) {

    QHBoxLayout* layout = new QHBoxLayout;
    setLayout(layout);

    layout->setContentsMargins(0, 0, 0, 0);

    bool l_editable = true;
    subwidget1 = new GlvWidget<T1>(_pair.first, l_editable, _parent);
    connect(subwidget1, SIGNAL(valueChanged()), this, SIGNAL(valueChanged_first()));
    layout->addWidget(subwidget1);
    subwidget2 = new GlvWidget<T2>(_pair.second, l_editable, _parent);
    connect(subwidget2, SIGNAL(valueChanged()), this, SIGNAL(valueChanged_second()));
    layout->addWidget(subwidget2);

}

template <class T1, class T2>
GlvPairWidget<T1, T2>::~GlvPairWidget() {

}

template <class T1, class T2>
void GlvPairWidget<T1, T2>::set_pair(const _Tdata_ _pair) {

    subwidget1->set_value(_pair.first);
    subwidget2->set_value(_pair.second);

}

template <class T1, class T2>
_Tdata_ GlvPairWidget<T1, T2>::get_pair() const {

    _Tdata_ value;
    value.first = subwidget1->get_value();
    value.second = subwidget2->get_value();
    return value;

}

#undef _Tdata_
