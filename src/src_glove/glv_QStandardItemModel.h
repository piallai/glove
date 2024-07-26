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
class QStandardItemModel;

namespace glv {
	/*! Template data to QStandardItemModel management.*/
	namespace tdata {
		/*! Class to specialize to write and read a data to a QStandardItemModel at QModelIndex.
		* This is the very entry point specialization. Remainder is supposed to be automatic.*/
		template <class Tdata, typename = void>
		struct QStandardItemModelMaker {
			static constexpr bool is_specialized = false;
		};

		/*! Creates a model with a data.*/
		template <class Tdata>
		QStandardItemModel* toQStandardItemModel(const Tdata& _data);
		/*! Writes \p _data in \p _model at \p _index location.
		* Requires glv::tdata::QStandardItemModelMaker<Tdata> specialization.
		* _flag_additional adds a flag to QStandardItem created model. For instance, if flag is set to Qt::ItemIsEnabled, then disables Item */
		template <class Tdata>
		void toQStandardItemModel(const Tdata& _data, QStandardItemModel* _model, const QModelIndex _index = QModelIndex(), const Qt::ItemFlag _flag_additional = Qt::NoItemFlags);
		/*! Get data from a model.*/
		template <class Tdata>
		Tdata fromQStandardItemModel(const QStandardItemModel* _model, const QModelIndex _index = QModelIndex(), int _Mrows = -1, int _Ncols = -1);

		/*! Cast the QStandardItem corresponding to _index.*/
		template <class T>
		T* get_item(const QModelIndex& _index);

		template <class T>
		std::vector<int> get_coordinates(const QModelIndex& _index);

		constexpr Qt::ItemFlags type_mismatch_flag = Qt::ItemNeverHasChildren;
		constexpr bool l_allow_type_mismatch_edit = true;
	}

	/*! Resize a model at _index location.*/
	void resize(QStandardItemModel* _model, unsigned int _Mrows, unsigned int _Ncols = 1, const QModelIndex _index = QModelIndex());
	void resize_rows(QStandardItemModel* _model, unsigned int _Mrows, const QModelIndex _index = QModelIndex());
	void resize_cols(QStandardItemModel* _model, unsigned int _Ncols, const QModelIndex _index = QModelIndex());
}

#include <QStandardItemModel>
#include "glv_QStandardItem.h"//for get_coordinates

template <class Tdata>
QStandardItemModel* glv::tdata::toQStandardItemModel(const Tdata& _data) {

	QStandardItemModel* model = new QStandardItemModel;
	glv::tdata::toQStandardItemModel(_data, model);
	return model;

}

template <class Tdata>
void glv::tdata::toQStandardItemModel(const Tdata& _data, QStandardItemModel* _model, const QModelIndex _index, const Qt::ItemFlag _flag_additional) {

	glv::tdata::QStandardItemModelMaker<Tdata>::make(_data, _model, _index, _flag_additional);
}

template <class Tdata>
Tdata glv::tdata::fromQStandardItemModel(const QStandardItemModel* _model, const QModelIndex _index, int _Mrows, int _Ncols) {

	return glv::tdata::QStandardItemModelMaker<Tdata>::get_value(_model, _index, _Mrows, _Ncols);
}

template <class T>
T* glv::tdata::get_item(const QModelIndex& _index) {

	if (_index.isValid()) {
		const QStandardItemModel* standard_item_model = dynamic_cast<const QStandardItemModel*>(_index.model());
		if (standard_item_model) {
			return dynamic_cast<T*>(standard_item_model->itemFromIndex(_index));
		} else {
			return 0;
		}
	} else {
		return 0;
	}

}

template <class T>
std::vector<int> glv::tdata::get_coordinates(const QModelIndex& _index) {

	QModelIndex index = _index;
	return glv::tdata::QStandardItemMaker<T>::get_coordinates(index);

}
