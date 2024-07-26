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
#include <utility>

namespace slv {
    /*! Read functions for misc types. Common data types are being specialized.*/
    namespace rw {

        /*template <class Tdat>
        bool read(std::vector<Tdat>& _dat, std::ifstream& _input_file);*/
        template <class Tdat1, class Tdat2>
        bool readB(std::pair<Tdat1, Tdat2>& _pair, std::ifstream& _input_file);
        //bool read(std::vector<bool>& _vector, std::ifstream& _input_file);
        template <class Tdat1, class Tdat2>
        void writeB(const std::pair<Tdat1, Tdat2>& _pair, std::ofstream& _output_file);
    }
}
