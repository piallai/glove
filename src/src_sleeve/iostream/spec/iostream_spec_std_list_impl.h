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

#include "iostream/spec/iostream_spec_std_list_decl.h"

template <class T>
std::ostream& operator<<(std::ostream& _os, const std::list<T>& _list) {
    _os << "[";
    for (typename std::list<T>::const_iterator it = _list.begin(); it != _list.end(); ++it) {
        _os << " " << *it;
    }
    _os << "]";
    return _os;
}

template <class T>
std::istream& operator>>(std::istream& _is, std::list<T>& _list) {
    _list.clear();
    std::cout << "enter list size:" << std::endl;
    unsigned int list_size;
    _is >> list_size;
    T value;
    for (unsigned int i = 0; i < list_size; i++) {
        std::cout << "enter element: " << i << std::endl;
        _is >> value;
        _list.push_back(value);
    }
    return _is;
}
