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

#include "misc/SlvDataName.h"
#include <string>

// Arithmetic Types explicit specializations

/*! Get name of template type. Specialization. Name int.*/
template <>
struct SlvDataName<int> {
    glvm_staticVariable(const, std::string, name, "int");
};

/*! Get name of template type. Specialization. Name unsigned int.*/
template <>
struct SlvDataName<unsigned int> {
    glvm_staticVariable(const, std::string, name, "uint");
};

/*! Get name of template type. Specialization. Name float.*/
template <>
struct SlvDataName<float> {
    glvm_staticVariable(const, std::string, name, "float");
};

/*! Get name of template type. Specialization. Name double.*/
template <>
struct SlvDataName<double> {
    glvm_staticVariable(const, std::string, name, "double");
};

/*! Get name of template type. Specialization. Name bool.*/
template <>
struct SlvDataName<bool> {
    glvm_staticVariable(const, std::string, name, "bool");
};
