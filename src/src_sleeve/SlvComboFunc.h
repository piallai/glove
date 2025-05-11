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

#include "SlvCombo.h"

/*! Static methods for SlvCombo.*/
struct SlvComboFunc {

    /*! Get value of the first SlvCombo in \p _combos which data equals \p _data.
    * Return NULL if not found.*/
    template <class Tdata, class Tvalue>
    static const Tvalue* get_combo_value(const Tdata& _data, const std::vector< SlvCombo<Tdata, Tvalue> >& _combos);

    /*! Get index of \p _combos of the first SlvCombo in \p _combos which data equals \p _data.
    * Return -1 if not found.*/
    template <class Tdata, class Tvalue>
    static unsigned int get_combo_index(const Tdata& _data, const std::vector< SlvCombo<Tdata, Tvalue> >& _combos);

    /*! Get iterator of \p _combos of the first SlvCombo in \p _combos which data equals \p _data.
    * Return _combos.end() if not found.*/
    template <class Tdata, class Tvalue>
    static typename std::vector< SlvCombo<Tdata, Tvalue> >::const_iterator find_data(const Tdata& _data, const std::vector< SlvCombo<Tdata, Tvalue> >& _combos);

    /*! Get value sum of \p _combos.*/
    template <class Tdata, class Tvalue>
    static Tvalue calc_value_sum(const std::vector< SlvCombo<Tdata, Tvalue> >& _combos);

};

template <class Tdata, class Tvalue>
const Tvalue* SlvComboFunc::get_combo_value(const Tdata& _data, const std::vector< SlvCombo<Tdata, Tvalue> >& _combos) {

    typename std::vector< SlvCombo<Tdata, Tvalue> >::const_iterator it = find_data(_data, _combos);
    if (it != _combos.end()) {
        return &it->value;
    } else {
        return NULL;
    }

}

template <class Tdata, class Tvalue>
unsigned int SlvComboFunc::get_combo_index(const Tdata& _data, const std::vector< SlvCombo<Tdata, Tvalue> >& _combos) {

    typename std::vector< SlvCombo<Tdata, Tvalue> >::const_iterator it = find_data(_data, _combos);
    if (it != _combos.end()) {
        return std::distance(_combos.begin(), it);
    } else {
        return -1;
    }

}

template <class Tdata, class Tvalue>
typename std::vector< SlvCombo<Tdata, Tvalue> >::const_iterator SlvComboFunc::find_data(const Tdata& _data, const std::vector< SlvCombo<Tdata, Tvalue> >& _combos) {

    typename std::vector< SlvCombo<Tdata, Tvalue> >::const_iterator it = _combos.begin();

    while (it != _combos.end() && it->data != _data) {
        ++it;
    }

    return it;
}

template <class Tdata, class Tvalue>
Tvalue SlvComboFunc::calc_value_sum(const std::vector< SlvCombo<Tdata, Tvalue> >& _combos) {

    Tvalue sum = 0;

    for (typename std::vector< SlvCombo<Tdata, Tvalue> >::const_iterator it = _combos.begin(); it != _combos.end(); ++it) {
        sum += it->value;
    }

    return sum;
}
