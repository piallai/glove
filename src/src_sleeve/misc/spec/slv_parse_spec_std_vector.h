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
    /*! Parse \p _string to assign \p _vector. Reciprocal to << operator.*/
    template <class T>
    bool parse(const std::string& _string, std::vector<T>& _vector);
}

#include "slv_string.h"
#include "SlvDataName_spec_std_vector.h"

template <class T>
bool slv::parse(const std::string& _string, std::vector<T>& _vector) {
    
    bool l_parsing_ok = true;

    _vector.clear();


    T value;
    if (_string.front() == '[' && _string.back() == ']') {

        std::string string = _string;
        std::string sub_string;
        std::size_t pos;

        string.erase(string.begin());
        string.pop_back();

        do {
            pos = slv::string::find_first_of(string, ',');

            if (pos != 0) {
                sub_string = string.substr(0, pos);

                l_parsing_ok = slv::parse(sub_string, value);
                if (l_parsing_ok) {
                    _vector.push_back(value);

                    if (pos != std::string::npos) {
                        string.erase(0, pos + 1);
                    } else {
                        string.clear();
                    }
                }

            }

        } while (!string.empty() && l_parsing_ok);

        if (!l_parsing_ok) {
            std::cout << "Parsing issue for type " << SlvDataName<std::vector<T>>::name() << " and for string " << _string << std::endl;
            _vector.clear();
        }

    } else {
        // Parse a single value
        l_parsing_ok = slv::parse(_string, value);
        if (l_parsing_ok) {
            _vector.push_back(value);
        }
    }

    return l_parsing_ok;
}
