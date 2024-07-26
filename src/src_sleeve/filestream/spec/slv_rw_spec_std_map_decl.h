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

#include "std_map.h"
#include "filestream/slv_rw.h"

namespace slv {
	namespace rw {
		template <class Tkey, class T>
		void writeB(const std::map<Tkey, T>& _map, std::ofstream& _output_file);
		template <class Tkey, class T>
		bool readB(std::map<Tkey, T>& _map, std::ifstream& _input_file);
	}
}
