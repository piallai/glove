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

/*! Contains functions for the slv framework. No Qt/Glv here.*/
namespace slv {
    /*! Misc convenient functions.*/
    namespace misc {
        /*! Get number of decimals of \p _value.
        * \p _l_floating_point_arithmetic_error : whether to assume rounding in the order of floating point arithmetic error.*/
        template <class T>
        unsigned int get_Ndecimals(const T& _value, bool _l_round_floating_point_arithmetic_error = true);
    }
}

template <class T>
unsigned int slv::misc::get_Ndecimals(const T& _value, bool _l_round_floating_point_arithmetic_error) {

    unsigned int count = 0;
    T value = std::abs(_value);
    value = value - int(value);
    // Floating point arithmetic error
    T fpae = T(100) * std::numeric_limits<T>::epsilon();
    T tolerance = fpae;
    T error(0);// initalization value is not used
    if (_l_round_floating_point_arithmetic_error) error = std::abs(T(1) - value);
    while (value > tolerance && (!_l_round_floating_point_arithmetic_error || error > fpae)) {
        value *= T(10);
        ++count;
        value = value - int(value);
        if (_l_round_floating_point_arithmetic_error) error = std::abs(T(1) - value);
    }

    return count;
}