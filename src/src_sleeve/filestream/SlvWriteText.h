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
#include "SlvOFS.h"

/*! Convenience class to be inherited to provide a direct method to write the instance into a text file.*/
class SlvWriteText : public SlvOFS {

public:

	SlvWriteText();
	virtual ~SlvWriteText();

	/*! Export the object by writing the TEXT file (Clear writing) at \p _file_path.
	* Uses operator<<.*/
	SlvStatus write_text(std::string _file_path, std::ios::openmode _position = std::ios::trunc) const;

};
