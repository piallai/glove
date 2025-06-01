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

/*! Example of parametrization dialog containing std::vector, std::map and std::array parameters.*/

#include <QApplication>

#ifdef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "glove.h"
#else
#include "param/SlvParametrizationMacro.h"
#include "param/SlvParametrization2.h"
#include "GlvParametrizationDialog.h"
#include "GlvWidgetData_spec_AT.h"
#include "GlvWidgetData_spec_std_vector.h"
#include "GlvWidgetData_spec_std_string.h"
#include "GlvWidgetData_spec_std_map.h"
#include "GlvWidgetData_spec_std_array.h"
#include "GlvWidgetData_spec_std_container_container.h"

#include "GlvParametrizationSaveLoad.h"
#include "filestream/spec/slv_rw_spec_std_vector.h"
#include "filestream/spec/slv_rw_spec_std_map.h"
#include "filestream/spec/slv_rw_spec_std_array.h"
#endif

typedef std::map<unsigned int, std::string> Tmap;
typedef std::array<int, 4> Tarray;

glvm_parametrization(ClassA, "ClassA",
	vector1, std::vector< std::vector<int> >, "vector1", "vector1", std::vector< std::vector<int> >({ {3,5}, {2,4} }),
	vector2, std::vector< std::vector<std::string> >, "vector2", "vector2", std::vector< std::vector<std::string> >({ {"foo3","foo5"}, {"bar2","bar4"} }),
	map1, Tmap, "map1", "map1", Tmap({ { 3, "foo" }, { 5, "bar" }, {1, "foobar"}}),
	array1, Tarray, "array1", "array1", {},
	test, nullptr_t, "bar", "foo", )

int main(int argc, char* argv[]) {

	/*ClassA a;
	a.get_test();*/

    QApplication app(argc, argv);

	GlvParametrizationDialog<ClassA>* parametrization_dialog = new GlvParametrizationDialog<ClassA>();
	GlvParametrizationSaveLoad<ClassA>* save_load_widget = new GlvParametrizationSaveLoad<ClassA>(parametrization_dialog->get_parametrization_widget());


	int result = parametrization_dialog->exec();

	if (result == QDialog::Accepted) {

		ClassA classA = parametrization_dialog->get_parametrization();

		std::cout << "classA : " << classA << std::endl;

	}

    return app.exec();

}

