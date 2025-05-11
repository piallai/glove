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

/* Example of for json save/load with basic types.*/

#include <QApplication>

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrizationMacro.h"
#else
#define GLOVE_ENABLE_JSON
#include "glove.h"
#endif
glvm_parametrization(ClassB, "ClassB",
                                        paramA, int, "paramA", "comment about parameterA", 0,
                                        paramB, float, "paramB", "comment about parameter B", 0.f,
                                        paramC, bool, "paramC", "comment about parameter C", true,
                                        paramD, std::vector<double>, "paramD", "comment about parameter D", {7.},
                                        paramE, std::string, "paramE", "comment about parameter E", "default")
glvm_parametrization(ClassA, "ClassA",
                                        paramA, int, "paramA", "comment about parameterA", 0,
                                        paramB, float, "paramB", "comment about parameter B", 0.f,
                                        paramC, bool, "paramC", "comment about parameter C", true,
                                        paramD, std::vector<double>, "paramD", "comment about parameter D", std::vector<double>({5., 9.}),
                                        paramE, std::string, "paramE", "comment about parameter E", "default",
                                        paramF, ClassB, "paramF", "comment about parameter F", ClassB())

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvWidgetData_spec_AT.h"
#include "GlvWidgetData_spec_std_string.h"
#include "GlvWidgetData_spec_std_vector.h"
#include "GlvWidgetData_spec_SlvParametrization.h"
#include "GlvParametrizationWidget.h"
#include "GlvParametrizationSaveLoad.h"
#endif

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

	GlvParametrizationWidget<ClassA>* param_widget = new GlvParametrizationWidget<ClassA>;
	GlvParametrizationSaveLoad<ClassA>* save_load_widget = new GlvParametrizationSaveLoad<ClassA>(param_widget);
	param_widget->show();

    return app.exec();

}

