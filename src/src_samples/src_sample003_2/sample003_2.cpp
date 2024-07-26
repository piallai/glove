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

/*! Advanced example of how to manage different parametrizations in an optional list.
Special case:
- One of the listed parametrizations (ListElementA) has a template parameter which type is a template parametrization.
- The template parameter is managed by the same initial list (List)
- The second layer of template parametrization is managed by List2.
- The optional list (List2) for the templated parametrization configuration has a filter on the type.*/
/* | List
   |-- ListElementA<T> -> | List
   |-- ListElementB       |-- ListElementA<T> -> | List2
   |-- ListElementC       |-- ListElementB       |-- ListElementD
                          |-- ListElementC       |-- ListElementE

Possible parametrizations in this example: - ListElementA<ListElementA<ListElementE>>
                                           - ListElementA<ListElementB>
                                           - ListElementA<ListElementC>
                                           - ListElementB
                                           - ListElementC
*/

#include <QApplication>

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvParamListDialog.h"
#endif
#include "List.h"
#include "GlvParamListDialog_Open_spec_List.h"
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvWidgetData_spec_AT.h"
#include "GlvWidgetData_spec_std_string.h"
#include "GlvWidgetData_spec_SlvParametrization.h"
#endif

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    GlvParamListDialog<List>* list_dialog = new GlvParamListDialog<List>();

    list_dialog->exec();

    std::cout << *dynamic_cast<const SlvParametrization0*>(list_dialog->get_parametrization_base()) << std::endl;

    return app.exec();

}

