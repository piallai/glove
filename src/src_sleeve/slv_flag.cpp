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

#include "slv_flag.h"
#ifndef _MSC_VER
#include <signal.h>//for BREAK
#endif
#include "GloveOptions.h"

const std::string& slv::flag::str_delimiter0() {
    static std::string* str_delimiter0 = new std::string("################################################################################");
    return *str_delimiter0;
}

const std::string& slv::flag::str_delimiter1() {
    static std::string* str_delimiter1 = new std::string("---------------------------------------------------------------------");
    return *str_delimiter1;
}

const std::string& slv::flag::str_delimiter2() {
    static std::string* str_delimiter2 = new std::string("***********************************************************");
    return *str_delimiter2;
}

const std::string slv::flag::str_delimiter0(const std::string& _string) {
    std::string pattern = "###########";
    std::string delimiter = pattern;
    delimiter += _string;
    delimiter += pattern;
    return delimiter;
}

const std::string slv::flag::str_delimiter1(const std::string& _string) {
    std::string pattern = "----------";
    std::string delimiter = pattern;
    delimiter += _string;
    delimiter += pattern;
    return delimiter;
}

const std::string slv::flag::str_delimiter2(const std::string& _string) {
    std::string pattern = "***********";
    std::string delimiter = pattern;
    delimiter += _string;
    delimiter += pattern;
    return delimiter;
}


const std::string& slv::flag::warning_intro() {
    static std::string* str = new std::string();
    *str = "WARNING - ";
    return *str;
}

void slv::flag::WARNING(std::string warning_message) {
    std::cout << warning_intro() << warning_message << std::endl;
}

void slv::flag::BREAK() {
#if OPTION_STD_BREAK_THROW_EXCEPTION==0
#ifdef _MSC_VER
    __debugbreak();
#else
    raise(SIGTRAP);
#endif
#else
    throw std::runtime_error("");
#endif
}

void slv::flag::BREAK(std::string warning_message) {
    ISSUE(FlagType::Critical, warning_message);
}

void slv::flag::WIP() {
    slv::flag::ISSUE(FlagType::Critical, "Work in progress");
}

void slv::flag::WIP(std::string _work_in_progress_message) {
    slv::flag::ISSUE(FlagType::Critical, "Work in progress : " + _work_in_progress_message);
}

void slv::flag::ISSUE(FlagType _flag_type, std::string warning_message) {
    std::cout << warning_intro() << warning_message << std::endl;
    if (_flag_type == FlagType::Critical) {
        BREAK();
    } else {
        // Do not crash
    }
}

void slv::flag::ISSUE(FlagType _flag_type, const std::ostringstream& _stream) {

    if (_flag_type == FlagType::Critical) {
#if OPTION_STD_BREAK_THROW_EXCEPTION==0
        std::cout << _stream.str();
        BREAK();
#else
        throw std::runtime_error(_stream.str());
#endif
    } else if (_flag_type == FlagType::Warning) {
        std::cout << _stream.str();
    }

}

void slv::flag::loop_display(const unsigned int _i_loop, const unsigned int _Nloop, const std::string _message, const unsigned int _Nfraction) {

    unsigned int Ndelta;
    if (_Nloop < _Nfraction) {
        Ndelta = 1;
    } else {
        Ndelta = _Nloop / _Nfraction;
    }

    if (_i_loop == 0) {

        std::cout << "Loop starting, " << _message << " : " << _Nloop << " iterations" << std::endl;

    } else if ((_i_loop + 1) % Ndelta == 0) {

        unsigned int percent = 100 * (_i_loop + 1) / (_Nloop);

        std::cout << "Loop, " << _message << " : " << percent << " %" << std::endl;
    }
}
