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

/*! Macro for type detection, for instance when using std::enable_if.
* struct_name is the name of the structure to be used such as: std::enable_if<struct_name<T>::value>
* Ttest_subtype is the type struct_name is supposed to contain such as: struct_name::Ttest_subtype */
#define glvm_SlvIsType(struct_name, Ttest_subtype) \
template <class Ttested_type>\
struct struct_name  {\
    template <class T>\
    static char test(typename T::Ttest_subtype*);\
    template <class T>\
    static long test(T*);\
    static const bool value = sizeof(test<Ttested_type>(0)) == 1;\
};

