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

// Example of use of GlvProportionWidget

#include <QApplication>
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvProportionWidget.h"
#include "GlvDialog.h"
#include <iostream>
#else
#include "glove.h"
#endif

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    GlvProportionWidget widget(0, 1000);
    widget.show();

    GlvDialog<GlvProportionWidget> dialog;
    dialog.widget->set_slider_size(200);
    if (dialog.exec()) {
        std::cout << dialog.widget->get_value() << std::endl;
    }

    return app.exec();
}

