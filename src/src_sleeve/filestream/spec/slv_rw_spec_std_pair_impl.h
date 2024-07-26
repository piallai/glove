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

#include "filestream/spec/slv_rw_spec_std_pair_decl.h"

template <class Tdat1, class Tdat2>
bool slv::rw::readB(std::pair<Tdat1, Tdat2>& _pair, std::ifstream& _input_file) {
    bool l_read = slv::rw::readB(_pair.first, _input_file);
    if (l_read) l_read = slv::rw::readB(_pair.second, _input_file);
    return l_read;
}

template <class Tdat1, class Tdat2>
void slv::rw::writeB(const std::pair<Tdat1, Tdat2>& _pair, std::ofstream& _output_file) {
    slv::rw::writeB(_pair.first, _output_file);
    slv::rw::writeB(_pair.second, _output_file);
}
