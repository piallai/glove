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

#pragma once

/*! Use Qt signals.*/
#include "SlvProgressionQt.h"

/*! Convenience class to embed a SlvProgressionQt in a class.
* Typical use: to be inherited by a class which contains a method to monitor.
* The key class is actually SlvProgressionQt, but it is convenient to encapsulate it in SlvProgression in order to not add too many inherited methods in inheriting classes.
* Also convenient to track the get_progression() method.*/
class SlvProgression {

private:

	SlvProgressionQt progression;

public:

	SlvProgression(std::string _name = "");
	SlvProgression(const SlvProgression& _progression);
	~SlvProgression();

	/*! To be used. Const qualifier make the instance compliant with inherited const method.
	In other words, the progression ignores the const qualifier of the child class instance.*/
	SlvProgressionQt* get_progression() const;

protected:

	SlvProgression& operator=(const SlvProgression& _progression);

};
