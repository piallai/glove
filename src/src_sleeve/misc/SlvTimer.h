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

#include <time.h>
#include "SlvName.h"

/*! Class to measure execution time.
* At instantiation/reset, a reference time is measured and added to stack of checked times.
* Each time get_elasped_time, get_elasped_time_last, or check_display, method is called, a new checked time is added. Check sample012 for example.*/
class SlvTimer : public SlvName {

private:

	std::vector<clock_t> check_times;

public:

	SlvTimer(std::string _name = "");
	~SlvTimer();

	/*! Reset timer by clearing all checked times and taking current time as new reference.*/
	void reset();


	/*! Parse elapsed time since instance reference into a string.*/
	std::string get_string() const;

	/*! Get elapsed time from reference into hours, minutes, seconds, milliseconds.
	* Each time this method is called, a check time is added.*/
	std::vector<int> get_elasped_time();
	/*! Get elapsed time from last check into hours, minutes, seconds, milliseconds.
	* Each time this method is called, a check time is added.*/
	std::vector<int> get_elasped_time_last();

	/*! Measure elapsed time and display it via std::cout. \p _message is an optional display message.
	* Each time this method is called, a check time is added.*/
	void check_display(std::string _message = "");

private:

	/*! Display time \p _time.*/
	void time_display(clock_t _time) const;
	/*! Parse \p _time into hours, minutes, seconds, milliseconds.*/
	std::vector<int> get_time(clock_t _time) const;

};
