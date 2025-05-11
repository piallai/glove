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

template <typename Tcontainer, typename = void>
struct SlvIsContainer {
    static constexpr bool value = false;
};

#include "SlvIsType.h"
glvm_SlvIsType(SlvHasValueType, value_type)

template <typename T, typename = void>
struct SlvIsIterable : std::false_type {};

template <typename T>
struct SlvIsIterable<T, std::void_t<decltype(std::begin(std::declval<T&>())), decltype(std::end(std::declval<T&>()))> > : std::true_type {
};

template <typename Tcontainer>
struct SlvIsContainer<Tcontainer, typename std::enable_if<SlvIsIterable<Tcontainer>::value && SlvHasValueType<Tcontainer>::value>::type> {
    static constexpr bool value = true;
};
