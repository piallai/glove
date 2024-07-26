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

#pragma once

#include <QModelIndex>
#include "std_vector.h"
class QTreeView;
class QStandardItemModel;

namespace glv {
	/*! Methods managing View widgets.*/
	namespace view {
		/*! Creates new QTreeView from a \p _model.*/
		QTreeView* toQTreeView(QStandardItemModel* _model);
		/*! Creates new QTreeView from a \p _data.*/
		template <class Tdata>
		QTreeView* toQTreeView(const Tdata& _data);

		/*! Tree expansions coordinates.*/
		typedef std::vector< std::vector<unsigned int> > Ttree_expansions;
		namespace {//anonymous namespace to simulate private attribute
			void get_tree_expansions(QTreeView* _tree_view, QModelIndex _index, Ttree_expansions& _expansions, const std::vector<unsigned int>& _expansion_element);
		}
		/*! Get the tree expansions of the \p _tree_view*/
		Ttree_expansions get_tree_expansions(QTreeView* _tree_view);
		/*! Set the tree expansions of the \p _tree_view*/
		void set_tree_expansions(QTreeView* _tree_view, const Ttree_expansions& _expansion);
	}
}

template <class Tdata>
QTreeView* glv::view::toQTreeView(const Tdata& _data) {

	return toQTreeView(toQStandardItemModel(_data));
}
