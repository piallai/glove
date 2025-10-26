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

// Example for generating a paramrtrization windows from a json parametrization file

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrizationMacro.h"
#include "GlvParametrizationDialog.h"
#include "GlvWidgetData_spec_SlvFile.h"
#include "GlvWidgetData_spec_AT.h"
#include "GlvWidgetData_spec_SlvParametrization.h"
#include "GlvCLI.h"
#else
#define GLOVE_ENABLE_JSON
#include "glove.h"
#endif

#include "parametrization_gui.h"

int main(int argc, char* argv[]) {

	GLOVE_APP_PARAM(Parametrization)

	std::cout << "argc = " << argc << std::endl;
	for (int i = 1; i < argc; i++) {
		std::cout << "argv[i] = " << argv[i] << std::endl;
	}

	// Additionally, the configured parametrization is available in the variable glv_parametrization if -glove cli argument was used
	if (is_glove) {
		std::cout << glove_parametrization << std::endl;
	}

	return 0;
	
}
