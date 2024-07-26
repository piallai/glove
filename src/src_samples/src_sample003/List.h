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
#include "param/SlvParametrizationMacro.h"
#else
#include "glove.h"
#endif
// Detailed declaration
class ListElementA : public SlvParametrization1<double> {
	glvm_parametrization1_init("ListElementA")
	glvm_parameter_ruled(1, paramA, double, "paramA", "comment parameterA")
	glvm_parameter_add_rule(exception, 20)
	glvm_parameter_add_rule(max, 30)
	glvm_parameter_end
public:
	ListElementA() :glvm_parametrization_constructor(paramA) {}
};
// Easy declaration
glvm_parametrization(ListElementB, "ListElementB", paramA, bool, "paramA", "comment parameterA", true)
// Easy declaration
glvm_parametrization(ListElementC, "ListElementC", paramA, std::string, "paramA", "comment parameterA", "default")

// Define the macro associating each parametrization name to its corresponding type
#define glvm_List_instruction_name_to_type(instruction_front, parametrization_name, instruction_end)\
if (parametrization_name==ListElementA::name()) {instruction_front ListElementA instruction_end}\
else if (parametrization_name==ListElementB::name()) {instruction_front ListElementB instruction_end}\
else if (parametrization_name==ListElementC::name()) {instruction_front ListElementC instruction_end}\
else { slv::flag::ISSUE(slv::flag::Critical, "No such parametrization name = ", parametrization_name); }

#include <vector>
#include <string>

/* Declare the list of the parametrizations
* Requirements:
* - static std::vector<std::string> list() method
* - static std::string name() method.
* - static bool is_templated(onst std::string _name) method
* Simply build a std::vector storing the names of the listed parametrizations.*/
class List {

public:

	glvm_staticVariable(const, std::string, name, "List");
	glvm_staticVariable(const, std::vector<std::string>, list,
		{ ListElementA::name() COMMA
		ListElementB::name() COMMA
		ListElementC::name() }
	);
	// Whether a parametrization (by name) is a template or not.
	static bool is_templated(const std::string _name) {
		// No parametrization is templated here
		return false;
	}

};