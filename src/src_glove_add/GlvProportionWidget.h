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
class QSlider;
class QLabel;
#include "GlvWidgetData_spec_AT.h"
#include "SlvProportion.h"

/*! Widget managing a ratio value SlvProportion.
* The value is in the range [0, 1].
* The interaction can be done using a slider or a direct value input.*/
class GlvProportionWidget : public QWidget {

    Q_OBJECT

private:

    QDoubleSpinBox* value_widget;
    QLabel* percentage_label;
    QSlider* slider;

    int slider_size;

public:

    /*! \p _proportion : initial value.
    * \p _slider_size : number of sampled values for the slider.*/
    GlvProportionWidget(SlvProportion _proportion = 0, int _slider_size = 100, QWidget* _parent = 0);
    ~GlvProportionWidget();

    SlvProportion get_value() const;

    /*! Set the number of sampled values for the slider.*/
    void set_slider_size(int _slider_size);

    void set_editable(bool l_editable);

public slots:

    void set_value(const SlvProportion& _proportion);

private slots:

    void set_value_to_spinbox(int _value);
    void set_value_to_slider(double _value);
    void valueChanged_slot(double _value);

signals:
    void valueChanged(double _value);

};

