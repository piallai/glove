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

#include "SlvWriteBinary.h"

/*! Convenience class to manage file writing by using automatically the name of the instance.
* Tname_class must have the method std::string get_name().*/
template <class Tname_class>
class SlvWriteBinaryNamedT : virtual public SlvWriteBinary, public Tname_class {

public:

	SlvWriteBinaryNamedT(std::string _name = "") :Tname_class(_name) {}
	~SlvWriteBinaryNamedT() {}

	/*! Write the instance in a file named after the instance's name.
	* \p _prefix_path can be set so that the path will be such as \p _prefix_path + get_name()*/
	SlvStatus write_binary_auto(std::string _prefix_path = "", std::ios::openmode _position = std::ios::trunc) const;

};

template <class Tname_class>
SlvStatus SlvWriteBinaryNamedT<Tname_class>::write_binary_auto(std::string _prefix, std::ios::openmode _position) const {

	return SlvWriteBinary::write_binary(_prefix + Tname_class::get_name(), _position);

}


#include "SlvLblName.h"
/*! Convenience class.*/
typedef SlvWriteBinaryNamedT<SlvLblName> SlvWriteBinaryLblNamed;

#include "SlvName.h"
/*! Convenience class.*/
typedef SlvWriteBinaryNamedT<SlvName> SlvWriteBinaryNamed;
