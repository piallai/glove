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

// Example for automatic CLI parametrization widget, global progressions management and pop-up message display.
// In this example a program can be easily modified to provide both widget for parameters input and progression feedback and control (ex: cancel).

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "param/SlvParametrizationMacro.h"
#include "GlvParametrizationDialog.h"
#include "GlvWidgetData_spec_AT.h"
#include "GlvCLI.h"
#else
#define GLOVE_ENABLE_JSON
#include "glove.h"
#endif


#include <chrono>// for computation simulation
#include <thread>// for computation simulation

glvm_parametrization(ParametersCLI, "CLI parameters",
										N1, int, "-N1", "Number of iterations for loop 1.", 100,
										N2, int, "-N2", "Number of iterations for loop 2.", 100,
										N3, int, "-N3", "Number of iterations for loop 3.", 100);


// If using MSVC, do not display the console:
#pragma GLOVE_APP_MSVC_NO_CONSOLE

struct RecurrentStruct {
	int total_loops;
};

// Program supposed to manage 3 command line arguments
// -N1 : Number of iterations for loop 1
// -N2 : Number of iterations for loop 2
// -N3 : Number of iterations for loop 3
int main(int argc, char* argv[]) {

	// Register progressions in GlvApp
	GlvApp::get_progression("Loop1");
	GlvApp::get_progression("Loop2")->set_recurrent(true);
	GlvApp::get_progression("Loop3")->set_recurrent(true);// Set loop 3 as recurrent to adapt visibility policy when ending.

	// Optional : Disable program execution in a separate thread. Progressions and status display can not be managed in this mode, only input parametrization can.
	// Can be convenient if one wants to execute the program in the closest conditions as the initial program is.
	// The program being 'gloved' remains fully compliant with thread mode deactivated.
	// Default is : true
//#define GLOVE_APP_THREAD_MODE false 

#define GLOVE_APP_AUTO true // "-glove" is set by default upon launching
#define GLOVE_APP_RECURRENT_MODE true
#define GLOVE_APP_RECURRENT_TYPE RecurrentStruct
	RecurrentStruct glove_recurrent_var;
	glove_recurrent_var.total_loops = 0;

	GLOVE_APP_PARAM(ParametersCLI);
	// ***** Alternative:
	//GLOVE_APP;// No parametrization widget is used. 

	// Additionally, the configured parametrization is available in the variable glv_parametrization if -glove cli argument was used
	if (is_glove) {
		std::cout << glove_parametrization << std::endl;
	}

	{	// Core program. This program is supposed to be a glove adaptation of an already existing program.
		// Glove modifications are indicated with the the character %.

		int N1, N2, N3;
		bool l_args_valid = true;

		{	// Arguments parsing using SlvCLI. Used here just for this basic example. One can find more advanced cli arguments parsers if needed.
			// CLI arguments parsing in the core program is actually out of the scope of the library for now.
			// GLOVE_APP_PARAM acts a parametrization by-pass to input modified CLI arguments, and resume the core program without any perturbation.

			std::string param_N1_name = "-N1";
			std::string param_N2_name = "-N2";
			std::string param_N3_name = "-N3";

			SlvCLI::Arguments args(argc, argv);
			if (args.get_parameter_arguments().find(param_N1_name) != args.get_parameter_arguments().end()) {
				N1 = std::atoi(args.get_parameter_arguments().at(param_N1_name).front().c_str());
			} else {
				l_args_valid = false;
			}
			if (args.get_parameter_arguments().find(param_N2_name) != args.get_parameter_arguments().end()) {
				N2 = std::atoi(args.get_parameter_arguments().at(param_N2_name).front().c_str());
			} else {
				l_args_valid = false;
			}
			if (args.get_parameter_arguments().find(param_N3_name) != args.get_parameter_arguments().end()) {
				N3 = std::atoi(args.get_parameter_arguments().at(param_N3_name).front().c_str());
			} else {
				l_args_valid = false;
			}
		}

		if (l_args_valid) {

			// Similar to sample010_0 here

			SlvProgressionQt& i = *GlvApp::get_progression("Loop1");// % instead of: int i;
			for (i = 0; i << N1; i++) {// % instead of : i < N1

				SlvProgressionQt& j = *GlvApp::get_progression("Loop2");
				for (j = 0; j << N2; j++) {// % instead of : j < N2

					SlvProgressionQt& k = *GlvApp::get_progression("Loop3");
					for (k = 0; k << N3; k++) {// % instead of : k < N3

						// Simulates computation
						std::this_thread::sleep_for(std::chrono::milliseconds(10));

						glove_recurrent_var.total_loops++;
					}

				}

				// % instead of printf("display some values: %zu and %.2f", std::size_t(i), float(j))
				GlvApp::show(SlvStatus(SlvStatus::statusType::warning, "display some values: %zu and %.2f", std::size_t(i), float(j)), true);

			}

		}

		GlvApp::show(SlvStatus(SlvStatus::statusType::information, "Total loops: " + std::to_string(glove_recurrent_var.total_loops)), true);

		return 0;

	}

}
