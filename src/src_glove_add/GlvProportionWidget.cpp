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

#include "GlvProportionWidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QDoubleSpinBox>//for value_widget

GlvProportionWidget::GlvProportionWidget(SlvProportion _proportion, int _slider_size, QWidget* _parent) {
    
    QGridLayout* layout = new QGridLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    
    value_widget = new QDoubleSpinBox;
    value_widget->setMaximum(100);
    value_widget->setMinimum(0);
    value_widget->setDecimals(2);

    layout->addWidget(value_widget, 0, 0);
    percentage_label = new QLabel("%");
    layout->addWidget(percentage_label, 0, 1);
    slider = new QSlider;
    slider->setMinimum(0);
    slider->setOrientation(Qt::Horizontal);
    layout->addWidget(slider, 1, 0);
    setLayout(layout);

    set_slider_size(_slider_size);

    connect(value_widget, SIGNAL(valueChanged(double)), this, SLOT(valueChanged_slot(double)));
    
    //sync spinbox and slider
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(set_value_to_spinbox(int)));
    connect(value_widget, SIGNAL(valueChanged(double)), this, SLOT(set_value_to_slider(double)));
    
    set_value(_proportion);
}

GlvProportionWidget::~GlvProportionWidget() {
    
}

void GlvProportionWidget::set_slider_size(int _slider_size) {

    slider_size = _slider_size;

    value_widget->setSingleStep(double(100) / slider_size);
    slider->setMaximum(slider_size);

    set_value_to_slider(value_widget->value());

}

SlvProportion GlvProportionWidget::get_value() const {
    
    return SlvProportion(value_widget->value() / 100);
}

void GlvProportionWidget::set_value(const SlvProportion& _proportion) {
    
    value_widget->setValue(_proportion * 100);
}

void GlvProportionWidget::set_editable(bool l_editable) {
    
    value_widget->setEnabled(l_editable);
    slider->setEnabled(l_editable);
    
}

void GlvProportionWidget::set_value_to_spinbox(int _value) {
    
    value_widget->setValue(double(_value) * double(100) / slider_size);
    
}

void GlvProportionWidget::set_value_to_slider(double _value) {

    slider->setValue(int(_value * slider_size / 100));
    
}

void GlvProportionWidget::valueChanged_slot(double _value) {
    
    emit valueChanged(_value);

}
