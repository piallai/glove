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
#include "SlvFileExtensions.h"
#include "SlvFileName.h"
#include "SlvDirectory.h"

/*! Represents a file location (directory) and name.*/
class SlvFile : public SlvIOS {

public:

    enum IO { Read, Write, Any };

private:

    /*! File of the file instance.*/
    SlvFileName file_name;
    /*! Directory of the file instance.*/
    SlvDirectory directory;

    /*! About file type (ex: image, etc..).*/
    std::string description;

    /*! Input or output file (read or write).*/
    IO io_mode;

    /*! Allowed extensions for the file.
    * The name used at construction provides the first allowed extension.
    * Unless adding other extensions, it is not possible to change the file's extension.*/
    SlvFileExtensions allowed_extensions;

public:

    SlvFile();
    /*! Set path of file. The extension of the file will be added to allowed extensions.*/
    SlvFile(const std::string& _path, IO _io_mode = IO::Any, std::string _description = "");
    SlvFile(const char* _string, IO _io_mode = IO::Any, std::string _description = "");
    SlvFile(const std::string& _path, const SlvFileExtensions& _allowed_extensions, IO _io_mode = IO::Any, std::string _description = "");
    SlvFile(const char* _string, const SlvFileExtensions& _allowed_extensions, IO _io_mode = IO::Any, std::string _description = "");
    SlvFile(IO _io_mode, std::string _description = "");
    SlvFile(const SlvDirectory& _directory, const SlvFileName& _file_name, IO _io_mode = IO::Any, std::string _description = "");
    SlvFile(const SlvDirectory& _directory, SlvFileExtensions _allowed_extensions = SlvFileExtensions(), IO _io_mode = IO::Any);
    SlvFile(SlvFileExtensions _allowed_extensions, IO _io_mode = IO::Any, std::string _description = "");
    ~SlvFile();

    /*! Get file name with extension.*/
    const std::string get_name() const;
    /*! Get directory + file name with extensions.*/
    const std::string get_path() const;
    /*! Get file item.*/
    const SlvFileName& get_file_name() const;
    /*! Get directory item.*/
    const SlvDirectory& get_directory() const;
    /*! Get description.*/
    const std::string& get_description() const;
    /*! Get allowed extensions for this file.*/
    const SlvFileExtensions& get_allowed_extensions() const;
    /*! Input or output file (read or write).*/
    IO get_io_mode() const;

    /*! Set file name (ignoring directories). Return true if the name was properly set.*/
    bool set_name(const std::string& _path);
    /*! Set directory (ignoring file names).
    * It means that the directory will be handled up to the last directory separator '/'.
    * Ex:   Providing /a/b/c will set directory /a/b/
    *       Providing /a/b/c/ will set directory /a/b/c/.*/
    void set_directory(const std::string& _path);

    /*! Add extension \p _ext in the allowed extensions for this file (format: .ext)*/
    void add_allowed_extension(const std::string& _ext);
    void add_allowed_extensions(const SlvFileExtensions& _extensions);

    /*! Return true if the file exists.*/
    bool exists() const;

    bool operator==(const SlvFile& _file) const;
    bool operator!=(const SlvFile& _file) const;

    bool readB(std::ifstream& _input_file);
    void writeB(std::ofstream& _output_file) const;

private:

    void istream(std::istream& _is);
    void ostream(std::ostream& _os) const;
};

#include "slv_string.h"
template <>
std::string slv::string::to_id_str(const SlvFile& _value);

