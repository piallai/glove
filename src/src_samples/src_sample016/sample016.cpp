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

// Example for size widget

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include <QApplication>
#include "param/SlvParametrizationMacro.h"
#include "GlvParametrizationDialog.h"
#include "GlvWidgetData_spec_SlvSize2d.h"
#include "GlvWidgetData_spec_AT.h"
#else
//#define GLOVE_ENABLE_JSON
#include "glove.h"
#endif

glvm_parametrization(Test, "Test", size, SlvSize2d<int>, "size", "size comment", SlvSize2d<int>(10, 20))

int main(int argc, char* argv[]) {

	QApplication app(argc, argv);

	GlvWidget<SlvSize2d<int>> size_widget(SlvSize2d<int>(200, 100));
	size_widget.show();

	GlvParametrizationDialog<Test> dialog;
	dialog.show();

	return app.exec();
}
