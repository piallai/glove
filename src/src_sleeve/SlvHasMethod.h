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

/*! Macro for method detection in a struct/class/type, for instance when using std::enable_if.
* struct_name is the name of the structure to be used such as: std::enable_if<struct_name<T>::value>
* method_name is the method struct_name is supposed to contain such as: struct_name::method_name.
* method_name must be a public method.*/
#define glvm_SlvHasMethod(struct_name, method_name) \
template <typename T>\
class struct_name {\
    typedef char one;\
    struct two { char x[2]; };\
    template <typename C> static one test(decltype(&C::method_name));\
    template <typename C> static two test(...);\
public:\
    enum { value = sizeof(test<T>(0)) == sizeof(char) };\
};

/*! Same as glvm_SlvHasMethod but can manage overloaded methods.*/
#define glvm_SlvHasMethodSignature(struct_name, method_type, method_name, method_argument) \
template <typename T>\
class struct_name {\
    typedef char one;\
    struct two { char x[2]; };\
    template <typename C> static one test(decltype(method_type (std::declval<C &>().method_name(method_argument)))*);\
    template <typename C> static two test(...);\
public:\
    enum { value = sizeof(test<T>(0)) == sizeof(char) };\
};
