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

#include "SlvIOS.h"
#include "GloveOptions.h"
#if OPTION_USE_THIRDPARTY_JSON==1
#include "json.hpp"
#include "SlvStatus.h"
#endif

template <class T>
class SlvSides2d : public SlvIOS {

public:

	T left;
	T right;
	T up;
	T bottom;

	SlvSides2d(T _left = T(), T _right = T(), T _up = T(), T _bottom = T());

	bool operator==(const SlvSides2d<T>& _sides) const;

	bool readB(std::ifstream& _input_file);
	void writeB(std::ofstream& _output_file) const;

#if OPTION_USE_THIRDPARTY_JSON==1
	void writeJson(nlohmann::json& _json) const;
	SlvStatus readJson(const nlohmann::json& _json);
#endif

private:

	void istream(std::istream& _is);
	void ostream(std::ostream& _os) const;

};

#include "filestream/slv_rw.h"
#include "filestream/slv_rw_json.h"
#include "iostream/spec/iostream_spec_std_array.h"

template <class T>
SlvSides2d<T>::SlvSides2d(T _left, T _right, T _up, T _bottom) {

	left = _left;
	right = _right;
	up = _up;
	bottom = _bottom;

}

template <class T>
bool SlvSides2d<T>::operator==(const SlvSides2d<T>& _size) const {

	return left == _size.left && right == _size.right && up == _size.up && bottom == _size.bottom;

}

template <class T>
bool SlvSides2d<T>::readB(std::ifstream& _input_file) {

    bool l_read = slv::rw::readB(left, _input_file);
    if (l_read) l_read = slv::rw::readB(right, _input_file);
    if (l_read) l_read = slv::rw::readB(up, _input_file);
    if (l_read) l_read = slv::rw::readB(bottom, _input_file);
    return l_read;

}

template <class T>
void SlvSides2d<T>::writeB(std::ofstream& _output_file) const {

    slv::rw::writeB(left, _output_file);
    slv::rw::writeB(right, _output_file);
    slv::rw::writeB(up, _output_file);
    slv::rw::writeB(bottom, _output_file);
}

template <class T>
void SlvSides2d<T>::istream(std::istream& _is) {
	
	std::array<T, 4> array;
	_is >> array;
	left = array[0];
	right = array[1];
	up = array[2];
	bottom = array[3];

}

template <class T>
void SlvSides2d<T>::ostream(std::ostream& _os) const {

	std::array<T, 4> array;
	array[0] = left;
	array[1] = right;
	array[2] = up;
	array[3] = bottom;
	_os << array;

}

#if OPTION_USE_THIRDPARTY_JSON==1
template <class T>
void SlvSides2d<T>::writeJson(nlohmann::json& _json) const {

	slv::rw::json::writeJson(left, _json["left"]);
	slv::rw::json::writeJson(right, _json["right"]);
	slv::rw::json::writeJson(up, _json["up"]);
	slv::rw::json::writeJson(bottom, _json["bottom"]);

}

template <class T>
SlvStatus SlvSides2d<T>::readJson(const nlohmann::json& _json) {

	SlvStatus status = slv::rw::json::readJson(left, "left", _json);
	status += slv::rw::json::readJson(right, "right", _json);
	status += slv::rw::json::readJson(up, "up", _json);
	status += slv::rw::json::readJson(bottom, "bottom", _json);

	return status;
}
#endif


namespace slv {
	/*! Parse \p _string to assign \p _sides. Reciprocal to << operator.*/
	template <class T>
	bool parse(const std::string& _string, SlvSides2d<T>& _sides);
}

#include "misc/spec/slv_parse_spec_std_array.h"

template <class T>
bool slv::parse(const std::string& _string, SlvSides2d<T>& _sides) {

	bool l_parsing_ok = true;

	std::array<T, 4> array;
	l_parsing_ok = slv::parse(_string, array);
	if (l_parsing_ok) {
		_sides.left = array[0];
		_sides.right = array[1];
		_sides.up = array[2];
		_sides.bottom = array[3];
	}

	return l_parsing_ok;
}
