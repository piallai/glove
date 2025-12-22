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

/*! Parametrizations are closed by default.*/
template <class Tparametrization>
struct GlvParametrizationWidgetDefaultOpen {
	static constexpr bool open = false;
};

/*! Make the parametrization open by default.*/
#define glvm_parametrization_open(Tparametrization) \
template <>\
struct GlvParametrizationWidgetDefaultOpen<Tparametrization> {\
	static constexpr bool open = true;\
};
