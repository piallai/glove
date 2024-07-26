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

#define _COMMA ,
#define _PARENTHESIS1 (
#define _PARENTHESIS2 )

#define COMMA _COMMA
#define PARENTHESIS1 _PARENTHESIS1
#define PARENTHESIS2 _PARENTHESIS2

#define BRACKET1 {
#define BRACKET2 }

#define _STRINGIFY(arg) #arg
#define STRINGIFY(arg) _STRINGIFY(arg)

#define EXPAND(arg) arg

#define MYDEBUG1(value1) std::cout << std::string(#value1) +" = " << value1 << std::endl;
#define MYDEBUG2(value1,value2) std::cout << std::string(#value1) +" = " << value1 << std::string(", ")+ #value2 + " = " << value2 << std::endl;

#define INCLUDE_HEADER(file_name) STRINGIFY(file_name.h)

//OS TYPE MACROS
#ifdef _WIN32
#define OS_WIN
#ifdef _WIN64
#define OS_WIN
#endif
#elif __APPLE__
#if TARGET_OS_MAC
#define OS_MAC
#else
#   error "Apple platform not managed"
#endif
#elif __linux__
#define OS_LINUX
#elif __unix__ // all "unices" not caught above
#define OS_UNIX
#else
#   error "Compiler not managed"
#endif

#if defined(__clang__)
#define COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
#define COMPILER_GCC
#elif defined(_MSC_VER)
#define COMPILER_MSVC
#endif
