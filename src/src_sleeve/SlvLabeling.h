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

#include "SlvOS.h"

/*! Label class for unicity check. Mostly used to be inherited. Allows labeling of the child class with template type Tlabel.
* The label is not supposed to change after instantation.*/
template <class Tlabel>
class SlvLabeling : virtual public SlvOS {

public:

	typedef Tlabel Tlabeling;

private:

	const Tlabel label;

public:

	SlvLabeling(const Tlabel& _label);
	~SlvLabeling();

	/*! Get label value.*/
	const Tlabel& get_label() const;

protected:

	void ostream(std::ostream& _os) const;

};

template <class Tlabel>
SlvLabeling<Tlabel>::SlvLabeling(const Tlabel& _label) :label(_label) {

}

template <class Tlabel>
SlvLabeling<Tlabel>::~SlvLabeling() {

}

template <class Tlabel>
const Tlabel& SlvLabeling<Tlabel>::get_label() const {
	return label;
}

template <class Tlabel>
void SlvLabeling<Tlabel>::ostream(std::ostream& _os) const {

	_os << "SlvLabeling: " << label << std::endl;
}
