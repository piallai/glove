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

/*! Example of how to design data modeling with QStandardItemModel.
Here is demonstrated how GlvTableView can manage data of multiple dimensions (arrays of arrays of arrays etc..).*/

#include <QApplication>

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvTableView.h"
#include "glv_QStandardItemModelMaker_spec_std_container.h"
#include "GlvDialogData.h"

#include "glv_QStandardItemModelMaker_spec_std_map.h"
//#include "iostream/spec/iostream_spec_std_map.h"// output value in terminal

#include <QHeaderView>//to resize columns to content
#else
#include "glove.h"
#endif

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    typedef std::map<int, std::string> Tvalue;
    std::vector< std::vector<Tvalue> > matrix_map;
    int Mrows = 6;
    int Ncols = 8;
    matrix_map.resize(Mrows);
    for (int i = 0; i < Mrows; i++) {
        matrix_map[i].resize(Ncols);
        for (int j = 0; j < Ncols; j++) {
            int Npool;
            Npool = 2 * i + j;
            for (int k = 0; k < Npool; k++) {
                matrix_map[i][j][k] = std::to_string(i) + "-" + std::to_string(j) + "+" + std::to_string(k);
            }
        }
    }

    // To simply display as a table view widget:
    GlvTableView< std::vector< std::vector<Tvalue> > >* table_view = new GlvTableView< std::vector< std::vector<Tvalue> > >(matrix_map);
    table_view->show();

    GlvDialogData<GlvTableViewLineEdit, std::vector< std::vector<Tvalue> > >* table_dialog = new GlvDialogData<GlvTableViewLineEdit, std::vector< std::vector<Tvalue> > >(matrix_map);
    // resize colums to content: Do not use QHeaderView::ResizeMode::Stretch
    table_dialog->get_widget()->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    if (table_dialog->exec() == QDialog::Accepted) {
        std::cout << table_dialog->get_value() << std::endl;
    }
    
    std::map<int, std::vector<std::string> > test;
    std::cout << test << std::endl;

    return app.exec();

}
