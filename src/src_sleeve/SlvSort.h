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
#include "slv_flag.h"
#include "param/SlvParametrization2.h"
#include "SlvIOS.h"

/*! Sort management of a list of template data. Not to be used directly. Use SlvSortAscending or SlvSortDescending.
* Sort data as soon as they are added.
* Tdata is the type of data to sort, and Trange is the type by which two Tdata are being compared.
* Range is the maximal range between data. Range value must be positive.
* Maximum number of datas sorted is always 1 at minimum.
* Possibility to limit the number of data.
* Ascending: Input priority (front of datas) to the lowest values.
* Descending: Input priority (front of datas) to the highest values.*/
template <class Tdata, class Trange = Tdata>
class SlvSort : public SlvParametrization2<unsigned int, Trange>, virtual public SlvIOS {

    glvm_parameter_ruled(1, Ndatas_max, unsigned int, "Maximum number of elements", "Maximum number the sort instance can contain.", (unsigned int)-1)
    glvm_parameter_add_rule(min, 1)
    glvm_parameter_end
    glvm_parameter_ruled(2, range, Trange, "Maximum range", "Maximum delta from the front element.", 0)
    glvm_parameter_add_rule(min, 0)
    glvm_parameter_end

protected:

    std::vector<Tdata> datas;

public:

    SlvSort() :glvm_parametrization_constructor(Ndatas_max, range) {}
    /*! \p _Ndatas_max is the maximum number of elements in the instance.
    * \p _range is the maximum delta from the front element.*/
    SlvSort(unsigned int _Ndatas_max, Trange _range = 0);
    ~SlvSort();

    /*! Clear sorted datas. Keeps parameters.*/
    void clear();

    unsigned int size() const;
    const Tdata& operator[] (const unsigned int i) const;

    /*! Access datas vector.*/
    const std::vector<Tdata>& get() const;
    /*! Access datas vector.*/
    std::vector<Tdata>& get();

    /*! Get index where \p _data should belong.*/
    unsigned int get_index(const Tdata& _data) const;
    /*! Add \p _data. Return true if successfully added.*/
    bool add(const Tdata& _data);

    /*! Comparison test between two datas. Implemented in SlvSortAscending and SlvSortDescending.*/
    virtual bool test_data(const Tdata& _data1, const Tdata& _data2) const = 0;
    /*! Return true if \p _data is in the proper range, comparing from front sorted data.*/
    virtual bool check_range(const Tdata& _data) const = 0;

    void writeB(std::ofstream& _output_file) const;
    bool readB(std::ifstream& _input_file);

private:

    void ostream(std::ostream& _os) const;
    void istream(std::istream& _is);

};

#include "filestream/slv_rw.h"

template <class Tdata, class Trange>
SlvSort<Tdata, Trange>::SlvSort(unsigned int _Ndatas_max, Trange _range) :SlvSort() {
    set_Ndatas_max(_Ndatas_max);
    set_range(_range);
}

template <class Tdata, class Trange>
SlvSort<Tdata, Trange>::~SlvSort() {

}

template <class Tdata, class Trange>
void SlvSort<Tdata, Trange>::clear() {

    datas.clear();
}

template <class Tdata, class Trange>
unsigned int SlvSort<Tdata, Trange>::size() const {

    return (unsigned int)datas.size();
}

template <class Tdata, class Trange>
const Tdata& SlvSort<Tdata, Trange>::operator[] (const unsigned int i) const {

    return datas[i];
}

template <class Tdata, class Trange>
const std::vector<Tdata>& SlvSort<Tdata, Trange>::get() const {
    return datas;
}

template <class Tdata, class Trange>
std::vector<Tdata>& SlvSort<Tdata, Trange>::get() {
    return datas;
}

template <class Tdata, class Trange>
unsigned int SlvSort<Tdata, Trange>::get_index(const Tdata& _data) const {

    unsigned int i = 0;
    unsigned int i_lower = 0;
    unsigned int i_upper = (unsigned int)datas.size();

    while (i_lower + 1 < i_upper) {

        i = i_lower + (i_upper - i_lower) / 2;

        if (test_data(datas[i], _data)) {
            i_lower = i;
        } else {
            i_upper = i;
        }

    }

    if (i_lower != i_upper) {
        if (test_data(datas[i_lower], _data)) {
            i = i_upper;
        } else {
            i = i_lower;
        }
    }

    return i;

}

template <class Tdata, class Trange>
bool SlvSort<Tdata, Trange>::add(const Tdata& _data) {

    bool l_return = true;

    //get index where _data should belong
    unsigned int i = get_index(_data);

    if (i == 0) {

        datas.insert(datas.begin(), _data);
        if (datas.size() > get_Ndatas_max()) {
            datas.pop_back();
        } else if (get_range() != Trange(0)) {// range reference may have changed
            while (!check_range(datas.back())) {
                datas.pop_back();
            }
        }

    } else {

        if (i == datas.size()) {

            if (i < get_Ndatas_max() && (get_range() == Trange(0) || check_range(_data))) {
                datas.push_back(_data);
            } else {
                l_return = false;
            }

        } else {

            datas.insert(datas.begin() + i, _data);
            if (datas.size() > get_Ndatas_max()) {
                datas.pop_back();
            }

        }

    }

    return l_return;
}


template <class Tdata, class Trange>
void SlvSort<Tdata, Trange>::writeB(std::ofstream& _output_file) const {
    slv::rw::writeB(datas, _output_file);
}


template <class Tdata, class Trange>
void SlvSort<Tdata, Trange>::ostream(std::ostream& _os) const {
    _os << datas;
}

template <class Tdata, class Trange>
bool SlvSort<Tdata, Trange>::readB(std::ifstream& _input_file) {
    return slv::rw::readB(datas, _input_file);
}

template <class Tdata, class Trange>
void SlvSort<Tdata, Trange>::istream(std::istream& _is) {
    _is >> datas;
}

/////////////////////////////////////////////////////////////////////////////////////
//////////////////// Ascending/Descending ///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

template <class Tdata, class Trange = Tdata>
class SlvSortDescending : public SlvSort<Tdata, Trange> {

    glvm_parametrization2_inherited_template_init(SlvSort<Tdata COMMA Trange>)// Required for GCC
    glvm_parametrization2_init("Sort descending")

public:

    /*! \p _Ndatas_max is the maximum number of elements in the instance.
    * \p _range is the maximum delta from the front element.*/
    SlvSortDescending(unsigned int _Ndatas_max = -1, Trange _range = Trange(0));
    ~SlvSortDescending();

private:

    bool test_data(const Tdata& _data1, const Tdata& _data2) const;
    bool check_range(const Tdata& _data) const;

};

template <class Tdata, class Trange>
SlvSortDescending<Tdata, Trange>::SlvSortDescending(unsigned int _Ndatas_max, Trange _range) :SlvSort<Tdata, Trange>(_Ndatas_max, _range) {

}

template <class Tdata, class Trange>
SlvSortDescending<Tdata, Trange>::~SlvSortDescending() {

}

template <class Tdata, class Trange>
bool SlvSortDescending<Tdata, Trange>::test_data(const Tdata& _data1, const Tdata& _data2) const {
    return _data1 >= _data2;
}

template <class Tdata, class Trange>
bool SlvSortDescending<Tdata, Trange>::check_range(const Tdata& _data) const {
    return this->datas.front() - _data <= this->get_range();
}


template <class Tdata, class Trange = Tdata>
class SlvSortAscending : public SlvSort<Tdata, Trange> {

    glvm_parametrization2_inherited_template_init(SlvSort<Tdata COMMA Trange>)// Required for GCC
    glvm_parametrization2_init("Sort ascending")

public:

    /*! \p _Ndatas_max is the maximum number of elements in the instance.
    * \p _range is the maximum delta from the front element.*/
    SlvSortAscending(unsigned int _Ndatas_max = -1, Trange _range = Trange(0));
    ~SlvSortAscending();

private:

    bool test_data(const Tdata& _data1, const Tdata& _data2) const;
    bool check_range(const Tdata& _data) const;

};

template <class Tdata, class Trange>
SlvSortAscending<Tdata, Trange>::SlvSortAscending(unsigned int _Ndatas_max, Trange _range) :SlvSort<Tdata, Trange>(_Ndatas_max, _range) {

}

template <class Tdata, class Trange>
SlvSortAscending<Tdata, Trange>::~SlvSortAscending() {

}

template <class Tdata, class Trange>
bool SlvSortAscending<Tdata, Trange>::test_data(const Tdata& _data1, const Tdata& _data2) const {
    return _data1 <= _data2;
}

template <class Tdata, class Trange>
bool SlvSortAscending<Tdata, Trange>::check_range(const Tdata& _data) const {
    return _data - this->datas.front() <= this->get_range();
}