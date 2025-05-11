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
struct SlvIsMap {
    static constexpr bool value = false;
};

#include <map>
template <class Tkey, class Tvalue>
struct SlvIsMap< std::map<Tkey, Tvalue> > {
    static constexpr bool value = true;
};

#include <unordered_map>
template <class Tkey, class Tvalue>
struct SlvIsMap< std::unordered_map<Tkey, Tvalue> > {
    static constexpr bool value = true;
};
