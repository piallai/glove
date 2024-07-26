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

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "SlvLabeling.h"
#else
#include "glove.h"
#endif

struct Element : public SlvLabeling<int> {
    std::string value;
    Element(int _label = 0) :SlvLabeling(_label) {}
    Element& operator=(const Element& _element) {
        value = _element.value;
        return *this;
    }

    friend std::istream& operator>>(std::istream& _is, Element& _element) {
        _is >> _element.value;
        return _is;
    }

private:
    void ostream(std::ostream& _os) const {
        _os << value;
    }
};
