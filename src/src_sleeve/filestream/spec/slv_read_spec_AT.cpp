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

#include "slv_read_spec_AT.h"

//const std::string end_of_file_str = "end of file";
//const std::string slv::rw::end_of_file_str = "end of file";

template <>
bool slv::rw::readB<int>(int& _dat, std::ifstream& _input_file) {
    if (!_input_file.eof()) {
        _input_file.read((char*)&_dat, sizeof(int));
        return true;
    } else {
        slv::flag::ISSUE(slv::flag::EndOfFile, end_of_file_str());
        return false;
    }
}

template <>
bool slv::rw::readB<unsigned int>(unsigned int& _dat, std::ifstream& _input_file) {
    if (!_input_file.eof()) {
        _input_file.read((char*)&_dat, sizeof(unsigned int));
        return true;
    } else {
        slv::flag::ISSUE(slv::flag::EndOfFile, end_of_file_str());
        return false;
    }
}

template <>
bool slv::rw::readB<long unsigned int>(long unsigned int& _dat, std::ifstream& _input_file) {
    if (!_input_file.eof()) {
        _input_file.read((char*)&_dat, sizeof(long unsigned int));
        return true;
    } else {
        slv::flag::ISSUE(slv::flag::EndOfFile, end_of_file_str());
        return false;
    }
}

template <>
bool slv::rw::readB<unsigned long long>(unsigned long long& _dat, std::ifstream& _input_file) {
    if (!_input_file.eof()) {
        _input_file.read((char*)&_dat, sizeof(unsigned long long));
        return true;
    } else {
        slv::flag::ISSUE(slv::flag::EndOfFile, end_of_file_str());
        return false;
    }
}

template <>
bool slv::rw::readB<float>(float& _dat, std::ifstream& _input_file) {
    if (!_input_file.eof()) {
        _input_file.read((char*)&_dat, sizeof(float));
        return true;
    } else {
        slv::flag::ISSUE(slv::flag::EndOfFile, end_of_file_str());
        return false;
    }
}

template <>
bool slv::rw::readB<double>(double& _dat, std::ifstream& _input_file) {
    if (!_input_file.eof()) {
        _input_file.read((char*)&_dat, sizeof(double));
        return true;
    } else {
        slv::flag::ISSUE(slv::flag::EndOfFile, end_of_file_str());
        return false;
    }
}

template <>
bool slv::rw::readB<bool>(bool& _dat, std::ifstream& _input_file) {
    if (!_input_file.eof()) {
        _input_file.read((char*)&_dat, sizeof(bool));
        return true;
    } else {
        slv::flag::ISSUE(slv::flag::EndOfFile, end_of_file_str());
        return false;
    }
}

template <>
bool slv::rw::readB<char>(char& _dat, std::ifstream& _input_file) {
    if (!_input_file.eof()) {
        _input_file.read((char*)&_dat, sizeof(char));
        return true;
    } else {
        slv::flag::ISSUE(slv::flag::EndOfFile, end_of_file_str());
        return false;
    }
}

template <>
bool slv::rw::readB<unsigned char>(unsigned char& _dat, std::ifstream& _input_file) {
    if (!_input_file.eof()) {
        _input_file.read((char*)&_dat, sizeof(unsigned char));
        return true;
    } else {
        slv::flag::ISSUE(slv::flag::EndOfFile, end_of_file_str());
        return false;
    }
}
