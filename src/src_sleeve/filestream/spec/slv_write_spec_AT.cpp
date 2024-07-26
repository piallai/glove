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

#include "filestream/spec/slv_write_spec_AT.h"

template <>
void slv::rw::writeB<int>(const int& _dat, std::ofstream& _output_file) {
    _output_file.write((char*)&_dat, sizeof(int));
}

template <>
void slv::rw::writeB<unsigned int>(const unsigned int& _dat, std::ofstream& _output_file) {
    _output_file.write((char*)&_dat, sizeof(unsigned int));
}

template <>
void slv::rw::writeB<long unsigned int>(const long unsigned int& _dat, std::ofstream& _output_file) {
    _output_file.write((char*)&_dat, sizeof(long unsigned int));
}

template <>
void slv::rw::writeB<unsigned long long>(const unsigned long long& _dat, std::ofstream& _output_file) {
    _output_file.write((char*)&_dat, sizeof(unsigned long long));
}

template <>
void slv::rw::writeB<float>(const float& _dat, std::ofstream& _output_file) {
    _output_file.write((char*)&_dat, sizeof(float));
}

template <>
void slv::rw::writeB<double>(const double& _dat, std::ofstream& _output_file) {
    _output_file.write((char*)&_dat, sizeof(double));
}

template <>
void slv::rw::writeB<bool>(const bool& _dat, std::ofstream& _output_file) {
    _output_file.write((char*)&_dat, sizeof(bool));
}

template <>
void slv::rw::writeB<char>(const char& _dat, std::ofstream& _output_file) {
    _output_file.write((char*)&_dat, sizeof(char));
}

template <>
void slv::rw::writeB<unsigned char>(const unsigned char& _dat, std::ofstream& _output_file) {
    _output_file.write((char*)&_dat, sizeof(unsigned char));
}
