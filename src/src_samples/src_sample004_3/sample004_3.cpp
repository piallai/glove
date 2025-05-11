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

/*! Example of how to simply create a matrix table.
In this example is presented how to use the specialized widget associated to the data.*/

#include <QApplication>

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvTableView.h"
#include "glv_QStandardItemModelMaker_spec_std_container.h"
#include "GlvDialogData.h"
#include "GlvWidgetData_spec_AT.h"
#else
#include "glove.h"
#endif

typedef float Tvalue;// Any type provided there is an associated GlvWidgetData_spec_xxx header included
// Use alias for std::vector<std::vector<>> for simplicity
template <class T>
using Matrix = std::vector< std::vector<T> >;

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    Matrix<Tvalue> matrix2D;
    int Mrows = 3;
    int Ncols = 2;
    matrix2D.resize(Mrows);
    for (int i = 0; i < Mrows; i++) {
        matrix2D[i].resize(Ncols);
        for (int j = 0; j < Ncols; j++) {
            matrix2D[i][j] = Tvalue(i + j);
        }
    }

    GlvTableView<Matrix<Tvalue>, GlvWidget>* table_view2D = new GlvTableView<Matrix<Tvalue>, GlvWidget>(matrix2D);
    table_view2D->show();

    GlvTableView<Matrix<Tvalue>, GlvWidget, true>* table_view2D_persistent = new GlvTableView<Matrix<Tvalue>, GlvWidget, true>(matrix2D);
    table_view2D_persistent->show();

    // Use GlvTableViewWidget instead of GlvTableWidgetT
    GlvDialogData<GlvTableViewWidget, Matrix<Tvalue> >* table_dialog2D = new GlvDialogData<GlvTableViewWidget, Matrix<Tvalue> >(matrix2D);
    if (table_dialog2D->exec() == QDialog::Accepted) {
        std::cout << table_dialog2D->get_value() << std::endl;
    }


    return app.exec();

}

