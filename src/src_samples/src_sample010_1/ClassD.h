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

#include "ClassC.h"
#include "ClassE.h"

class ClassD : public SlvProgression {

private:

	/*! Number of iterations of the virtual algorithm.*/
	unsigned int Niterations;

public:

	ClassC classC = ClassC(100);
	ClassE classE = ClassE(100);
	/*! Supplementary progression for example of deletion while in a loop.*/
	SlvProgressionQt* progression_ptr;

	/*! \p _Niterations : Number of iterations of the virtual algorithm.*/
	ClassD(int _Niterations);

	/*! Simulate the computation of an algorithm which progress needs to be tracked.*/
	void process();
#ifdef USE_OMP
	/*! Simulate the computation of an algorithm which progress needs to be tracked.
	* This time using OpenMP.*/
	void processOMP();
#endif

};
