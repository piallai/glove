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

/* Example for a class parametrization containing a parameter which is another parametrization.
* The variable fooA, fooB, param_initA, param_initB are here only to illustrate the behaviour of the parametrization assignment.
*/

#include <QApplication>

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrization2.h"
#else
#include "glove.h"
#endif

class ClassB : public SlvParametrization2<int, double> {

	glvm_parametrization2_init("ClassB")

	glvm_parameter(1, paramA, int, "parameter_A", "Comment about parameter A", 1)
	glvm_parameter(2, paramB, double, "parameter_B", "Comment about parameter B", 2.)

public:

	int fooB;
	double param_initB;

	ClassB() :glvm_parametrization_constructor(paramA, paramB) {

		fooB = 0;
		param_init();

	}

	/*! Reimplementation of SlvParametrization_base::param_init().*/
	void param_init() {
		param_initB = get_paramB() * get_paramA() * 5;
	}

private:

	void ostream(std::ostream& _os) const {
		SlvParametrization2<int, double>::ostream(_os);
		_os << "fooB = " << fooB << std::endl;
		_os << "param_initB = " << param_initB << std::endl;
	}

};

class ClassA : public SlvParametrization2<ClassB, double> {

	glvm_parametrization2_init("ClassA")

	glvm_parameter(1, paramA, ClassB, "parameter_A", "Comment about parameter A")
	glvm_parameter(2, paramB, double, "parameter_B", "Comment about parameter B", 2.)


public:

	int fooA;
	double param_initA;

	ClassA() :glvm_parametrization_constructor(paramA, paramB) {

		fooA = 0;
		param_init();

	}

	/*! Reimplementation of SlvParametrization_base::param_init().*/
	void param_init() {
		param_initA = get_paramB() * 10;
	}

private:

	void ostream(std::ostream& _os) const {
		SlvParametrization2<ClassB, double>::ostream(_os);
		_os << "fooA = " << fooA << std::endl;
		_os << "param_initA = " << param_initA << std::endl;
	}

};

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvParametrizationDialog.h"
#include "GlvWidgetData_spec_AT.h"
#include "GlvWidgetData_spec_SlvParametrization.h"
#endif

/*! Parameter as a parametrization. Example to pass member values not belonging to SlvParametrization.
* Here are presented few special cases regarding parametrization assignments.
* --------------------------------------------------------------------------------
* In short, by default, a parametrization widget manages only the parameters (and its derived parameters through param_init()).
* It means that leaving _l_param_only as true (default) is strongly recommended.
* To assign the new parameters from parametrization widget, simply use param_cast() and SlvParametrization_base::param_init(), if needed.*/

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

	ClassA classA;
	classA.set_paramB(3.);
	classA.fooA = 17;
	ClassB classB;
	classB.fooB = 18;
	classA.set_paramA(classB);
	std::cout << "classA : " << classA << std::endl;//fooB is valued 0
	classA.set_paramA(classB, false);// Set parameter by assigning the whole instance
	std::cout << "classA : " << classA << std::endl;//fooB is valued 18

	GlvParametrizationDialog<ClassA>* parametrization_classA = new GlvParametrizationDialog<ClassA>(classA);
	//fooA and fooB are valued 0, because GlvParametrization only manages the parameters. Avoids copying data not related to parameterization in widgets.
	std::cout << "parametrization_classA->get_parametrization() : " << parametrization_classA->get_parametrization() << std::endl;

	int result = parametrization_classA->exec();
	if (result == QDialog::Accepted) {

		classA.param_cast() = parametrization_classA->get_parametrization();
		//fooA is valued 17 because param_cast() only assign parameters.
		//fooB is valued 18, because assignment of parameters types deriving from SlvParametrization are performed using param_cast() by default. Therefore fooB keeps its value.
		std::cout << "classA : " << classA << std::endl;
		// Caution: here param_initA is still valued 20, its original initialization, even if ClassA::paramB was modified in the dialog widget parametrization_classA.
		// In order to update the value, classA.param_init() must be called.
		// In general it is recommended to call param_init() after any param_cast() assignment.
		classA.param_init();
		std::cout << "classA : " << classA << std::endl;// this time param_initA is properly updated
		// It is to be noted here that the 'parameters only' behaviour presented in this very example is the default behaviour for any parameter being a SlvParametrization.
		// As a consequence, param_initB is always up to date regarding the parameters of ClassB.

		// For convenience param_cast() and param_init() are regrouped in the method param_assign()
		classA.param_assign(parametrization_classA->get_parametrization());
		std::cout << "classA : " << classA << std::endl;// this time param_initA is properly updated

		classA = parametrization_classA->get_parametrization();
		//fooA is valued 0 because this time param_cast() was not used. Default value of fooA contained in parametrization_classA->get_parametrization() is assigned this time.
		std::cout << "classA : " << classA << std::endl;
	}

    return app.exec();

}

