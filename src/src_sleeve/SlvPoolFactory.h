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

#include "SlvPool.h"

/*! Same as SlvPool, but get method creates the element if not found.
* This auto get function only work if Tvalue has a constructor taking only Tlabel as argument. Otherwise, use SlvPool.*/
template <class Tvalue, class Tlabel>
class SlvPoolFactory : public SlvPool<Tvalue, Tlabel> {

public:

	SlvPoolFactory();
	~SlvPoolFactory();

	/*! Get the element which label is equal to \p _label.
	* Creates the element if \p _label is not found.*/
	const Tvalue* get(const Tlabel& _label) const;
	/*! Get the element which label is equal to \p _label.
	* Creates the element if \p _label is not found.*/
	Tvalue* get(const Tlabel& _label);

};

template <class Tvalue, class Tlabel>
SlvPoolFactory<Tvalue, Tlabel>::SlvPoolFactory() :SlvPool<Tvalue, Tlabel>() {

}

template <class Tvalue, class Tlabel>
SlvPoolFactory<Tvalue, Tlabel>::~SlvPoolFactory() {

}

template <class Tvalue, class Tlabel>
const Tvalue* SlvPoolFactory<Tvalue, Tlabel>::get(const Tlabel& _label) const {

	return const_cast<SlvPoolFactory<Tvalue, Tlabel>*>(this)->get(_label);

}

template <class Tvalue, class Tlabel>
Tvalue* SlvPoolFactory<Tvalue, Tlabel>::get(const Tlabel& _label) {

	Tvalue* element = SlvPool< Tvalue, Tlabel >::get(_label);
	if (!element) {
		element = this->new_element(_label);
	}

	return element;

}
