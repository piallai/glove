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

#include <string>

namespace slv {

	/*! Parse \p _string to assign \p _value. Default parsing is using >> operator.*/
	template <class T>
	void parse(const std::string& _string, T& _value);
	/*! Parse \p _string to assign \p _value.
	* Specialization by direct assignment because >> will parse a string separated by spaces.*/
	void parse(const std::string& _string, std::string& _value);
}

template <class T>
void slv::parse(const std::string& _string, T& _value) {

	std::istringstream iss(_string);

	iss >> _value;

}

inline void slv::parse(const std::string& _string, std::string& _value) {

	_value = _string;

}
