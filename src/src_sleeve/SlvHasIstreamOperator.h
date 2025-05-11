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

#include <iostream>
#include <type_traits>

template <typename T>
struct SlvHasIstreamOperator {
    template <typename V>
    static auto test(void*) -> decltype(std::declval<std::istream>() >> std::declval<V&>(), void());
    template <typename>
    static auto test(...) -> std::false_type;

    static constexpr bool value = std::is_same<decltype(test<T>(nullptr)), void>::value;
};
