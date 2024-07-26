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

#include "glv_QTreeView.h"
#include <QTreeView>
#include <QStandardItemModel>

QTreeView* glv::view::toQTreeView(QStandardItemModel* _model) {

	QTreeView* view = new QTreeView;
	view->setEditTriggers(QAbstractItemView::NoEditTriggers);
	view->setModel(_model);
	return view;
}

namespace glv {
	namespace view {
		namespace {
			void get_tree_expansions(QTreeView* _tree_view, QModelIndex _index, Ttree_expansions& _expansions, const std::vector<unsigned int>& _expansion_element) {

				QAbstractItemModel* model = _tree_view->model();
				if (_index.model() == model && model) {

					std::vector<unsigned int> expansion_element;
					for (int i = 0; i < model->rowCount(_index); i++) {

						expansion_element = _expansion_element;
						expansion_element.push_back(i);

						get_tree_expansions(_tree_view, model->index(i, 0, _index), _expansions, expansion_element);

						if (_tree_view->isExpanded(model->index(i, 0, _index))) {

							_expansions.push_back(expansion_element);
						}
					}
				}

			}

		}
	}
}

glv::view::Ttree_expansions glv::view::get_tree_expansions(QTreeView* _tree_view) {

	Ttree_expansions expansions;//coordinates
	std::vector<unsigned int> expansion_element;

	QAbstractItemModel* model = _tree_view->model();
	QModelIndex index;
	for (int i = 0; i < model->rowCount(); i++) {

		index = model->index(i, 0);

		expansion_element.clear();
		expansion_element.push_back(i);
		get_tree_expansions(_tree_view, index, expansions, expansion_element);

		if (_tree_view->isExpanded(index)) {

			expansions.push_back(expansion_element);
		}

	}

	return expansions;
}


void glv::view::set_tree_expansions(QTreeView* _tree_view, const Ttree_expansions& _expansions) {

	_tree_view->collapseAll();

	QAbstractItemModel* model = _tree_view->model();

	for (unsigned int i = 0; i < _expansions.size(); i++) {

		QModelIndex index = model->index(_expansions[i][0], 0);
		for (unsigned int j = 1; j < _expansions[i].size(); j++) {
			index = model->index(_expansions[i][j], 0, index);
		}
		_tree_view->setExpanded(index, true);
	}

}
