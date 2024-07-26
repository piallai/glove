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

#include "filestream/slv_rw.h"
#include "iostream/spec/iostream_spec_boost_unordered_map.h"

#if !defined(GLOVE_PV_SINGLE_HEADER) || OPTION_USE_BOOST==1

namespace slv {
    namespace rw {
        template <class Tkey, class T>
        void writeB(const boost::unordered::unordered_map<Tkey, T>& _map, std::ofstream& _output_file);
        template <class Tkey, class T>
        bool readB(boost::unordered::unordered_map<Tkey, T>& _map, std::ifstream& _input_file);
    }

}

#endif
