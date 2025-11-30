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

#include "param/SlvParametrizationMacro.h"
glvm_parametrization(SlvParametersParserConfig, "Parameters parser",
	arguments, std::string, "Arguments", "Arguments to parse", "",
	CLI_mode, bool, "CLI mode", "* If enabled, the arguments are applied on a default parametrization.\
	\nBoolean arguments are being activated if the parameter name is specified. There is no need to set a 0/1 value.\
	\nHowever, deactivating a boolean parameter (activated by default) is not possible in this mode.\
	\n* If disabled, the arguments are applied on the current parametrization.\
	\nBoolean arguments can be enabled/disabled at will.", true,
	show_parsed_argument_only, bool, "Show parsed args only", "Show only the arguments that are parsed in the 'arguments' line.", true
)
#include "GlvWidgetData_spec_AT.h"
#include "GlvWidgetData_spec_std_string.h"
#include "GlvParametrizationDialog.h"

typedef GlvParametrizationDialog<SlvParametersParserConfig> GlvParametersParserConfigDialog;
