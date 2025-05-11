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

template <class T, class Toption>
class ListElementA;// Forward declaration for Tderived

// Detailed declaration
class ListElementA_base : virtual public SlvVirtualGetName {// Catch pure virtual get_name here instead of the one of: SlvParametrization_base : virtual public SlvVirtualGetName
	glvm_parametrization_name("ListElementA")
public:
	ListElementA_base() {}
	template <class T, class Toption>
	using Tderived = ListElementA<T, Toption>;
};
template <class T, class Toption>
class ListElementA : public SlvParametrization1<T>, public ListElementA_base {
	glvm_parametrization1_static_init
	glvm_parameter(1, paramA, T, "paramA", "comment parameterA")
	Toption* foo;
public:
	ListElementA() :glvm_parametrization_constructor(paramA) {}
};
// Easy declaration
glvm_parametrization(ListElementB, "ListElementB", paramA, bool, "paramA", "comment parameterA", true)
// Easy declaration
glvm_parametrization(ListElementC, "ListElementC", paramA, std::string, "paramA", "comment parameterA", "default")

#define glvm_List_instruction_name_to_type(instruction_front, parametrization_name, instruction_end)\
if (parametrization_name==ListElementA_base::name()) {instruction_front ListElementA_base instruction_end}\
else if (parametrization_name==ListElementB::name()) {instruction_front ListElementB instruction_end}\
else if (parametrization_name==ListElementC::name()) {instruction_front ListElementC instruction_end}\
else { slv::flag::ISSUE(slv::flag::Critical, "No such parametrization name = ", parametrization_name); }

// As compared to glvm_List_instruction_name_to_type, limits the number of compiled objects
#define glvm_List_instruction_name_to_type_templated_only(instruction_front, parametrization_name, instruction_end)\
if (parametrization_name==ListElementA_base::name()) {instruction_front ListElementA_base instruction_end}\
else { slv::flag::ISSUE(slv::flag::Critical, "No such parametrization name = ", parametrization_name); }

#define glvm_List_instruction_name_to_type_not_templated_only(instruction_front, parametrization_name, instruction_end)\
if (parametrization_name==ListElementB::name()) {instruction_front ListElementB instruction_end}\
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
		{ ListElementA_base::name() COMMA
		ListElementB::name() COMMA
		ListElementC::name() }
	);
	/*! Required for secondary template list.
	* Description of what represents an element of List2 in a general way.
	* For instance, if List2 was instead named "Boots", item description could be "boot".*/
	glvm_staticVariable(const, std::string, item_description, "list element");

	static bool is_templated(const std::string _name) {
		if (_name == ListElementA_base::name()) {
			return true;
		} else {
			return false;
		}
	}

};