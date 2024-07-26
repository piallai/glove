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

#include "SlvFileMgr.h"
#include <algorithm>//for replace

std::string SlvFileMgr::get_extension(const std::string& _name) {

    size_t position = _name.find_last_of('.');

    if (position != std::string::npos) {
        std::string extension = _name.substr(position, _name.size() - position);
        if (extension != "./") {
            return extension;
        } else {
            return slv::string::str_void();
        }
    } else {
        return slv::string::str_void();
    }

}

std::string SlvFileMgr::remove_extension(const std::string& _name) {

    size_t position = _name.find_last_of('.');

    if (position != std::string::npos) {
        //few cases to avoid dots for directory, ex: ../test/test
        if (position > 0 && _name[position - 1] == '.') {
            return _name;
        } else if (position < _name.size() - 1 && _name[position + 1] == '/') {
            return _name;
        } else {
            return _name.substr(0, position);
        }
    } else {
        return _name;
    }

}

std::string SlvFileMgr::get_file_name_str(const std::string& _path, bool _l_extension) {

    std::string file_name;

    size_t position = _path.find_last_of('/');

    if (position != std::string::npos) {
        position++;
        file_name = _path.substr(position, _path.size() - position);
    } else {
        file_name = _path;
    }

    if (file_name == "..") {
        file_name.clear();
    }

    if (!_l_extension) {
        file_name = remove_extension(file_name);
    }

    return file_name;
}

std::string SlvFileMgr::get_directory_str(const std::string& _path) {

    std::string directory_path;

    std::string file_name = get_file_name_str(_path, true);
    directory_path = _path.substr(0, _path.size() - file_name.size());
    if (!directory_path.empty() && directory_path.back() != '/') {
        directory_path.push_back('/');
    }

    return directory_path;

}

std::string SlvFileMgr::get_path(const SlvDirectory& _directory) {

    if (_directory.is_relative()) {
        return SlvFileMgr::master_relative_path() + _directory.get_path();
    } else {
        return _directory.get_path();
    }

}

std::string SlvFileMgr::get_path(const SlvFile& _file) {

    return get_path(_file.get_directory()) + _file.get_name();

}

bool SlvFileMgr::is_path_relative(const std::string& _path) {

    bool l_relative;
#ifdef OS_WIN
    if (_path.size() >= 2) {
        l_relative = (_path[1] != ':');
    } else {
        l_relative = true;
    }
#else
    if (_path.size() >= 1) {
        l_relative = (_path[0] != '/');
    } else {
        l_relative = true;
    }
#endif
    return l_relative;
}

SlvStatus SlvFileMgr::open_file(std::ofstream& _file_stream, const SlvFile& _file) {

    return open_file(_file_stream, _file, std::ios::out, std::ios::trunc);

}

SlvStatus SlvFileMgr::open_file(std::ifstream& _file_stream, const SlvFile& _file) {

    return open_file(_file_stream, _file, std::ios::in);

}

std::string SlvFileMgr::replace_forbidden_file_characters(const std::string& _string, char _replacement, bool _l_consecutive, bool _l_extension) {

    std::string result = _string;
    for (std::string::iterator it = result.begin(); it != result.end();) {
        if (forbidden_file_characters().find(*it) != std::string::npos || (_l_extension && *it == ' ')) {
            if (std::next(it) != result.end() && (forbidden_file_characters().find(*std::next(it)) != std::string::npos || (_l_extension && *std::next(it) == ' '))) {
                it = result.erase(it);
            } else {
                *it = _replacement;
                ++it;
            }
        } else {
            ++it;
        }
    }
    return result;

}

bool SlvFileMgr::test_file(const SlvFile& _file, std::ios::openmode _io_mode) {

    bool l_opened;
    if (_io_mode == std::ios::in) {

        std::ifstream input_file;
        input_file.open(SlvFileMgr::get_path(_file).c_str(), _io_mode);
        l_opened = input_file.is_open();
        if (l_opened) input_file.close();
        return l_opened;

    } else if (_io_mode == std::ios::out) {

        // An empty directory is considered implicitly as ./
        return (_file.get_directory().get_path().empty() || _file.get_directory().exists()) && !_file.get_file_name().get_total_name().empty();

    } else {
        slv::flag::ISSUE(slv::flag::InvalidArgument, "_io_mode must be either std::ios::in or std::ios::out");
        return false;
    }

}

bool SlvFileMgr::mkdir(const std::string& _subpath, bool _l_force_parents) {

    std::string command = "mkdir ";
#ifndef OS_WIN
    if (_l_force_parents) command += "-p ";
#endif
    if (SlvFileMgr::is_path_relative(_subpath)) {
        command += SlvFileMgr::master_relative_path();
    }
    command += _subpath;
#ifdef OS_WIN
    std::replace(command.begin(), command.end(), '/', '\\');
#endif
    int code = system(command.c_str());

    if (code == 0) {
        return true;
    } else if (code == -1) {
        return false;
    } else {
        return false;
    }

}

