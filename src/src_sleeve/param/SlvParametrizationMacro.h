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

#define EXPAND(arg) arg
#define glvm_pv_get_macro_parametrization(\
_1_1, _1_2, _1_3, _1_4, _1_5,\
_2_1, _2_2, _2_3, _2_4, _2_5,\
_3_1, _3_2, _3_3, _3_4, _3_5,\
_4_1, _4_2, _4_3, _4_4, _4_5,\
_5_1, _5_2, _5_3, _5_4, _5_5,\
_6_1, _6_2, _6_3, _6_4, _6_5,\
_7_1, _7_2, _7_3, _7_4, _7_5,\
_8_1, _8_2, _8_3, _8_4, _8_5,\
_9_1, _9_2, _9_3, _9_4, _9_5,\
_10_1, _10_2, _10_3, _10_4, _10_5,\
_11_1, _11_2, _11_3, _11_4, _11_5,\
_12_1, _12_2, _12_3, _12_4, _12_5,\
_13_1, _13_2, _13_3, _13_4, _13_5,\
_14_1, _14_2, _14_3, _14_4, _14_5,\
_15_1, _15_2, _15_3, _15_4, _15_5,\
_16_1, _16_2, _16_3, _16_4, _16_5,\
_17_1, _17_2, _17_3, _17_4, _17_5,\
_18_1, _18_2, _18_3, _18_4, _18_5,\
_19_1, _19_2, _19_3, _19_4, _19_5,\
_20_1, _20_2, _20_3, _20_4, _20_5,\
_21_1, _21_2, _21_3, _21_4, _21_5,\
_22_1, _22_2, _22_3, _22_4, _22_5,\
_23_1, _23_2, _23_3, _23_4, _23_5,\
_24_1, _24_2, _24_3, _24_4, _24_5,\
_25_1, _25_2, _25_3, _25_4, _25_5,\
macro_arg, ...) macro_arg

/*! Declare a parametrization class implementing only parameters.
* Convenient for quickly declare a class inheriting SlvParametrizationX.
* Does not allow rule management, all parameters are simply named, typed, and commented.*/
#define glvm_parametrization(class_declaration, class_name, ...) EXPAND( glvm_pv_get_macro_parametrization(__VA_ARGS__,\
glvm_parametrization25, _null25a, _null25b, _null25c, _null25d,\
glvm_parametrization24, _null24a, _null24b, _null24c, _null24d,\
glvm_parametrization23, _null23a, _null23b, _null23c, _null23d,\
glvm_parametrization22, _null22a, _null22b, _null22c, _null22d,\
glvm_parametrization21, _null21a, _null21b, _null21c, _null21d,\
glvm_parametrization20, _null20a, _null20b, _null20c, _null20d,\
glvm_parametrization19, _null19a, _null19b, _null19c, _null19d,\
glvm_parametrization18, _null18a, _null18b, _null18c, _null18d,\
glvm_parametrization17, _null17a, _null17b, _null17c, _null17d,\
glvm_parametrization16, _null16a, _null16b, _null16c, _null16d,\
glvm_parametrization15, _null15a, _null15b, _null15c, _null15d,\
glvm_parametrization14, _null14a, _null14b, _null14c, _null14d,\
glvm_parametrization13, _null13a, _null13b, _null13c, _null13d,\
glvm_parametrization12, _null12a, _null12b, _null12c, _null12d,\
glvm_parametrization11, _null11a, _null11b, _null11c, _null11d,\
glvm_parametrization10, _null10a, _null10b, _null10c, _null10d,\
glvm_parametrization9, _null9a, _null9b, _null9c, _null9d,\
glvm_parametrization8, _null8a, _null8b, _null8c, _null8d,\
glvm_parametrization7, _null7a, _null7b, _null7c, _null7d,\
glvm_parametrization6, _null6a, _null6b, _null6c, _null6d,\
glvm_parametrization5, _null5a, _null5b, _null5c, _null5d,\
glvm_parametrization4, _null4a, _null4b, _null4c, _null4d,\
glvm_parametrization3, _null3a, _null3b, _null3c, _null3d,\
glvm_parametrization2, _null2a, _null2b, _null2c, _null2d,\
glvm_parametrization1)(class_declaration, class_name, __VA_ARGS__))

#include "param/SlvParametrization1.h"
#define glvm_parametrization1(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
class class_declaration : public SlvParametrization1<param1_type> {\
glvm_parametrization1_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration) {}\
};

#include "param/SlvParametrization2.h"
#define glvm_parametrization2(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
class class_declaration : public SlvParametrization2<param1_type, param2_type> {\
glvm_parametrization2_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration) {}\
};

#include "param/SlvParametrization3.h"
#define glvm_parametrization3(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
class class_declaration : public SlvParametrization3<param1_type, param2_type, param3_type> {\
glvm_parametrization3_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration) {}\
};

#include "param/SlvParametrization4.h"
#define glvm_parametrization4(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
class class_declaration : public SlvParametrization4<param1_type, param2_type, param3_type, param4_type> {\
glvm_parametrization4_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration) {}\
};

#include "param/SlvParametrization5.h"
#define glvm_parametrization5(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
class class_declaration : public SlvParametrization5<param1_type, param2_type, param3_type, param4_type, param5_type> {\
glvm_parametrization5_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration) {}\
};

#include "param/SlvParametrization6.h"
#define glvm_parametrization6(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
class class_declaration : public SlvParametrization6<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type> {\
glvm_parametrization6_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration) {}\
};

#include "param/SlvParametrization7.h"
#define glvm_parametrization7(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
class class_declaration : public SlvParametrization7<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type> {\
glvm_parametrization7_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration) {}\
};

#include "param/SlvParametrization8.h"
#define glvm_parametrization8(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
class class_declaration : public SlvParametrization8<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type> {\
glvm_parametrization8_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration) {}\
};

#include "param/SlvParametrization9.h"
#define glvm_parametrization9(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
class class_declaration : public SlvParametrization9<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type> {\
glvm_parametrization9_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration) {}\
};

#include "param/SlvParametrization10.h"
#define glvm_parametrization10(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
class class_declaration : public SlvParametrization10<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type> {\
glvm_parametrization10_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration) {}\
};

#include "param/SlvParametrization11.h"
#define glvm_parametrization11(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value,\
param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
class class_declaration : public SlvParametrization11<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type, param11_type> {\
glvm_parametrization11_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
glvm_parameter(11, param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration, param11_declaration) {}\
};

#include "param/SlvParametrization12.h"
#define glvm_parametrization12(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value,\
param11_declaration, param11_type, param11_name, param11_comment, param11_default_value,\
param12_declaration, param12_type, param12_name, param12_comment, param12_default_value)\
class class_declaration : public SlvParametrization12<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type, param11_type, param12_type> {\
glvm_parametrization12_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
glvm_parameter(11, param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
glvm_parameter(12, param12_declaration, param12_type, param12_name, param12_comment, param12_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration, param11_declaration, param12_declaration) {}\
};

#include "param/SlvParametrization13.h"
#define glvm_parametrization13(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value,\
param11_declaration, param11_type, param11_name, param11_comment, param11_default_value,\
param12_declaration, param12_type, param12_name, param12_comment, param12_default_value,\
param13_declaration, param13_type, param13_name, param13_comment, param13_default_value)\
class class_declaration : public SlvParametrization13<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type, param11_type, param12_type, param13_type> {\
glvm_parametrization13_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
glvm_parameter(11, param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
glvm_parameter(12, param12_declaration, param12_type, param12_name, param12_comment, param12_default_value)\
glvm_parameter(13, param13_declaration, param13_type, param13_name, param13_comment, param13_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration, param11_declaration, param12_declaration, param13_declaration) {}\
};

#include "param/SlvParametrization14.h"
#define glvm_parametrization14(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value,\
param11_declaration, param11_type, param11_name, param11_comment, param11_default_value,\
param12_declaration, param12_type, param12_name, param12_comment, param12_default_value,\
param13_declaration, param13_type, param13_name, param13_comment, param13_default_value,\
param14_declaration, param14_type, param14_name, param14_comment, param14_default_value)\
class class_declaration : public SlvParametrization14<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type, param11_type, param12_type, param13_type, param14_type> {\
glvm_parametrization14_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
glvm_parameter(11, param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
glvm_parameter(12, param12_declaration, param12_type, param12_name, param12_comment, param12_default_value)\
glvm_parameter(13, param13_declaration, param13_type, param13_name, param13_comment, param13_default_value)\
glvm_parameter(14, param14_declaration, param14_type, param14_name, param14_comment, param14_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration, param11_declaration, param12_declaration, param13_declaration, param14_declaration) {}\
};

#include "param/SlvParametrization15.h"
#define glvm_parametrization15(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value,\
param11_declaration, param11_type, param11_name, param11_comment, param11_default_value,\
param12_declaration, param12_type, param12_name, param12_comment, param12_default_value,\
param13_declaration, param13_type, param13_name, param13_comment, param13_default_value,\
param14_declaration, param14_type, param14_name, param14_comment, param14_default_value,\
param15_declaration, param15_type, param15_name, param15_comment, param15_default_value)\
class class_declaration : public SlvParametrization15<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type, param11_type, param12_type, param13_type, param14_type, param15_type> {\
glvm_parametrization15_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
glvm_parameter(11, param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
glvm_parameter(12, param12_declaration, param12_type, param12_name, param12_comment, param12_default_value)\
glvm_parameter(13, param13_declaration, param13_type, param13_name, param13_comment, param13_default_value)\
glvm_parameter(14, param14_declaration, param14_type, param14_name, param14_comment, param14_default_value)\
glvm_parameter(15, param15_declaration, param15_type, param15_name, param15_comment, param15_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration, param11_declaration, param12_declaration, param13_declaration, param14_declaration, param15_declaration) {}\
};

#include "param/SlvParametrization16.h"
#define glvm_parametrization16(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value,\
param11_declaration, param11_type, param11_name, param11_comment, param11_default_value,\
param12_declaration, param12_type, param12_name, param12_comment, param12_default_value,\
param13_declaration, param13_type, param13_name, param13_comment, param13_default_value,\
param14_declaration, param14_type, param14_name, param14_comment, param14_default_value,\
param15_declaration, param15_type, param15_name, param15_comment, param15_default_value,\
param16_declaration, param16_type, param16_name, param16_comment, param16_default_value)\
class class_declaration : public SlvParametrization16<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type, param11_type, param12_type, param13_type, param14_type, param15_type, param16_type> {\
glvm_parametrization16_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
glvm_parameter(11, param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
glvm_parameter(12, param12_declaration, param12_type, param12_name, param12_comment, param12_default_value)\
glvm_parameter(13, param13_declaration, param13_type, param13_name, param13_comment, param13_default_value)\
glvm_parameter(14, param14_declaration, param14_type, param14_name, param14_comment, param14_default_value)\
glvm_parameter(15, param15_declaration, param15_type, param15_name, param15_comment, param15_default_value)\
glvm_parameter(16, param16_declaration, param16_type, param16_name, param16_comment, param16_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration, param11_declaration, param12_declaration, param13_declaration, param14_declaration, param15_declaration, param16_declaration) {}\
};

#include "param/SlvParametrization17.h"
#define glvm_parametrization17(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value,\
param11_declaration, param11_type, param11_name, param11_comment, param11_default_value,\
param12_declaration, param12_type, param12_name, param12_comment, param12_default_value,\
param13_declaration, param13_type, param13_name, param13_comment, param13_default_value,\
param14_declaration, param14_type, param14_name, param14_comment, param14_default_value,\
param15_declaration, param15_type, param15_name, param15_comment, param15_default_value,\
param16_declaration, param16_type, param16_name, param16_comment, param16_default_value,\
param17_declaration, param17_type, param17_name, param17_comment, param17_default_value)\
class class_declaration : public SlvParametrization17<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type, param11_type, param12_type, param13_type, param14_type, param15_type, param16_type, param17_type> {\
glvm_parametrization17_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
glvm_parameter(11, param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
glvm_parameter(12, param12_declaration, param12_type, param12_name, param12_comment, param12_default_value)\
glvm_parameter(13, param13_declaration, param13_type, param13_name, param13_comment, param13_default_value)\
glvm_parameter(14, param14_declaration, param14_type, param14_name, param14_comment, param14_default_value)\
glvm_parameter(15, param15_declaration, param15_type, param15_name, param15_comment, param15_default_value)\
glvm_parameter(16, param16_declaration, param16_type, param16_name, param16_comment, param16_default_value)\
glvm_parameter(17, param17_declaration, param17_type, param17_name, param17_comment, param17_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration, param11_declaration, param12_declaration, param13_declaration, param14_declaration, param15_declaration, param16_declaration, param17_declaration) {}\
};

#include "param/SlvParametrization18.h"
#define glvm_parametrization18(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value,\
param11_declaration, param11_type, param11_name, param11_comment, param11_default_value,\
param12_declaration, param12_type, param12_name, param12_comment, param12_default_value,\
param13_declaration, param13_type, param13_name, param13_comment, param13_default_value,\
param14_declaration, param14_type, param14_name, param14_comment, param14_default_value,\
param15_declaration, param15_type, param15_name, param15_comment, param15_default_value,\
param16_declaration, param16_type, param16_name, param16_comment, param16_default_value,\
param17_declaration, param17_type, param17_name, param17_comment, param17_default_value,\
param18_declaration, param18_type, param18_name, param18_comment, param18_default_value)\
class class_declaration : public SlvParametrization18<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type, param11_type, param12_type, param13_type, param14_type, param15_type, param16_type, param17_type, param18_type> {\
glvm_parametrization18_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
glvm_parameter(11, param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
glvm_parameter(12, param12_declaration, param12_type, param12_name, param12_comment, param12_default_value)\
glvm_parameter(13, param13_declaration, param13_type, param13_name, param13_comment, param13_default_value)\
glvm_parameter(14, param14_declaration, param14_type, param14_name, param14_comment, param14_default_value)\
glvm_parameter(15, param15_declaration, param15_type, param15_name, param15_comment, param15_default_value)\
glvm_parameter(16, param16_declaration, param16_type, param16_name, param16_comment, param16_default_value)\
glvm_parameter(17, param17_declaration, param17_type, param17_name, param17_comment, param17_default_value)\
glvm_parameter(18, param18_declaration, param18_type, param18_name, param18_comment, param18_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration, param11_declaration, param12_declaration, param13_declaration, param14_declaration, param15_declaration, param16_declaration, param17_declaration, param18_declaration) {}\
};

#include "param/SlvParametrization19.h"
#define glvm_parametrization19(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value,\
param11_declaration, param11_type, param11_name, param11_comment, param11_default_value,\
param12_declaration, param12_type, param12_name, param12_comment, param12_default_value,\
param13_declaration, param13_type, param13_name, param13_comment, param13_default_value,\
param14_declaration, param14_type, param14_name, param14_comment, param14_default_value,\
param15_declaration, param15_type, param15_name, param15_comment, param15_default_value,\
param16_declaration, param16_type, param16_name, param16_comment, param16_default_value,\
param17_declaration, param17_type, param17_name, param17_comment, param17_default_value,\
param18_declaration, param18_type, param18_name, param18_comment, param18_default_value,\
param19_declaration, param19_type, param19_name, param19_comment, param19_default_value)\
class class_declaration : public SlvParametrization19<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type, param11_type, param12_type, param13_type, param14_type, param15_type, param16_type, param17_type, param18_type, param19_type> {\
glvm_parametrization19_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
glvm_parameter(11, param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
glvm_parameter(12, param12_declaration, param12_type, param12_name, param12_comment, param12_default_value)\
glvm_parameter(13, param13_declaration, param13_type, param13_name, param13_comment, param13_default_value)\
glvm_parameter(14, param14_declaration, param14_type, param14_name, param14_comment, param14_default_value)\
glvm_parameter(15, param15_declaration, param15_type, param15_name, param15_comment, param15_default_value)\
glvm_parameter(16, param16_declaration, param16_type, param16_name, param16_comment, param16_default_value)\
glvm_parameter(17, param17_declaration, param17_type, param17_name, param17_comment, param17_default_value)\
glvm_parameter(18, param18_declaration, param18_type, param18_name, param18_comment, param18_default_value)\
glvm_parameter(19, param19_declaration, param19_type, param19_name, param19_comment, param19_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration, param11_declaration, param12_declaration, param13_declaration, param14_declaration, param15_declaration, param16_declaration, param17_declaration, param18_declaration, param19_declaration) {}\
};

#include "param/SlvParametrization20.h"
#define glvm_parametrization20(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value,\
param11_declaration, param11_type, param11_name, param11_comment, param11_default_value,\
param12_declaration, param12_type, param12_name, param12_comment, param12_default_value,\
param13_declaration, param13_type, param13_name, param13_comment, param13_default_value,\
param14_declaration, param14_type, param14_name, param14_comment, param14_default_value,\
param15_declaration, param15_type, param15_name, param15_comment, param15_default_value,\
param16_declaration, param16_type, param16_name, param16_comment, param16_default_value,\
param17_declaration, param17_type, param17_name, param17_comment, param17_default_value,\
param18_declaration, param18_type, param18_name, param18_comment, param18_default_value,\
param19_declaration, param19_type, param19_name, param19_comment, param19_default_value,\
param20_declaration, param20_type, param20_name, param20_comment, param20_default_value)\
class class_declaration : public SlvParametrization20<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type, param11_type, param12_type, param13_type, param14_type, param15_type, param16_type, param17_type, param18_type, param19_type, param20_type> {\
glvm_parametrization20_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
glvm_parameter(11, param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
glvm_parameter(12, param12_declaration, param12_type, param12_name, param12_comment, param12_default_value)\
glvm_parameter(13, param13_declaration, param13_type, param13_name, param13_comment, param13_default_value)\
glvm_parameter(14, param14_declaration, param14_type, param14_name, param14_comment, param14_default_value)\
glvm_parameter(15, param15_declaration, param15_type, param15_name, param15_comment, param15_default_value)\
glvm_parameter(16, param16_declaration, param16_type, param16_name, param16_comment, param16_default_value)\
glvm_parameter(17, param17_declaration, param17_type, param17_name, param17_comment, param17_default_value)\
glvm_parameter(18, param18_declaration, param18_type, param18_name, param18_comment, param18_default_value)\
glvm_parameter(19, param19_declaration, param19_type, param19_name, param19_comment, param19_default_value)\
glvm_parameter(20, param20_declaration, param20_type, param20_name, param20_comment, param20_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration, param11_declaration, param12_declaration, param13_declaration, param14_declaration, param15_declaration, param16_declaration, param17_declaration, param18_declaration, param19_declaration, param20_declaration) {}\
};

#include "param/SlvParametrization21.h"
#define glvm_parametrization21(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value,\
param11_declaration, param11_type, param11_name, param11_comment, param11_default_value,\
param12_declaration, param12_type, param12_name, param12_comment, param12_default_value,\
param13_declaration, param13_type, param13_name, param13_comment, param13_default_value,\
param14_declaration, param14_type, param14_name, param14_comment, param14_default_value,\
param15_declaration, param15_type, param15_name, param15_comment, param15_default_value,\
param16_declaration, param16_type, param16_name, param16_comment, param16_default_value,\
param17_declaration, param17_type, param17_name, param17_comment, param17_default_value,\
param18_declaration, param18_type, param18_name, param18_comment, param18_default_value,\
param19_declaration, param19_type, param19_name, param19_comment, param19_default_value,\
param20_declaration, param20_type, param20_name, param20_comment, param20_default_value,\
param21_declaration, param21_type, param21_name, param21_comment, param21_default_value)\
class class_declaration : public SlvParametrization21<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type, param11_type, param12_type, param13_type, param14_type, param15_type, param16_type, param17_type, param18_type, param19_type, param20_type, param21_type> {\
glvm_parametrization21_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
glvm_parameter(11, param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
glvm_parameter(12, param12_declaration, param12_type, param12_name, param12_comment, param12_default_value)\
glvm_parameter(13, param13_declaration, param13_type, param13_name, param13_comment, param13_default_value)\
glvm_parameter(14, param14_declaration, param14_type, param14_name, param14_comment, param14_default_value)\
glvm_parameter(15, param15_declaration, param15_type, param15_name, param15_comment, param15_default_value)\
glvm_parameter(16, param16_declaration, param16_type, param16_name, param16_comment, param16_default_value)\
glvm_parameter(17, param17_declaration, param17_type, param17_name, param17_comment, param17_default_value)\
glvm_parameter(18, param18_declaration, param18_type, param18_name, param18_comment, param18_default_value)\
glvm_parameter(19, param19_declaration, param19_type, param19_name, param19_comment, param19_default_value)\
glvm_parameter(20, param20_declaration, param20_type, param20_name, param20_comment, param20_default_value)\
glvm_parameter(21, param21_declaration, param21_type, param21_name, param21_comment, param21_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration, param11_declaration, param12_declaration, param13_declaration, param14_declaration, param15_declaration, param16_declaration, param17_declaration, param18_declaration, param19_declaration, param20_declaration, param21_declaration) {}\
};

#include "param/SlvParametrization22.h"
#define glvm_parametrization22(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value,\
param11_declaration, param11_type, param11_name, param11_comment, param11_default_value,\
param12_declaration, param12_type, param12_name, param12_comment, param12_default_value,\
param13_declaration, param13_type, param13_name, param13_comment, param13_default_value,\
param14_declaration, param14_type, param14_name, param14_comment, param14_default_value,\
param15_declaration, param15_type, param15_name, param15_comment, param15_default_value,\
param16_declaration, param16_type, param16_name, param16_comment, param16_default_value,\
param17_declaration, param17_type, param17_name, param17_comment, param17_default_value,\
param18_declaration, param18_type, param18_name, param18_comment, param18_default_value,\
param19_declaration, param19_type, param19_name, param19_comment, param19_default_value,\
param20_declaration, param20_type, param20_name, param20_comment, param20_default_value,\
param21_declaration, param21_type, param21_name, param21_comment, param21_default_value,\
param22_declaration, param22_type, param22_name, param22_comment, param22_default_value)\
class class_declaration : public SlvParametrization22<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type, param11_type, param12_type, param13_type, param14_type, param15_type, param16_type, param17_type, param18_type, param19_type, param20_type, param21_type, param22_type> {\
glvm_parametrization22_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
glvm_parameter(11, param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
glvm_parameter(12, param12_declaration, param12_type, param12_name, param12_comment, param12_default_value)\
glvm_parameter(13, param13_declaration, param13_type, param13_name, param13_comment, param13_default_value)\
glvm_parameter(14, param14_declaration, param14_type, param14_name, param14_comment, param14_default_value)\
glvm_parameter(15, param15_declaration, param15_type, param15_name, param15_comment, param15_default_value)\
glvm_parameter(16, param16_declaration, param16_type, param16_name, param16_comment, param16_default_value)\
glvm_parameter(17, param17_declaration, param17_type, param17_name, param17_comment, param17_default_value)\
glvm_parameter(18, param18_declaration, param18_type, param18_name, param18_comment, param18_default_value)\
glvm_parameter(19, param19_declaration, param19_type, param19_name, param19_comment, param19_default_value)\
glvm_parameter(20, param20_declaration, param20_type, param20_name, param20_comment, param20_default_value)\
glvm_parameter(21, param21_declaration, param21_type, param21_name, param21_comment, param21_default_value)\
glvm_parameter(22, param22_declaration, param22_type, param22_name, param22_comment, param22_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration, param11_declaration, param12_declaration, param13_declaration, param14_declaration, param15_declaration, param16_declaration, param17_declaration, param18_declaration, param19_declaration, param20_declaration, param21_declaration, param22_declaration) {}\
};

#include "param/SlvParametrization23.h"
#define glvm_parametrization23(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value,\
param11_declaration, param11_type, param11_name, param11_comment, param11_default_value,\
param12_declaration, param12_type, param12_name, param12_comment, param12_default_value,\
param13_declaration, param13_type, param13_name, param13_comment, param13_default_value,\
param14_declaration, param14_type, param14_name, param14_comment, param14_default_value,\
param15_declaration, param15_type, param15_name, param15_comment, param15_default_value,\
param16_declaration, param16_type, param16_name, param16_comment, param16_default_value,\
param17_declaration, param17_type, param17_name, param17_comment, param17_default_value,\
param18_declaration, param18_type, param18_name, param18_comment, param18_default_value,\
param19_declaration, param19_type, param19_name, param19_comment, param19_default_value,\
param20_declaration, param20_type, param20_name, param20_comment, param20_default_value,\
param21_declaration, param21_type, param21_name, param21_comment, param21_default_value,\
param22_declaration, param22_type, param22_name, param22_comment, param22_default_value,\
param23_declaration, param23_type, param23_name, param23_comment, param23_default_value)\
class class_declaration : public SlvParametrization23<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type, param11_type, param12_type, param13_type, param14_type, param15_type, param16_type, param17_type, param18_type, param19_type, param20_type, param21_type, param22_type, param23_type> {\
glvm_parametrization23_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
glvm_parameter(11, param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
glvm_parameter(12, param12_declaration, param12_type, param12_name, param12_comment, param12_default_value)\
glvm_parameter(13, param13_declaration, param13_type, param13_name, param13_comment, param13_default_value)\
glvm_parameter(14, param14_declaration, param14_type, param14_name, param14_comment, param14_default_value)\
glvm_parameter(15, param15_declaration, param15_type, param15_name, param15_comment, param15_default_value)\
glvm_parameter(16, param16_declaration, param16_type, param16_name, param16_comment, param16_default_value)\
glvm_parameter(17, param17_declaration, param17_type, param17_name, param17_comment, param17_default_value)\
glvm_parameter(18, param18_declaration, param18_type, param18_name, param18_comment, param18_default_value)\
glvm_parameter(19, param19_declaration, param19_type, param19_name, param19_comment, param19_default_value)\
glvm_parameter(20, param20_declaration, param20_type, param20_name, param20_comment, param20_default_value)\
glvm_parameter(21, param21_declaration, param21_type, param21_name, param21_comment, param21_default_value)\
glvm_parameter(22, param22_declaration, param22_type, param22_name, param22_comment, param22_default_value)\
glvm_parameter(23, param23_declaration, param23_type, param23_name, param23_comment, param23_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration, param11_declaration, param12_declaration, param13_declaration, param14_declaration, param15_declaration, param16_declaration, param17_declaration, param18_declaration, param19_declaration, param20_declaration, param21_declaration, param22_declaration, param23_declaration) {}\
};

#include "param/SlvParametrization24.h"
#define glvm_parametrization24(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value,\
param11_declaration, param11_type, param11_name, param11_comment, param11_default_value,\
param12_declaration, param12_type, param12_name, param12_comment, param12_default_value,\
param13_declaration, param13_type, param13_name, param13_comment, param13_default_value,\
param14_declaration, param14_type, param14_name, param14_comment, param14_default_value,\
param15_declaration, param15_type, param15_name, param15_comment, param15_default_value,\
param16_declaration, param16_type, param16_name, param16_comment, param16_default_value,\
param17_declaration, param17_type, param17_name, param17_comment, param17_default_value,\
param18_declaration, param18_type, param18_name, param18_comment, param18_default_value,\
param19_declaration, param19_type, param19_name, param19_comment, param19_default_value,\
param20_declaration, param20_type, param20_name, param20_comment, param20_default_value,\
param21_declaration, param21_type, param21_name, param21_comment, param21_default_value,\
param22_declaration, param22_type, param22_name, param22_comment, param22_default_value,\
param23_declaration, param23_type, param23_name, param23_comment, param23_default_value,\
param24_declaration, param24_type, param24_name, param24_comment, param24_default_value)\
class class_declaration : public SlvParametrization24<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type, param11_type, param12_type, param13_type, param14_type, param15_type, param16_type, param17_type, param18_type, param19_type, param20_type, param21_type, param22_type, param23_type, param24_type> {\
glvm_parametrization24_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
glvm_parameter(11, param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
glvm_parameter(12, param12_declaration, param12_type, param12_name, param12_comment, param12_default_value)\
glvm_parameter(13, param13_declaration, param13_type, param13_name, param13_comment, param13_default_value)\
glvm_parameter(14, param14_declaration, param14_type, param14_name, param14_comment, param14_default_value)\
glvm_parameter(15, param15_declaration, param15_type, param15_name, param15_comment, param15_default_value)\
glvm_parameter(16, param16_declaration, param16_type, param16_name, param16_comment, param16_default_value)\
glvm_parameter(17, param17_declaration, param17_type, param17_name, param17_comment, param17_default_value)\
glvm_parameter(18, param18_declaration, param18_type, param18_name, param18_comment, param18_default_value)\
glvm_parameter(19, param19_declaration, param19_type, param19_name, param19_comment, param19_default_value)\
glvm_parameter(20, param20_declaration, param20_type, param20_name, param20_comment, param20_default_value)\
glvm_parameter(21, param21_declaration, param21_type, param21_name, param21_comment, param21_default_value)\
glvm_parameter(22, param22_declaration, param22_type, param22_name, param22_comment, param22_default_value)\
glvm_parameter(23, param23_declaration, param23_type, param23_name, param23_comment, param23_default_value)\
glvm_parameter(24, param24_declaration, param24_type, param24_name, param24_comment, param24_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration, param11_declaration, param12_declaration, param13_declaration, param14_declaration, param15_declaration, param16_declaration, param17_declaration, param18_declaration, param19_declaration, param20_declaration, param21_declaration, param22_declaration, param23_declaration, param24_declaration) {}\
};

#include "param/SlvParametrization25.h"
#define glvm_parametrization25(class_declaration, class_name, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value,\
param2_declaration, param2_type, param2_name, param2_comment, param2_default_value,\
param3_declaration, param3_type, param3_name, param3_comment, param3_default_value,\
param4_declaration, param4_type, param4_name, param4_comment, param4_default_value,\
param5_declaration, param5_type, param5_name, param5_comment, param5_default_value,\
param6_declaration, param6_type, param6_name, param6_comment, param6_default_value,\
param7_declaration, param7_type, param7_name, param7_comment, param7_default_value,\
param8_declaration, param8_type, param8_name, param8_comment, param8_default_value,\
param9_declaration, param9_type, param9_name, param9_comment, param9_default_value,\
param10_declaration, param10_type, param10_name, param10_comment, param10_default_value,\
param11_declaration, param11_type, param11_name, param11_comment, param11_default_value,\
param12_declaration, param12_type, param12_name, param12_comment, param12_default_value,\
param13_declaration, param13_type, param13_name, param13_comment, param13_default_value,\
param14_declaration, param14_type, param14_name, param14_comment, param14_default_value,\
param15_declaration, param15_type, param15_name, param15_comment, param15_default_value,\
param16_declaration, param16_type, param16_name, param16_comment, param16_default_value,\
param17_declaration, param17_type, param17_name, param17_comment, param17_default_value,\
param18_declaration, param18_type, param18_name, param18_comment, param18_default_value,\
param19_declaration, param19_type, param19_name, param19_comment, param19_default_value,\
param20_declaration, param20_type, param20_name, param20_comment, param20_default_value,\
param21_declaration, param21_type, param21_name, param21_comment, param21_default_value,\
param22_declaration, param22_type, param22_name, param22_comment, param22_default_value,\
param23_declaration, param23_type, param23_name, param23_comment, param23_default_value,\
param24_declaration, param24_type, param24_name, param24_comment, param24_default_value,\
param25_declaration, param25_type, param25_name, param25_comment, param25_default_value)\
class class_declaration : public SlvParametrization25<param1_type, param2_type, param3_type, param4_type, param5_type, param6_type, param7_type, param8_type, param9_type, param10_type, param11_type, param12_type, param13_type, param14_type, param15_type, param16_type, param17_type, param18_type, param19_type, param20_type, param21_type, param22_type, param23_type, param24_type, param25_type> {\
glvm_parametrization25_init(class_name)\
glvm_parameter(1, param1_declaration, param1_type, param1_name, param1_comment, param1_default_value)\
glvm_parameter(2, param2_declaration, param2_type, param2_name, param2_comment, param2_default_value)\
glvm_parameter(3, param3_declaration, param3_type, param3_name, param3_comment, param3_default_value)\
glvm_parameter(4, param4_declaration, param4_type, param4_name, param4_comment, param4_default_value)\
glvm_parameter(5, param5_declaration, param5_type, param5_name, param5_comment, param5_default_value)\
glvm_parameter(6, param6_declaration, param6_type, param6_name, param6_comment, param6_default_value)\
glvm_parameter(7, param7_declaration, param7_type, param7_name, param7_comment, param7_default_value)\
glvm_parameter(8, param8_declaration, param8_type, param8_name, param8_comment, param8_default_value)\
glvm_parameter(9, param9_declaration, param9_type, param9_name, param9_comment, param9_default_value)\
glvm_parameter(10, param10_declaration, param10_type, param10_name, param10_comment, param10_default_value)\
glvm_parameter(11, param11_declaration, param11_type, param11_name, param11_comment, param11_default_value)\
glvm_parameter(12, param12_declaration, param12_type, param12_name, param12_comment, param12_default_value)\
glvm_parameter(13, param13_declaration, param13_type, param13_name, param13_comment, param13_default_value)\
glvm_parameter(14, param14_declaration, param14_type, param14_name, param14_comment, param14_default_value)\
glvm_parameter(15, param15_declaration, param15_type, param15_name, param15_comment, param15_default_value)\
glvm_parameter(16, param16_declaration, param16_type, param16_name, param16_comment, param16_default_value)\
glvm_parameter(17, param17_declaration, param17_type, param17_name, param17_comment, param17_default_value)\
glvm_parameter(18, param18_declaration, param18_type, param18_name, param18_comment, param18_default_value)\
glvm_parameter(19, param19_declaration, param19_type, param19_name, param19_comment, param19_default_value)\
glvm_parameter(20, param20_declaration, param20_type, param20_name, param20_comment, param20_default_value)\
glvm_parameter(21, param21_declaration, param21_type, param21_name, param21_comment, param21_default_value)\
glvm_parameter(22, param22_declaration, param22_type, param22_name, param22_comment, param22_default_value)\
glvm_parameter(23, param23_declaration, param23_type, param23_name, param23_comment, param23_default_value)\
glvm_parameter(24, param24_declaration, param24_type, param24_name, param24_comment, param24_default_value)\
glvm_parameter(25, param25_declaration, param25_type, param25_name, param25_comment, param25_default_value)\
public:\
class_declaration() :glvm_parametrization_constructor(param1_declaration, param2_declaration, param3_declaration, param4_declaration, param5_declaration, param6_declaration, param7_declaration, param8_declaration, param9_declaration, param10_declaration, param11_declaration, param12_declaration, param13_declaration, param14_declaration, param15_declaration, param16_declaration, param17_declaration, param18_declaration, param19_declaration, param20_declaration, param21_declaration, param22_declaration, param23_declaration, param24_declaration, param25_declaration) {}\
};

