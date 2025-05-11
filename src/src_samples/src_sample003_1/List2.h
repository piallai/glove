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

#pragma once

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrizationMacro.h"
#else
#include "glove.h"
#endif

glvm_parametrization(ListElementD, "ListElementD", paramA, bool, "paramA", "comment parameterA", true)
glvm_parametrization(ListElementE, "ListElementE", paramA, std::string, "paramA", "comment parameterA", "default")

#define glvm_List2_instruction_name_to_type(instruction_front, parametrization_name, instruction_end)\
if (parametrization_name==ListElementD::name()) {instruction_front ListElementD instruction_end}\
else if (parametrization_name==ListElementE::name()) {instruction_front ListElementE instruction_end}\
else { slv::flag::ISSUE(slv::flag::Critical, "No such parametrization name = ", parametrization_name); }

#include <vector>
#include <string>

/* Declare the list of the parametrizations
* Requirements:
* - static std::vector<std::string> list() method
* - static std::string name() method.
* - static bool is_templated(onst std::string _name) method
* Simply build a std::vector storing the names of the listed parametrizations.*/
class List2 {

public:

	glvm_staticVariable(const, std::string, name, "List2");
	glvm_staticVariable(const, std::vector<std::string>, list,
		{ ListElementD::name() COMMA
		ListElementE::name() }
	);
	/*! Required for secondary template list.
	* Description of what represents an element of List2 in a general way.
	* For instance, if List2 was instead named "Boots", item description could be "boot".*/
	glvm_staticVariable(const, std::string, item_description, "list2 element");

	static bool is_templated(const std::string _name) {
		return false;
	}

};
