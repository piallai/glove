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
#pragma warning(disable: 4505)

#include <fstream>
#include "slv_flag.h"
#include "SlvMacrosDeclarations.h"

namespace slv {
    /*! Read functions in binary file for misc types. Common data types are being specialized.*/
    namespace rw {

        template <class Tdat>
        bool readB(Tdat& _dat, std::ifstream& _input_file);
        template <class Tdat>
        bool readB(Tdat* _dat, std::ifstream& _input_file);
        template <class Tdat>
        bool readB(const Tdat* _dat, std::ifstream& _input_file);

        /*! Read an instance directly from a file.*/
        template <class Tdat>
        Tdat readB(std::ifstream& _input_file);

        /*! Read by constructor.*/
        template <class Tdat>
        Tdat readB_constr(std::ifstream& _input_file);

        glvm_staticVariable(const, std::string, end_of_file_str, "end of file")

    }
}

#include "filestream/spec/slv_read_spec_AT.h"
#include "filestream/spec/slv_read_spec_AT_ptr.h"

template <class Tdat>
bool slv::rw::readB(Tdat& _dat, std::ifstream& _input_file) {
    if (!_input_file.eof()) {
        return _dat.readB(_input_file);
    } else {
        slv::flag::ISSUE(slv::flag::EndOfFile, "end of file");
        return false;
    }
}

template <class Tdat>
bool slv::rw::readB(Tdat* _dat, std::ifstream& _input_file) {
    if (!_input_file.eof()) {
        return _dat->readB(_input_file);
    } else {
        slv::flag::ISSUE(slv::flag::EndOfFile, "end of file");
        return false;
    }
}

template <class Tdat>
bool slv::rw::readB(const Tdat* _dat, std::ifstream& _input_file) {
    slv::flag::ISSUE(slv::flag::InvalidArgument, "can't read const object");
    return false;
}

template <class Tdat>
Tdat slv::rw::readB(std::ifstream& _input_file) {

    Tdat data;
    slv::rw::readB(data, _input_file);
    return data;
}

template <class Tdat>
Tdat slv::rw::readB_constr(std::ifstream& _input_file) {

    Tdat data(_input_file);
    return data;
}
