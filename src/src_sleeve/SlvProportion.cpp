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

#include "SlvProportion.h"
#include "filestream/slv_rw.h"

SlvProportion::SlvProportion(Tvalue _value) {
    *this = _value;
}

SlvProportion::~SlvProportion() {

}

SlvProportion::operator Tvalue() const {

    return value;
}

SlvProportion& SlvProportion::operator=(const Tvalue& _value) {

    if (_value < 0. || _value > 1.) {
        slv::flag::ISSUE(slv::flag::FlagType::Warning, "can't set SlvProportion with value : ", _value);
    }

    value = std::max(0., std::min(1., _value));

    return *this;
}

bool SlvProportion::readB(std::ifstream& _input_file) {

    return slv::rw::readB(value, _input_file);
}

void SlvProportion::writeB(std::ofstream& _output_file) const {

    slv::rw::writeB(value, _output_file);
}

void SlvProportion::istream(std::istream& _is) {

    std::string tmp;
    _is >> tmp;

    try {
        value = std::stod(tmp);
        value /= 100.;
    } catch (const std::invalid_argument&) {
        
    }
    
}

void SlvProportion::ostream(std::ostream& _os) const {

    _os << value * 100. << "%";
}