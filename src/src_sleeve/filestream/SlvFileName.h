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

#include "SlvFileTypedefs.h"

/*! Class representing a file path without its directory.*/
class SlvFileName {

public:
    /*! Name of the file (stem).*/
    SlvFileStem stem;
    /*! Extension of the file.*/
    SlvFileExtension extension;

public:

    SlvFileName();
    SlvFileName(const SlvFileStem& _stem, const SlvFileExtension& _extension);
    SlvFileName(const std::string& _string);
    ~SlvFileName();

    /*! Get total name of the file: name + extension*/
    std::string get_total_name() const;

    bool operator==(const SlvFileName& _file_name) const;

    bool readB(std::ifstream& _input_file);
    void writeB(std::ofstream& _output_file) const;

};
