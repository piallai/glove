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

#pragma once

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrization6.h"
#endif

class ClassTest {
public:
	ClassTest() {}
	~ClassTest() {}

	bool operator==(const ClassTest& _test) const {
		return true;
	}

	bool readB(std::ifstream& _input_file) {
		return true;
	}

	void writeB(std::ofstream& _output_file) const {

	}

	friend std::ostream& operator<<(std::ostream& _os, const ClassTest& _OS) {
		return _os;
	}
	friend std::istream& operator>>(std::istream& _is, ClassTest& _IS) {
		return _is;
	}
};

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include <QSpinBox>
#endif
template <>
class GlvWidgetData<ClassTest> : public QSpinBox {
public:
	GlvWidgetData(QWidget* _parent = 0) {}
	GlvWidgetData(const ClassTest& _value, QWidget* _parent = 0) {}
	~GlvWidgetData() {}
	void set_editable(bool l_editable) {}
	ClassTest get_value() const { return ClassTest(); }
	void set_value(const ClassTest& _value) {}
};
template <>
struct GlvWidgetMakerConnect<ClassTest> {
	static void connect(GlvWidgetData<ClassTest>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
		QObject::connect(_widget, SIGNAL(valueChanged(int)), _widget_connector, SLOT(valueChanged_slot(int)));
	}
};

class ClassA : public SlvParametrization6<unsigned int, bool, double, std::string, std::vector<int>, ClassTest> {

	glvm_parametrization6_init("ClassA")

	glvm_parameter_ruled(1, paramA, unsigned int, "parameter_A", "Comment about parameter A", 1)
	glvm_parameter_add_rule(exception, 0)
	glvm_parameter_end
	glvm_parameter(2, paramB, bool, "parameter_B", "Comment about parameter B", true)
	glvm_parameter(3, paramC, double, "parameter_C", "Comment about parameter C", 10.)
	glvm_parameter(4, paramD, std::string, "parameter_D", "Comment about parameter D", "foo")
	glvm_parameter(5, paramE, std::vector<int>, "parameter_E", "Comment about parameter E")
	glvm_parameter(6, paramF, ClassTest, "parameter_F", "Comment about parameter F")

public:

	ClassA() :glvm_parametrization_constructor(paramA, paramB, paramC, paramD, paramE, paramF) {}

};


class ClassZ : public SlvParametrization0 {

	glvm_parametrization0_init("ClassZ")

public:

	ClassZ() :
		SlvParametrization0() {

	}

};
