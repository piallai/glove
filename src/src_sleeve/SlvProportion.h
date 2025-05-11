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

/*! Class managing a value ranging in [0, 1].*/
class SlvProportion : public SlvIOS {

public:

    typedef double Tvalue;

private:

    Tvalue value;

public:

    SlvProportion(Tvalue _value = 0.);
    ~SlvProportion();

    /*! Cast SlvProportion to value type.*/
    operator Tvalue() const;

    /*! Assign a \p _value to the instance.*/
    SlvProportion& operator=(const Tvalue& _value);

    bool readB(std::ifstream& _input_file);
    void writeB(std::ofstream& _output_file) const;

private:

    void istream(std::istream& _is);
    void ostream(std::ostream& _os) const;

};
