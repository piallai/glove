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

#include <QString>
class QComboBox;
class QWidget;

namespace glv {

	/*! Create a QComboBox from a Tdata. Displayed values are the first template argument.*/
	template <class Tdata>
	QComboBox* toQComboBox(const Tdata& _data, QString _name = "", QWidget* _parent = 0);
	/*! Assign a Tdata to a QComboBox. Displayed values are the first template argument.*/
	template <class Tdata>
	void toQComboBox(QComboBox* _combo_box, const Tdata& _data, QString _name = "");

}

#include <QComboBox>
#include "glv_QStandardItemModel.h"

template <class Tdata>
QComboBox* glv::toQComboBox(const Tdata& _data, QString _name, QWidget* _parent) {

	QComboBox* combo_box = new QComboBox(_parent);
	toQComboBox(combo_box, _data, _name);
	return combo_box;

}

template <class Tdata>
void glv::toQComboBox(QComboBox* _combo_box, const Tdata& _data, QString _name) {

	QStandardItemModel* model = glv::tdata::toQStandardItemModel(_data);
	_combo_box->clear();
	_combo_box->setObjectName(_name);
	_combo_box->setModel(model);

}