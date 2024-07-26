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

// Example for table with multiple different containers (vector, list, deque, array)

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include <QApplication>
#include "GlvTableView.h"
#include "glv_QStandardItemModelMaker_spec_std_container.h"
#include "GlvWidgetData_spec_SlvProportion.h"

#include <deque>
#include <list>
#include <array>
#else
//#define GLOVE_ENABLE_JSON
#include "glove.h"
#endif

typedef SlvProportion Tdata;
static constexpr int Narray = 8;
typedef std::array< std::vector< std::list< std::deque<Tdata> > >, Narray>  Table;

typedef std::deque< std::list< std::vector< std::array<Tdata, Narray> > > >  Table_reciprocal;// test reciprocal type

#define OPTIONAL_SAVE_LOAD_EXAMPLE
#if !defined(OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER) && defined(OPTIONAL_SAVE_LOAD_EXAMPLE)
#include "GlvWidgetSaveLoad.h"
#include "GlvWidgetData_spec_std_container_container.h"
#include "GlvWidgetData_spec_std_array.h"
#include "filestream/spec/slv_rw_spec_std_array.h"
#include "misc/spec/SlvDataName_spec_std_array.h"
#include "filestream/spec/slv_rw_spec_std_list.h"
#include "misc/spec/SlvDataName_spec_std_list.h"
#include "filestream/spec/slv_rw_spec_std_deque.h"
#include "misc/spec/SlvDataName_spec_std_deque.h"
#endif

int main(int argc, char* argv[]) {

	QApplication app(argc, argv);

	int N1 = 8;
	int N2 = 10;
	int N3 = 5;

	Table table;
	for (int i0 = 0; i0 < Narray; i0++) {
		std::vector< std::list< std::deque<Tdata> > > vector;
		for (int i1 = 0; i1 < N1; i1++) {
			std::list< std::deque<Tdata> > list;
			for (int i2 = 0; i2 < N2; i2++) {
				std::deque<Tdata> deque;
				for (int i3 = 0; i3 < N3; i3++) {
					deque.push_back(i0 + i1 + i2 + i3);
				}
				list.push_back(deque);
			}
			vector.push_back(list);
		}
		table[i0] = vector;
	}

	GlvTableView<Table> table_view(table);
	table_view.set_dynamically_update_data(false);
	table_view.show();

#ifdef OPTIONAL_SAVE_LOAD_EXAMPLE
	/*GlvWidget<Table> widget(table);
	GlvWidgetSaveLoad<Table>* save_load_widget = new GlvWidgetSaveLoad<Table>(&widget);
	widget.show();*/

	GlvWidget<Table::value_type> widget(table[0]);
	GlvWidgetSaveLoad<Table::value_type>* save_load_widget = new GlvWidgetSaveLoad<Table::value_type>(&widget);
	widget.show();

	std::cout << table << std::endl;// test ostream
	std::cout << Table_reciprocal() << std::endl;// test ostream
#endif

	return app.exec();

}
