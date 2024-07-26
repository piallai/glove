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

#include "slv_rw_spec_QVector.h"

//specialized with double because "Function template partial specialization is not allowed ..."
template <>
void slv::rw::writeB< QVector<double> >(const QVector<double>& _vector, std::ofstream& _output_file) {

    slv::rw::writeB(std::vector<double>(_vector.begin(), _vector.end()), _output_file);
}

template <>
bool slv::rw::readB< QVector<double> >(QVector<double>& _vector, std::ifstream& _input_file) {

    std::vector<double> _std_vector;
    bool l_read = slv::rw::readB(_std_vector, _input_file);
    _vector = QVector<double>(_std_vector.begin(), _std_vector.end());
    return l_read;

}
