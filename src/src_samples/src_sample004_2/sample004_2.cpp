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

#include "glv_QStandardItemModelMaker_spec_SlvPool.h"
#else
#include "glove.h"
#endif
#include "Element.h"// SlvPool container: label int, value std::string

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    typedef SlvPool<Element> Tvalue;
    std::vector< std::vector<Tvalue> > matrix_pool;
    int Mrows = 3;
    int Ncols = 2;
    matrix_pool.resize(Mrows);
    for (int i = 0; i < Mrows; i++) {
        matrix_pool[i].resize(Ncols);
        for (int j = 0; j < Ncols; j++) {
            int Npool;
            Npool = 2 * i + j;
            for (int k = 0; k < Npool; k++) {
                matrix_pool[i][j].new_element(k)->value = std::to_string(i) + "-" + std::to_string(j) + "+" + std::to_string(k);
            }
        }
    }

    // To simply display as a table view widget:
    GlvTableView< std::vector< std::vector<Tvalue> > >* table_view = new GlvTableView< std::vector< std::vector<Tvalue> > >(matrix_pool);
    table_view->show();

    /*GlvDialogData<GlvTableView, std::vector< std::vector<Tvalue> > >* table_dialog = new GlvDialogData<GlvTableView, std::vector< std::vector<Tvalue> > >(matrix_pool);

    if (table_dialog->exec() == QDialog::Accepted) {
        std::cout << table_dialog->get_value() << std::endl;
    }*/
    

    return app.exec();

}
