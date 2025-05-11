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

#include "iostream/spec/iostream_spec_std_array_decl.h"

template <class T, size_t N>
std::ostream& operator<<(std::ostream& _os, const std::array<T, N>& _array) {
    _os << "[";
    for (typename std::array<T, N>::const_iterator it = _array.begin(); it != _array.end(); ++it) {
        _os << *it;
        if (std::next(it) != _array.end()) {
            _os << ", ";
        }
    }
    _os << "]";
    return _os;
}

template <class T, size_t N>
std::istream& operator>>(std::istream& _is, std::array<T, N>& _array) {
    int i = 0;
    for (typename std::array<T, N>::iterator it = _array.begin(); it != _array.end(); ++it, i++) {
        std::cout << "enter element: " << i << std::endl;
        _is >> *it;
    }
    return _is;
}
