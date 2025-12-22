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

#include "SlvTimer.h"
//#include "slv_string.h"

SlvTimer::SlvTimer(std::string _name) :SlvName(_name) {

    reset();
}

SlvTimer::~SlvTimer() {

}

void SlvTimer::reset() {

    check_times.clear();
    check_times.push_back(clock());//start time
}

void SlvTimer::check_display(std::string _message) {

    check_times.push_back(clock());

    std::cout << "(SlvTimer " << name << ", " << _message << ")" << std::endl;
    std::cout << "last check: ";
    time_display(check_times.back() - check_times[check_times.size() - 2]);
    std::cout << " ago " << std::endl;
    std::cout << "from start: ";
    time_display(check_times.back() - check_times.front());
    std::cout << std::endl;


}

std::string SlvTimer::get_string() const {

    std::string time;
    Time time_array = get_time(clock() - check_times[0]);
    if (time_array[0] > 0) {
        time = slv::string::to_string(time_array[0]) + " h ";
    }
    if (time_array[1] > 0 || time_array[0] > 0) {
        time += slv::string::to_string(time_array[1]) + " min ";
    }
    if (time_array[2] > 0 || time_array[1] > 0 || time_array[0] > 0) {
        time += slv::string::to_string(time_array[2]) + " s ";
    }
    if (time_array[3] > 0 || time_array[2] > 0 || time_array[1] > 0 || time_array[0] > 0) {
        time += slv::string::to_string(time_array[3]) + " ms ";
    }

    return time;
}

SlvTimer::Time SlvTimer::get_elapsed_time() {

    check_times.push_back(clock());

    return get_time(check_times.back() - check_times[0]);

}

SlvTimer::Time SlvTimer::get_elapsed_time_last() {

    check_times.push_back(clock());

    return get_time(check_times.back() - check_times.end()[-2]);

}

void SlvTimer::time_display(clock_t _time) const {

    Time time_array = get_time(_time);
    std::cout << time_array[0] << " h " << time_array[1] << " min " << time_array[2] << " s " << time_array[3] << " ms";

}

SlvTimer::Time SlvTimer::get_time(clock_t _time) const {

    Time time_array;

    double time = double(_time) / CLOCKS_PER_SEC;

    long int time_int = (long int)time;
    int n_milliseconds = int((time - double(time_int)) * 1000);

    int n_hours, n_minutes, n_seconds;

    n_hours = (time_int - time_int % 3600) / 3600;
    time_array[0] = n_hours;
    time_int -= n_hours * 3600;
    n_minutes = (time_int - time_int % 60) / 60;
    time_array[1] = n_minutes;
    time_int -= n_minutes * 60;
    n_seconds = (time_int - time_int % 1) / 1;
    time_array[2] = n_seconds;

    time_array[3] = n_milliseconds;

    return time_array;
}

int SlvTimer::to_milliseconds(const Time& _time) {

    return (_time[0] * 3600 + _time[1] * 60 + _time[2]) * 1000 + _time[3];

}

SlvTimer::Time SlvTimer::from_milliseconds(const int& _milliseconds) {

    Time time_array;

    int n_hours, n_minutes, n_seconds;
    int time_int = _milliseconds;

    n_hours = (_milliseconds % 3600000) / 3600000;
    time_array[0] = n_hours;
    time_int -= n_hours * 3600000;
    n_minutes = (time_int - time_int % 60000) / 60000;
    time_array[1] = n_minutes;
    time_int -= n_minutes * 60000;
    n_seconds = (time_int - time_int % 1000) / 1000;
    time_array[2] = n_seconds;
    time_int -= n_seconds * 1000;
    time_array[3] = time_int;

    return time_array;
}