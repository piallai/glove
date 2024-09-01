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

#define glvm_pv_get_macro_enum(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,\
		macro_arg, ...) macro_arg
#define glvm_SlvEnum(enum_Type, ...) EXPAND( glvm_pv_get_macro_enum(__VA_ARGS__,\
glvm_SlvEnum62, glvm_SlvEnum61, glvm_SlvEnum60, glvm_SlvEnum59, glvm_SlvEnum58, glvm_SlvEnum57, glvm_SlvEnum56, glvm_SlvEnum55, glvm_SlvEnum54, glvm_SlvEnum53, glvm_SlvEnum52, glvm_SlvEnum51, glvm_SlvEnum50, glvm_SlvEnum49, glvm_SlvEnum48, glvm_SlvEnum47, glvm_SlvEnum46, glvm_SlvEnum45, glvm_SlvEnum44, glvm_SlvEnum43, glvm_SlvEnum42, glvm_SlvEnum41, glvm_SlvEnum40, glvm_SlvEnum39, glvm_SlvEnum38, glvm_SlvEnum37, glvm_SlvEnum36, glvm_SlvEnum35, glvm_SlvEnum34, glvm_SlvEnum33, glvm_SlvEnum32, glvm_SlvEnum31, glvm_SlvEnum30, glvm_SlvEnum29, glvm_SlvEnum28, glvm_SlvEnum27, glvm_SlvEnum26, glvm_SlvEnum25, glvm_SlvEnum24, glvm_SlvEnum23, glvm_SlvEnum22, glvm_SlvEnum21, glvm_SlvEnum20, glvm_SlvEnum19, glvm_SlvEnum18, glvm_SlvEnum17, glvm_SlvEnum16, glvm_SlvEnum15, glvm_SlvEnum14, glvm_SlvEnum13, glvm_SlvEnum12, glvm_SlvEnum11, glvm_SlvEnum10, glvm_SlvEnum9, glvm_SlvEnum8, glvm_SlvEnum7, glvm_SlvEnum6, glvm_SlvEnum5, glvm_SlvEnum4, glvm_SlvEnum3, glvm_SlvEnum2, glvm_SlvEnum1)(enum_Type, __VA_ARGS__))

#define glvm_pv_get_macro_enum_named(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,\
		_1_n, _2_n, _3_n, _4_n, _5_n, _6_n, _7_n, _8_n, _9_n, _10_n, _11_n, _12_n, _13_n, _14_n, _15_n, _16_n, _17_n, _18_n, _19_n, _20_n, _21_n, _22_n, _23_n, _24_n, _25_n, _26_n, _27_n, _28_n, _29_n, _30_n, _31_n, _32_n, _33_n, _34_n, _35_n, _36_n, _37_n, _38_n, _39_n, _40_n, _41_n, _42_n, _43_n, _44_n, _45_n, _46_n, _47_n, _48_n, _49_n, _50_n, _51_n, _52_n, _53_n, _54_n, _55_n, _56_n, _57_n, _58_n, _59_n, _60_n, _61_n, _62_n,\
		macro_arg, ...) macro_arg
#define glvm_SlvEnum_named(enum_Type, ...) EXPAND( glvm_pv_get_macro_enum_named(__VA_ARGS__,\
glvm_SlvEnum62_named, _null62, glvm_SlvEnum61_named, _null61, glvm_SlvEnum60_named, _null60, glvm_SlvEnum59_named, _null59, glvm_SlvEnum58_named, _null58, glvm_SlvEnum57_named, _null57, glvm_SlvEnum56_named, _null56, glvm_SlvEnum55_named, _null55, glvm_SlvEnum54_named, _null54, glvm_SlvEnum53_named, _null53, glvm_SlvEnum52_named, _null52, glvm_SlvEnum51_named, _null51, glvm_SlvEnum50_named, _null50, glvm_SlvEnum49_named, _null49, glvm_SlvEnum48_named, _null48, glvm_SlvEnum47_named, _null47, glvm_SlvEnum46_named, _null46, glvm_SlvEnum45_named, _null45, glvm_SlvEnum44_named, _null44, glvm_SlvEnum43_named, _null43, glvm_SlvEnum42_named, _null42, glvm_SlvEnum41_named, _null41, glvm_SlvEnum40_named, _null40, glvm_SlvEnum39_named, _null39, glvm_SlvEnum38_named, _null38, glvm_SlvEnum37_named, _null37, glvm_SlvEnum36_named, _null36, glvm_SlvEnum35_named, _null35, glvm_SlvEnum34_named, _null34, glvm_SlvEnum33_named, _null33, glvm_SlvEnum32_named, _null32, glvm_SlvEnum31_named, _null31, glvm_SlvEnum30_named, _null30, glvm_SlvEnum29_named, _null29, glvm_SlvEnum28_named, _null28, glvm_SlvEnum27_named, _null27, glvm_SlvEnum26_named, _null26, glvm_SlvEnum25_named, _null25, glvm_SlvEnum24_named, _null24, glvm_SlvEnum23_named, _null23, glvm_SlvEnum22_named, _null22, glvm_SlvEnum21_named, _null21, glvm_SlvEnum20_named, _null20, glvm_SlvEnum19_named, _null19, glvm_SlvEnum18_named, _null18, glvm_SlvEnum17_named, _null17, glvm_SlvEnum16_named, _null16, glvm_SlvEnum15_named, _null15, glvm_SlvEnum14_named, _null14, glvm_SlvEnum13_named, _null13, glvm_SlvEnum12_named, _null12, glvm_SlvEnum11_named, _null11, glvm_SlvEnum10_named, _null10, glvm_SlvEnum9_named, _null9, glvm_SlvEnum8_named, _null8, glvm_SlvEnum7_named, _null7, glvm_SlvEnum6_named, _null6, glvm_SlvEnum5_named, _null5, glvm_SlvEnum4_named, _null4, glvm_SlvEnum3_named, _null3, glvm_SlvEnum2_named, _null2, glvm_SlvEnum1_named)(enum_Type, __VA_ARGS__))

#define glvm_pv_get_macro_enum_impl(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,\
		macro_arg, ...) macro_arg
#define glvm_SlvEnum_implementation(enum_Type, ...) EXPAND( glvm_pv_get_macro_enum_impl(__VA_ARGS__,\
glvm_SlvEnum62_implementation, glvm_SlvEnum61_implementation, glvm_SlvEnum60_implementation, glvm_SlvEnum59_implementation, glvm_SlvEnum58_implementation, glvm_SlvEnum57_implementation, glvm_SlvEnum56_implementation, glvm_SlvEnum55_implementation, glvm_SlvEnum54_implementation, glvm_SlvEnum53_implementation, glvm_SlvEnum52_implementation, glvm_SlvEnum51_implementation, glvm_SlvEnum50_implementation, glvm_SlvEnum49_implementation, glvm_SlvEnum48_implementation, glvm_SlvEnum47_implementation, glvm_SlvEnum46_implementation, glvm_SlvEnum45_implementation, glvm_SlvEnum44_implementation, glvm_SlvEnum43_implementation, glvm_SlvEnum42_implementation, glvm_SlvEnum41_implementation, glvm_SlvEnum40_implementation, glvm_SlvEnum39_implementation, glvm_SlvEnum38_implementation, glvm_SlvEnum37_implementation, glvm_SlvEnum36_implementation, glvm_SlvEnum35_implementation, glvm_SlvEnum34_implementation, glvm_SlvEnum33_implementation, glvm_SlvEnum32_implementation, glvm_SlvEnum31_implementation, glvm_SlvEnum30_implementation, glvm_SlvEnum29_implementation, glvm_SlvEnum28_implementation, glvm_SlvEnum27_implementation, glvm_SlvEnum26_implementation, glvm_SlvEnum25_implementation, glvm_SlvEnum24_implementation, glvm_SlvEnum23_implementation, glvm_SlvEnum22_implementation, glvm_SlvEnum21_implementation, glvm_SlvEnum20_implementation, glvm_SlvEnum19_implementation, glvm_SlvEnum18_implementation, glvm_SlvEnum17_implementation, glvm_SlvEnum16_implementation, glvm_SlvEnum15_implementation, glvm_SlvEnum14_implementation, glvm_SlvEnum13_implementation, glvm_SlvEnum12_implementation, glvm_SlvEnum11_implementation, glvm_SlvEnum10_implementation, glvm_SlvEnum9_implementation, glvm_SlvEnum8_implementation, glvm_SlvEnum7_implementation, glvm_SlvEnum6_implementation, glvm_SlvEnum5_implementation, glvm_SlvEnum4_implementation, glvm_SlvEnum3_implementation, glvm_SlvEnum2_implementation, glvm_SlvEnum1_implementation)(enum_Type, __VA_ARGS__))

#define glvm_pv_get_macro_enum_named_impl(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,\
		_1_n, _2_n, _3_n, _4_n, _5_n, _6_n, _7_n, _8_n, _9_n, _10_n, _11_n, _12_n, _13_n, _14_n, _15_n, _16_n, _17_n, _18_n, _19_n, _20_n, _21_n, _22_n, _23_n, _24_n, _25_n, _26_n, _27_n, _28_n, _29_n, _30_n, _31_n, _32_n, _33_n, _34_n, _35_n, _36_n, _37_n, _38_n, _39_n, _40_n, _41_n, _42_n, _43_n, _44_n, _45_n, _46_n, _47_n, _48_n, _49_n, _50_n, _51_n, _52_n, _53_n, _54_n, _55_n, _56_n, _57_n, _58_n, _59_n, _60_n, _61_n, _62_n,\
		macro_arg, ...) macro_arg
#define glvm_SlvEnum_named_implementation(enum_Type, ...) EXPAND( glvm_pv_get_macro_enum_named_impl(__VA_ARGS__,\
glvm_SlvEnum62_named_implementation, _null62, glvm_SlvEnum61_named_implementation, _null61, glvm_SlvEnum60_named_implementation, _null60, glvm_SlvEnum59_named_implementation, _null59, glvm_SlvEnum58_named_implementation, _null58, glvm_SlvEnum57_named_implementation, _null57, glvm_SlvEnum56_named_implementation, _null56, glvm_SlvEnum55_named_implementation, _null55, glvm_SlvEnum54_named_implementation, _null54, glvm_SlvEnum53_named_implementation, _null53, glvm_SlvEnum52_named_implementation, _null52, glvm_SlvEnum51_named_implementation, _null51, glvm_SlvEnum50_named_implementation, _null50, glvm_SlvEnum49_named_implementation, _null49, glvm_SlvEnum48_named_implementation, _null48, glvm_SlvEnum47_named_implementation, _null47, glvm_SlvEnum46_named_implementation, _null46, glvm_SlvEnum45_named_implementation, _null45, glvm_SlvEnum44_named_implementation, _null44, glvm_SlvEnum43_named_implementation, _null43, glvm_SlvEnum42_named_implementation, _null42, glvm_SlvEnum41_named_implementation, _null41, glvm_SlvEnum40_named_implementation, _null40, glvm_SlvEnum39_named_implementation, _null39, glvm_SlvEnum38_named_implementation, _null38, glvm_SlvEnum37_named_implementation, _null37, glvm_SlvEnum36_named_implementation, _null36, glvm_SlvEnum35_named_implementation, _null35, glvm_SlvEnum34_named_implementation, _null34, glvm_SlvEnum33_named_implementation, _null33, glvm_SlvEnum32_named_implementation, _null32, glvm_SlvEnum31_named_implementation, _null31, glvm_SlvEnum30_named_implementation, _null30, glvm_SlvEnum29_named_implementation, _null29, glvm_SlvEnum28_named_implementation, _null28, glvm_SlvEnum27_named_implementation, _null27, glvm_SlvEnum26_named_implementation, _null26, glvm_SlvEnum25_named_implementation, _null25, glvm_SlvEnum24_named_implementation, _null24, glvm_SlvEnum23_named_implementation, _null23, glvm_SlvEnum22_named_implementation, _null22, glvm_SlvEnum21_named_implementation, _null21, glvm_SlvEnum20_named_implementation, _null20, glvm_SlvEnum19_named_implementation, _null19, glvm_SlvEnum18_named_implementation, _null18, glvm_SlvEnum17_named_implementation, _null17, glvm_SlvEnum16_named_implementation, _null16, glvm_SlvEnum15_named_implementation, _null15, glvm_SlvEnum14_named_implementation, _null14, glvm_SlvEnum13_named_implementation, _null13, glvm_SlvEnum12_named_implementation, _null12, glvm_SlvEnum11_named_implementation, _null11, glvm_SlvEnum10_named_implementation, _null10, glvm_SlvEnum9_named_implementation, _null9, glvm_SlvEnum8_named_implementation, _null8, glvm_SlvEnum7_named_implementation, _null7, glvm_SlvEnum6_named_implementation, _null6, glvm_SlvEnum5_named_implementation, _null5, glvm_SlvEnum4_named_implementation, _null4, glvm_SlvEnum3_named_implementation, _null3, glvm_SlvEnum2_named_implementation, _null2, glvm_SlvEnum1_named_implementation)(enum_Type, __VA_ARGS__))
