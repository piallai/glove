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

namespace slv {
    bool parse(const std::string& _string, float& _value);
    bool parse(const std::string& _string, double& _value);
    bool parse(const std::string& _string, long double& _value);
    namespace {//private
        template <class T>
        bool parseFP(const std::string& _string, T& _value) {
            if (_string == "inf") {
                _value = INFINITY;
            } else if (_string == "-inf") {
                _value = -INFINITY;
            } else {
                std::istringstream iss(_string);
                iss >> _value;
            }
            return true;
        }
    }
}

inline bool slv::parse(const std::string& _string, float& _value) {
    return parseFP(_string, _value);
}

inline bool slv::parse(const std::string& _string, double& _value) {
    return parseFP(_string, _value);
}

inline bool slv::parse(const std::string& _string, long double& _value) {
    return parseFP(_string, _value);
}

