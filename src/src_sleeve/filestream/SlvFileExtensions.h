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

#include "std_vector.h"
#include "SlvFileTypedefs.h"

/*! Just a class containing file extensions as strings.*/
class SlvFileExtensions {
private:
    std::vector<SlvFileExtension> extensions;

public:
    SlvFileExtensions();
    SlvFileExtensions(const std::vector<SlvFileExtension>& _extensions);
    ~SlvFileExtensions();

    const SlvFileExtension& operator[](int i) const;

    /*! Return true if \p _extension exits among the instance extensions.*/
    bool exists(const SlvFileExtension& _extension) const;

    /*! Get extensions.*/
    const std::vector<SlvFileExtension>& get() const;
    /*! Add an extension.*/
    void add(const SlvFileExtension& _extension);
    /*! Add an extension, first in the list.*/
    void add_front(const SlvFileExtension& _extension);
    /*! Remove an extension.*/
    void remove(const SlvFileExtension& _extension);

    /*! Whether the instance contains extensions or not.*/
    bool empty() const;

    bool operator==(const SlvFileExtensions& _file_extensions) const;

};

