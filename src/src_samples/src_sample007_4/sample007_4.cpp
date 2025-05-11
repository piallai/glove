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

class ClassB {

private:

    ClassA classA;
    std::vector<double> value = {1, 2, 4, 8, 16};

public:

    ClassB() {}

    bool readB(std::ifstream& _input_file) {
        bool l_read = slv::rw::readB(classA, _input_file);
        if (l_read) l_read = slv::rw::readB(value, _input_file);
        return l_read;
    }

    void writeB(std::ofstream& _output_file) const {
        slv::rw::writeB(classA, _output_file);
        slv::rw::writeB(value, _output_file);
    }

};

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "filestream/SlvFileMgr.h"
#endif

int main(int argc, char *argv[]) {

    ClassB classB;
    SlvFileMgr::write_binary(classB, "classB");//write to file ./classB
    SlvFileMgr::read_binary(classB, "classB");//read from file ./classB

    // Or 

    SlvFile file("classB");
    std::ofstream output_file_stream;
    SlvStatus status = SlvFileMgr::open_file(output_file_stream, file);
    if (status) {
        classB.writeB(output_file_stream);
        output_file_stream.close();
    }

    std::ifstream input_file_stream;
    status = SlvFileMgr::open_file(input_file_stream, file);
    if (status) {
        classB.readB(input_file_stream);
        input_file_stream.close();
    }

}

