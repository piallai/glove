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
#include "std_vector.h"
#include "slv_vector.h"
#include "SlvLabeling.h"
#include "slv_flag.h"
#include "SlvMacrosDeclarations.h"

/*! This class is a sort of std::map, with "factory" features.
Tvalue must inherit SlvLabeling<Tlabel>, with Tlabel being the 'key'.
Therefore, unlike std::map, the key (Tlabel) is owned by Tvalue.
The instance owns the elements (no shared pointer).*/
template <class Tvalue, class Tlabel = typename Tvalue::Tlabeling>
class SlvPool : virtual public SlvOS {

private:

	std::vector<Tvalue*> elements;

public:

	SlvPool();
	SlvPool(const SlvPool<Tvalue, Tlabel>& _pool);
	~SlvPool();

	/*! Clear the instance. Delete owned elements.*/
	void clear();

	typedef typename std::vector<Tvalue*>::const_iterator const_iterator;
	/*! Iterator to the first element.*/
	const_iterator begin() const;
	/*! Iterator to the last element.*/
	const_iterator end() const;

	typedef typename std::vector<Tvalue*>::iterator iterator;
	/*! Iterator to the first element.*/
	iterator begin();
	/*! Iterator to the last element.*/
	iterator end();

	/*! Create and delete elements to match \p _pool.*/
	SlvPool<Tvalue, Tlabel>& operator=(const SlvPool<Tvalue, Tlabel>& _pool);

	/*! Get number of elements. Size of the pool.*/
	unsigned int psize() const;

	/*! Add an element created externally.
	* Checks if an element with the same label already exists.
	* The pool instance will own the element (possible deletion).*/
	bool add(Tvalue* _element);

	/*! Get the element which label is equal to \p _label.
	* Return NULL if not found.
	* Template label argument for flexibility in the == operator.*/
	template <class Tlabel2>
	const Tvalue* get(const Tlabel2& _label) const;
	/*! Get the element which label is equal to \p _label.
	* Return NULL if not found.
	* Template label argument for flexibility in the == operator.*/
	template <class Tlabel2>
	Tvalue* get(const Tlabel2& _label);

	/*! Get vector of elements.*/
	const std::vector<Tvalue*>& get_elements() const;

	/*! Create and return an element labelled \p _label.
	* If an element with this _label already exists, returns it.*/
	Tvalue* new_element(const Tlabel& _label);
	/*! Delete element labelled \p _label.
	* Template label argument for flexibility in the == operator.*/
	template <class Tlabel2>
	bool delete_element(const Tlabel2& _label);
	/*! Delete element which label is the same as the one of \p _element.
	* If \p _l_owned is true, delete only if _element is part of the pool.
	* Ambiguous if Tlabel is the same type as Tvalue*. Unlikely though.*/
	template <class Tvalue2>
	bool delete_element(Tvalue2* _element, bool _l_owned = true);
	/*! Delete element at index \p el.
	* _at suffix for disambiguation with Tlabel/Tvalue */
	bool delete_element_at(const unsigned int el);

	/*! Returns the elements index where the element with label \p _label is located.
	* Returns -1 if \p _label is not found.
	* Template label argument for flexibility in the == operator.*/
	template <class Tlabel2>
	unsigned int get_n(const Tlabel2& _label) const;

	/* Returns the iterator of element which label is \p _label.
	* If not found, returns end().*/
	template <class Tlabel2>
	iterator find(const Tlabel2& _label);
	/* Returns the iterator of element which label is \p _label.
	* If not found, returns end().*/
	template <class Tlabel2>
	const_iterator find(const Tlabel2& _label) const;

	/*! Get element at index \p el.*/
	Tvalue* operator[](const unsigned int el);
	/*! Get element at index \p el.*/
	const Tvalue* operator[](const unsigned int el) const;

protected:

	void ostream(std::ostream& _os) const;

};

#include "slv_vector.h"

template <class Tvalue, class Tlabel>
SlvPool<Tvalue, Tlabel>::SlvPool() {

}

template <class Tvalue, class Tlabel>
SlvPool<Tvalue, Tlabel>::SlvPool(const SlvPool<Tvalue, Tlabel>& _pool) {

	*this = _pool;

}

template <class Tvalue, class Tlabel>
SlvPool<Tvalue, Tlabel>::~SlvPool() {

	clear();

}

template <class Tvalue, class Tlabel>
void SlvPool<Tvalue, Tlabel>::clear() {

	for (iterator it = begin(); it != end(); ++it) {
		delete* it;
	}
	elements.clear();

}

template <class Tvalue, class Tlabel>
typename SlvPool<Tvalue, Tlabel>::const_iterator SlvPool<Tvalue, Tlabel>::begin() const {

	return elements.begin();

}

template <class Tvalue, class Tlabel>
typename SlvPool<Tvalue, Tlabel>::const_iterator SlvPool<Tvalue, Tlabel>::end() const {

	return elements.end();

}

template <class Tvalue, class Tlabel>
typename SlvPool<Tvalue, Tlabel>::iterator SlvPool<Tvalue, Tlabel>::begin() {

	return elements.begin();

}

template <class Tvalue, class Tlabel>
typename SlvPool<Tvalue, Tlabel>::iterator SlvPool<Tvalue, Tlabel>::end() {

	return elements.end();

}

template <class Tvalue, class Tlabel>
SlvPool<Tvalue, Tlabel>& SlvPool<Tvalue, Tlabel>::operator=(const SlvPool<Tvalue, Tlabel>& _pool) {

	clear();

	for (const_iterator it = _pool.elements.begin(); it != _pool.elements.end(); ++it) {
		(*new_element(static_cast<const SlvLabeling<Tlabel>*>(*it)->get_label())) = **it;
	}

	return *this;
}

template <class Tvalue, class Tlabel>
unsigned int SlvPool<Tvalue, Tlabel>::psize() const {

	return (unsigned int)elements.size();

}

template <class Tvalue, class Tlabel>
bool SlvPool<Tvalue, Tlabel>::add(Tvalue* _element) {

	// Static cast to prevent get_label shadowing
	if (!get(static_cast<const SlvLabeling<Tlabel>*>(_element)->get_label())) {
		elements.push_back(_element);
		return true;
	} else {
		slv::flag::ISSUE(slv::flag::FlagType::Warning, "Can not add the element ", *_element, " in the pool, an element with the same label ", static_cast<const SlvLabeling<Tlabel>*>(_element)->get_label(), " already exists");
		return false;
	}

}

template <class Tvalue, class Tlabel>
template <class Tlabel2>
Tvalue* SlvPool<Tvalue, Tlabel>::get(const Tlabel2& _label) {

	iterator it = find(_label);
	if (it != end()) {
		return *it;
	} else {
		return NULL;
	}

}



template <class Tvalue, class Tlabel>
template <class Tlabel2>
const Tvalue* SlvPool<Tvalue, Tlabel>::get(const Tlabel2& _label) const {

	return const_cast<SlvPool<Tvalue, Tlabel>*>(this)->get(_label);

}

template <class Tvalue, class Tlabel>
template <class Tlabel2>
unsigned int SlvPool<Tvalue, Tlabel>::get_n(const Tlabel2& _label) const {

	const_iterator it = find(_label);

	if (it != end()) {
		return std::distance(begin(), it);
	} else {
		return -1;
	}

}

template <class Tvalue, class Tlabel>
const std::vector<Tvalue*>& SlvPool<Tvalue, Tlabel>::get_elements() const {
	return elements;
}

template <class Tvalue, class Tlabel>
Tvalue* SlvPool<Tvalue, Tlabel>::new_element(const Tlabel& _label) {

	Tvalue* value = get(_label);
	if (!value) {
		value = new Tvalue(_label);
		elements.push_back(value);
	} else {
		slv::flag::ISSUE(slv::flag::FlagType::Warning, "Can not create the element ", *value, " in the pool, an element with the same label ", value->get_label(), " already exists");
	}

	return value;
}

template <class Tvalue, class Tlabel>
template <class Tlabel2>
bool SlvPool<Tvalue, Tlabel>::delete_element(const Tlabel2& _label) {

	iterator it = find(_label);
	if (it != end()) {
		delete* it;
		elements.erase(it);
		return true;
	} else {
		slv::flag::ISSUE(slv::flag::FlagType::Warning, "Can not delete. The element labelled ", _label, " does not exist.");
		return false;
	}

}

template <class Tvalue, class Tlabel>
template <class Tvalue2>
bool SlvPool<Tvalue, Tlabel>::delete_element(Tvalue2* _element, bool _l_owned) {

	if (!_l_owned || slv::vector::find(static_cast<Tvalue*>(_element), elements)) {
		return delete_element(_element->get_label());
	} else {
		return false;
	}

}

template <class Tvalue, class Tlabel>
bool SlvPool<Tvalue, Tlabel>::delete_element_at(const unsigned int el) {

	if (el < psize()) {
		delete elements[el];
		elements.erase(elements.begin() + el);
		return true;
	} else {
		return false;
	}

}

template <class Tvalue, class Tlabel>
template <class Tlabel2>
typename SlvPool<Tvalue, Tlabel>::iterator SlvPool<Tvalue, Tlabel>::find(const Tlabel2& _label) {

	bool l_found = false;
	iterator it = begin();
	while (it != end() && !l_found) {
		l_found = (static_cast<const SlvLabeling<Tlabel>*>(*it)->get_label() == _label);
		if (!l_found) ++it;
	}

	return it;

}

template <class Tvalue, class Tlabel>
template <class Tlabel2>
typename SlvPool<Tvalue, Tlabel>::const_iterator SlvPool<Tvalue, Tlabel>::find(const Tlabel2& _label) const {

	bool l_found = false;
	const_iterator it = begin();
	while (it != end() && !l_found) {
		l_found = (static_cast<const SlvLabeling<Tlabel>*>(*it)->get_label() == _label);
		if (l_found) ++it;
	}

	return it;

}

template <class Tvalue, class Tlabel>
Tvalue* SlvPool<Tvalue, Tlabel>::operator[](const unsigned int el) {
	return elements[el];
}

template <class Tvalue, class Tlabel>
const Tvalue* SlvPool<Tvalue, Tlabel>::operator[](const unsigned int el) const {
	return elements[el];
}

template <class Tvalue, class Tlabel>
void SlvPool<Tvalue, Tlabel>::ostream(std::ostream& _os) const {

	for (const_iterator it = begin(); it != end(); ++it) {
		_os << **it << ", " << (*it)->get_label() << std::endl;
	}

}
