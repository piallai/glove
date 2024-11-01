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

	progression_ptr = new SlvProgressionQt("Track");
}

void ClassD::process() {

	classE.process();

	//// Delete progression in the middle of a process ////
	unsigned int Nw = 10;
	unsigned int w = 0;
	progression_ptr->set_message("Processing delete in the middle");
	progression_ptr->start(&w, Nw);
	for (w = 0; w < Nw; w++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		progression_ptr->update();
		if (w == Nw / 2) {
			delete progression_ptr;// ends loop
		}
	}
	///////////////////////////////////////////////////

	unsigned int i = 0;
	get_progression()->set_message("Processing ClassD");
	get_progression()->start(&i, Niterations);
	for (i = 0; i < Niterations; i++) {

		// Simulates computation
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
		classC.processOMP();

		get_progression()->update();

	}

}

#ifdef USE_OMP
void ClassD::processOMP() {

	classE.process();

	//// Delete progression in the middle of a process ////
	unsigned int Nw = 10;
	unsigned int w = 0;
	progression_ptr->set_message("Processing delete in the middle");
	progression_ptr->start(&w, Nw);
	for (w = 0; w < Nw; w++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		progression_ptr->update();
		if (w == Nw / 2) {
			delete progression_ptr;// ends loop
		}
	}
	///////////////////////////////////////////////////

	unsigned int i = 0;
	get_progression()->set_message("Processing ClassD");
	get_progression()->start(&i, Niterations);

#pragma omp parallel
	{
#pragma omp for
		for (int i_omp = 0; i_omp < (int)Niterations; i_omp++) {

			if (!get_progression()->was_canceled()) {

				// Simulates computation
				//std::this_thread::sleep_for(std::chrono::milliseconds(100));

				classC.process();// Concurrent

#pragma omp critical
				{
					get_progression()->update();
					i++;
				}

			}
			
		}
	}

	classC.get_progression()->finish();
}

#endif
