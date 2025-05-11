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

#include "filestream/spec/slv_rw_spec_std_vector.h"

bool slv::rw::readB(std::vector<bool>& _vector, std::ifstream& _input_file) {

    _vector.clear();

    unsigned int vector_size;
    bool l_read = slv::rw::readB(vector_size, _input_file);

    std::vector<unsigned char> char_vector;
    if (l_read) l_read = slv::rw::readB(char_vector, _input_file);

    unsigned int N = 8;
    bool l_temp;
    unsigned int c, j, i;

    i = 0;
    for (c = 0; c < char_vector.size(); c++) {
        for (j = 0; j < N; j++) {
            if (i < vector_size) {
                l_temp = char_vector[c] & (1 << j);
                _vector.push_back(l_temp);
            }
            i++;
        }
    }

    return l_read;
}

void slv::rw::writeB(const std::vector<bool>& _vector, std::ofstream& _output_file) {

    unsigned int vector_size = (unsigned int)_vector.size();
    slv::rw::writeB(vector_size, _output_file);

    std::vector<unsigned char> char_vector;

    unsigned int N = 8;
    unsigned int c = 0;

    unsigned int i, j, ipj;

    for (i = 0; i < vector_size;) {

        char_vector.push_back(0);

        for (j = 0; j < N; j++) {

            ipj = i;
            ipj += j;

            if (ipj < vector_size) {
                char_vector[c] = char_vector[c] | (_vector[ipj] << j);
            }

        }
        c++;
        i += N;

    }

    slv::rw::writeB(char_vector, _output_file);

}
