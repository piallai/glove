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

#include "slv_string.h"
#include "slv_flag.h"
#include <cmath>//log10

const std::string& slv::string::str_void() {
    static std::string* str_void = new std::string("");
    return *str_void;
}

std::string slv::string::number_to_string(int _n, int _Ndigits) {

    //auto Ndigits
    if (_Ndigits == 0) {
        if (_n != 0) {
            _Ndigits = int(std::log10(_n)) + 1;
        } else {
            _Ndigits = 1;
        }
    }

    int zero = 0;

    std::ostringstream out_n;

    int digit = 0;
    bool l_match = false;
    while (digit < _Ndigits && !l_match) {
        if (_n < std::pow(10., digit + 1)) {
            for (int digit2 = digit; digit2 < _Ndigits - 1; digit2++) {
                out_n << zero;
            }
            l_match = true;
        }
        digit++;
    }

    if (_n >= std::pow(10, _Ndigits)) {
        slv::flag::ISSUE(slv::flag::Warning, "in std::string number_to_string(int n, int Ndigits), int n = ", _n, " can't be expressed on ", _Ndigits, " digits");
    }

    out_n << _n;

    return out_n.str();
}

std::string slv::string::number_to_string_auto(int n) {

    if (n != 0) {
        return number_to_string(n, int(std::log10(n)) + 1);
    } else {
        return "0";
    }

}

std::string slv::string::value_to_string(const double& _value) {

    std::ostringstream strs;
    strs << _value;

    return strs.str();
}

void slv::string::remove_substring(const std::string& _substring, std::string& _string) {

    std::size_t found_pos = _string.find(_substring);

    if (found_pos != std::string::npos) {
        _string.erase(found_pos, _substring.size());
    }

}
