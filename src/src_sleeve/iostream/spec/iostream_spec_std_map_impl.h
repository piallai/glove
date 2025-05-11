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

#include "iostream/spec/iostream_spec_std_map_decl.h"

template <class Tkey, class T>
std::ostream& operator<<(std::ostream& _os, const std::map<Tkey, T>& _map) {
    _os << "[";
    for (typename std::map<Tkey, T>::const_iterator it = _map.begin(); it != _map.end(); it++) {
        _os << "{" << it->first << "," << it->second << "}";
        if (std::next(it) != _map.end()) {
            _os << ",";
        }
    }
    _os << "]";
    return _os;
}

template <class Tkey, class T>
std::istream& operator>>(std::istream& _is, std::map<Tkey, T>& _map) {

    _map.clear();

    Tkey key;
    T value;

    char ans('Y');
    while (ans == 'Y') {
        std::cout << "Add map value ? (Y/N)" << std::endl;

        std::cin >> ans;
        if (ans == 'Y') {


            bool l_enter_key = true;
            while (l_enter_key) {
                std::cout << "Enter map key:" << std::endl;
                _is >> key;
                typename std::map<Tkey, T>::iterator it = _map.find(key);
                if (it != _map.end()) {
                    std::cout << "The key already exists, value : " << it->second << std::endl;
                    std::cout << "Do you want to overwrite it ? (Y/N)" << std::endl;
                    char ans2 = 0;
                    while (ans2 != 'Y' && ans2 != 'N') {
                        std::cin >> ans2;
                        if (ans2 == 'Y') {
                            l_enter_key = false;
                        }
                    }
                } else {
                    l_enter_key = false;
                }
            }

            std::cout << "Enter map value:" << std::endl;
            _is >> value;
            _map[key] = value;

        }
    }


    return _is;

}
