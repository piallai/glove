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

#include "ClassD.h"

#include <chrono>
#include <thread>
#ifdef USE_OMP
#include <omp.h>
#endif

ClassD::ClassD(int _Niterations) {
	Niterations = _Niterations;
}

void ClassD::process() {

	unsigned int i = 0;
	get_progression()->emit_start("Processing ClassD", &i, Niterations);
	for (i = 0; i < Niterations; i++) {

		// Simulates computation
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
		classC.process();

		get_progression()->emit_progress(100 * (i + 1) / Niterations);

	}

	//get_progression()->emit_end();

}

#ifdef USE_OMP
void ClassD::processOMP() {

	unsigned int i = 0;
	get_progression()->emit_start("Processing ClassD", &i, Niterations);

#pragma omp parallel
	{
#pragma omp for
		for (int i_omp = 0; i_omp < (int)Niterations; i_omp++) {

			// Simulates computation
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			//classC.process();

			//progression->emit_progress(100 * (i + 1) / Niterations);
#pragma omp critical
			{
				get_progression()->emit_progress(100 * (i + 1) / Niterations);
				i++;
			}

		}
	}

	//get_progression()->emit_end();

}

#endif