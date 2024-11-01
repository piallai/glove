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

#include "ClassE.h"

#include <chrono>
#include <thread>
#ifdef USE_OMP
#include <omp.h>
#endif

ClassE::ClassE(int _Niterations) {
	Niterations = _Niterations;
}

void ClassE::process() {

	unsigned int i = 0;
	get_progression()->set_message("Processing ClassE");
	get_progression()->start(&i, Niterations);
	for (i = 0; i < Niterations; i++) {

		// Simulates computation
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		get_progression()->update();

	}

	get_progression()->finish();

}
