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

/*! Example of how to manage read and write.*/

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "SlvIOS.h"
#include <iostream>//only because using std::cout in ClassA
#else
#include "glove.h"
#endif

// Inherit << and >> operators
class ClassA : public SlvIOS {

private:

    float value1 = 20;
    std::string value2 = "foo";

public:
	ClassA() {}

private:

    // Implement istream pure virtual method for reading from operator >>
    void istream(std::istream& _is) {
        std::cout << "Enter value1 : ";
        _is >> value1;
        std::cout << "Enter value2 : ";
        _is >> value2;
    }

    // Implement ostream pure virtual method for output with operator <<
    void ostream(std::ostream& _os) const {
        _os << "value1 : " << value1 << " ; value2 : " << value2 << std::endl;
    }

};

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "filestream/SlvFileMgr.h"
#endif

int main(int argc, char *argv[]) {

    ClassA classA;
    std::cin >> classA;
    std::cout << classA << std::endl;

}

