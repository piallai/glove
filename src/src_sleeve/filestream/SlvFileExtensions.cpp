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

#include "SlvFileExtensions.h"
#include "SlvFile.h"
#include "slv_vector.h"

SlvFileExtensions::SlvFileExtensions() {

}

SlvFileExtensions::SlvFileExtensions(const std::vector<SlvFileExtension>& _extensions) {

    for (std::vector<SlvFileExtension>::const_iterator it = _extensions.begin(); it != _extensions.end(); ++it) {
        add(*it);
    }

}

SlvFileExtensions::~SlvFileExtensions() {

}

const SlvFileExtension& SlvFileExtensions::operator[](int i) const {

    return extensions[i];

}

const std::vector<SlvFileExtension>& SlvFileExtensions::get() const {
    return extensions;
}

void SlvFileExtensions::add(const SlvFileExtension& _extension) {
    if (!slv::vector::find(_extension, extensions)) {
        extensions.push_back(_extension);
    }
}

void SlvFileExtensions::add_front(const SlvFileExtension& _extension) {
    std::vector<SlvFileExtension>::iterator it = std::find(extensions.begin(), extensions.end(), _extension);
    if (it != extensions.end()) {
        extensions.erase(it);
    }
    extensions.insert(extensions.begin(), _extension);
}

void SlvFileExtensions::remove(const SlvFileExtension& _extension) {

    slv::vector::remove(_extension, extensions);

}

bool SlvFileExtensions::exists(const SlvFileExtension& _extension) const {

    return slv::vector::find(_extension, extensions);

}

bool SlvFileExtensions::empty() const {

    return extensions.empty();

}

bool SlvFileExtensions::operator==(const SlvFileExtensions& _file_extensions) const {

    return extensions == _file_extensions.extensions;
}
