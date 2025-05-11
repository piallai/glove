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

#include "SlvFile.h"
#include "SlvFileMgr.h"
#include "slv_vector.h"
#if __cplusplus > 201402L
#include <filesystem>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif
#include "filestream/slv_rw.h"
#include "SlvMacros.h"

SlvFile::SlvFile() {

}

SlvFile::SlvFile(const std::string& _path, IO _io_mode, std::string _description)
    :SlvFile(SlvDirectory(_path), SlvFileName(_path), _io_mode, _description) {

}

SlvFile::SlvFile(const char* _string, IO _io_mode, std::string _description) :SlvFile((_string) ? (std::string(_string)) : std::string(""), _io_mode, _description) {

}

SlvFile::SlvFile(const std::string& _path, const SlvFileExtensions& _allowed_extensions, IO _io_mode, std::string _description)
    :SlvFile(_path, _io_mode, _description) {

    add_allowed_extensions(_allowed_extensions);

}

SlvFile::SlvFile(const char* _string, const SlvFileExtensions& _allowed_extensions, IO _io_mode, std::string _description) :SlvFile((_string) ? (std::string(_string)) : std::string(""), _allowed_extensions, _io_mode, _description) {

}

SlvFile::SlvFile(IO _io_mode, std::string _description) :SlvFile("", _io_mode, _description) {

}

SlvFile::SlvFile(const SlvDirectory& _directory, const SlvFileName& _file_name, IO _io_mode, std::string _description) {

    directory = _directory;
    file_name = _file_name;

    if (file_name.extension != slv::string::str_void()) {
        add_allowed_extension(file_name.extension);
    }

    description = _description;

    io_mode = _io_mode;
}

SlvFile::SlvFile(const SlvDirectory& _directory, SlvFileExtensions _allowed_extensions, IO _io_mode) {

    directory = _directory;
    allowed_extensions = _allowed_extensions;
    io_mode = _io_mode;

}

SlvFile::SlvFile(SlvFileExtensions _allowed_extensions, IO _io_mode, std::string _description) {

    description = _description;
    allowed_extensions = _allowed_extensions;
    io_mode = _io_mode;

}

SlvFile::~SlvFile() {

}

const std::string SlvFile::get_name() const {

    return file_name.get_total_name();
}

const std::string SlvFile::get_path() const {
    std::string path = directory.get_path() + get_name();
    return path;
}

const SlvFileName& SlvFile::get_file_name() const {
    return file_name;
}

const SlvDirectory& SlvFile::get_directory() const {
    return directory;
}

const std::string& SlvFile::get_description() const {
    return description;
}

const SlvFileExtensions& SlvFile::get_allowed_extensions() const {
    return allowed_extensions;
}

SlvFile::IO SlvFile::get_io_mode() const {
    return io_mode;
}

bool SlvFile::set_name(const std::string& _path) {

    if (slv::vector::find(SlvFileMgr::get_extension(_path), allowed_extensions.get())) {
        file_name = SlvFileName(_path);
        return true;
    } else {
        slv::flag::ISSUE(slv::flag::FlagType::Warning, "can't set name: ", _path, " allowed extensions are: ", allowed_extensions.get());
        return false;
    }

}

void SlvFile::set_directory(const std::string& _path) {

    directory = SlvDirectory(_path);

}

void SlvFile::add_allowed_extension(const std::string& _ext) {

    allowed_extensions.add(_ext);

}

void SlvFile::add_allowed_extensions(const SlvFileExtensions& _extensions) {

    allowed_extensions.add(_extensions);

}

bool SlvFile::exists() const {

#if __cplusplus > 201402L
    return std::filesystem::is_regular_file(get_path());
#else
    if (file_name.get_total_name().empty()) {
        return false;
    } else if (file_name.get_total_name().find_first_not_of('.') == std::string::npos) {// stat recognize "." path as existing file
        return false;
    } else {
#ifdef COMPILER_MSVC
#define glvm_pv_stat _stat64
#else
#define glvm_pv_stat stat64
#endif
        struct glvm_pv_stat info;
        return (glvm_pv_stat(get_path().c_str(), &info) == 0);
    }
#endif

}

bool SlvFile::operator==(const SlvFile& _file) const {

    return file_name == _file.file_name \
        && directory == _file.directory \
        && description == _file.description \
        && allowed_extensions == _file.allowed_extensions;

}

bool SlvFile::operator!=(const SlvFile& _file) const {

    return !(*this == _file);

}

bool SlvFile::readB(std::ifstream& _input_file) {

    bool l_read = slv::rw::readB(file_name, _input_file);
    if (l_read) l_read = slv::rw::readB(directory, _input_file);
    return l_read;

}

void SlvFile::writeB(std::ofstream& _output_file) const {

    slv::rw::writeB(file_name, _output_file);
    slv::rw::writeB(directory, _output_file);
}

void SlvFile::istream(std::istream& _is) {

    std::string path;
    slv::string::istream(_is, path);
    directory = SlvDirectory(path);
    file_name = SlvFileName(path);

    if (io_mode == IO::Read && !exists()) {
        std::cout << "Caution : The file " << get_path()  << " does not exist " << std::endl;
    }

}

void SlvFile::ostream(std::ostream& _os) const {

    _os << get_path();

}

template <>
std::string slv::string::to_id_str(const SlvFile& _value) {

    return to_string(_value.get_name());
}
