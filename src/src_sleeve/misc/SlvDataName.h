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

#include "SlvMacrosDeclarations.h"
#include <string>
#include <typeinfo>

/*! Get name of template type by using typeid.*/
template <class T, typename = void>
struct SlvDataName {
    static std::string name() {
        return typeid(T).name();
    }
};

template <typename T>
class has_name_method {
    typedef char one;
    struct two { char x[2]; };
    template <typename T2> static one test(decltype(&T2::name));
    template <typename T2> static two test(...);
public:
    enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

/*! Get name of template type. Specializaition. If the template type has a static name() method, use it for name.*/
template <class T>
struct SlvDataName<T, typename std::enable_if<has_name_method<T>::value>::type> {
    static const std::string& name() {
        return T::name();
    }
};

/*! Get name of template type. Specialization. If the type is a container, add container name.*/
template < template <class T> class Tbox, class T>
struct SlvDataName< Tbox<T>, typename std::enable_if<has_name_method<Tbox<T> >::value>::type> {
    static std::string name() {
        std::string name = Tbox<T>::name();
        name += "<";
        name += SlvDataName<T>::name();
        name += ">";
        return name;
    }
};

#include "spec/SlvDataName_spec_AT.h"
// As standard, specialization for STL std::string and std::vector are included.
#include "spec/SlvDataName_spec_std_string.h"
#include "spec/SlvDataName_spec_std_vector.h"
