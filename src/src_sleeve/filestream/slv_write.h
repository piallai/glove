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

#include <fstream>

namespace slv {
    /*! Write functions in binary file for misc types. Common data types are being specialized.*/
    namespace rw {

        template <class Tdat>
        void writeB(const Tdat& _dat, std::ofstream& _output_file);
        template <class Tdat>
        void writeB(Tdat* const _dat, std::ofstream& _output_file);
        template <class Tdat, class Targ>
        void writeB(const Tdat& _dat, std::ofstream& _output_file, const Targ& _arg);
        template <class Tdat, class Targ>
        void writeB(Tdat* const _dat, std::ofstream& _output_file, const Targ& _arg);

    }
}

#include "filestream/spec/slv_write_spec_AT.h"
#include "filestream/spec/slv_write_spec_AT_ptr.h"

template <class Tdat>
void slv::rw::writeB(const Tdat& _dat, std::ofstream& _output_file) {
    _dat.writeB(_output_file);
}

template <class Tdat>
void slv::rw::writeB(Tdat* const _dat, std::ofstream& _output_file) {
    _dat->writeB(_output_file);
}

template <class Tdat, class Targ>
void slv::rw::writeB(const Tdat& _dat, std::ofstream& _output_file, const Targ& _arg) {
    _dat.writeB(_output_file, _arg);
}

template <class Tdat, class Targ>
void slv::rw::writeB(Tdat* const _dat, std::ofstream& _output_file, const Targ& _arg) {
    _dat->writeB(_output_file, _arg);
}
