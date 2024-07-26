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

#include <QApplication>

/*! Example of how to enable save/load of data in a GlvWidget<T>.
* Possible if slv::rw::write and slv::rw::read are specialized for type T,
* or if T inherits from SlvWrite and SlvRead.
* If one wants to set GlvWidgetSaveLoad to a parameter of GlvParametrization,
* GlvWidget can be accessed using: glvm_get_parameter_GlvWidget.*/

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvWidget.h"
#include "GlvWidgetData_spec_AT.h"
#include "GlvWidgetData_spec_std_string.h"
#include "GlvWidgetSaveLoad.h"
// Example 2 : Parametrization instead of simple widget
#include "param/SlvParametrization1.h"
#include "param/SlvParametrizationMacro.h"
#else
#include "glove.h"
#endif
glvm_parametrization(ParamArg, "ParamArg", paramA, int, "paramA", "comment about parameterA", 0)
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvWidgetData_spec_SlvParametrization.h"
#endif
glvm_parametrization(ParamTest, "ParamTest", paramA, int, "paramA", "comment about parameterA", 0,
                                              paramB, bool, "paramB", "comment about parameterB", true,
                                              paramC, std::string, "paramC", "comment about parameterC", "default",
                                              paramD, ParamArg, "paramD", "comment about parameterD", ParamArg())

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvParametrizationWidget.h"
#include "GlvParametrizationSaveLoad.h"
#endif

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    GlvWidget<int>* widget = new GlvWidget<int>;
    // GlvWidgetSaveLoad is not managed directly in GlvWidget, because not every type is compatible with read/write (depending on implementation).
    // It is more convenient to externalize the type instantiation of GlvWidgetSaveLoad.
    // The type (here 'int') must be either:
    // - managed directly, such as the implementation for basic types found in slv_write.h and slv_read.h
    // - have a class implementation by inheriting SlvRead and SlvWrite (not needed in this example)
    GlvWidgetSaveLoad<int>* save_load_widget_int = new GlvWidgetSaveLoad<int>(widget);
    //widget->delete_optional_widgets();// To delete the added GlvWidgetSaveLoad widget
    widget->show();
    // to delete the save/load widget:
    // *** widget->delete_save_load_widget();
    // Or
    // *** delete save_load_widget_int;

    // Add an allowed extension to save/load interface
    SlvFileExtensions allowed_extensions = save_load_widget_int->get_allowed_extensions();
    allowed_extensions.add_front("myext");
    save_load_widget_int->set_allowed_extensions(allowed_extensions);

    // Example 2

    GlvParametrizationWidget<ParamTest>* param_test_widget = new GlvParametrizationWidget<ParamTest>;
    save_load_widget_int = new GlvWidgetSaveLoad<int>(glvm_get_parameter_GlvWidget(param_test_widget, 1));
    save_load_widget_int->set_orientation(Qt::Orientation::Vertical);
    //GlvWidgetSaveLoad<ParamTest>* save_load_widget = new GlvWidgetSaveLoad<ParamTest>(param_test_widget);
    param_test_widget->show();

    GlvWidgetSaveLoad<std::string>* save_load_widget_string = new GlvWidgetSaveLoad<std::string>(glvm_get_parameter_GlvWidget(param_test_widget, 3));

    // Same logic with GlvParametrizationWidget. Save/load is managed externally for more flexibility because
    // parameters type may not always have read/write methods implemented.
    
    GlvParametrizationSaveLoad<ParamTest>* save_load_widget_ParamTest = new GlvParametrizationSaveLoad<ParamTest>(param_test_widget);
    // to delete the save/load widget:
    // *** param_test_widget->delete_save_load_widget();
    // Or
    // *** delete save_load_widget_ParamTest;

    return app.exec();

}

