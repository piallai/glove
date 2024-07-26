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

#include "SlvFileName.h"
#include "SlvDirectory.h"
#include "SlvFile.h"
#include "SlvMacrosDeclarations.h"
#include "SlvStatus.h"

/*! Static methods for file management.*/
class SlvFileMgr {

public:

    /*! Default file name extension: .data*/
    glvm_staticVariable(const, std::string, default_name_extension, ".data")

    /*! Path applied before any RELATIVE path managed by the SlvFileMgr framework.
    * Example: if set to "../../foo/", any relative path will be prefixed as so.*/
    glvm_staticVariable(, std::string, master_relative_path, "")

public:

    /*! Get extension of \p _name (last found dot). Return empty string if no extension found.*/
    static std::string get_extension(const std::string& _name);
    /*! Remove extension of \p _name. Stem. test.abc => test.*/
    static std::string remove_extension(const std::string& _name);

    /*! Get file name of a path \p _path. With our without (stem) extension \p _l_extension.*/
    static std::string get_file_name_str(const std::string& _path, bool _l_extension);

    /*! Get the directory part of a path \p _path.*/
    static std::string get_directory_str(const std::string& _path);

    /*! Get the effective path of \p _directory, relatively to master_relative_path() if relative.*/
    static std::string get_path(const SlvDirectory& _directory);
    /*! Get the effective path of \p _file, relatively to master_relative_path() if relative.*/
    static std::string get_path(const SlvFile& _file);

    /*! Return true if \p _path is relative, by analyzing first characters of the string.
    * On Windows: not relative if second character is ':'.
    * Otherwise: not relative if first character is '/'.*/
    static bool is_path_relative(const std::string& _path);

private:
    //glvm_staticVariable(const, std::vector<char>, forbidden_file_characters, std::vector<char>({ '*','/', '\\', '<' ,'>', ':', '|', '?' }))
    glvm_staticVariable(const, std::string, forbidden_file_characters, "*/\\<>:|?,")
public:
    /*! Replace forbiden characters by \p _replacement character.
    * \p _l_consecutive : if enabled, consecutive forbidden characters are replaced to a single replacement character.
    * \p _l_extension : if enabled, adds space character to list of forbidden characters.*/
    static std::string replace_forbidden_file_characters(const std::string& _string, char _replacement, bool _l_consecutive, bool _l_extension = false);

    /*! Write a template object \p _dat in a BINARY file located at \p _file_path.*/
    template <class Tdat>
    static SlvStatus write_binary(const Tdat& _dat, const std::string& _file_path, std::ios::openmode _position = std::ios::trunc);

    /*! Read a template object \p _dat from a BINARY file located at \p _file_path.*/
    template <class Tdat>
    static SlvStatus read_binary(Tdat& _dat, const std::string& _file_path);


    /*! Write a template object \p _dat in a TEXT file located at \p _file_path.*/
    template <class Tdat>
    static SlvStatus write_text(const Tdat& _dat, const std::string& _file_path, std::ios::openmode _position = std::ios::trunc);
    /*! Read a template object \p _dat from a TEXT file located at \p _file_path.*/
    template <class Tdat>
    static SlvStatus read_text(Tdat& _dat, const std::string& _file_path);



    /*! Open file \p _file_stream located at \p _file_path.*/
    template <class Tfile>
    static SlvStatus open_file(Tfile& _file_stream, const std::string& _file_path, std::ios::openmode _mode1, std::ios::openmode _mode2, std::ios::openmode _mode3);
    /*! Open file \p _file_stream located at \p _file_path.*/
    template <class Tfile>
    static SlvStatus open_file(Tfile& _file_stream, const std::string& _file_path, std::ios::openmode _mode1, std::ios::openmode _mode2);
    /*! Open file \p _file_stream located at \p _file_path.*/
    template <class Tfile>
    static SlvStatus open_file(Tfile& _file_stream, const std::string& _file_path, std::ios::openmode _mode1);

    /*! Return true if opening \p _file is possible using the mode \p _io_mode.*/
    static bool test_file(const SlvFile& _file, std::ios::openmode _io_mode);

    /*! Open file \p _file_stream located at \p _file.*/
    template <class Tfile>
    static SlvStatus open_file(Tfile& _file_stream, const SlvFile& _file, std::ios::openmode _mode1, std::ios::openmode _mode2, std::ios::openmode _mode3);
    /*! Open file \p _file_stream located at \p _file.*/
    template <class Tfile>
    static SlvStatus open_file(Tfile& _file_stream, const SlvFile& _file, std::ios::openmode _mode1, std::ios::openmode _mode2);
    /*! Open file \p _file_stream located at \p _file.*/
    template <class Tfile>
    static SlvStatus open_file(Tfile& _file_stream, const SlvFile& _file, std::ios::openmode _mode1);

    /*! Open file \p _file_stream located at \p _file in truncated mode. Convenience function.*/
    static SlvStatus open_file(std::ofstream& _file_stream, const SlvFile& _file);
    /*! Open file \p _file_stream located at \p _file. Convenience function.*/
    static SlvStatus open_file(std::ifstream& _file_stream, const SlvFile& _file);

    /*! Create directory \p _subpath relatively to master_relative_path(). Also create intermediate directories if they do not exist with \p _l_force_parents.*/
    static bool mkdir(const std::string& _subpath, bool _l_force_parents = false);

};

#include "slv_flag.h"
#include <cstring>//strerror
#include "SlvMacros.h"

template <class Tdat>
SlvStatus SlvFileMgr::write_binary(const Tdat& _dat, const std::string& _file_path, std::ios::openmode _position) {

    SlvStatus status;

    std::ofstream output_file;
    status = SlvFileMgr::open_file(output_file, _file_path, std::ios::out, _position, std::ios::binary);

    if (status) {
        slv::rw::writeB(_dat, output_file);
        output_file.close();
    }

    return status;

}

template <class Tdat>
SlvStatus SlvFileMgr::read_binary(Tdat& _dat, const std::string& _file_path) {

    SlvStatus status;

    std::ifstream input_file;
    status = SlvFileMgr::open_file(input_file, _file_path, std::ios::in, std::ios::binary);

    if (status) {
        bool l_read = slv::rw::readB(_dat, input_file);
        input_file.close();
        if (!l_read) status = SlvStatus(SlvStatus::statusType::warning, "Failed reading the file :\n" + _file_path);
    }

    return status;

}

template <class Tdat>
SlvStatus SlvFileMgr::write_text(const Tdat& _dat, const std::string& _file_path, std::ios::openmode _position) {

    SlvStatus status;

    std::ofstream output_file;
    status = SlvFileMgr::open_file(output_file, _file_path, std::ios::out, _position);

    if (status) {
        output_file << _dat;
        output_file.close();
    }

    return status;

}

template <class Tdat>
SlvStatus SlvFileMgr::read_text(Tdat& _dat, const std::string& _file_path) {

    SlvStatus status;

    std::ifstream input_file;
    status = SlvFileMgr::open_file(input_file, _file_path, std::ios::in);

    if (status) {
        input_file >> _dat;
        input_file.close();
    }

    return status;

}

template <class Tfile>
SlvStatus SlvFileMgr::open_file(Tfile& _file_stream, const std::string& _file_path, std::ios::openmode _mode1, std::ios::openmode _mode2, std::ios::openmode _mode3) {

    SlvFile file(_file_path);
    return open_file(_file_stream, file, _mode1, _mode2, _mode3);

}

template <class Tfile>
SlvStatus SlvFileMgr::open_file(Tfile& _file_stream, const std::string& _file_path, std::ios::openmode _mode1, std::ios::openmode _mode2) {

    SlvFile file(_file_path);
    return open_file(_file_stream, file, _mode1, _mode2);

}

template <class Tfile>
SlvStatus SlvFileMgr::open_file(Tfile& _file_stream, const std::string& _file_path, std::ios::openmode _mode1) {

    SlvFile file(_file_path);
    return open_file(_file_stream, file, _mode1);

}

template <class Tfile>
SlvStatus SlvFileMgr::open_file(Tfile& _file_stream, const SlvFile& _file, std::ios::openmode _mode1, std::ios::openmode _mode2, std::ios::openmode _mode3) {

    SlvStatus status;

    _file_stream.open(SlvFileMgr::get_path(_file).c_str(), _mode1 | _mode2 | _mode3);
    if (!_file_stream.is_open()) {
        const int max_errorlen = 95;// no access to strerrorlen_s
        char* errmsg = new char[max_errorlen];
#if defined(OS_WIN)
        strerror_s(errmsg, max_errorlen, errno);
#elif defined(OS_LINUX) || defined(OS_UNIX)
        errmsg = strerror_r(errno, errmsg, max_errorlen);
#endif
        status = SlvStatus(SlvStatus::statusType::information, std::string(errmsg) + ", couldn't open file: " + SlvFileMgr::get_path(_file));
        delete[] errmsg;
    }

    return status;

}

template <class Tfile>
SlvStatus SlvFileMgr::open_file(Tfile& _file_stream, const SlvFile& _file, std::ios::openmode _mode1, std::ios::openmode _mode2) {

    SlvStatus status;

    _file_stream.open(SlvFileMgr::get_path(_file).c_str(), _mode1 | _mode2);
    if (!_file_stream.is_open()) {
        const int max_errorlen = 95;// no access to strerrorlen_s
        char* errmsg = new char[max_errorlen];
#if defined(OS_WIN)
        strerror_s(errmsg, max_errorlen, errno);
#elif defined(OS_LINUX) || defined(OS_UNIX)
        errmsg = strerror_r(errno, errmsg, max_errorlen);
#endif
        status = SlvStatus(SlvStatus::statusType::information, std::string(errmsg) + ", couldn't open file: " + SlvFileMgr::get_path(_file));
        delete[] errmsg;
    }

    return status;

}
template <class Tfile>
SlvStatus SlvFileMgr::open_file(Tfile& _file_stream, const SlvFile& _file, std::ios::openmode _mode1) {

    SlvStatus status;

    _file_stream.open(SlvFileMgr::get_path(_file).c_str(), _mode1);
    if (!_file_stream.is_open()) {
        const int max_errorlen = 95;// no access to strerrorlen_s
        char* errmsg = new char[max_errorlen];
#if defined(OS_WIN)
        strerror_s(errmsg, max_errorlen, errno);
#elif defined(OS_LINUX) || defined(OS_UNIX)
        errmsg = strerror_r(errno, errmsg, max_errorlen);
#endif
        status = SlvStatus(SlvStatus::statusType::information, std::string(errmsg) + ", couldn't open file: " + SlvFileMgr::get_path(_file));
#if defined(OS_WIN)
        delete[] errmsg;
#endif
    }

    return status;

}
