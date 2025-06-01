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

#include "misc/slv_parse.h"
#include "std_vector.h"

namespace slv {
    /*! Parse \p _string to assign \p _array. Reciprocal to << operator.*/
    template <class T, size_t N>
    bool parse(const std::string& _string, std::array<T, N>& _array);
}

#include "misc/spec/slv_parse_spec_std_vector.h"

template <class T, size_t N>
bool slv::parse(const std::string& _string, std::array<T, N>& _array) {
    
    bool l_parsing_ok = true;

    std::vector<T> vector;
    l_parsing_ok = slv::parse(_string, vector);

    if (l_parsing_ok && vector.size() == N) {
        std::copy_n(vector.begin(), N, _array.begin());
    } else {
        std::cout << "Parsing issue for type " << SlvDataName<std::array<T, N>>::name() << " and for string " << _string << std::endl;
    }

    return l_parsing_ok;
}
