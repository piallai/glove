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

#define VECTOR_EXPLICIT_ALGORITHM 0 //Explicit reimplementation of algorithms

namespace slv {

    /*! Methods related to manipulation of std::vector which is by default std::vector. See OPTION_STD_VECTOR_DEBUG.*/
    namespace vector {

        /*! Remove from \p _elements the first value which equals \p _element.
        * Return true if found and removed.*/
        template <class T>
        bool remove(const T& _element, std::vector<T>& _elements);
        /*! Remove all \p _elements in \p element.*/
        template <class T>
        void remove(std::vector<T>& elements, const std::vector<T>& _elements);
        /*! Add all \p _elements in \p elements.*/
        template <class T>
        void add(std::vector<const T*>& elements, const std::vector<T*>& _elements);
        /*! Add all \p _elements in \p element.*/
        template <class T>
        void add(std::vector<const T>& elements, const std::vector<T>& _elements);
        /*! Add all \p _elements in \p element.*/
        template <class T>
        void add(std::vector<T>& elements, const std::vector<T>& _elements);
        /*! Add all \p _elements1 and \p _elements2 (concatenate) and return result.*/
        template <class T>
        std::vector<T> add(const std::vector<T>& _elements1, const std::vector<T>& _elements2);
        /*! Add all \p _elements in \p elements (concatenate). Static cast of Targ* to T*.*/
        template <class T, class Targ>
        void add_static_cast(std::vector<const T*>& elements, const std::vector<const Targ*>& _elements);
        /*! Add all \p _elements in \p elements (concatenate). Static cast of Targ* to T*.*/
        template <class T, class Targ>
        void add_static_cast(std::vector<T*>& elements, const std::vector<Targ*>& _elements);
        /*! Add all \p _elements in \p elements (concatenate). Dynamic cast of Targ* to T*.*/
        template <class T, class Targ>
        void add_dynamic_cast(std::vector<const T*>& elements, const std::vector<const Targ*>& _elements);
        /*! Converts \p _elements into \p elements by static cast of Targ* to T*.*/
        template <class T, class Targ>
        void assign_static_cast(std::vector<const T*>& elements, const std::vector<const Targ*>& _elements);
        /*! Converts \p _elements into \p elements by static cast of Targ* to T*.*/
        template <class T, class Targ>
        void assign_static_cast(std::vector<T*>& elements, const std::vector<Targ*>& _elements);
        /*! Converts \p _elements into \p elements by dynamic cast of Targ* to T*.*/
        template <class T, class Targ>
        void assign_dynamic_cast(std::vector<const T*>& elements, const std::vector<const Targ*>& _elements);
        /*! Return the first index where \p _elements is equal to \p _element. Returns -1 if no match is found.*/
        template <class T>
        unsigned int getIndex(const T& _element, const std::vector<T>& _elements);
        /*! Check if \p _elements contains a value equal to \p _element*/
        template <class T>
        bool find(const T& _element, const std::vector<T>& _elements);
        /*! Check if \p _elements contains a value equal to \p _element*/
        template <class T>
        bool find(const T& _element, const std::vector<const T>& _elements);
        /*! Check if \p _elements contains a dereferenced pointer equal to \p _element*/
        template <class T>
        bool find(const T& _element, const std::vector<T*>& _elements);
        /*! Returns the position where \p _element should be inserted in \p _elements in descending order.*/
        template <class T>
        unsigned int sortIndex_descending(const T& _element, const std::vector<T>& _elements);
        /*! Returns the position where \p _element should be inserted in \p _elements in ascending order.*/
        template <class T>
        unsigned int sortIndex_ascending(const T& _element, const std::vector<T>& _elements);

        /*! Return true if for each element of \p _vector1, there is an equal element in \p _vector2. False otherwise.*/
        template <class T>
        bool equalUnordered(const std::vector<T>& _vector1, const std::vector<T>& _vector2);

        /*! Return ascending sequence [\p _start, \p _start + \p _increment, \p _start + 2* \p _increment, ..] of size \p _size.*/
        template <class T>
        std::vector<T> make_sequence(const unsigned int _size, const T _start = 0, const T _increment = T(1));

        /*! Sort \p _element in ascending order up to \p _range index. If \p _range is 0, sort all vector.*/
        template <class T>
        void sort_ascending(std::vector<T>& _elements, unsigned int _range = 0);
        /*! Sort \p _element in ascending order up to \p _range index. If \p _range is 0, sort all vector.
        * Provided \p _elements_arg has the same size as \p elements, rearrange \p _elements_arg in the same way as \p _elements.*/
        template <class T, class Targ>
        void sort_ascending(std::vector<T>& _elements, std::vector<Targ>& _elements_arg, unsigned int _range = 0);
        /*! Sort \p _element in descending order up to \p _range index. If \p _range is 0, sort all vector.*/
        template <class T>
        void sort_descending(std::vector<T>& _elements, unsigned int _range = 0);
        /*! Sort \p _element in descending order up to \p _range index. If \p _range is 0, sort all vector.
        * Provided \p _elements_arg has the same size as \p elements, rearrange \p _elements_arg in the same way as \p _elements.*/
        template <class T, class Targ>
        void sort_descending(std::vector<T>& _elements, std::vector<Targ>& _elements_arg, unsigned int _range = 0);

        /*! Returns the position where \p _element would be inserted in \p _elements in descending order.*/
        template <class T>
        unsigned int sortInsert_descending(const T& _element, std::vector<T>& _elements);
        /*! Returns the position where \p _element would be inserted in \p _elements in ascending order.*/
        template <class T>
        unsigned int sortInsert_ascending(const T& _element, std::vector<T>& _elements);

        /*! Return true if every element of \p _elements1 matches the element of \p _elements2 (same order).*/
        template <class T>
        bool is_equal(const std::vector<T>& _elements1, const std::vector<T>& _elements2);

    }
}

#include "slv_flag.h"
#include <algorithm>//find

template <class T>
bool slv::vector::remove(const T& _element, std::vector<T>& _elements) {

#if VECTOR_EXPLICIT_ALGORITHM==1
    bool l_found = false;
    unsigned int el = 0;
    while (!l_found && el < _elements.size()) {
        l_found = (_element == _elements[el]);
        el++;
    }
    if (l_found) {
        el--;
        _elements.erase(_elements.begin() + el);
    }
    return l_found;
#else

    typename std::vector<T>::iterator it = std::find(_elements.begin(), _elements.end(), _element);
    if (it != _elements.end()) {
        _elements.erase(it);
        return true;
    } else {
        return false;
    }
#endif
}

template <class T>
void slv::vector::remove(std::vector<T>& elements, const std::vector<T>& _elements) {

    for (typename std::vector<T>::const_iterator it = _elements.begin(); it != _elements.end(); ++it) {
        remove(*it, elements);
    }

}

template <class T>
void slv::vector::add(std::vector<const T*>& elements, const std::vector<T*>& _elements) {

    for (typename std::vector<T>::const_iterator it = _elements.begin(); it != _elements.end(); ++it) {
        elements.push_back(*it);
    }
}

template <class T>
void slv::vector::add(std::vector<const T>& elements, const std::vector<T>& _elements) {

    for (typename std::vector<T>::const_iterator it = _elements.begin(); it != _elements.end(); ++it) {
        elements.push_back(*it);
    }

}

template <class T>
void slv::vector::add(std::vector<T>& elements, const std::vector<T>& _elements) {
    elements.insert(elements.end(), _elements.begin(), _elements.end());
}

template <class T>
std::vector<T> slv::vector::add(const std::vector<T>& _elements1, const std::vector<T>& _elements2) {
    std::vector<T> elements = _elements1;
    slv::vector::add(elements, _elements2);
    return elements;
}

template <class T, class Targ>
void slv::vector::add_static_cast(std::vector<const T*>& elements, const std::vector<const Targ*>& _elements) {

    for (typename std::vector<const Targ*>::const_iterator it = _elements.begin(); it != _elements.end(); it++) {
        elements.push_back(static_cast<const T*> (*it));
    }
}

template <class T, class Targ>
void slv::vector::add_static_cast(std::vector<T*>& elements, const std::vector<Targ*>& _elements) {

    for (typename std::vector<Targ*>::const_iterator it = _elements.begin(); it != _elements.end(); it++) {
        elements.push_back(static_cast<T*> (*it));
    }
}

template <class T, class Targ>
void slv::vector::add_dynamic_cast(std::vector<const T*>& elements, const std::vector<const Targ*>& _elements) {

    for (typename std::vector<const Targ*>::const_iterator it = _elements.begin(); it != _elements.end(); it++) {
        elements.push_back(dynamic_cast<const T*> (*it));
    }
}

template <class T, class Targ>
void slv::vector::assign_static_cast(std::vector<const T*>& elements, const std::vector<const Targ*>& _elements) {

    elements.resize(0);
    add_static_cast(elements, _elements);
}

template <class T, class Targ>
void slv::vector::assign_static_cast(std::vector<T*>& elements, const std::vector<Targ*>& _elements) {

    elements.resize(0);
    add_static_cast(elements, _elements);
}

template <class T, class Targ>
void slv::vector::assign_dynamic_cast(std::vector<const T*>& elements, const std::vector<const Targ*>& _elements) {

    elements.resize(0);
    vectorAdd_dynamic_cast(elements, _elements);
}

template <class T>
unsigned int slv::vector::getIndex(const T& _element, const std::vector<T>& _elements) {

#if VECTOR_EXPLICIT_ALGORITHM==1
    bool l_found = false;
    unsigned int el = 0;
    while (!l_found && el < _elements.size()) {
        l_found = (_element == _elements[el]);
        el++;
    }
    if (l_found) {
        el--;
        return el;
    } else {
        //std::cout << "WARNING - vectorGetIndex - there is no element " << _element << " in the vector" << std::endl;
        return -1;
    }
#else
    typename std::vector<T>::const_iterator it = std::find(_elements.begin(), _elements.end(), _element);
    if (it != _elements.end()) {
        return std::distance(_elements.begin(), it);
    } else {
        return -1;
    }
#endif
}

template <class T>
bool slv::vector::find(const T& _element, const std::vector<T>& _elements) {
#if VECTOR_EXPLICIT_ALGORITHM==1
    bool l_found = false;
    unsigned int el = 0;
    while (!l_found && el < _elements.size()) {
        l_found = (_element == _elements[el]);
        el++;
    }
    return l_found;
#else
    return std::find(_elements.begin(), _elements.end(), _element) != _elements.end();
#endif
}

template <class T>
bool slv::vector::find(const T& _element, const std::vector<const T>& _elements) {
#if VECTOR_EXPLICIT_ALGORITHM==1
    bool l_found = false;
    unsigned int el = 0;
    while (!l_found && el < _elements.size()) {
        l_found = (_element == _elements[el]);
        el++;
    }
    return l_found;
#else
    return std::find(_elements.begin(), _elements.end(), _element) != _elements.end();
#endif
}

template <class T>
bool slv::vector::find(const T& _element, const std::vector<T*>& _elements) {

#if VECTOR_EXPLICIT_ALGORITHM==1
    bool l_found = false;
    unsigned int el = 0;
    while (!l_found && el < _elements.size()) {
        l_found = (_element == *_elements[el]);
        el++;
    }
    return l_found;
#else

    typename std::vector<T*>::const_iterator it = _elements.begin();
    while (it != _elements.end() && **it != _element) {
        ++it;
    }

    return it != _elements.end();
#endif
}

template <class T>
unsigned int slv::vector::sortIndex_descending(const T& _element, const std::vector<T>& _elements) {

#if VECTOR_EXPLICIT_ALGORITHM==1
    bool l_found = false;
    unsigned int el = 0;
    while (!l_found && el < _elements.size()) {
        l_found = (_element > _elements[el]);
        el++;
    }
    if (l_found) {
        el--;
    }
    return el;
#else

    typename std::vector<T>::const_iterator it = _elements.begin();
    bool l_found = false;
    while (!l_found && it != _elements.end()) {
        l_found = (_element > *it);
        if (!l_found) ++it;
    }

    return std::distance(_elements.begin(), it);
#endif
}

template <class T>
unsigned int slv::vector::sortIndex_ascending(const T& _element, const std::vector<T>& _elements) {

#if VECTOR_EXPLICIT_ALGORITHM==1
    bool l_found = false;
    unsigned int el = 0;
    while (!l_found && el < _elements.size()) {
        l_found = (_element < _elements[el]);
        el++;
    }
    if (l_found) {
        el--;
    }
    return el;
#else

    typename std::vector<T>::const_iterator it = _elements.begin();
    bool l_found = false;
    while (!l_found && it != _elements.end()) {
        l_found = (_element < *it);
        if (!l_found) ++it;
    }

    return std::distance(_elements.begin(), it);
#endif
}

template <class T>
unsigned int slv::vector::sortInsert_descending(const T& _element, std::vector<T>& _elements) {

    unsigned int el = sortIndex_decrease(_element, _elements);
    _elements.insert(_elements.begin() + el, _element);
    return el;
}

template <class T>
unsigned int slv::vector::sortInsert_ascending(const T& _element, std::vector<T>& _elements) {

    unsigned int el = sortIndex_increase(_element, _elements);
    _elements.insert(_elements.begin() + el, _element);
    return el;
}


template <class T>
bool slv::vector::equalUnordered(const std::vector<T>& _vector1, const std::vector<T>& _vector2) {

    if (_vector1.size() != _vector2.size()) {
        return false;
    } else {
        unsigned int i = 0;
        unsigned int j;
        std::vector<bool> vector2_already_match(_vector2.size(), false);
        bool l_equal = true;
        while (l_equal && i < _vector1.size()) {
            j = 0;
            while (j < _vector2.size() && (_vector1[i] != _vector2[j] || vector2_already_match[j])) {
                j++;
            }//stops : either if j out of range, either if matching is found (provided not already match)
            if (j == _vector2.size()) {
                l_equal = false;//no matching found
            } else {
                vector2_already_match[j] = true;
                i++;
            }
        }
        return l_equal;
    }

}

template <class T>
std::vector<T> slv::vector::make_sequence(const unsigned int _size, const T _start, const T _increment) {

    std::vector<T> vector_sequence;
    vector_sequence.push_back(_start);
    for (unsigned int i = 1; i < _size; i++) {
        vector_sequence.push_back(vector_sequence.back() + _increment);
    }

    return vector_sequence;
}

template <class T>
void slv::vector::sort_ascending(std::vector<T>& _elements, unsigned int _range) {

#if VECTOR_EXPLICIT_ALGORITHM==1
    if (_range == 0) {
        _range = _elements.size();
    }

    unsigned int el, el2;
    for (el = 1; el < _range; el++) {
        el2 = el;
        while (el2 > 0 && _elements[el2] < _elements[el2 - 1]) {
            std::swap(_elements[el2 - 1], _elements[el2]);
            el2--;
        }
    }
#else
    typename std::vector<T>::iterator it;
    if (_range != 0) {
        it = _elements.begin() + _range;
    } else {
        it = _elements.end();
    }
    std::sort(_elements.begin(), it);
#endif
}

template <class T, class Targ>
void slv::vector::sort_ascending(std::vector<T>& _elements, std::vector<Targ>& _elements_arg, unsigned int _range) {

    if (_elements.size() == _elements_arg.size()) {

        if (_range == 0) {
            _range = _elements.size();
        }

        unsigned int el, el2;
        for (el = 1; el < _range; el++) {
            el2 = el;
            while (el2 > 0 && _elements[el2] < _elements[el2 - 1]) {
                std::swap(_elements[el2 - 1], _elements[el2]);
                std::swap(_elements_arg[el2 - 1], _elements_arg[el2]);
                el2--;
            }
        }

    } else {
        slv::flag::ISSUE(slv::flag::InvalidArgument, "bad size");
    }

}

template <class T>
void slv::vector::sort_descending(std::vector<T>& _elements, unsigned int _range) {

#if VECTOR_EXPLICIT_ALGORITHM==1
    if (_range == 0) {
        _range = _elements.size();
    }

    unsigned int el, el2;
    for (el = 1; el < _range; el++) {
        el2 = el;
        while (el2 > 0 && _elements[el2] > _elements[el2 - 1]) {
            std::swap(_elements[el2 - 1], _elements[el2]);
            el2--;
        }
    }
#else

    typename std::vector<T>::iterator it;
    if (_range != 0) {
        it = _elements.begin() + _range;
    } else {
        it = _elements.end();
    }
    std::sort(_elements.begin(), it, std::greater<T>());
#endif

}

template <class T, class Targ>
void slv::vector::sort_descending(std::vector<T>& _elements, std::vector<Targ>& _elements_arg, unsigned int _range) {

    if (_elements.size() == _elements_arg.size()) {

        if (_range == 0) {
            _range = _elements.size();
        }

        unsigned int el, el2;
        for (el = 1; el < _range; el++) {
            el2 = el;
            while (el2 > 0 && _elements[el2] > _elements[el2 - 1]) {
                std::swap(_elements[el2 - 1], _elements[el2]);
                std::swap(_elements_arg[el2 - 1], _elements_arg[el2]);
                el2--;
            }
        }

    } else {
        slv::flag::ISSUE(slv::flag::InvalidArgument, "bad size");
    }

}


template <class T>
bool slv::vector::is_equal(const std::vector<T>& _elements1, const std::vector<T>& _elements2) {

#if VECTOR_EXPLICIT_ALGORITHM==1
    if (_elements1.size() == _elements2.size()) {
        unsigned int i = 0;
        bool l_ok = true;
        while (l_ok && i < _elements1.size()) {
            l_ok = (_elements1[i] == _elements2[i]);
            i++;
        }
        return l_ok;
    } else {
        return false;
    }
#else
    bool l_equal = true;
    if (_elements1.size() == _elements2.size()) {

        typename std::vector<T>::const_iterator it1 = _elements1.begin();
        typename std::vector<T>::const_iterator it2 = _elements2.begin();

        while (l_equal && it1 != _elements1.end()) {
            l_equal = (*it1 == *it2);
            ++it1;
            ++it2;
        }

    } else {
        l_equal = false;
    }
    return l_equal;
#endif

}

#undef VECTOR_EXPLICIT_ALGORITHM