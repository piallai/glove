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

/*! Example of how to manage read and write.*/

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "filestream/slv_rw.h"
#else
#include "glove.h"
#endif

class ClassA {

private:

    float value1 = 20;
    std::string value2 = "foo";

public:

	ClassA() {}

    bool readB(std::ifstream& _input_file) {
        bool l_read = slv::rw::readB(value1, _input_file);
        if (l_read) l_read = slv::rw::readB(value2, _input_file);
        return l_read;
    }

    void writeB(std::ofstream& _output_file) const {
        slv::rw::writeB(value1, _output_file);
        slv::rw::writeB(value2, _output_file);
    }

};

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "filestream/SlvFileMgr.h"
#endif

int main(int argc, char *argv[]) {

    ClassA classA;
    SlvFileMgr::write_binary(classA, "classA");//write to file ./classA
    SlvFileMgr::read_binary(classA, "classA");//read from file ./classA

}

