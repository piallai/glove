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

// Example data type
struct Foo {
	int a;
	Foo(int _a = 0) { a = _a; }
	bool operator!=(const Foo& _foo) const {// a != operator has to be defined for SlvParameterRuleT exception
		return a != _foo.a;
	}
	bool operator==(const Foo& _foo) const {// a != operator has to be defined for SlvParameterRuleT exception
		return a == _foo.a;
	}
#ifdef OPTION_FOO_AS_ARITHMETIC
	bool operator<(const Foo& _foo) const {
		return a < _foo.a;
	}
	bool operator>(const Foo& _foo) const {
		return a > _foo.a;
	}
	bool operator<=(const Foo& _foo) const {
		return a <= _foo.a;
	}
	bool operator>=(const Foo& _foo) const {
		return a >= _foo.a;
	}
	Foo& operator++() {
		a++;
		return *this;
	}
	Foo& operator--() {
		a--;
		return *this;
	}
#else
	void set_null() {
		a = -9999;//example of null value
	}
#endif
};

#include <iostream>
inline std::ostream& operator<<(std::ostream& _os, const Foo& _foo) {
	return _os << _foo.a;
}
inline std::istream& operator>>(std::istream& _is, Foo& _foo) {
	return _is >> _foo.a;
}

#ifdef OPTION_FOO_AS_ARITHMETIC

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "slv_is_arithmetic.h"
#else
#include "glove.h"
#endif
template <>
struct slv::ts::is_arithmetic<Foo> {
	static const bool value = true;
};

#endif