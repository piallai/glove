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

#include "iostream/spec/iostream_spec_std_vector_decl.h"

template <class T>
std::ostream& operator<<(std::ostream& _os, const std::vector<T>& _vector) {
    _os << "[";
    for (typename std::vector<T>::const_iterator it = _vector.begin(); it != _vector.end(); ++it) {
        _os << *it;
        if (std::next(it) != _vector.end()) {
            _os << ",";
        }
    }
    _os << "]";
    return _os;
}

template <class T>
std::istream& operator>>(std::istream& _is, std::vector<T>& _vector) {
    _vector.clear();
    std::cout << "enter vector size:" << std::endl;
    unsigned int vector_size;
    _is >> vector_size;
    T value;
    for (unsigned int i = 0; i < vector_size; i++) {
        std::cout << "enter element: " << i << std::endl;
        _is >> value;
        _vector.push_back(value);
    }
    return _is;
}
