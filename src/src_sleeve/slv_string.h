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

#include <string>
#include <sstream>
#include "std_vector.h"
#include <cstdarg>

/*! Contains functions for the slv framework. No Qt/Glv here.*/
namespace slv {
    /*! String functions.*/
    namespace string {

        /*! Return "" */
        const std::string& str_void();

        /*! Transform \p n into a string of \p Ndigits.*/
        std::string number_to_string(int _n, int _Ndigits = 0);
        /*! Transform \p n into a string with the adequate number of digits.*/
        std::string number_to_string_auto(int n);
        /*! Convert \p _string to value.*/
        template <class T>
        T string_to_value(const std::string& _string);
        /*! Convert \p _value to string.*/
        std::string value_to_string(const double& _value);
        /*! Convert \p _string to value.*/
        unsigned int string_to_number(const std::string& _string);
        /*! Convert \p _value to string.*/
        template <class T>
        std::string to_string(const T& _value);
        /*! Convert \p _value to string.*/
        template <class T>
        std::string to_string(T* _value);

        /*! Get identifier string from instance.*/
        template <class T>
        std::string to_id_str(const T& _value);
        /*! Structure to specialize in order to get an identifier string from a template instance.*/
        template <class T>
        struct struct_to_id_str;

        /*! Get first part of \p _string (substring) up to \p _stop.*/
        template <class T>
        std::string extract_str_up_to(const std::string& _string, const T _stop);

        /*! Used by read_datas_line.*/
        template <class T>
        T read_data_line(std::string& _string_line, const std::string _separator = " ");
        /*! Extract a vector of template instances by reading \p _string_line.
        * Each instance is separated by \p _separator.
        * The max number of instances is defined by \p _Ndatas.
        * String to template is performed using string_to_value.*/
        template <class T>
        std::vector<T> read_datas_line(std::string _string_line, const std::string _separator = " ", const unsigned int _Ndatas = -1);

        /*! Remove \p _substring in \p _string.*/
        void remove_substring(const std::string& _substring, std::string& _string);

        /*! Read a string from istream with space character. Replaces _is >> _string.*/
        void istream(std::istream& _is, std::string& _string);

        /*! Parse formated \p _format arguments \p _args and returns the corresponding std::string.*/
        std::string format_va_list(const char* _format, std::va_list _args);
    }

}

template <class T>
std::string slv::string::to_string(const T& _value) {

    std::ostringstream strs;
    strs << _value;
    return strs.str();

}

template <class T>
std::string slv::string::to_string(T* _value) {

    std::ostringstream strs;
    strs << *_value;
    return strs.str();

}

template <class T>
std::string slv::string::to_id_str(const T& _value) {
    //allows specialization in somes cases (SlvFile for example)
    return struct_to_id_str<T>::to_id_str(_value);
}

template <class T>
struct slv::string::struct_to_id_str {
    static std::string to_id_str(const T& _value) {
        return to_string(_value);
    }
};

template <class T>
T slv::string::string_to_value(const std::string& _string) {

    std::istringstream buffer(_string);
    T value;
    buffer >> value;

    return value;
}

template <class T>
std::string slv::string::extract_str_up_to(const std::string& _string, const T _stop) {

    std::string::size_type pos = _string.find(_stop);
    if (pos != std::string::npos) {
        return _string.substr(0, pos);
    } else {
        return _string;
    }
}

template <class T>
T slv::string::read_data_line(std::string& _string_line, const std::string _separator) {

    std::string data_string = extract_str_up_to(_string_line, _separator);
    T data = string_to_value<T>(data_string);
    _string_line.erase(0, data_string.size() + _separator.size());
    return data;

}

template <class T>
std::vector<T> slv::string::read_datas_line(std::string _string_line, const std::string _separator, const unsigned int _Ndatas) {

    std::vector<T> datas(0);
    T buff_data;

    std::string buff_str;
    while (_string_line.size() > 0 && datas.size() < _Ndatas) {

        buff_data = read_data_line<T>(_string_line, _separator);
        datas.push_back(buff_data);
    }


    return datas;

}
