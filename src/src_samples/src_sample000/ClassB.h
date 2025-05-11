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

#include "ClassA.h"
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrization7.h"
#include "SlvProportion.h"
#include "filestream/SlvFile.h"
#include "SlvEnum.h"
#endif

glvm_SlvEnum(EnumName, A, B, C, D)

class ClassB : public SlvParametrization7<ClassA, float, bool, SlvProportion, SlvFile, EnumName, SlvDirectory> {

	glvm_parametrization7_init("ClassB")

	glvm_parameter(1, paramA, ClassA, "parameter_A", "Comment about parameter A")
	glvm_parameter_ruled(2, paramB, float, "parameter_B", "Comment about parameter B", 2.f)
	glvm_parameter_add_rule(min, 0)
	glvm_parameter_add_rule(max, 10.)
	glvm_parameter_add_rule(exception, 4)
	glvm_parameter_end
	glvm_parameter(3, paramC, bool, "parameter_C", "Comment about parameter C", false)
	glvm_parameter(4, paramD, SlvProportion, "parameter_D", "Comment about parameter D", 0.5)
	glvm_parameter(5, paramE, SlvFile, "parameter_E", "Comment about parameter E", SlvFile("", SlvFile::IO::Read))
	glvm_parameter(6, paramF, EnumName, "parameter_F", "Comment about parameter F", EnumName::A)
	glvm_parameter(7, paramG, SlvDirectory, "parameter_G", "Comment about parameter G")

public:

	ClassB() :glvm_parametrization_constructor(paramA, paramB, paramC, paramD, paramE, paramF, paramG) {}

	void method() {

		std::cout << "get_paramA() = " << get_paramA() << std::endl;
		std::cout << "get_paramB() = " << get_paramB() << std::endl;
		std::cout << "get_paramC() = " << get_paramC() << std::endl;

	}

};
