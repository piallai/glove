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
#include "std_vector.h"

namespace slv {
    /*! Read functions for misc types. Common data types are being specialized.*/
    namespace rw {

        template <class Tdat>
        bool readB(std::vector<Tdat>& _vector, std::ifstream& _input_file);
        bool readB(std::vector<bool>& _vector, std::ifstream& _input_file);

        template <class Tdat>
        void writeB(const std::vector<Tdat>& _vector, std::ofstream& _output_file);
        void writeB(const std::vector<bool>& _vector, std::ofstream& _output_file);
    }
}
