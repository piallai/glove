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

#include <string>

namespace slv {

	/*! Parse \p _string to assign \p _value. Default parsing is using >> operator.*/
	template <class T>
	bool parse(const std::string& _string, T& _value);
	/*! Parse \p _string to assign \p _value.
	* Specialization by direct assignment because >> will parse a string separated by spaces.*/
	bool parse(const std::string& _string, std::string& _value);

}

template <class T>
bool slv::parse(const std::string& _string, T& _value) {

	std::istringstream iss(_string);

	iss >> _value;

	return true;
}

inline bool slv::parse(const std::string& _string, std::string& _value) {

	_value = _string;

	return true;
}

#include "misc/spec/slv_parse_spec_std_vector.h"
#include "misc/spec/slv_parse_spec_std_map.h"
