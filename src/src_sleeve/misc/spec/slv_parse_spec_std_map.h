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
#include "std_map.h"

namespace slv {
	/*! Parse \p _string to assign \p _map. Reciprocal to << operator.*/
	template <class Tkey, class Tvalue>
	bool parse(const std::string& _string, std::map<Tkey, Tvalue>& _map);

    namespace {
        template <class Tkey, class Tvalue>
        bool parse(const std::string& _string, Tkey& _key, Tvalue& _value);
    }
}

#include "slv_string.h"
#include "SlvDataName_spec_std_map.h"

namespace slv {
    namespace {
        template <class Tkey, class Tvalue>
        bool parse(const std::string& _string, Tkey& _key, Tvalue& _value) {

            bool l_parsing_ok = true;

            if (_string[0] == '{' && _string.back() == '}') {
                std::string string = _string;
                string.erase(string.begin());
                string.pop_back();

                std::size_t pos = slv::string::find_first_of(string, ',');
                if (pos != std::string::npos) {
                    std::string string_key = string.substr(0, pos);
                    string.erase(0, pos + 1);
                    std::string string_value = string;

                    slv::parse(string_key, _key);
                    slv::parse(string_value, _value);

                } else {
                    // Issue : map element must contain a comma
                    l_parsing_ok = false;
                }

            } else {
                l_parsing_ok = false;
            }

            return l_parsing_ok;

        }
    }
}

template <class Tkey, class Tvalue>
bool slv::parse(const std::string& _string, std::map<Tkey, Tvalue>& _map) {

    bool l_parsing_ok = true;

    _map.clear();

    Tkey key;
    Tvalue value;
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

                l_parsing_ok = parse(sub_string, key, value);
                if (l_parsing_ok) {
                    _map[key] = value;

                    if (pos != std::string::npos) {
                        string.erase(0, pos + 1);
                    } else {
                        string.clear();
                    }
                }

            }

        } while (!string.empty() && l_parsing_ok);

        if (!l_parsing_ok) {
            std::cout << "Parsing issue for type " << SlvDataName<std::map<Tkey, Tvalue>>::name() << " and for string " << _string << std::endl;
            _map.clear();
        }

    } else {
        // Parse a single value
        l_parsing_ok = parse(_string, key, value);
        if (l_parsing_ok) {
            _map[key] = value;
        }
    }

    return l_parsing_ok;
}
