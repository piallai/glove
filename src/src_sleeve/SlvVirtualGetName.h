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

/*! Class allowing to access the name of instance when the type is not known.
* Usefull for templated parametrizations to redirect pure virtual get_name() to base parametrization's.
* Usefull to be inherited by classes having a static name, defined by macro staticGetVariable.*/
class SlvVirtualGetName {

public:
    SlvVirtualGetName() {}
    virtual ~SlvVirtualGetName() {}
    /*! Get name of the instance.*/
    virtual const std::string& get_name() const = 0;
};
