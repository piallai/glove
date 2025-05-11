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

#pragma once

#include "SlvIOS.h"

/*! Class representing a system directory.*/
class SlvDirectory : public SlvIOS {

private:
    /*! Path of the directory.*/
    std::string path;
    /*! Whether the directory's path is relative or not.*/
    bool l_relative;

public:

    SlvDirectory();
    /*Ex:   Providing /a/b/c will set directory /a/b/
    * Providing /a/b/c/ will set directory /a/b/c/ .*/
    SlvDirectory(const std::string _string);
    SlvDirectory(const char* _string);
    SlvDirectory(const SlvDirectory& _directory);
    ~SlvDirectory();

    /*! Get path of the directory.*/
    const std::string& get_path() const;
    /*! Whether the directory's path is relative or not.*/
    bool is_relative() const;

    /*! Return true if the directory exists.*/
    bool exists() const;

    bool operator==(const SlvDirectory& _directory) const;
    bool operator!=(const SlvDirectory& _directory) const;

    bool readB(std::ifstream& _input_file);
    void writeB(std::ofstream& _output_file) const;

private:

    void istream(std::istream& _is);
    void ostream(std::ostream& _os) const;

};
