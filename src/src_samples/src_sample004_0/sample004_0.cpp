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

/*! Here is showed how GlvTableView can manage data of multiple dimensions (arrays of arrays of arrays etc..).*/

#include <QApplication>

#ifdef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "glove.h"
#else
#include "GlvTableView.h"
#include "glv_QStandardItemModelMaker_spec_std_container.h"
// Specializations depending on the managed type below ***
//#include "GlvWidgetData_spec_AT.h"
//#include "GlvWidgetData_spec_SlvProportion.h"
#include "GlvWidgetData_spec_SlvEnum.h"
#endif

/////////////////////////////////////////////
// Define the type for the example ***
/////////////////////////////////////////////
//typedef float Tvalue;// Any arithmetic (spec_AT) type
//typedef SlvProportion Tvalue;
glvm_SlvEnum(EnumName, A, B, C, D)
typedef EnumName Tvalue;
/////////////////////////////////////////////

// Use alias for std::vector<std::vector<>> for simplicity
template <class T>
using Matrix = std::vector< std::vector<T> >;

Matrix< Matrix< Matrix< Matrix<Tvalue> > > > build_matrix8D() {

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

    Matrix< Matrix< Tvalue> > matrix4D;
    Mrows = 4;
    Ncols = 5;
    matrix4D.resize(Mrows);
    for (int i = 0; i < Mrows; i++) {
        matrix4D[i].resize(Ncols);
        for (int j = 0; j < Ncols; j++) {
            matrix4D[i][j] = matrix2D;
        }
    }

    Matrix< Matrix< Matrix<Tvalue> > > matrix6D;
    Mrows = 7;
    Ncols = 6;
    matrix6D.resize(Mrows);
    for (int i = 0; i < Mrows; i++) {
        matrix6D[i].resize(Ncols);
        for (int j = 0; j < Ncols; j++) {
            matrix6D[i][j] = matrix4D;
        }
    }

    Matrix< Matrix< Matrix< Matrix<Tvalue> > > > matrix8D;
    Mrows = 3;
    Ncols = 4;
    matrix8D.resize(Mrows);
    for (int i = 0; i < Mrows; i++) {
        matrix8D[i].resize(Ncols);
        for (int j = 0; j < Ncols; j++) {
            matrix8D[i][j] = matrix6D;
        }
    }

    return matrix8D;
}

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    // 8D, and use GlvWidget for end data: use GlvWidget as template argument
    GlvTableView< Matrix< Matrix< Matrix< Matrix<Tvalue> > > >, GlvWidget, true>* table_view8D = new GlvTableView< Matrix< Matrix< Matrix< Matrix<Tvalue> > > >, GlvWidget, true>(build_matrix8D());
    table_view8D->setWindowTitle("matrix8D");
    table_view8D->show();
    table_view8D->set_dynamically_update_data(false);//ex: disable dynamic model data update because of the big size/dimension of the data

    return app.exec();

}
