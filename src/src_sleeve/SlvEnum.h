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

#include "std_map.h"
#include "filestream/slv_rw.h"

/*! Class in charge of enum management. Not recommended to use directly. Use glvm_SlvEnum of glvm_SlvEnum_simple for instantiation.
* Example: glvm_SlvEnum(EnumName, A, B, C, D), or glvm_SlvEnum_named(EnumName, A, "A", B, "B", C, "C", D, "D").*/
template <class Tenum>
class SlvEnum {

public:
    static const std::map<Tenum, std::string>& enum_names() {
        static std::map<Tenum, std::string>* enum_names = new std::map<Tenum, std::string>(create_enum_names());
        return *enum_names;
    }
    static const std::map<Tenum, int>& enum_positions() {
        static std::map<Tenum, int>* enum_position = new std::map<Tenum, int>(create_enum_positions());
        return *enum_position;
    }
    static const std::vector<Tenum>& enum_positions_inv() {
        static std::vector<Tenum>* enum_positions_inv = new std::vector<Tenum>(create_enum_positions_inv());
        return *enum_positions_inv;
    }
private:
    static const std::map<std::string, Tenum>& enum_names_inv() {
        static std::map<std::string, Tenum>* enum_names_inv = new std::map<std::string, Tenum>(create_enum_names_inv());
        return *enum_names_inv;
    }

public:
    /*! Get enum size.*/
    static const unsigned int size() { return (unsigned int)enum_names().size(); };
    /*! Get name associated to the i-th enum element.*/
    static const std::string& get_name(const unsigned int i) {
        //return get_name(static_cast<Tenum>(i));
        return get_name(enum_positions_inv()[i]);
    }
    /*! Get name associated to enum element \p _enum_item.*/
    static const std::string& get_name(const Tenum& _enum_item) {
        return enum_names().at(_enum_item);
    }
    /*! Get index of enum element (i-th enum element) \p _enum_item.*/
    static unsigned int get_index(const Tenum& _enum_item) {
        //return static_cast<unsigned int>(_enum_item);
        return enum_positions().at(_enum_item);
    }
    /*! Get enum element corresponding to the associated name \p _enum_item_name.
    * If \p _enum_item_name is not found, returns first enum element. */
    static Tenum get_enum(const std::string& _enum_item_name) {
        typename std::map<std::string, Tenum>::const_iterator it = enum_names_inv().find(_enum_item_name);
        if (it != enum_names_inv().end()) {
            return it->second;
        } else {
            return Tenum();
        }
    }

private:
    static std::map<Tenum, std::string> create_enum_names();
    static std::map<std::string, Tenum> create_enum_names_inv() {
        std::map<std::string, Tenum> enum_names_inv;
        for (typename std::map<Tenum, std::string>::const_iterator it = enum_names().begin(); it != enum_names().end(); it++) {
            enum_names_inv[it->second] = it->first;
        }
        return enum_names_inv;
    }
    static std::map<Tenum, int> create_enum_positions() {
        std::map<Tenum, int> enum_positions;
        int count = 0;
        for (typename std::map<Tenum, std::string>::const_iterator it = enum_names().begin(); it != enum_names().end(); it++) {
            enum_positions[it->first] = count;
            count++;
        }
        return enum_positions;
    }
    static std::vector<Tenum> create_enum_positions_inv() {
        std::vector<Tenum> enum_positions_inv;
        for (typename std::map<Tenum, std::string>::const_iterator it = enum_names().begin(); it != enum_names().end(); it++) {
            enum_positions_inv.push_back(it->first);
        }
        return enum_positions_inv;
    }

};

#define glvm_pv_SlvEnum_misc(enum_Type)\
inline std::ostream& operator<<(std::ostream& _os, const enum_Type& _enum_item){_os << SlvEnum<enum_Type>::get_name(_enum_item);return _os;}\
inline std::istream& operator>>(std::istream& _is, enum_Type& _enum_item){std::string enum_item_str;_is>>enum_item_str;_enum_item=SlvEnum<enum_Type>::get_enum(enum_item_str);return _is;}\
template <> inline void slv::rw::writeB<enum_Type>(const enum_Type& _value, std::ofstream& _output_file) {slv::rw::writeB(int(_value), _output_file);}\
template <> inline bool slv::rw::readB<enum_Type>(enum_Type& _value, std::ifstream& _input_file) {int i; bool l_read = slv::rw::readB(i, _input_file); _value=static_cast<enum_Type>(i); return l_read;}\

#include "SlvEnum_macros_msvc.h"

#if defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL
#include "SlvEnum_macros_var_msvc.h"
#else // /Zc:preprocessor 
#include "SlvEnum_macros.h"
#include "SlvEnum_macros_var.h"
#endif

