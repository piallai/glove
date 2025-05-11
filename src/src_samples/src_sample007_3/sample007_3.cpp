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
#include "SlvIOFS.h"
#else
#include "glove.h"
#endif

class ClassA : public SlvIOFS {

private:

    float value1 = 20;
    std::string value2 = "foo";

public:

	ClassA() {}

    void ifstream(std::ifstream& _is) {
        _is.seekg(std::string("value1 : ").size(), std::ios_base::cur);
        _is >> value1;
        _is.seekg(std::string(" ; value2 : ").size(), std::ios_base::cur);
        _is >> value2;
    }

    void ofstream(std::ofstream& _os) const {
        _os << "value1 : " << value1 << " ; value2 : " << value2 << std::endl;
    }

};

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "filestream/SlvFileMgr.h"
#endif

int main(int argc, char *argv[]) {

    ClassA classA;

    SlvFileMgr::write_text(classA, "classA.txt");// use std::ofstream& operator<< and ClassA::ofstream
    SlvFileMgr::read_text(classA, "classA.txt");// use std::ifstream& operator>> and ClassA::ifstream

}

