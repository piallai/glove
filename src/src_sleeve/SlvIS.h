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

#include <istream>

/*! Class to be inherited to provide file input stream.*/
class SlvIS {

public:

	SlvIS();
	virtual ~SlvIS();

	friend std::istream& operator>>(std::istream& _is, SlvIS& _IS);

protected:

	/*! Input stream method to reimplement.*/
	virtual void istream(std::istream& _is) = 0;

};
