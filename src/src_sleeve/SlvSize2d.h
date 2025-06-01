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
class SlvSize2d : public SlvIOS {

public:

	T width;
	T height;

	SlvSize2d(T _width = T(), T _height = T());

	bool operator==(const SlvSize2d<T>& _size) const;

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

template <class T>
SlvSize2d<T>::SlvSize2d(T _width, T _height) {

	width = _width;
	height = _height;

}

template <class T>
bool SlvSize2d<T>::operator==(const SlvSize2d<T>& _size) const {

	return width == _size.width && height == _size.height;

}

template <class T>
bool SlvSize2d<T>::readB(std::ifstream& _input_file) {

    bool l_read = slv::rw::readB(width, _input_file);
    if (l_read) l_read = slv::rw::readB(height, _input_file);
    return l_read;

}

template <class T>
void SlvSize2d<T>::writeB(std::ofstream& _output_file) const {

    slv::rw::writeB(width, _output_file);
    slv::rw::writeB(height, _output_file);
}

template <class T>
void SlvSize2d<T>::istream(std::istream& _is) {

    std::string size_str;
    _is >> size_str;

	slv::parse(size_str, *this);

}

template <class T>
void SlvSize2d<T>::ostream(std::ostream& _os) const {

    _os << width << "x" << height;

}

#if OPTION_USE_THIRDPARTY_JSON==1
template <class T>
void SlvSize2d<T>::writeJson(nlohmann::json& _json) const {

	slv::rw::json::writeJson(width, _json["width"]);
	slv::rw::json::writeJson(height, _json["height"]);

}

template <class T>
SlvStatus SlvSize2d<T>::readJson(const nlohmann::json& _json) {

	SlvStatus status = slv::rw::json::readJson(width, "width", _json);
	status += slv::rw::json::readJson(height, "height", _json);

	return status;
}
#endif


namespace slv {
    /*! Parse \p _string to assign \p _size. Reciprocal to << operator.*/
    template <class T>
    bool parse(const std::string& _string, SlvSize2d<T>& _size);
}

#include "misc/slv_parse.h"

template <class T>
bool slv::parse(const std::string& _string, SlvSize2d<T>& _size) {

    bool l_parsing_ok = true;

    size_t pos = _string.find('x');
    if (pos != std::string::npos) {
        l_parsing_ok = slv::parse(_string.substr(0, pos), _size.width);
        l_parsing_ok &= slv::parse(_string.substr(pos + 1), _size.height);
    } else {
        l_parsing_ok = false;
		std::cout << "Parsing issue for type " << SlvDataName<SlvSize2d<T>>::name() << " and for string " << _string << std::endl;
    }

    return l_parsing_ok;
}
