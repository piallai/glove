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

#include "GlvParamListDialog_base.h"
template <class Tparametrization>
class GlvParametrizationDialog;

/*! Configuration list of Tlist type.
* Tlist must have:
* - static const std::vector<std::string>& list() method
* - static const std::string& name() method
* Toption is the type of the optional data provided for the parametrization windows. See GlvParamListDialog_Open::open.
* The optional data is not stored in the GlvParamListDialog instance.*/
template <class Tlist, class Toption = void>
class GlvParamListDialog;
