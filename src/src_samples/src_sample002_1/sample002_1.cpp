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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Widget specialization of a type 'Foo', in case the dedicated widget (FooWidget) does not contain the methods:
// Foo get_value() const;
// void set_value(const Foo _value);
// void set_editable(bool _l_editable);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Two options for the example:
// OPTIONS_USE_RULES
// If not defined : simple glvm_parametrization can apply, but rules can not be defined in the macro.
// If defined : Class is explicitly implemented to be able to use addRule macro.
// OPTION_FOO_AS_ARITHMETIC
// If defined : Foo is considered as an arithmetic type (operators > and < are implemented).
// Default SlvParameterRuleT can apply.
// If not defined : SlvParameterRuleT must be specialized for Foo.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// If Foo is defined as arithmetic, SlvParameterRuleT for arithmetic types is used. See SlvParameterRuleT_spec_Arithmetic.h
// If not, parameter rules must be defined in SlvParameterRuleT_spec_Foo.h
#define OPTION_FOO_AS_ARITHMETIC
#define OPTION_USE_RULES //Rule example for Parametrization declaration 

#include <QApplication>

#include "Foo.h"//Example data type
#include "FooWidget.h"// Example widget, supposed not to be modifiable and out of the Glove context, such as a third party widget
#include "GlvWidgetData_spec_Foo.h"//specialization class Foo

#ifndef OPTION_FOO_AS_ARITHMETIC
#include "SlvParameterRuleT_spec_Foo.h"
#endif

#ifndef OPTION_USE_RULES
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrizationMacro.h"
#endif
glvm_parametrization(Parameterization, "Parameterization", paramA, Foo, "paramA", "comment parameterA")
#else
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrization1.h"
#endif
class Parameterization : public SlvParametrization1<Foo> {
    glvm_parametrization1_init("Parameterization")
    glvm_parameter_ruled(1, paramA, Foo, "paramA", "comment parameterA")
    glvm_parameter_add_rule(exception, 20)
#ifdef OPTION_FOO_AS_ARITHMETIC
    glvm_parameter_add_rule(max, 30)
#else
    glvm_parameter_add_rule(foo_special_rule, 0)//0 is ignored here
#endif
    glvm_parameter_end
public:
    Parameterization() :glvm_parametrization_constructor(paramA) {}
};
#endif

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvParametrizationDialog.h"
#endif

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    GlvParametrizationDialog<Parameterization>* parametrization_dialog = new GlvParametrizationDialog<Parameterization>();
    parametrization_dialog->show();

    return app.exec();

}

