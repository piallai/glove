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

#include "Foo.h"
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include <QWidget>
#include <QVBoxLayout>
#include <QSpinBox>
#else
#include "glove.h"
#endif

// Example widget, supposed not to be modifiable and out of the Glove context, such as a third party widget
class FooWidget : public QWidget {
	Q_OBJECT
signals:
	void foo_changed(int _value);
private:
	QSpinBox* spinbox;
public:
	FooWidget(const Foo& _foo, QWidget* _parent = 0) :QWidget(_parent) {
		QVBoxLayout* layout = new QVBoxLayout;
		setLayout(layout);
		spinbox = new QSpinBox;
		spinbox->setMaximum(std::numeric_limits<int>::max());
		spinbox->setMinimum(std::numeric_limits<int>::lowest());
		layout->addWidget(spinbox);
		set_foo(_foo);
		connect(spinbox, SIGNAL(valueChanged(int)), this, SIGNAL(foo_changed(int)));
	}

	Foo get_foo() const {
		Foo foo;
		foo.a = spinbox->value();
		return foo;
	}

	void set_foo(const Foo& _foo) {
		spinbox->setValue(_foo.a);
	}

	void allow_edition(bool _l_allow) {
		spinbox->setEnabled(_l_allow);
	}

#ifdef OPTION_FOO_AS_ARITHMETIC
	void setMinimum(const Foo& _foo) {
		spinbox->setMinimum(_foo.a);
	}
	void setMaximum(const Foo& _foo) {
		spinbox->setMaximum(_foo.a);
	}
#endif

};

