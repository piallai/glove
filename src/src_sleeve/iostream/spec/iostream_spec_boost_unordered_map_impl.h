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

#include "iostream/spec/iostream_spec_boost_unordered_map_decl.h"

#if !defined(GLOVE_PV_SINGLE_HEADER) || OPTION_USE_BOOST==1

template <class Tkey, class T>
std::ostream& operator<<(std::ostream& _os, const boost::unordered::unordered_map<Tkey, T>& _map) {
    _os << "[";
    for (typename boost::unordered::unordered_map<Tkey, T>::const_iterator it = _map.begin(); it != _map.end(); it++) {
        _os << " ";
        _os << "(" << it->first << "," << it->second << ")";
    }
    _os << "]";
    return _os;
}

template <class Tkey, class T>
std::istream& operator>>(std::istream& _is, const boost::unordered::unordered_map<Tkey, T>& _map) {

    slv::flag::WIP();
    return _is;
}

#endif
