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

#include "misc/SlvDataName.h"
#include "std_map.h"
#include <string>

/*! Get name of template type. Specialization. Name std::map.*/
template <class Tkey, class Tvalue>
struct SlvDataName< std::map<Tkey, Tvalue> > {
    static std::string name() {
        std::string name = "std::map";
        name += "<";
        name += SlvDataName<Tkey>::name();
        name += ", ";
        name += SlvDataName<Tvalue>::name();
        name += ">";
        return name;
    }
};
