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



#pragma once

#include <string>
#include <iostream>
#include <sstream>

namespace slv {
    /*! Usefull flags, such as BREAK, or string delimiters in terminal output.*/
    namespace flag {

        /*! Output: #################*/
        const std::string& str_delimiter0();
        /*! Output: ---------------*/
        const std::string& str_delimiter1();
        /*! Output: ************ */
        const std::string& str_delimiter2();

        /*! Delimiter + \p _string.*/
        const std::string str_delimiter0(const std::string& _string);
        /*! Delimiter + \p _string.*/
        const std::string str_delimiter1(const std::string& _string);
        /*! Delimiter + \p _string.*/
        const std::string str_delimiter2(const std::string& _string);

        /*! Type of issue. Critical is by default std::runtime_error.*/
        enum FlagType { Info, Warning, Critical, InvalidArgument, EndOfFile };

        /*! Private*/
        const std::string& warning_intro();
        /*! Ouput a warning: \p _warning_message.*/
        void WARNING(std::string warning_message);

        /*! Intentional crash. Throws std::runtime_error if OPTION_STD_BREAK_THROW_EXCEPTION is ON, or basic break if OFF.*/
        void BREAK();

        /*! Critical + work in progress output.*/
        void WIP();
        /*! Critical + work in progress output + \p _work_in_progress_message.*/
        void WIP(std::string _work_in_progress_message);

        /*! Critical + _warning message.*/
        void BREAK(std::string warning_message);
        /*! Critical + _warning message + template argument output.*/
        template <class T>
        void BREAK(std::string warning_message, const T& warning_arg);
        template <class T>
        void BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2);
        template <class T, class T2>
        void BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2);
        template <class T, class T2>
        void BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3);
        template <class T, class T2, class T3>
        void BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3);
        template <class T, class T2, class T3>
        void BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4);
        template <class T, class T2, class T3, class T4>
        void BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4);
        template <class T, class T2, class T3, class T4>
        void BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5);
        template <class T, class T2, class T3, class T4, class T5>
        void BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5, const T5& warning_arg5);
        template <class T, class T2, class T3, class T4, class T5>
        void BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5, const T5& warning_arg5, std::string warning_message6);
        template <class T, class T2, class T3, class T4, class T5, class T6>
        void BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5, const T5& warning_arg5, std::string warning_message6, const T6& warning_arg6);

        /*! Issue (type \p _flag_type) + _warning message*/
        void ISSUE(FlagType _flag_type, std::string warning_message);
        /*! Issue (type \p _flag_type) + _warning message + template argument output*/
        template <class T>
        void ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg);
        template <class T>
        void ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2);
        template <class T, class T2>
        void ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2);
        template <class T, class T2>
        void ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3);
        template <class T, class T2, class T3>
        void ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3);
        template <class T, class T2, class T3>
        void ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4);
        template <class T, class T2, class T3, class T4>
        void ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4);
        template <class T, class T2, class T3, class T4>
        void ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5);
        template <class T, class T2, class T3, class T4, class T5>
        void ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5, const T5& warning_arg5);
        template <class T, class T2, class T3, class T4, class T5>
        void ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5, const T5& warning_arg5, std::string warning_message6);
        template <class T, class T2, class T3, class T4, class T5, class T6>
        void ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5, const T5& warning_arg5, std::string warning_message6, const T6& warning_arg6);

        void ISSUE(FlagType _flag_type, const std::ostringstream& _stream);

        /*! Output a loop message as a percentage. The fraction is defined as (_i_loop + 1) / _Nloop.
        * Can output a message only \p _Nfraction times during a full loop.*/
        void loop_display(const unsigned int _i_loop, const unsigned int _Nloop, const std::string _message, const unsigned int _Nfraction = 10);

        /*! std::cout of \p _value by dereferencing the pointer.*/
        template <class T>
        void cout_ptr(const T* _value);
        /*! Compatibility overload.*/
        template <class T>
        void cout_ptr(const T& _value);
        /*! Overload with message.*/
        template <class T>
        void cout_ptr(const std::string& _message, const T& _value);
    }
}

template <class T>
void slv::flag::BREAK(std::string warning_message, const T& warning_arg) {
    ISSUE(FlagType::Critical, warning_message, warning_arg);
}
template <class T>
void slv::flag::BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2) {
    ISSUE(FlagType::Critical, warning_message, warning_arg, warning_message2);
}
template <class T, class T2>
void slv::flag::BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2) {
    ISSUE(FlagType::Critical, warning_message, warning_arg, warning_message2, warning_arg2);
}
template <class T, class T2>
void slv::flag::BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3) {
    ISSUE(FlagType::Critical, warning_message, warning_arg, warning_message2, warning_arg2, warning_message3);
}
template <class T, class T2, class T3>
void slv::flag::BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3) {
    ISSUE(FlagType::Critical, warning_message, warning_arg, warning_message2, warning_arg2, warning_message3, warning_arg3);
}
template <class T, class T2, class T3>
void slv::flag::BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4) {
    ISSUE(FlagType::Critical, warning_message, warning_arg, warning_message2, warning_arg2, warning_message3, warning_arg3, warning_message4);
}
template <class T, class T2, class T3, class T4>
void slv::flag::BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4) {
    ISSUE(FlagType::Critical, warning_message, warning_arg, warning_message2, warning_arg2, warning_message3, warning_arg3, warning_message4, warning_arg4);
}
template <class T, class T2, class T3, class T4>
void slv::flag::BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5) {
    ISSUE(FlagType::Critical, warning_message, warning_arg, warning_message2, warning_arg2, warning_message3, warning_arg3, warning_message4, warning_arg4, warning_message5);
}
template <class T, class T2, class T3, class T4, class T5>
void slv::flag::BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5, const T5& warning_arg5) {
    ISSUE(FlagType::Critical, warning_message, warning_arg, warning_message2, warning_arg2, warning_message3, warning_arg3, warning_message4, warning_arg4, warning_message5, warning_arg5);
}
template <class T, class T2, class T3, class T4, class T5>
void slv::flag::BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5, const T5& warning_arg5, std::string warning_message6) {
    ISSUE(FlagType::Critical, warning_message, warning_arg, warning_message2, warning_arg2, warning_message3, warning_arg3, warning_message4, warning_arg4, warning_message5, warning_arg5, warning_message6);
}
template <class T, class T2, class T3, class T4, class T5, class T6>
void slv::flag::BREAK(std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5, const T5& warning_arg5, std::string warning_message6, const T6& warning_arg6) {
    ISSUE(FlagType::Critical, warning_message, warning_arg, warning_message2, warning_arg2, warning_message3, warning_arg3, warning_message4, warning_arg4, warning_message5, warning_arg5, warning_message6, warning_arg6);
}


template <class T>
void slv::flag::ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg) {
    std::ostringstream stream;
    stream << warning_intro() << warning_message << warning_arg << std::endl;
    ISSUE(_flag_type, stream);
}
template <class T>
void slv::flag::ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2) {
    std::ostringstream stream;
    stream << warning_intro() << warning_message << warning_arg << warning_message2 << std::endl;
    ISSUE(_flag_type, stream);
}
template <class T, class T2>
void slv::flag::ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2) {
    std::ostringstream stream;
    stream << warning_intro() << warning_message << warning_arg << warning_message2 << warning_arg2 << std::endl;
    ISSUE(_flag_type, stream);
}
template <class T, class T2>
void slv::flag::ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3) {
    std::ostringstream stream;
    stream << warning_intro() << warning_message << warning_arg << warning_message2 << warning_arg2 << warning_message3 << std::endl;
    ISSUE(_flag_type, stream);
}
template <class T, class T2, class T3>
void slv::flag::ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3) {
    std::ostringstream stream;
    stream << warning_intro() << warning_message << warning_arg << warning_message2 << warning_arg2 << warning_message3 << warning_arg3 << std::endl;
    ISSUE(_flag_type, stream);
}
template <class T, class T2, class T3>
void slv::flag::ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4) {
    std::ostringstream stream;
    stream << warning_intro() << warning_message << warning_arg << warning_message2 << warning_arg2 << warning_message3 << warning_arg3 << warning_message4 << std::endl;
    ISSUE(_flag_type, stream);
}
template <class T, class T2, class T3, class T4>
void slv::flag::ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4) {
    std::ostringstream stream;
    stream << warning_intro() << warning_message << warning_arg << warning_message2 << warning_arg2 << warning_message3 << warning_arg3 << warning_message4 << warning_arg4 << std::endl;
    ISSUE(_flag_type, stream);
}
template <class T, class T2, class T3, class T4>
void slv::flag::ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5) {
    std::ostringstream stream;
    stream << warning_intro() << warning_message << warning_arg << warning_message2 << warning_arg2 << warning_message3 << warning_arg3 << warning_message4 << warning_arg4 << warning_message5 << std::endl;
    ISSUE(_flag_type, stream);
}
template <class T, class T2, class T3, class T4, class T5>
void slv::flag::ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5, const T5& warning_arg5) {
    std::ostringstream stream;
    stream << warning_intro() << warning_message << warning_arg << warning_message2 << warning_arg2 << warning_message3 << warning_arg3 << warning_message4 << warning_arg4 << warning_message5 << warning_arg5 << std::endl;
    ISSUE(_flag_type, stream);
}
template <class T, class T2, class T3, class T4, class T5>
void slv::flag::ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5, const T5& warning_arg5, std::string warning_message6) {
    std::ostringstream stream;
    stream << warning_intro() << warning_message << warning_arg << warning_message2 << warning_arg2 << warning_message3 << warning_arg3 << warning_message4 << warning_arg4 << warning_message5 << warning_arg5 << warning_message6 << std::endl;
    ISSUE(_flag_type, stream);
}
template <class T, class T2, class T3, class T4, class T5, class T6>
void slv::flag::ISSUE(FlagType _flag_type, std::string warning_message, const T& warning_arg, std::string warning_message2, const T2& warning_arg2, std::string warning_message3, const T3& warning_arg3, std::string warning_message4, const T4& warning_arg4, std::string warning_message5, const T5& warning_arg5, std::string warning_message6, const T6& warning_arg6) {
    std::ostringstream stream;
    stream << warning_intro() << warning_message << warning_arg << warning_message2 << warning_arg2 << warning_message3 << warning_arg3 << warning_message4 << warning_arg4 << warning_message5 << warning_arg5 << warning_message6 << warning_arg6 << std::endl;
    ISSUE(_flag_type, stream);
}



template <class T>
void slv::flag::cout_ptr(const T& _value) {

    std::cout << _value;
}
template <class T>
void slv::flag::cout_ptr(const T* _value) {

    std::cout << *_value;
}

template <class T>
void slv::flag::cout_ptr(const std::string& _message, const T& _value) {

    std::cout << _message;
    cout_ptr(_value);
    std::cout << std::endl;
}
