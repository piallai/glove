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

#include "filestream/spec/slv_rw_spec_std_array_decl.h"

template <class Tdat, size_t N>
bool slv::rw::readB(std::array<Tdat, N>& _array, std::ifstream& _input_file) {
    bool l_read = true;
    for (typename std::array<Tdat, N>::iterator it = _array.begin(); it != _array.end() && l_read; ++it) {
        l_read = slv::rw::readB(*it, _input_file);
    }
    return l_read;
}

template <class Tdat, size_t N>
void slv::rw::writeB(const std::array<Tdat, N>& _array, std::ofstream& _output_file) {
    for (typename std::array<Tdat, N>::const_iterator it = _array.begin(); it != _array.end(); ++it) {
        slv::rw::writeB(*it, _output_file);
    }
}
