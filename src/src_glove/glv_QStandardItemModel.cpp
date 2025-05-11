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

#include "glv_QStandardItemModel.h"

#include <QStandardItemModel>

void glv::resize(QStandardItemModel* _model, unsigned int _Mrow, unsigned int _Ncol, const QModelIndex _index) {


	unsigned int current_rowCount = _model->rowCount(_index);
	unsigned int current_columnCount = _model->columnCount(_index);

	if (_Mrow >= current_rowCount) {
		_model->insertRows(current_rowCount, _Mrow - current_rowCount, _index);
	} else {
		_model->removeRows(_Mrow, current_rowCount - _Mrow, _index);
	}

	if (_Ncol >= current_columnCount) {
		_model->insertColumns(current_columnCount, _Ncol - current_columnCount, _index);
	} else {
		_model->removeColumns(_Ncol, current_columnCount - _Ncol, _index);
	}

}

void glv::resize_rows(QStandardItemModel* _model, unsigned int _Mrow, const QModelIndex _index) {

	unsigned int current_rowCount = _model->rowCount(_index);

	if (_Mrow >= current_rowCount) {
		_model->insertRows(current_rowCount, _Mrow - current_rowCount, _index);
	} else {
		_model->removeRows(_Mrow, current_rowCount - _Mrow, _index);
	}

}

void glv::resize_cols(QStandardItemModel* _model, unsigned int _Ncol, const QModelIndex _index) {

	unsigned int current_columnCount = _model->columnCount(_index);

	if (_Ncol >= current_columnCount) {
		_model->insertColumns(current_columnCount, _Ncol - current_columnCount, _index);
	} else {
		_model->removeColumns(_Ncol, current_columnCount - _Ncol, _index);
	}

}
