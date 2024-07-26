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

#include "SlvIOS.h"
#include "filestream/slv_rw.h"

/*! SAME AS std::pair.
Combos are compared according to their value for inf/sup operators.
Combos are compared according to their data for equal/different operators.*/
template <class Tdata, class Tvalue>
class SlvCombo : public SlvIOS {

public:

	Tdata data;
	Tvalue value;

	SlvCombo();
	SlvCombo(const Tdata& _data, const Tvalue& _value);
	~SlvCombo();

	////////////////////
	//comparable data
	////////////////////
	bool operator==(const SlvCombo<Tdata, Tvalue>& _combo) const;
	bool operator!=(const SlvCombo<Tdata, Tvalue>& _combo) const;
	////////////////////

	////////////////////
	//comparable value
	////////////////////
	bool operator>(const SlvCombo<Tdata, Tvalue>& _combo) const;
	bool operator>(const Tvalue& _value) const;
	bool operator<(const SlvCombo<Tdata, Tvalue>& _combo) const;
	bool operator<(const Tvalue& _value) const;
	bool operator>=(const SlvCombo<Tdata, Tvalue>& _combo) const;
	bool operator>=(const Tvalue& _value) const;
	bool operator<=(const SlvCombo<Tdata, Tvalue>& _combo) const;
	bool operator<=(const Tvalue& _value) const;

	Tvalue operator-(const SlvCombo<Tdata, Tvalue>& _combo) const;
	Tvalue operator+(const SlvCombo<Tdata, Tvalue>& _combo) const;

	void writeB(std::ofstream& _output_file) const;
	bool readB(std::ifstream& _input_file);

private:

	void ostream(std::ostream& _os) const;
	void istream(std::istream& _is);

};

template <class Tdata, class Tvalue>
SlvCombo<Tdata, Tvalue>::SlvCombo() {

}

template <class Tdata, class Tvalue>
SlvCombo<Tdata, Tvalue>::SlvCombo(const Tdata& _data, const Tvalue& _value) {
	data = _data;
	value = _value;
}

template <class Tdata, class Tvalue>
SlvCombo<Tdata, Tvalue>::~SlvCombo() {

}

template <class Tdata, class Tvalue>
bool SlvCombo<Tdata, Tvalue>::operator==(const SlvCombo<Tdata, Tvalue>& _combo) const {
	//for slv::vector::remove for instance
	return data == _combo.data;
}

template <class Tdata, class Tvalue>
bool SlvCombo<Tdata, Tvalue>::operator!=(const SlvCombo<Tdata, Tvalue>& _combo) const {
	return !(*this == _combo);
}

template <class Tdata, class Tvalue>
bool SlvCombo<Tdata, Tvalue>::operator>(const SlvCombo<Tdata, Tvalue>& _combo) const {
	return value > _combo.value;
}

template <class Tdata, class Tvalue>
bool SlvCombo<Tdata, Tvalue>::operator>(const Tvalue& _value) const {
	return value > _value;
}

template <class Tdata, class Tvalue>
bool SlvCombo<Tdata, Tvalue>::operator<(const SlvCombo<Tdata, Tvalue>& _combo) const {
	return value < _combo.value;
}

template <class Tdata, class Tvalue>
bool SlvCombo<Tdata, Tvalue>::operator<(const Tvalue& _value) const {
	return value < _value;
}

template <class Tdata, class Tvalue>
bool SlvCombo<Tdata, Tvalue>::operator>=(const SlvCombo<Tdata, Tvalue>& _combo) const {
	return value >= _combo.value;
}

template <class Tdata, class Tvalue>
bool SlvCombo<Tdata, Tvalue>::operator>=(const Tvalue& _value) const {
	return value >= _value;
}

template <class Tdata, class Tvalue>
bool SlvCombo<Tdata, Tvalue>::operator<=(const SlvCombo<Tdata, Tvalue>& _combo) const {
	return value <= _combo.value;
}

template <class Tdata, class Tvalue>
bool SlvCombo<Tdata, Tvalue>::operator<=(const Tvalue& _value) const {
	return value <= _value;
}

template <class Tdata, class Tvalue>
Tvalue SlvCombo<Tdata, Tvalue>::operator-(const SlvCombo<Tdata, Tvalue>& _combo) const {
	return Tvalue(value - _combo.value);//constructor called here for enum managmenet
}

template <class Tdata, class Tvalue>
Tvalue SlvCombo<Tdata, Tvalue>::operator+(const SlvCombo<Tdata, Tvalue>& _combo) const {
	return Tvalue(value + _combo.value);
}

template <class Tdata, class Tvalue>
void SlvCombo<Tdata, Tvalue>::writeB(std::ofstream& _output_file) const {

	slv::rw::writeB(data, _output_file);
	slv::rw::writeB(value, _output_file);

}

template <class Tdata, class Tvalue>
void SlvCombo<Tdata, Tvalue>::ostream(std::ostream& _os) const {

	_os << '{' << data << ", " << value << '}';
}

template <class Tdata, class Tvalue>
bool SlvCombo<Tdata, Tvalue>::readB(std::ifstream& _input_file) {

	bool l_read = slv::rw::readB(data, _input_file);
	if (l_read) l_read = slv::rw::readB(value, _input_file);
	return l_read;
}

template <class Tdata, class Tvalue>
void SlvCombo<Tdata, Tvalue>::istream(std::istream& _is) {

	_is >> data;
	_is >> value;
}
