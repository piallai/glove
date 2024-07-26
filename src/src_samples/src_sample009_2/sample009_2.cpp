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

/* Example of how to implement json reading and writing for a class for compliance with GlvParametrizationSaveLoad.*/

#include <QApplication>

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GloveOptions.h"
#if OPTION_USE_THIRDPARTY_JSON==1
#include "json.hpp"
#endif
#include "SlvStatus.h"
#else
#define GLOVE_ENABLE_JSON
#include "glove.h"
#endif

// Example class for json implementation
class ClassTest {

	int value;

public:
	ClassTest(int _value = 2) { value = _value; }
	~ClassTest() {}

	int get_value() const {
		return value;
	}

	void set_value(const int _value) {
		value = _value;
	}

	bool operator==(const ClassTest& _test) const {
		return value == _test.value;
	}

	bool readB(std::ifstream& _input_file) {
		return slv::rw::readB(value, _input_file);
	}

	void writeB(std::ofstream& _output_file) const {
		slv::rw::writeB(value, _output_file);
	}

	friend std::ostream& operator<<(std::ostream& _os, const ClassTest& _test) {
		_os << _test.value;
		return _os;
	}
	friend std::istream& operator>>(std::istream& _is, ClassTest& _test) {
		_is >> _test.value;
		return _is;
	}
#if OPTION_USE_THIRDPARTY_JSON==1
	void writeJson(nlohmann::json& _json) const {
		_json = value;
	}
	SlvStatus readJson(const nlohmann::json& _json) {
		value = _json.get<int>();
		return SlvStatus();
	}
#endif
};

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "filestream/slv_rw_json.h"
#endif
#if OPTION_USE_THIRDPARTY_JSON==1
template <>
void slv::rw::json::writeJson_spec<ClassTest>(const ClassTest& _test, nlohmann::json& _json) {
	_json = _test.get_value();
}

template <>
SlvStatus slv::rw::json::readJson_spec<ClassTest>(ClassTest& _test, const nlohmann::json& _json) {
	_test.set_value(_json.get<int>());
	return SlvStatus();
}
#endif

///////////////////////////////////////////////////////////////////////////
///// Basic GlvWidgetData management for ClassTest ////////////////////////
///// Not in the scope of the example but necessary ///////////////////////
///////////////////////////////////////////////////////////////////////////
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvWidgetData.h"
#include <QSpinBox>
#endif
template <>
class GlvWidgetData<ClassTest> : public QSpinBox {
public:
	GlvWidgetData(QWidget* _parent = 0) {}
	GlvWidgetData(const ClassTest& _value, QWidget* _parent = 0) { set_value(_value); }
	~GlvWidgetData() {}
	void set_editable(bool l_editable) {}
	ClassTest get_value() const { return ClassTest(QSpinBox::value()); }
	void set_value(const ClassTest& _value) { QSpinBox::setValue(_value.get_value()); }
};
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvWidgetMakerConnect.h"
#endif
template <>
struct GlvWidgetMakerConnect<ClassTest> {
	static void connect(GlvWidgetData<ClassTest>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
		QObject::connect(_widget, SIGNAL(valueChanged(int)), _widget_connector, SLOT(valueChanged_slot(int)));
	}
};
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrizationMacro.h"
#endif
glvm_parametrization(ClassA, "ClassA", paramA, int, "paramA", "comment about parameterA", 0,
                                        paramB, float, "paramB", "comment about parameter B", 0.f,
                                        paramC, bool, "paramC", "comment about parameter C", true,
										paramD, std::vector<double>, "paramD", "comment about parameter D", {},
                                        paramE, std::string, "paramE", "comment about parameter E", "default",
                                        paramF, ClassTest, "paramF", "comment about parameter F", ClassTest())

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvWidgetData_spec_AT.h"
#include "GlvWidgetData_spec_std_string.h"
#include "GlvWidgetData_spec_std_vector.h"
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

