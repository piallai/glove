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

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "SlvProgression.h"
#else
#include "glove.h"
#endif

/*! Example class containing a method which progress requires monitoring.*/
class ClassC : public SlvProgression {

private:

	/*! Number of iterations of the virtual algorithm.*/
	unsigned int Niterations;

public:

	/*! \p _Niterations : Number of iterations of the virtual algorithm.*/
	ClassC(int _Niterations);

	/*! Simulate the computation of an algorithm which progress needs to be tracked.*/
	void process();
#ifdef USE_OMP
	/*! Simulate the computation of an algorithm which progress needs to be tracked.
	* This time using OpenMP.*/
	void processOMP();
#endif

};
