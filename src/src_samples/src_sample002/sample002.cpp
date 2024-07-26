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

/* Example for a class parametrization which parameters have rules on their value.*/

#include <QApplication>

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrization2.h"
#else
#include "glove.h"
#endif

class ClassA : public SlvParametrization2<int, double> {

	glvm_parametrization2_init("ClassA");

	glvm_parameter_ruled(1, paramA, int, "parameter_A", "Comment about parameter A", 1)
	glvm_parameter_add_rule(exception, 20)
	glvm_parameter_add_rule(max, 30)
	glvm_parameter_end
	glvm_parameter_ruled(2, paramB, double, "parameter_B", "Comment about parameter B", 2.)
	glvm_parameter_add_rule(min_exception, 10)
	glvm_parameter_end

public:

	ClassA(): glvm_parametrization_constructor(paramA, paramB) {}

};

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvParametrizationDialog.h"
#include "GlvWidgetData_spec_AT.h"
#endif

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

	ClassA classA;
	
	SlvStatus status = classA.set_paramA(31);
	std::cout << status << std::endl;

	status = classA.check_parameters();
	if (!status) {
		std::cout << status << std::endl;
		// Output: {Parameter parameter_A can not be greater than 30, warning}
		classA.abide_rules();
		std::cout << classA << std::endl;// Parameters are ok
	}
	classA.set_paramB_unruled(2);// back to initial wrong parameter value

    GlvParametrizationDialog<ClassA>* parametrization_dialog = new GlvParametrizationDialog<ClassA>(classA);
    parametrization_dialog->exec();

    return app.exec();

}

