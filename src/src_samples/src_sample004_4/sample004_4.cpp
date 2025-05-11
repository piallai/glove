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

/*! Example of how to simply create a matrix table.*/

#include <QApplication>

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvTableView.h"
#include "glv_QStandardItemModelMaker_spec_std_container.h"
#include "GlvDialogData.h"
#else
#include "glove.h"
#endif

typedef float Tvalue;// Any type provided >> and << operators are defined
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

    GlvTableView< Matrix<Tvalue> >* table_view2D = new GlvTableView< Matrix<Tvalue> >(matrix2D);
    table_view2D->show();

    GlvDialogData<GlvTableViewLineEdit, Matrix<Tvalue> >* table_dialog2D = new GlvDialogData<GlvTableViewLineEdit, Matrix<Tvalue> >(matrix2D);
    if (table_dialog2D->exec() == QDialog::Accepted) {
        std::cout << table_dialog2D->get_value() << std::endl;
    }


    return app.exec();

}
