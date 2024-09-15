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

#include "iostream/spec/iostream_spec_std_pair_decl.h"

template <class T1, class T2>
std::ostream& operator<<(std::ostream& _os, const std::pair<T1, T2>& _pair) {
    _os << "[" << _pair.first << " ; " << _pair.second << "]";
    return _os;
}

template <class T1, class T2>
std::istream& operator>>(std::istream& _is, std::pair<T1, T2>& _pair) {
    _is >> _pair.first;
    _is >> _pair.second;
    return _is;
}