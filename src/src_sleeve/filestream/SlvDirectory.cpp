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

#include "SlvDirectory.h"
#include "SlvFileMgr.h"
#if __cplusplus > 201402L
#include <filesystem>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif
#include "filestream/slv_rw.h"

SlvDirectory::SlvDirectory() {
    l_relative = false;
}

SlvDirectory::SlvDirectory(const std::string _string) {
    path = SlvFileMgr::get_directory_str(_string);
    l_relative = SlvFileMgr::is_path_relative(path);
}

SlvDirectory::SlvDirectory(const char* _string) :SlvDirectory(std::string(_string)) {

}

SlvDirectory::SlvDirectory(const SlvDirectory& _directory) {
    path = _directory.path;
    l_relative = _directory.l_relative;
}

SlvDirectory::~SlvDirectory() {

}

const std::string& SlvDirectory::get_path() const {
    return path;
}

bool SlvDirectory::is_relative() const {
    return l_relative;
}

bool SlvDirectory::exists() const {

#if __cplusplus > 201402L
    return std::filesystem::exists(path);
#else
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        return false;
    } else if (info.st_mode & S_IFDIR) {
        return true;
    } else {
        return false;
    }
#endif

}

bool SlvDirectory::operator==(const SlvDirectory& _directory) const {

    return path == _directory.path \
        && l_relative == _directory.l_relative;

}

bool SlvDirectory::operator!=(const SlvDirectory& _directory) const {

    return !(*this == _directory);

}

void SlvDirectory::istream(std::istream& _is) {

    std::string tmp_path;
    slv::string::istream(_is, tmp_path);
    *this = SlvDirectory(tmp_path);

}

void SlvDirectory::ostream(std::ostream& _os) const {

    _os << path;

}

bool SlvDirectory::readB(std::ifstream& _input_file) {

    bool l_read = slv::rw::readB(path, _input_file);
    if (l_read) l_read = slv::rw::readB(l_relative, _input_file);
    return l_read;

}

void SlvDirectory::writeB(std::ofstream& _output_file) const {

    slv::rw::writeB(path, _output_file);
    slv::rw::writeB(l_relative, _output_file);

}
