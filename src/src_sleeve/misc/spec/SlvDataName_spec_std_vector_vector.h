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
#include "std_vector.h"
#include <string>

/*! Get name of template type. Specialization. Name std::vector< std::vector<> >.*/
template <class T>
struct SlvDataName< std::vector< std::vector<T> > > {
    static std::string name() {
        std::string name = "matrix";
        name += "<";
        name += SlvDataName<T>::name();
        name += ">";
        return name;
    }
};
