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

#include <type_traits>

/*! Can be used in GlvParamListDialog::filter_list<SlvIsSameFilter, Targ>().
* Possibility to filter list with filter structure and a template argument.*/
template <class T1, class T2, typename = void>
struct SlvIsSameFilter {
    static constexpr bool is_compatible = std::is_same<T1, T2>::value;
};
