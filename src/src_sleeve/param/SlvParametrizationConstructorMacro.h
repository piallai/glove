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
#define glvm_pv_parametrization_constructor(\
_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24,\
macro_arg, ...) macro_arg

/*! Define parametrization constructor.*/
#define glvm_parametrization_constructor(...) EXPAND( glvm_pv_parametrization_constructor(__VA_ARGS__,\
glvm_parametrization24_constructor,\
glvm_parametrization23_constructor,\
glvm_parametrization22_constructor,\
glvm_parametrization21_constructor,\
glvm_parametrization20_constructor,\
glvm_parametrization19_constructor,\
glvm_parametrization18_constructor,\
glvm_parametrization17_constructor,\
glvm_parametrization16_constructor,\
glvm_parametrization15_constructor,\
glvm_parametrization14_constructor,\
glvm_parametrization13_constructor,\
glvm_parametrization12_constructor,\
glvm_parametrization11_constructor,\
glvm_parametrization10_constructor,\
glvm_parametrization9_constructor,\
glvm_parametrization8_constructor,\
glvm_parametrization7_constructor,\
glvm_parametrization6_constructor,\
glvm_parametrization5_constructor,\
glvm_parametrization4_constructor,\
glvm_parametrization3_constructor,\
glvm_parametrization2_constructor,\
glvm_parametrization1_constructor)(__VA_ARGS__))


#define glvm_parametrization0_constructor()\
SlvParametrization0

#define glvm_parametrization1_constructor(\
param1_decl)\
SlvParametrization1<typename SlvPvClassParam_##param1_decl::Tparam>(new SlvPvClassParam_##param1_decl(this)\
)

#define glvm_parametrization2_constructor(\
param1_decl,\
param2_decl)\
SlvParametrization2<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this)\
)

#define glvm_parametrization3_constructor(\
param1_decl,\
param2_decl,\
param3_decl)\
SlvParametrization3<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this)\
)

#define glvm_parametrization4_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl)\
SlvParametrization4<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this)\
)

#define glvm_parametrization5_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl)\
SlvParametrization5<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this)\
)

#define glvm_parametrization6_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl)\
SlvParametrization6<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this)\
)

#define glvm_parametrization7_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl)\
SlvParametrization7<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this)\
)

#define glvm_parametrization8_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl)\
SlvParametrization8<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this)\
)

#define glvm_parametrization9_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl)\
SlvParametrization9<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this)\
)

#define glvm_parametrization10_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl,\
param10_decl)\
SlvParametrization10<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam, typename SlvPvClassParam_##param10_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this),\
new SlvPvClassParam_##param10_decl(this)\
)

#define glvm_parametrization11_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl,\
param10_decl,\
param11_decl)\
SlvParametrization11<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam, typename SlvPvClassParam_##param10_decl::Tparam, typename SlvPvClassParam_##param11_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this),\
new SlvPvClassParam_##param10_decl(this),\
new SlvPvClassParam_##param11_decl(this)\
)

#define glvm_parametrization12_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl,\
param10_decl,\
param11_decl,\
param12_decl)\
SlvParametrization12<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam, typename SlvPvClassParam_##param10_decl::Tparam, typename SlvPvClassParam_##param11_decl::Tparam, typename SlvPvClassParam_##param12_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this),\
new SlvPvClassParam_##param10_decl(this),\
new SlvPvClassParam_##param11_decl(this),\
new SlvPvClassParam_##param12_decl(this)\
)

#define glvm_parametrization13_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl,\
param10_decl,\
param11_decl,\
param12_decl,\
param13_decl)\
SlvParametrization13<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam, typename SlvPvClassParam_##param10_decl::Tparam, typename SlvPvClassParam_##param11_decl::Tparam, typename SlvPvClassParam_##param12_decl::Tparam, typename SlvPvClassParam_##param13_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this),\
new SlvPvClassParam_##param10_decl(this),\
new SlvPvClassParam_##param11_decl(this),\
new SlvPvClassParam_##param12_decl(this),\
new SlvPvClassParam_##param13_decl(this)\
)

#define glvm_parametrization14_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl,\
param10_decl,\
param11_decl,\
param12_decl,\
param13_decl,\
param14_decl)\
SlvParametrization14<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam, typename SlvPvClassParam_##param10_decl::Tparam, typename SlvPvClassParam_##param11_decl::Tparam, typename SlvPvClassParam_##param12_decl::Tparam, typename SlvPvClassParam_##param13_decl::Tparam, typename SlvPvClassParam_##param14_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this),\
new SlvPvClassParam_##param10_decl(this),\
new SlvPvClassParam_##param11_decl(this),\
new SlvPvClassParam_##param12_decl(this),\
new SlvPvClassParam_##param13_decl(this),\
new SlvPvClassParam_##param14_decl(this)\
)

#define glvm_parametrization15_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl,\
param10_decl,\
param11_decl,\
param12_decl,\
param13_decl,\
param14_decl,\
param15_decl)\
SlvParametrization15<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam, typename SlvPvClassParam_##param10_decl::Tparam, typename SlvPvClassParam_##param11_decl::Tparam, typename SlvPvClassParam_##param12_decl::Tparam, typename SlvPvClassParam_##param13_decl::Tparam, typename SlvPvClassParam_##param14_decl::Tparam, typename SlvPvClassParam_##param15_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this),\
new SlvPvClassParam_##param10_decl(this),\
new SlvPvClassParam_##param11_decl(this),\
new SlvPvClassParam_##param12_decl(this),\
new SlvPvClassParam_##param13_decl(this),\
new SlvPvClassParam_##param14_decl(this),\
new SlvPvClassParam_##param15_decl(this)\
)

#define glvm_parametrization16_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl,\
param10_decl,\
param11_decl,\
param12_decl,\
param13_decl,\
param14_decl,\
param15_decl,\
param16_decl)\
SlvParametrization16<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam, typename SlvPvClassParam_##param10_decl::Tparam, typename SlvPvClassParam_##param11_decl::Tparam, typename SlvPvClassParam_##param12_decl::Tparam, typename SlvPvClassParam_##param13_decl::Tparam, typename SlvPvClassParam_##param14_decl::Tparam, typename SlvPvClassParam_##param15_decl::Tparam, typename SlvPvClassParam_##param16_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this),\
new SlvPvClassParam_##param10_decl(this),\
new SlvPvClassParam_##param11_decl(this),\
new SlvPvClassParam_##param12_decl(this),\
new SlvPvClassParam_##param13_decl(this),\
new SlvPvClassParam_##param14_decl(this),\
new SlvPvClassParam_##param15_decl(this),\
new SlvPvClassParam_##param16_decl(this)\
)

#define glvm_parametrization17_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl,\
param10_decl,\
param11_decl,\
param12_decl,\
param13_decl,\
param14_decl,\
param15_decl,\
param16_decl,\
param17_decl)\
SlvParametrization17<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam, typename SlvPvClassParam_##param10_decl::Tparam, typename SlvPvClassParam_##param11_decl::Tparam, typename SlvPvClassParam_##param12_decl::Tparam, typename SlvPvClassParam_##param13_decl::Tparam, typename SlvPvClassParam_##param14_decl::Tparam, typename SlvPvClassParam_##param15_decl::Tparam, typename SlvPvClassParam_##param16_decl::Tparam, typename SlvPvClassParam_##param17_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this),\
new SlvPvClassParam_##param10_decl(this),\
new SlvPvClassParam_##param11_decl(this),\
new SlvPvClassParam_##param12_decl(this),\
new SlvPvClassParam_##param13_decl(this),\
new SlvPvClassParam_##param14_decl(this),\
new SlvPvClassParam_##param15_decl(this),\
new SlvPvClassParam_##param16_decl(this),\
new SlvPvClassParam_##param17_decl(this)\
)

#define glvm_parametrization18_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl,\
param10_decl,\
param11_decl,\
param12_decl,\
param13_decl,\
param14_decl,\
param15_decl,\
param16_decl,\
param17_decl,\
param18_decl)\
SlvParametrization18<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam, typename SlvPvClassParam_##param10_decl::Tparam, typename SlvPvClassParam_##param11_decl::Tparam, typename SlvPvClassParam_##param12_decl::Tparam, typename SlvPvClassParam_##param13_decl::Tparam, typename SlvPvClassParam_##param14_decl::Tparam, typename SlvPvClassParam_##param15_decl::Tparam, typename SlvPvClassParam_##param16_decl::Tparam, typename SlvPvClassParam_##param17_decl::Tparam, typename SlvPvClassParam_##param18_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this),\
new SlvPvClassParam_##param10_decl(this),\
new SlvPvClassParam_##param11_decl(this),\
new SlvPvClassParam_##param12_decl(this),\
new SlvPvClassParam_##param13_decl(this),\
new SlvPvClassParam_##param14_decl(this),\
new SlvPvClassParam_##param15_decl(this),\
new SlvPvClassParam_##param16_decl(this),\
new SlvPvClassParam_##param17_decl(this),\
new SlvPvClassParam_##param18_decl(this)\
)

#define glvm_parametrization19_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl,\
param10_decl,\
param11_decl,\
param12_decl,\
param13_decl,\
param14_decl,\
param15_decl,\
param16_decl,\
param17_decl,\
param18_decl,\
param19_decl)\
SlvParametrization19<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam, typename SlvPvClassParam_##param10_decl::Tparam, typename SlvPvClassParam_##param11_decl::Tparam, typename SlvPvClassParam_##param12_decl::Tparam, typename SlvPvClassParam_##param13_decl::Tparam, typename SlvPvClassParam_##param14_decl::Tparam, typename SlvPvClassParam_##param15_decl::Tparam, typename SlvPvClassParam_##param16_decl::Tparam, typename SlvPvClassParam_##param17_decl::Tparam, typename SlvPvClassParam_##param18_decl::Tparam, typename SlvPvClassParam_##param19_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this),\
new SlvPvClassParam_##param10_decl(this),\
new SlvPvClassParam_##param11_decl(this),\
new SlvPvClassParam_##param12_decl(this),\
new SlvPvClassParam_##param13_decl(this),\
new SlvPvClassParam_##param14_decl(this),\
new SlvPvClassParam_##param15_decl(this),\
new SlvPvClassParam_##param16_decl(this),\
new SlvPvClassParam_##param17_decl(this),\
new SlvPvClassParam_##param18_decl(this),\
new SlvPvClassParam_##param19_decl(this)\
)

#define glvm_parametrization20_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl,\
param10_decl,\
param11_decl,\
param12_decl,\
param13_decl,\
param14_decl,\
param15_decl,\
param16_decl,\
param17_decl,\
param18_decl,\
param19_decl,\
param20_decl)\
SlvParametrization20<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam, typename SlvPvClassParam_##param10_decl::Tparam, typename SlvPvClassParam_##param11_decl::Tparam, typename SlvPvClassParam_##param12_decl::Tparam, typename SlvPvClassParam_##param13_decl::Tparam, typename SlvPvClassParam_##param14_decl::Tparam, typename SlvPvClassParam_##param15_decl::Tparam, typename SlvPvClassParam_##param16_decl::Tparam, typename SlvPvClassParam_##param17_decl::Tparam, typename SlvPvClassParam_##param18_decl::Tparam, typename SlvPvClassParam_##param19_decl::Tparam, typename SlvPvClassParam_##param20_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this),\
new SlvPvClassParam_##param10_decl(this),\
new SlvPvClassParam_##param11_decl(this),\
new SlvPvClassParam_##param12_decl(this),\
new SlvPvClassParam_##param13_decl(this),\
new SlvPvClassParam_##param14_decl(this),\
new SlvPvClassParam_##param15_decl(this),\
new SlvPvClassParam_##param16_decl(this),\
new SlvPvClassParam_##param17_decl(this),\
new SlvPvClassParam_##param18_decl(this),\
new SlvPvClassParam_##param19_decl(this),\
new SlvPvClassParam_##param20_decl(this)\
)

#define glvm_parametrization21_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl,\
param10_decl,\
param11_decl,\
param12_decl,\
param13_decl,\
param14_decl,\
param15_decl,\
param16_decl,\
param17_decl,\
param18_decl,\
param19_decl,\
param20_decl,\
param21_decl)\
SlvParametrization21<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam, typename SlvPvClassParam_##param10_decl::Tparam, typename SlvPvClassParam_##param11_decl::Tparam, typename SlvPvClassParam_##param12_decl::Tparam, typename SlvPvClassParam_##param13_decl::Tparam, typename SlvPvClassParam_##param14_decl::Tparam, typename SlvPvClassParam_##param15_decl::Tparam, typename SlvPvClassParam_##param16_decl::Tparam, typename SlvPvClassParam_##param17_decl::Tparam, typename SlvPvClassParam_##param18_decl::Tparam, typename SlvPvClassParam_##param19_decl::Tparam, typename SlvPvClassParam_##param20_decl::Tparam, typename SlvPvClassParam_##param21_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this),\
new SlvPvClassParam_##param10_decl(this),\
new SlvPvClassParam_##param11_decl(this),\
new SlvPvClassParam_##param12_decl(this),\
new SlvPvClassParam_##param13_decl(this),\
new SlvPvClassParam_##param14_decl(this),\
new SlvPvClassParam_##param15_decl(this),\
new SlvPvClassParam_##param16_decl(this),\
new SlvPvClassParam_##param17_decl(this),\
new SlvPvClassParam_##param18_decl(this),\
new SlvPvClassParam_##param19_decl(this),\
new SlvPvClassParam_##param20_decl(this),\
new SlvPvClassParam_##param21_decl(this)\
)

#define glvm_parametrization22_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl,\
param10_decl,\
param11_decl,\
param12_decl,\
param13_decl,\
param14_decl,\
param15_decl,\
param16_decl,\
param17_decl,\
param18_decl,\
param19_decl,\
param20_decl,\
param21_decl,\
param22_decl)\
SlvParametrization22<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam, typename SlvPvClassParam_##param10_decl::Tparam, typename SlvPvClassParam_##param11_decl::Tparam, typename SlvPvClassParam_##param12_decl::Tparam, typename SlvPvClassParam_##param13_decl::Tparam, typename SlvPvClassParam_##param14_decl::Tparam, typename SlvPvClassParam_##param15_decl::Tparam, typename SlvPvClassParam_##param16_decl::Tparam, typename SlvPvClassParam_##param17_decl::Tparam, typename SlvPvClassParam_##param18_decl::Tparam, typename SlvPvClassParam_##param19_decl::Tparam, typename SlvPvClassParam_##param20_decl::Tparam, typename SlvPvClassParam_##param21_decl::Tparam, typename SlvPvClassParam_##param22_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this),\
new SlvPvClassParam_##param10_decl(this),\
new SlvPvClassParam_##param11_decl(this),\
new SlvPvClassParam_##param12_decl(this),\
new SlvPvClassParam_##param13_decl(this),\
new SlvPvClassParam_##param14_decl(this),\
new SlvPvClassParam_##param15_decl(this),\
new SlvPvClassParam_##param16_decl(this),\
new SlvPvClassParam_##param17_decl(this),\
new SlvPvClassParam_##param18_decl(this),\
new SlvPvClassParam_##param19_decl(this),\
new SlvPvClassParam_##param20_decl(this),\
new SlvPvClassParam_##param21_decl(this),\
new SlvPvClassParam_##param22_decl(this)\
)

#define glvm_parametrization23_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl,\
param10_decl,\
param11_decl,\
param12_decl,\
param13_decl,\
param14_decl,\
param15_decl,\
param16_decl,\
param17_decl,\
param18_decl,\
param19_decl,\
param20_decl,\
param21_decl,\
param22_decl,\
param23_decl)\
SlvParametrization23<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam, typename SlvPvClassParam_##param10_decl::Tparam, typename SlvPvClassParam_##param11_decl::Tparam, typename SlvPvClassParam_##param12_decl::Tparam, typename SlvPvClassParam_##param13_decl::Tparam, typename SlvPvClassParam_##param14_decl::Tparam, typename SlvPvClassParam_##param15_decl::Tparam, typename SlvPvClassParam_##param16_decl::Tparam, typename SlvPvClassParam_##param17_decl::Tparam, typename SlvPvClassParam_##param18_decl::Tparam, typename SlvPvClassParam_##param19_decl::Tparam, typename SlvPvClassParam_##param20_decl::Tparam, typename SlvPvClassParam_##param21_decl::Tparam, typename SlvPvClassParam_##param22_decl::Tparam, typename SlvPvClassParam_##param23_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this),\
new SlvPvClassParam_##param10_decl(this),\
new SlvPvClassParam_##param11_decl(this),\
new SlvPvClassParam_##param12_decl(this),\
new SlvPvClassParam_##param13_decl(this),\
new SlvPvClassParam_##param14_decl(this),\
new SlvPvClassParam_##param15_decl(this),\
new SlvPvClassParam_##param16_decl(this),\
new SlvPvClassParam_##param17_decl(this),\
new SlvPvClassParam_##param18_decl(this),\
new SlvPvClassParam_##param19_decl(this),\
new SlvPvClassParam_##param20_decl(this),\
new SlvPvClassParam_##param21_decl(this),\
new SlvPvClassParam_##param22_decl(this),\
new SlvPvClassParam_##param23_decl(this)\
)

#define glvm_parametrization24_constructor(\
param1_decl,\
param2_decl,\
param3_decl,\
param4_decl,\
param5_decl,\
param6_decl,\
param7_decl,\
param8_decl,\
param9_decl,\
param10_decl,\
param11_decl,\
param12_decl,\
param13_decl,\
param14_decl,\
param15_decl,\
param16_decl,\
param17_decl,\
param18_decl,\
param19_decl,\
param20_decl,\
param21_decl,\
param22_decl,\
param23_decl,\
param24_decl)\
SlvParametrization24<typename SlvPvClassParam_##param1_decl::Tparam, typename SlvPvClassParam_##param2_decl::Tparam, typename SlvPvClassParam_##param3_decl::Tparam, typename SlvPvClassParam_##param4_decl::Tparam, typename SlvPvClassParam_##param5_decl::Tparam, typename SlvPvClassParam_##param6_decl::Tparam, typename SlvPvClassParam_##param7_decl::Tparam, typename SlvPvClassParam_##param8_decl::Tparam, typename SlvPvClassParam_##param9_decl::Tparam, typename SlvPvClassParam_##param10_decl::Tparam, typename SlvPvClassParam_##param11_decl::Tparam, typename SlvPvClassParam_##param12_decl::Tparam, typename SlvPvClassParam_##param13_decl::Tparam, typename SlvPvClassParam_##param14_decl::Tparam, typename SlvPvClassParam_##param15_decl::Tparam, typename SlvPvClassParam_##param16_decl::Tparam, typename SlvPvClassParam_##param17_decl::Tparam, typename SlvPvClassParam_##param18_decl::Tparam, typename SlvPvClassParam_##param19_decl::Tparam, typename SlvPvClassParam_##param20_decl::Tparam, typename SlvPvClassParam_##param21_decl::Tparam, typename SlvPvClassParam_##param22_decl::Tparam, typename SlvPvClassParam_##param23_decl::Tparam, typename SlvPvClassParam_##param24_decl::Tparam>(new SlvPvClassParam_##param1_decl(this),\
new SlvPvClassParam_##param2_decl(this),\
new SlvPvClassParam_##param3_decl(this),\
new SlvPvClassParam_##param4_decl(this),\
new SlvPvClassParam_##param5_decl(this),\
new SlvPvClassParam_##param6_decl(this),\
new SlvPvClassParam_##param7_decl(this),\
new SlvPvClassParam_##param8_decl(this),\
new SlvPvClassParam_##param9_decl(this),\
new SlvPvClassParam_##param10_decl(this),\
new SlvPvClassParam_##param11_decl(this),\
new SlvPvClassParam_##param12_decl(this),\
new SlvPvClassParam_##param13_decl(this),\
new SlvPvClassParam_##param14_decl(this),\
new SlvPvClassParam_##param15_decl(this),\
new SlvPvClassParam_##param16_decl(this),\
new SlvPvClassParam_##param17_decl(this),\
new SlvPvClassParam_##param18_decl(this),\
new SlvPvClassParam_##param19_decl(this),\
new SlvPvClassParam_##param20_decl(this),\
new SlvPvClassParam_##param21_decl(this),\
new SlvPvClassParam_##param22_decl(this),\
new SlvPvClassParam_##param23_decl(this),\
new SlvPvClassParam_##param24_decl(this)\
)

#define glvm_parametrization_name(_name)\
glvm_staticVariable_const_get(std::string, name, _name);

#define glvm_parametrization0_static_init \
public:\
static bool has_rules() {\
return false;\
}\
private:

#define glvm_parametrization0_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization0_static_init

#define glvm_parametrization1_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules();\
}\
private:

#define glvm_parametrization1_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization1_static_init

#define glvm_parametrization2_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules();\
}\
private:

#define glvm_parametrization2_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization2_static_init

#define glvm_parametrization3_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules();\
}\
private:

#define glvm_parametrization3_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization3_static_init

#define glvm_parametrization4_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules();\
}\
private:

#define glvm_parametrization4_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization4_static_init

#define glvm_parametrization5_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules();\
}\
private:

#define glvm_parametrization5_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization5_static_init

#define glvm_parametrization6_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules();\
}\
private:

#define glvm_parametrization6_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization6_static_init

#define glvm_parametrization7_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules();\
}\
private:

#define glvm_parametrization7_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization7_static_init

#define glvm_parametrization8_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules();\
}\
private:

#define glvm_parametrization8_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization8_static_init

#define glvm_parametrization9_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules();\
}\
private:

#define glvm_parametrization9_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization9_static_init

#define glvm_parametrization10_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules()\
 || Tpv_parameter10::has_rules();\
}\
private:

#define glvm_parametrization10_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization10_static_init

#define glvm_parametrization11_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules()\
 || Tpv_parameter10::has_rules()\
 || Tpv_parameter11::has_rules();\
}\
private:

#define glvm_parametrization11_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization11_static_init

#define glvm_parametrization12_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules()\
 || Tpv_parameter10::has_rules()\
 || Tpv_parameter11::has_rules()\
 || Tpv_parameter12::has_rules();\
}\
private:

#define glvm_parametrization12_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization12_static_init

#define glvm_parametrization13_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules()\
 || Tpv_parameter10::has_rules()\
 || Tpv_parameter11::has_rules()\
 || Tpv_parameter12::has_rules()\
 || Tpv_parameter13::has_rules();\
}\
private:

#define glvm_parametrization13_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization13_static_init

#define glvm_parametrization14_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules()\
 || Tpv_parameter10::has_rules()\
 || Tpv_parameter11::has_rules()\
 || Tpv_parameter12::has_rules()\
 || Tpv_parameter13::has_rules()\
 || Tpv_parameter14::has_rules();\
}\
private:

#define glvm_parametrization14_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization14_static_init

#define glvm_parametrization15_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules()\
 || Tpv_parameter10::has_rules()\
 || Tpv_parameter11::has_rules()\
 || Tpv_parameter12::has_rules()\
 || Tpv_parameter13::has_rules()\
 || Tpv_parameter14::has_rules()\
 || Tpv_parameter15::has_rules();\
}\
private:

#define glvm_parametrization15_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization15_static_init

#define glvm_parametrization16_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules()\
 || Tpv_parameter10::has_rules()\
 || Tpv_parameter11::has_rules()\
 || Tpv_parameter12::has_rules()\
 || Tpv_parameter13::has_rules()\
 || Tpv_parameter14::has_rules()\
 || Tpv_parameter15::has_rules()\
 || Tpv_parameter16::has_rules();\
}\
private:

#define glvm_parametrization16_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization16_static_init

#define glvm_parametrization17_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules()\
 || Tpv_parameter10::has_rules()\
 || Tpv_parameter11::has_rules()\
 || Tpv_parameter12::has_rules()\
 || Tpv_parameter13::has_rules()\
 || Tpv_parameter14::has_rules()\
 || Tpv_parameter15::has_rules()\
 || Tpv_parameter16::has_rules()\
 || Tpv_parameter17::has_rules();\
}\
private:

#define glvm_parametrization17_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization17_static_init

#define glvm_parametrization18_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules()\
 || Tpv_parameter10::has_rules()\
 || Tpv_parameter11::has_rules()\
 || Tpv_parameter12::has_rules()\
 || Tpv_parameter13::has_rules()\
 || Tpv_parameter14::has_rules()\
 || Tpv_parameter15::has_rules()\
 || Tpv_parameter16::has_rules()\
 || Tpv_parameter17::has_rules()\
 || Tpv_parameter18::has_rules();\
}\
private:

#define glvm_parametrization18_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization18_static_init

#define glvm_parametrization19_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules()\
 || Tpv_parameter10::has_rules()\
 || Tpv_parameter11::has_rules()\
 || Tpv_parameter12::has_rules()\
 || Tpv_parameter13::has_rules()\
 || Tpv_parameter14::has_rules()\
 || Tpv_parameter15::has_rules()\
 || Tpv_parameter16::has_rules()\
 || Tpv_parameter17::has_rules()\
 || Tpv_parameter18::has_rules()\
 || Tpv_parameter19::has_rules();\
}\
private:

#define glvm_parametrization19_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization19_static_init

#define glvm_parametrization20_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules()\
 || Tpv_parameter10::has_rules()\
 || Tpv_parameter11::has_rules()\
 || Tpv_parameter12::has_rules()\
 || Tpv_parameter13::has_rules()\
 || Tpv_parameter14::has_rules()\
 || Tpv_parameter15::has_rules()\
 || Tpv_parameter16::has_rules()\
 || Tpv_parameter17::has_rules()\
 || Tpv_parameter18::has_rules()\
 || Tpv_parameter19::has_rules()\
 || Tpv_parameter20::has_rules();\
}\
private:

#define glvm_parametrization20_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization20_static_init

#define glvm_parametrization21_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules()\
 || Tpv_parameter10::has_rules()\
 || Tpv_parameter11::has_rules()\
 || Tpv_parameter12::has_rules()\
 || Tpv_parameter13::has_rules()\
 || Tpv_parameter14::has_rules()\
 || Tpv_parameter15::has_rules()\
 || Tpv_parameter16::has_rules()\
 || Tpv_parameter17::has_rules()\
 || Tpv_parameter18::has_rules()\
 || Tpv_parameter19::has_rules()\
 || Tpv_parameter20::has_rules()\
 || Tpv_parameter21::has_rules();\
}\
private:

#define glvm_parametrization21_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization21_static_init

#define glvm_parametrization22_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules()\
 || Tpv_parameter10::has_rules()\
 || Tpv_parameter11::has_rules()\
 || Tpv_parameter12::has_rules()\
 || Tpv_parameter13::has_rules()\
 || Tpv_parameter14::has_rules()\
 || Tpv_parameter15::has_rules()\
 || Tpv_parameter16::has_rules()\
 || Tpv_parameter17::has_rules()\
 || Tpv_parameter18::has_rules()\
 || Tpv_parameter19::has_rules()\
 || Tpv_parameter20::has_rules()\
 || Tpv_parameter21::has_rules()\
 || Tpv_parameter22::has_rules();\
}\
private:

#define glvm_parametrization22_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization22_static_init

#define glvm_parametrization23_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules()\
 || Tpv_parameter10::has_rules()\
 || Tpv_parameter11::has_rules()\
 || Tpv_parameter12::has_rules()\
 || Tpv_parameter13::has_rules()\
 || Tpv_parameter14::has_rules()\
 || Tpv_parameter15::has_rules()\
 || Tpv_parameter16::has_rules()\
 || Tpv_parameter17::has_rules()\
 || Tpv_parameter18::has_rules()\
 || Tpv_parameter19::has_rules()\
 || Tpv_parameter20::has_rules()\
 || Tpv_parameter21::has_rules()\
 || Tpv_parameter22::has_rules()\
 || Tpv_parameter23::has_rules();\
}\
private:

#define glvm_parametrization23_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization23_static_init

#define glvm_parametrization24_static_init \
public:\
static bool has_rules() {\
return Tpv_parameter1::has_rules()\
 || Tpv_parameter2::has_rules()\
 || Tpv_parameter3::has_rules()\
 || Tpv_parameter4::has_rules()\
 || Tpv_parameter5::has_rules()\
 || Tpv_parameter6::has_rules()\
 || Tpv_parameter7::has_rules()\
 || Tpv_parameter8::has_rules()\
 || Tpv_parameter9::has_rules()\
 || Tpv_parameter10::has_rules()\
 || Tpv_parameter11::has_rules()\
 || Tpv_parameter12::has_rules()\
 || Tpv_parameter13::has_rules()\
 || Tpv_parameter14::has_rules()\
 || Tpv_parameter15::has_rules()\
 || Tpv_parameter16::has_rules()\
 || Tpv_parameter17::has_rules()\
 || Tpv_parameter18::has_rules()\
 || Tpv_parameter19::has_rules()\
 || Tpv_parameter20::has_rules()\
 || Tpv_parameter21::has_rules()\
 || Tpv_parameter22::has_rules()\
 || Tpv_parameter23::has_rules()\
 || Tpv_parameter24::has_rules();\
}\
private:

#define glvm_parametrization24_init(_name)\
glvm_parametrization_name(_name);\
glvm_parametrization24_static_init

#define glvm_parametrization1_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;

#define glvm_parametrization2_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;

#define glvm_parametrization3_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;

#define glvm_parametrization4_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;

#define glvm_parametrization5_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;

#define glvm_parametrization6_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;

#define glvm_parametrization7_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;

#define glvm_parametrization8_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;

#define glvm_parametrization9_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;

#define glvm_parametrization10_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;\
using typename base_class::Tpv_parameter10;

#define glvm_parametrization11_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;\
using typename base_class::Tpv_parameter10;\
using typename base_class::Tpv_parameter11;

#define glvm_parametrization12_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;\
using typename base_class::Tpv_parameter10;\
using typename base_class::Tpv_parameter11;\
using typename base_class::Tpv_parameter12;

#define glvm_parametrization13_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;\
using typename base_class::Tpv_parameter10;\
using typename base_class::Tpv_parameter11;\
using typename base_class::Tpv_parameter12;\
using typename base_class::Tpv_parameter13;

#define glvm_parametrization14_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;\
using typename base_class::Tpv_parameter10;\
using typename base_class::Tpv_parameter11;\
using typename base_class::Tpv_parameter12;\
using typename base_class::Tpv_parameter13;\
using typename base_class::Tpv_parameter14;

#define glvm_parametrization15_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;\
using typename base_class::Tpv_parameter10;\
using typename base_class::Tpv_parameter11;\
using typename base_class::Tpv_parameter12;\
using typename base_class::Tpv_parameter13;\
using typename base_class::Tpv_parameter14;\
using typename base_class::Tpv_parameter15;

#define glvm_parametrization16_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;\
using typename base_class::Tpv_parameter10;\
using typename base_class::Tpv_parameter11;\
using typename base_class::Tpv_parameter12;\
using typename base_class::Tpv_parameter13;\
using typename base_class::Tpv_parameter14;\
using typename base_class::Tpv_parameter15;\
using typename base_class::Tpv_parameter16;

#define glvm_parametrization17_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;\
using typename base_class::Tpv_parameter10;\
using typename base_class::Tpv_parameter11;\
using typename base_class::Tpv_parameter12;\
using typename base_class::Tpv_parameter13;\
using typename base_class::Tpv_parameter14;\
using typename base_class::Tpv_parameter15;\
using typename base_class::Tpv_parameter16;\
using typename base_class::Tpv_parameter17;

#define glvm_parametrization18_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;\
using typename base_class::Tpv_parameter10;\
using typename base_class::Tpv_parameter11;\
using typename base_class::Tpv_parameter12;\
using typename base_class::Tpv_parameter13;\
using typename base_class::Tpv_parameter14;\
using typename base_class::Tpv_parameter15;\
using typename base_class::Tpv_parameter16;\
using typename base_class::Tpv_parameter17;\
using typename base_class::Tpv_parameter18;

#define glvm_parametrization19_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;\
using typename base_class::Tpv_parameter10;\
using typename base_class::Tpv_parameter11;\
using typename base_class::Tpv_parameter12;\
using typename base_class::Tpv_parameter13;\
using typename base_class::Tpv_parameter14;\
using typename base_class::Tpv_parameter15;\
using typename base_class::Tpv_parameter16;\
using typename base_class::Tpv_parameter17;\
using typename base_class::Tpv_parameter18;\
using typename base_class::Tpv_parameter19;

#define glvm_parametrization20_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;\
using typename base_class::Tpv_parameter10;\
using typename base_class::Tpv_parameter11;\
using typename base_class::Tpv_parameter12;\
using typename base_class::Tpv_parameter13;\
using typename base_class::Tpv_parameter14;\
using typename base_class::Tpv_parameter15;\
using typename base_class::Tpv_parameter16;\
using typename base_class::Tpv_parameter17;\
using typename base_class::Tpv_parameter18;\
using typename base_class::Tpv_parameter19;\
using typename base_class::Tpv_parameter20;

#define glvm_parametrization21_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;\
using typename base_class::Tpv_parameter10;\
using typename base_class::Tpv_parameter11;\
using typename base_class::Tpv_parameter12;\
using typename base_class::Tpv_parameter13;\
using typename base_class::Tpv_parameter14;\
using typename base_class::Tpv_parameter15;\
using typename base_class::Tpv_parameter16;\
using typename base_class::Tpv_parameter17;\
using typename base_class::Tpv_parameter18;\
using typename base_class::Tpv_parameter19;\
using typename base_class::Tpv_parameter20;\
using typename base_class::Tpv_parameter21;

#define glvm_parametrization22_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;\
using typename base_class::Tpv_parameter10;\
using typename base_class::Tpv_parameter11;\
using typename base_class::Tpv_parameter12;\
using typename base_class::Tpv_parameter13;\
using typename base_class::Tpv_parameter14;\
using typename base_class::Tpv_parameter15;\
using typename base_class::Tpv_parameter16;\
using typename base_class::Tpv_parameter17;\
using typename base_class::Tpv_parameter18;\
using typename base_class::Tpv_parameter19;\
using typename base_class::Tpv_parameter20;\
using typename base_class::Tpv_parameter21;\
using typename base_class::Tpv_parameter22;

#define glvm_parametrization23_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;\
using typename base_class::Tpv_parameter10;\
using typename base_class::Tpv_parameter11;\
using typename base_class::Tpv_parameter12;\
using typename base_class::Tpv_parameter13;\
using typename base_class::Tpv_parameter14;\
using typename base_class::Tpv_parameter15;\
using typename base_class::Tpv_parameter16;\
using typename base_class::Tpv_parameter17;\
using typename base_class::Tpv_parameter18;\
using typename base_class::Tpv_parameter19;\
using typename base_class::Tpv_parameter20;\
using typename base_class::Tpv_parameter21;\
using typename base_class::Tpv_parameter22;\
using typename base_class::Tpv_parameter23;

#define glvm_parametrization24_inherited_template_init(base_class)\
using typename base_class::Tpv_parameter1;\
using typename base_class::Tpv_parameter2;\
using typename base_class::Tpv_parameter3;\
using typename base_class::Tpv_parameter4;\
using typename base_class::Tpv_parameter5;\
using typename base_class::Tpv_parameter6;\
using typename base_class::Tpv_parameter7;\
using typename base_class::Tpv_parameter8;\
using typename base_class::Tpv_parameter9;\
using typename base_class::Tpv_parameter10;\
using typename base_class::Tpv_parameter11;\
using typename base_class::Tpv_parameter12;\
using typename base_class::Tpv_parameter13;\
using typename base_class::Tpv_parameter14;\
using typename base_class::Tpv_parameter15;\
using typename base_class::Tpv_parameter16;\
using typename base_class::Tpv_parameter17;\
using typename base_class::Tpv_parameter18;\
using typename base_class::Tpv_parameter19;\
using typename base_class::Tpv_parameter20;\
using typename base_class::Tpv_parameter21;\
using typename base_class::Tpv_parameter22;\
using typename base_class::Tpv_parameter23;\
using typename base_class::Tpv_parameter24;

