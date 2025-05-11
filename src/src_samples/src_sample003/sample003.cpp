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

/*! Example of how to manage different parametrizations in an optional list.*/
/* | List
   |-- ListElementA
   |-- ListElementB
   |-- ListElementC
 */

#include <QApplication>

#include "List.h"
#include "GlvParamListDialog_Open_spec_List.h"
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvParamListDialog.h"
#include "GlvWidgetData_spec_AT.h"
#include "GlvWidgetData_spec_std_string.h"
#endif

template <class T>
void func(const T* _parametrization) {
    std::cout << *_parametrization << std::endl;
}

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    GlvParamListDialog<List>* list_dialog = new GlvParamListDialog<List>();

    int result = list_dialog->exec();
    if (result == QDialog::Accepted) {
        // Access the configured type through a template function
#if defined(COMPILER_MSVC) && _MSVC_TRADITIONAL // /Zc:preprocessor 
        glvm_instruction_base_to_dcast_const(List, func PARENTHESIS1, list_dialog->get_parametrization_base(), PARENTHESIS2;)
#elif defined(COMPILER_GCC) || !_MSVC_TRADITIONAL //glvm_instruction_base_to_dcast_const does not work on gcc. Use direct macro instead.
        glvm_List_instruction_name_to_type(func PARENTHESIS1 dynamic_cast<const, list_dialog->get_parametrization_base()->get_name(), *>(list_dialog->get_parametrization_base()) PARENTHESIS2;)
#endif
    }

    return app.exec();

}

