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

#include "GlvWidget_base.h"
#include "GlvWidgetConnector.h"
#include <QHBoxLayout>
#include <algorithm>
#include "GlvWidgetSaveLoad_base.h"

GlvWidget_base::GlvWidget_base(QWidget* _parent) :QWidget(_parent) {

    data_widget = 0;
    connector = new GlvWidgetConnector(this);

    layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

}

GlvWidget_base::~GlvWidget_base() {

    delete connector;
}

void GlvWidget_base::set_widget() {

    layout->addWidget(data_widget);

}

void GlvWidget_base::set_save_load_widget(GlvWidgetSaveLoad_base* _save_load_widget) {

    save_load_widget = _save_load_widget;
    if (save_load_widget) {
        layout->insertWidget(1, save_load_widget);// index 1 because of optional widgets
    }

}

void GlvWidget_base::add_optional_widget(QWidget* _widget) {

    optional_widgets.push_back(_widget);
    layout->addWidget(_widget);

}

std::vector<QWidget*>::iterator GlvWidget_base::delete_optional_widget(QWidget* _widget) {

    std::vector<QWidget*>::iterator it;

    if (_widget != data_widget) {// Forbid removal of main widget

        it = std::find(optional_widgets.begin(), optional_widgets.end(), _widget);

        if (it != optional_widgets.end()) {
            it = optional_widgets.erase(it);
            delete _widget;
            layout->removeWidget(_widget);
        }

    } else {
        it = optional_widgets.end();
    }

    return it;
}

void GlvWidget_base::delete_optional_widgets() {

    for (std::vector<QWidget*>::iterator it = optional_widgets.begin(); it != optional_widgets.end(); ) {
        it = delete_optional_widget(*it);
    }

}

void GlvWidget_base::resizeEvent(QResizeEvent* _resize_event) {

    emit sizeChanged();
    QWidget::resizeEvent(_resize_event);

}
