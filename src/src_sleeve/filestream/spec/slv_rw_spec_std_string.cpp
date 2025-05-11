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

#include "filestream/spec/slv_rw_spec_std_string.h"

template <>
bool slv::rw::readB<std::string>(std::string& _dat, std::ifstream& _input_file) {
    unsigned int N;
    bool l_read = slv::rw::readB(N, _input_file);
    if (!l_read) N = 0;
    _dat.resize(N);
    for (unsigned int i = 0; i < N && l_read; i++) {
        l_read = slv::rw::readB(_dat[i], _input_file);
    }
    return l_read;
}

template <>
void slv::rw::writeB<std::string>(const std::string& _dat, std::ofstream& _output_file) {
    unsigned int size = (unsigned int)_dat.size();
    slv::rw::writeB(size, _output_file);
    for (unsigned int i = 0; i < _dat.size(); i++) {
        slv::rw::writeB(_dat[i], _output_file);
    }
}
