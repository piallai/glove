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

/*! Convenience class to be inherited to provide a direct method to read the instance from a binary file.*/
class SlvReadBinary {

public:

	SlvReadBinary();
	virtual ~SlvReadBinary();

	/*! Set the object by reading the BINARY file at \p _file_path.*/
	SlvStatus read_binary(std::string _file_path);

	/*! Binary read method to implement.*/
	virtual bool readB(std::ifstream& _input_file) = 0;

};
