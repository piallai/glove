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

// Example for automatic CLI, without Qt management

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrizationMacro.h"
#include "filestream/SlvFile.h"
#include "SlvSize2d.h"
#include "SlvCLI.h"
#else
#define GLOVE_DISABLE_QT // no need of Qt here
#define GLOVE_ENABLE_JSON
#include "glove.h"
#endif

#include "GloveOptions.h"
// This example can work only if:
// - compiling samples with single headers
// - Or compiling the library with OPTION_ENABLE_SLV_QT_PROGRESS is disabled
#if OPTION_ENABLE_SLV_QT_PROGRESS==0 || defined(OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER)

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

// Program supposed to manage 7 command line arguments
// -I : input path of a .txt file
// -O : output path of a .txt file
// -k : a float parameter
// -enable : an option to enable something (no parameter value associated)
// -foo : an advanced float parameter
// -bar : an advanced int parameter
// -size : and advanced parameter formatted as intxint (widthxheight)
int main(int argc, char* argv[]) {

	ParametersCLI parameters_CLI = SlvCLI::parse<ParametersCLI>(argc, argv);

	std::cout << parameters_CLI << std::endl;

	return 0;
}

#else

int main(int argc, char* argv[]) {

	std::cout << "This example can work only if:\n\
	- compiling samples with single headers\n\
	- Or compiling with OPTION_ENABLE_SLV_QT_PROGRESS is disabled" << std::endl;

	return 0;
}

#endif
