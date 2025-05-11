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

/*! Example of how to use GlvVectorWidget to manage std::vector
* and how to use GlvMapWidget to manage std::map.*/

#include <QApplication>

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvVectorWidget.h"
#include "GlvWidgetData_spec_AT.h"
#include "GlvWidgetData_spec_std_string.h"

#include "GlvMapWidget.h"
#else
#include "glove.h"
#endif
#include "QtSlotsExample.h"
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
// SlvProportion as key for example
#include "GlvWidgetData_spec_SlvProportion.h"
#endif

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    QtSlotsExample qtslots;

    /////////////////////////////////////////
    // std::vector example
    /////////////////////////////////////////

    std::vector<float> vector({ 5.3f, 1.2f, -2.8f, 6.4f });
    GlvVectorWidget<float>* vector_widget = new GlvVectorWidget<float>(vector);
    vector_widget->show();
    QObject::connect(vector_widget, SIGNAL(valueChanged(int)), &qtslots, SLOT(get(int)));

    /////////////////////////////////////////
    // std::map example
    /////////////////////////////////////////

    std::map<int, std::string> map({ {2, "foo1"}, {-1, "foo2"} , {3, "foo3"} });
    GlvMapWidget<int, std::string>* map_widget = new GlvMapWidget<int, std::string>(map);
    map_widget->show();
    QObject::connect(map_widget, SIGNAL(valueChanged(int)), &qtslots, SLOT(get(int)));

    std::map<SlvProportion, std::string> map2({ {0., "foo1"}, {0.9, "foo2"} });
    GlvMapWidget<SlvProportion, std::string>* map_widget2 = new GlvMapWidget<SlvProportion, std::string>(map2);
    map_widget2->show();
    map_widget2->set_key_editable(true);
    QObject::connect(map_widget2, SIGNAL(valueChanged(int)), &qtslots, SLOT(get(int)));

    return app.exec();

}

