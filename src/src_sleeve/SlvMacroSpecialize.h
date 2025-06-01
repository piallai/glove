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

// Inspired from https://stackoverflow.com/questions/11632219/c-preprocessor-macro-specialisation-based-on-an-argument

#define MACSPEC_CAT(a, ...) MACSPEC_PRIMITIVE_CAT(a, __VA_ARGS__)
#define MACSPEC_PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define MACSPEC_IIF(c) MACSPEC_PRIMITIVE_CAT(MACSPEC_IIF_, c)
#define MACSPEC_IIF_0(t, ...) __VA_ARGS__
#define MACSPEC_IIF_1(t, ...) t

#define MACSPEC_COMPL(b) MACSPEC_PRIMITIVE_CAT(MACSPEC_COMPL_, b)
#define MACSPEC_COMPL_0 1
#define MACSPEC_COMPL_1 0

#define MACSPEC_BITAND(x) MACSPEC_PRIMITIVE_CAT(MACSPEC_BITAND_, x)
#define MACSPEC_BITAND_0(y) 0
#define MACSPEC_BITAND_1(y) y

#define MACSPEC_MSVC_VA_ARGS_WORKAROUND(define, args) define args
#define MACSPEC_CHECK(...) MACSPEC_MSVC_VA_ARGS_WORKAROUND(MACSPEC_CHECK_N, (__VA_ARGS__, 0))
#define MACSPEC_CHECK_N(x, n, ...) n
#define MACSPEC_PROBE(x) x, 1,

#define MACSPEC_IS_PAREN(x) MACSPEC_CHECK(MACSPEC_IS_PAREN_PROBE x)
#define MACSPEC_IS_PAREN_PROBE(...) MACSPEC_PROBE(~)

#define MACSPEC_COMPARE(a, b) MACSPEC_PRIMITIVE_COMPARE(a, b)
#define MACSPEC_PRIMITIVE_COMPARE(a, b)\
    MACSPEC_IIF(\
        MACSPEC_BITAND\
            (MACSPEC_IS_PAREN(MACSPEC_COMPARE_ ## a(())))\
            (MACSPEC_IS_PAREN(MACSPEC_COMPARE_ ## b(())))\
    )( \
        MACSPEC_COMPL(MACSPEC_IS_PAREN(\
            MACSPEC_COMPARE_ ## a(\
                MACSPEC_COMPARE_ ## b\
            )(())\
        )),\
        0\
    )

