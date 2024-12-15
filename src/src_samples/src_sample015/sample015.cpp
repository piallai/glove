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

// Example for automatic CLI

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrizationMacro.h"
#include "GlvParametrizationDialog.h"
#include "GlvWidgetData_spec_SlvFile.h"
#include "GlvWidgetData_spec_AT.h"
#include "GlvWidgetData_spec_SlvSize2d.h"
#include "GlvWidgetData_spec_SlvParametrization.h"
#include "GlvCLI.h"
#else
#define GLOVE_ENABLE_JSON
#include "glove.h"
#endif

glvm_parametrization(FooBar, "Foo Bar Size",
										foo, float, "-foo", "Foo value", 2.f,
										bar, int, "-bar", "Bar value", 7,
										size, SlvSize2d<int>, "-size", "Size of processing", SlvSize2d<int>(- 1, -1))

glvm_parametrization(ParametersCLI, "CLI parameters",
										input_file, SlvFile, "-I", "Input file", SlvFile(SlvFileExtensions({ ".txt", ".bla"}), SlvFile::IO::Read),
										output_file, SlvFile, "-O", "Output file", SlvFile(SlvFileExtensions({ ".txt", ".bla"}), SlvFile::IO::Write),
										k, float, "-k", "K value", 2.f,
										enable, bool, "-enable", "Enable something", false,
										advanced, FooBar, "Advanced", "Advanced parameters", FooBar());

GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY(ParametersCLI, "-O")

// Program supposed to manage 7 command line arguments
// -I : input path of a .txt file
// -O : output path of a .txt file
// -k : a float parameter
// -enable : an option to enable something (no parameter value associated)
// -foo : an advanced float parameter
// -bar : an advanced int parameter
// -size : and advanced parameter formatted as intxint (widthxheight)
int main(int argc, char* argv[]) {

	GLOVE_APP_PARAM(ParametersCLI)

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
