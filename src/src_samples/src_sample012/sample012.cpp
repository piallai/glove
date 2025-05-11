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

// Example of timer management

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "misc/SlvTimer.h"
#else
#define GLOVE_DISABLE_QT // no need of Qt here
#include "glove.h"
#endif

#include <thread>//used only for simulating elasped time

int main(int argc, char* argv[]) {

    SlvTimer timer;
    timer.check_display();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    timer.check_display();
    std::cout << timer.get_elasped_time() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << timer.get_elasped_time_last() << std::endl;
    std::cout << timer.get_elasped_time() << std::endl;

}

