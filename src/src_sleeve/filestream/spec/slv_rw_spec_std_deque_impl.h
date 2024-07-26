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

#include "filestream/spec/slv_rw_spec_std_deque_decl.h"

template <class Tdat>
bool slv::rw::readB(std::deque<Tdat>& _deque, std::ifstream& _input_file) {
    unsigned int size;
    bool l_read = slv::rw::readB(size, _input_file);
    if (size > 100000000) {
        slv::flag::ISSUE(slv::flag::InvalidArgument, "reading a vector of size : ", size, " is suspicious. Data formatting is probably wrong.");
    }
    if (!l_read) size = 0;
    _deque.resize(size);
    for (typename std::deque<Tdat>::iterator it = _deque.begin(); it != _deque.end() && l_read; ++it) {
        l_read = slv::rw::readB(*it, _input_file);
    }
    return l_read;
}

template <class Tdat>
void slv::rw::writeB(const std::deque<Tdat>& _deque, std::ofstream& _output_file) {
    unsigned int size = (unsigned int)_deque.size();
    slv::rw::writeB(size, _output_file);
    for (typename std::deque<Tdat>::const_iterator it = _deque.begin(); it != _deque.end(); ++it) {
        slv::rw::writeB(*it, _output_file);
    }
}
