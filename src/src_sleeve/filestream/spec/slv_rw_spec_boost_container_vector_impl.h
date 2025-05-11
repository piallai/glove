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

#include "filestream/spec/slv_rw_spec_boost_container_vector_decl.h"

#if !defined(GLOVE_PV_SINGLE_HEADER) || OPTION_USE_BOOST==1

template <class Tdat>
bool slv::rw::readB(boost::container::vector<Tdat>& _dat, std::ifstream& _input_file) {

    unsigned int size;
    bool l_read = slv::rw::readB(size, _input_file);
    if (!l_read) size = 0;
    _dat.resize(size);
    for (typename boost::container::vector<Tdat>::iterator it = _dat.begin(); it != _dat.end() && l_read; ++it) {
        l_read = slv::rw::readB(*it, _input_file);
    }

    return l_read;
}

template <class Tdat>
void slv::rw::writeB(const boost::container::vector<Tdat>& _dat, std::ofstream& _output_file) {

    unsigned int size = _dat.size();
    slv::rw::writeB(size, _output_file);
    for (typename boost::container::vector<Tdat>::const_iterator it = _dat.begin(); it != _dat.end(); ++it) {
        slv::rw::writeB(*it, _output_file);
    }
}

#endif
