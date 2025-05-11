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

/*! Example of how to use table view with std::map.*/

#include <QApplication>

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvTableView.h"
#include "GlvTableDialog.h"
#include "glv_QStandardItemModelMaker_spec_std_map.h"
#include "glv_QStandardItemModelMaker_spec_std_container.h"
#include "GlvWidgetData_spec_AT.h"
#else
#include "glove.h"
#endif

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    std::map<int, std::string> map;
    map[0] = "foo1";
    map[2] = "foo2";
    map[8] = "foo3";

    GlvTableDialog< std::map<int, std::string> > map_dialog;
    map_dialog.get_widget()->set_value(map);


    std::map<int, int> map2;
    map2[0] = 4;
    map2[2] = 5;
    map2[8] = 6;

    GlvTableView< std::map<int, int>, GlvWidget > map2_table(map2);
    map2_table.show();

    std::map<float, int> map3;
    map3[0.f] = 4;
    map3[2.f] = 5;
    map3[8.f] = 6;

    GlvTableView<std::map<float, int>, GlvWidget> map3_table(map3);
    map3_table.show();

    std::map<std::vector<int>, int> map_vector2;
    map_vector2[{ 1, 2 }] = 1;
    map_vector2[{ 3, 4, 5 }] = 2;
    GlvTableView< std::map<std::vector<int>, int> > map_vector2_table(map_vector2);
    map_vector2_table.show();

    if (map_dialog.exec() == QDialog::Accepted) {
        std::cout << map_dialog.get_widget()->get_value() << std::endl;
    }

    return app.exec();

}
