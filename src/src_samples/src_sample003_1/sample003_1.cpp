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

/*! Advanced example of how to manage different parametrizations in an optional list.
Special case:
- One of the listed parametrizations (ListElementA<T, Toption>) has a template parameter which type is a template parametrization.
- The template parameter is managed by a second optional list to select the type (List2)
- ListElementA<T, Toption> also has a second template parameter (Toption), not related to the parametrization framework.
- Toption is defined directly at GlvParamListDialog level.
- The optional list (List2) for the templated parametrization configuration has a filter on the type.*/
/* | List
   |-- ListElementA<T, Toption> ->  | List2
   |-- ListElementB                 |-- ListElementD
   |-- ListElementC                 |-- ListElementE

Possible parametrizations in this example: - ListElementA<ListElementE, Toption>
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

    typedef int Toption;

    GlvParamListDialog<List, Toption>* list_dialog = new GlvParamListDialog<List, Toption>();

    list_dialog->exec();

    std::cout << *list_dialog->get_parametrization_base() << std::endl;

    return app.exec();

}

