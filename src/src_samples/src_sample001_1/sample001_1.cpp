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

/* Example for a simple class parametrization containing two parameters of type int and double.
* The int foo variable is here only to illustrate the behaviour of the parametrization assignment.
*/

#include <QApplication>

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrization2.h"
#else
#include "glove.h"
#endif

class ClassA : public SlvParametrization2<int, double> {

	glvm_parametrization2_init("ClassA")
	// parameter index, variable name, type, name of the parameter, comment about the parameter, default value
	glvm_parameter(1, paramA, int, "parameter_A", "Comment about parameter A", 1)
	glvm_parameter(2, paramB, double, "parameter_B", "Comment about parameter B", 2.)

public:

	int foo;

	ClassA() :glvm_parametrization_constructor(paramA, paramB) {

		foo = 0;

	}

private:

	void ostream(std::ostream& _os) const {
		SlvParametrization2<int, double>::ostream(_os);
		_os << "foo = " << foo << std::endl;
	}

};

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvParametrizationDialog.h"
#include "GlvWidgetData_spec_AT.h"
#endif

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

	ClassA classA;
	classA.foo = 17;
	classA.get_paramA();
	classA.set_paramA(4);

	GlvParametrizationDialog<ClassA>* parametrization_classA = new GlvParametrizationDialog<ClassA>(classA);

	int result = parametrization_classA->exec();
	if (result == QDialog::Accepted) {
		classA.param_cast() = parametrization_classA->get_parametrization();// assign only parameters
		std::cout << "classA : " << classA << std::endl;//foo is still 17
		classA = parametrization_classA->get_parametrization();// assign whole instance
		std::cout << "classA : " << classA << std::endl;//foo is constructor value 0 now
	}

    return app.exec();

}

