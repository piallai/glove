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

#include "List2.h"

template <class Tlist2Element, class Toption, typename = void>
struct List2Filter {
    static constexpr bool is_compatible = true;//whether Toption is compatible with Tlist2Element
};

template <class T>
struct List2Filter<ListElementD, T> {
	static constexpr bool is_compatible = false;//whether int is compatible with ListElementE
};
