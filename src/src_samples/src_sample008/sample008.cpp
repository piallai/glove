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

/*! Example of how to sort data using SlvSort.
* Either: SlvSortDescending 
* Either: SlvSortAscending
* Both inherit from SlvSort which is a SlvParametrization.
* Parameters are managing the number of sorted elements, and the maximum range between first sorted value and last.*/

#include <QApplication>

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "SlvSort.h"
#include "GlvParametrizationDialog.h"
#include "GlvWidgetData_spec_AT.h"

#include "filestream/SlvFileMgr.h"
#else
#include "glove.h"
#endif

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    SlvSortDescending<double> sort((unsigned int)(-1), 2);//-1: Any number of value. 2: maximum range.
    std::cout << sort.add(2) << std::endl;
    std::cout << sort.add(1) << std::endl;
    std::cout << sort.add(4) << std::endl;
    std::cout << sort.add(1) << std::endl;
    std::cout << sort.add(5) << std::endl;
    std::cout << sort.add(-4) << std::endl;

    std::cout << sort << std::endl;

    GlvParametrizationDialog< SlvSortDescending<double> > parametrization_dialog(sort);
    parametrization_dialog.show();

    return app.exec();

}

