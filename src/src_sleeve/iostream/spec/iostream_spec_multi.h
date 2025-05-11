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

//! This header is only useful for clang compiler or C++ before 17. No need to use it otherwise (adds potential unnecessary headers to include)

#pragma once

#include "iostream/spec/iostream_spec_std_vector_decl.h"
#include "iostream/spec/iostream_spec_std_array_decl.h"
#include "iostream/spec/iostream_spec_std_list_decl.h"
#include "iostream/spec/iostream_spec_std_deque_decl.h"
#include "iostream/spec/iostream_spec_std_map_decl.h"
#include "iostream/spec/iostream_spec_std_unordered_map_decl.h"
#include "iostream/spec/iostream_spec_std_pair_decl.h"
#include "GloveOptions.h"
#if OPTION_USE_BOOST==1
#include "iostream/spec/iostream_spec_boost_container_vector_decl.h"
#include "iostream/spec/iostream_spec_boost_unordered_map_decl.h"
#endif