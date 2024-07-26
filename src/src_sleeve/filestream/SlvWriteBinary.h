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

#include "SlvStatus.h"
#include <fstream>

/*! Convenience class to be inherited to provide a direct method to write the instance into a binary file.*/
class SlvWriteBinary {

public:

	SlvWriteBinary();
	virtual ~SlvWriteBinary();

	/*! Export the object by writing the BINARY file at \p _file_path.*/
	SlvStatus write_binary(std::string _file_path, std::ios::openmode _position = std::ios::trunc) const;

	/*! Binary write method to implement.*/
	virtual void writeB(std::ofstream& _output_file) const = 0;

};
