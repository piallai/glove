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

/* Example to specialize GlvWidgetData from a class.*/

#include <QApplication>
#include <iostream>

/*! Here Foo encapsulate a simple int.*/
class Foo {

	int value;

public:
	Foo(int _value = 7) { value = _value; }
	~Foo() {}

	int get_value() const {
		return value;
	}

	void set_value(const int _value) {
		value = _value;
	}

	bool operator==(const Foo& _foo) const {
		return value == _foo.value;
	}

	friend std::ostream& operator<<(std::ostream& _os, const Foo& _foo) {
		_os << _foo.value;
		return _os;
	}

	friend std::istream& operator>>(std::istream& _is, Foo& _foo) {
		_is >> _foo.value;
		return _is;
	}

};

/*! The widget associated to Foo can here be a simple QSpinBox. But one can design a more specific widget.*/

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvWidgetData.h"
#include <QSpinBox>
#else
#include "glove.h"
#endif

template <>
class GlvWidgetData<Foo> : public QSpinBox {
public:
	GlvWidgetData(QWidget* _parent = 0) {}
	GlvWidgetData(const Foo& _value, QWidget* _parent = 0) {
		set_value(_value);
	}
	~GlvWidgetData() {}
	/*! Implement editability of associated widget.*/
	void set_editable(bool _l_editable) {
		QSpinBox::setReadOnly(!_l_editable);
	}
	/*! Implement Foo from associated widget.*/
	Foo get_value() const {
		return Foo(QSpinBox::value());
	}
	/*! Implement Foo to associated widget.*/
	void set_value(const Foo& _value) {
		QSpinBox::setValue(_value.get_value());
	}
};
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvWidgetMakerConnect.h"
#endif
template <>
struct GlvWidgetMakerConnect<Foo> {
	static void connect(GlvWidgetData<Foo>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
		/*! Apply connections of the associated widget (first two arguments of QObject::connect). Necessary for GlvParametrizationWidget.*/
		QObject::connect(_widget, SIGNAL(valueChanged(int)), _widget_connector, SLOT(valueChanged_slot(int)));
	}
};

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrizationMacro.h"
#endif
glvm_parametrization(ClassA, "ClassA", paramA, Foo, "paramA", "comment about parameterA", Foo())

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvParametrizationWidget.h"
#endif

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

	// Use a simple type widget
	GlvWidget<Foo>* widget = new GlvWidget<Foo>;
	widget->show();

	// Use a parametrization widget
	GlvParametrizationWidget<ClassA>* parametrization_widget = new GlvParametrizationWidget<ClassA>;
	parametrization_widget->show();

    return app.exec();

}

