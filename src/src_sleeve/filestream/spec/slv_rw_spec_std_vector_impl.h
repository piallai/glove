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

#include "filestream/spec/slv_rw_spec_std_vector_decl.h"

template <class Tdat>
bool slv::rw::readB(std::vector<Tdat>& _vector, std::ifstream& _input_file) {
    unsigned int size;
    bool l_read = slv::rw::readB(size, _input_file);
    if (size > 100000000) {
        slv::flag::ISSUE(slv::flag::InvalidArgument, "reading a vector of size : ", size, " is suspicious. Data formatting is probably wrong.");
    }
    if (!l_read) size = 0;
    _vector.resize(size);
    for (typename std::vector<Tdat>::iterator it = _vector.begin(); it != _vector.end() && l_read; ++it) {
        l_read = slv::rw::readB(*it, _input_file);
    }
    return l_read;
}

template <class Tdat>
void slv::rw::writeB(const std::vector<Tdat>& _vector, std::ofstream& _output_file) {
    unsigned int size = (unsigned int)_vector.size();
    slv::rw::writeB(size, _output_file);
    for (typename std::vector<Tdat>::const_iterator it = _vector.begin(); it != _vector.end(); ++it) {
        slv::rw::writeB(*it, _output_file);
    }
}
