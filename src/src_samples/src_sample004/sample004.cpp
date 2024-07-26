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
#endif

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvTableView.h"
#include "glv_QStandardItemModelMaker_spec_std_container.h"
#include "GlvTableDialog.h"

// Specializations depending on the managed type below
#include "GlvWidgetData_spec_AT.h"
#include "GlvWidgetData_spec_SlvProportion.h"
#include "GlvWidgetData_spec_SlvEnum.h"
#endif
glvm_SlvEnum(EnumName, A, B, C, D)

/////////////////////////////////////////////
// Define the type for the example
/////////////////////////////////////////////
//typedef float Tvalue;// Any arithmetic (spec_AT) type
//typedef SlvProportion Tvalue;
typedef EnumName Tvalue;
/////////////////////////////////////////////

// Use alias for std::vector<std::vector<>> for simplicity
template <class T>
using Matrix = std::vector< std::vector<T> >;

//////////////////////////////////////////
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvWidgetData_spec_std_container_container.h"
//#include "GlvWidgetSaveLoad.h"
//#include "misc/spec/SlvDataName_spec_std_vector_vector.h"// "matrix" name
#endif
#include "QtSlotsExample.h"
//////////////////////////////////////////

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

    /*GlvWidget< Matrix<Tvalue> > test(matrix2D);
    GlvWidgetSaveLoad< Matrix<Tvalue> > save_load(&test, { "blob" });
    SlvFileExtensions allowed_extensions = save_load.get_allowed_extensions();
    allowed_extensions.add_front("flop");
    save_load.set_allowed_extensions(allowed_extensions);
    test.show();*/


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

    GlvTableView< Matrix<Tvalue> >* table_view2D = new GlvTableView< Matrix<Tvalue> >(matrix2D);
    table_view2D->show();

    // Using a QDialog, matrix4D this time:
    GlvTableDialog< Matrix< Matrix<Tvalue> > >* table_dialog4D = new GlvTableDialog< Matrix< Matrix<Tvalue> > >(matrix4D);
    
    GlvTableView< Matrix< Matrix<Tvalue> > >* table_view4D = new GlvTableView< Matrix< Matrix<Tvalue> > >(matrix4D);
    table_view4D->setWindowTitle("matrix4D");
    table_view4D->show();

    QtSlotsExample qtslots;
    QObject::connect(table_dialog4D->get_widget(), SIGNAL(cell_changed(const std::vector<int>&)), &qtslots, SLOT(get(const std::vector<int>&)));
    if (table_dialog4D->exec() == QDialog::Accepted) {
        std::cout << table_dialog4D->get_value() << std::endl;
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

    GlvTableView< Matrix< Matrix< Matrix<Tvalue> > > >* table_view6D = new GlvTableView< Matrix< Matrix< Matrix<Tvalue> > > >(matrix6D);
    table_view6D->setWindowTitle("matrix6D");
    table_view6D->show();

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

    // 8D, and use GlvWidget for end data: use GlvWidget as template argument
    GlvTableView< Matrix< Matrix< Matrix< Matrix<Tvalue> > > >, GlvWidget, true>* table_view8D = new GlvTableView< Matrix< Matrix< Matrix< Matrix<Tvalue> > > >, GlvWidget, true>(matrix8D);
    table_view8D->setWindowTitle("matrix8D");
    table_view8D->show();
    table_view8D->set_dynamically_update_data(false);//ex: disable dynamic model data update because of the big size/dimension of the data

    // Using a QDialog, matrix8D this time.
    // Also using GlvWidget for end data: use GlvTableViewWidget as template argument
    GlvTableWidgetDialog<Matrix < Matrix< Matrix< Matrix<Tvalue> > > > >* table_dialog8D = new GlvTableWidgetDialog<Matrix < Matrix< Matrix< Matrix<Tvalue> > > > >(matrix8D);

    QObject::connect(table_dialog8D->get_widget(), SIGNAL(cell_changed(const std::vector<int>&)), &qtslots, SLOT(get(const std::vector<int>&)));
    table_dialog8D->get_widget()->set_dynamically_update_data(false);
    if (table_dialog8D->exec() == QDialog::Accepted) {
        //std::cout << table_dialog8D->get_value()[1][1][1][1][1][1][1][1] << std::endl;
        std::cout << table_dialog8D->get_value() << std::endl;
    }

    Matrix< Matrix< Matrix< Matrix< std::vector<Tvalue> > > > > matrix9D;
    Mrows = 9;
    matrix9D.resize(Mrows);
    for (int i = 0; i < Mrows; i++) {
        matrix9D[i] = matrix8D;
    }

    // 9D, and use GlvWidget for end data: use GlvWidget as template argument
    GlvTableView< Matrix< Matrix< Matrix< Matrix< std::vector<Tvalue> > > > >, GlvWidget >* table_view9D = new GlvTableView< Matrix< Matrix< Matrix< Matrix< std::vector<Tvalue> > > > >, GlvWidget>(matrix9D);
    table_view9D->setWindowTitle("matrix9D");
    table_view9D->show();
    table_view9D->set_dynamically_update_data(false);//ex: disable dynamic model data update because of the big size/dimension of the data
    QObject::connect(table_view9D, SIGNAL(cell_changed(const std::vector<int>&)), &qtslots, SLOT(get(const std::vector<int>&)));


    Matrix< Matrix< Matrix< Matrix< Matrix<Tvalue> > > > > matrix10D;
    Mrows = 9;
    Ncols = 8;
    matrix10D.resize(Mrows);
    for (int i = 0; i < Mrows; i++) {
        matrix10D[i].resize(Ncols);
        for (int j = 0; j < Ncols; j++) {
            matrix10D[i][j] = matrix8D;
        }
    }

    /*
    // 10D, and use GlvWidget for end data: use GlvWidget as template argument
    GlvTableView< Matrix< Matrix< Matrix< Matrix< Matrix<Tvalue> > > > >, GlvWidget >* table_view10D = new GlvTableView< Matrix< Matrix< Matrix< Matrix< Matrix<Tvalue> > > > >, GlvWidget>(matrix10D);
    table_view10D->setWindowTitle("matrix10D");
    table_view10D->show();
    table_view10D->set_dynamically_update_data(false);//ex: disable dynamic model data update because of the big size/dimension of the data
    */

    return app.exec();

}
