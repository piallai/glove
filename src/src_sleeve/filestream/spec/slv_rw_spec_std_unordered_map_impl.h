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

#include "filestream/spec/slv_rw_spec_std_unordered_map_decl.h"

template <class Tkey, class T>
void slv::rw::writeB(const std::unordered_map<Tkey, T>& _map, std::ofstream& _output_file) {

	slv::rw::writeB((unsigned int)_map.size(), _output_file);
	for (typename std::unordered_map<Tkey, T>::const_iterator it = _map.begin(); it != _map.end(); it++) {

		slv::rw::writeB(it->first, _output_file);
		slv::rw::writeB(it->second, _output_file);
	}

}

template <class Tkey, class T>
bool slv::rw::readB(std::unordered_map<Tkey, T>& _map, std::ifstream& _input_file) {

	_map.clear();
	unsigned int size;
	bool l_read = slv::rw::readB(size, _input_file);
	if (!l_read) size = 0;
	Tkey key;
	T value;
	for (unsigned int i = 0; i < size && l_read; i++) {
		l_read = slv::rw::readB(key, _input_file);
		if (l_read) l_read = slv::rw::readB(value, _input_file);
		_map[key] = value;
	}

	return l_read;
}
