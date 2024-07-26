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

class QStandardItem;
#include <qnamespace.h>

namespace glv {
	/*! Contains methods managing the conversion between template data and QStandardItemModel*/
	namespace tdata {
		/*! Manages Tdata to QStandardItem.*/
		/*! By default: data to string, string to data.*/
		/*! If a QStandardItemModelMaker specialization exists, then it is used to 2-ways translate Tdata to QStandardItem.*/
		template <class Tdata, typename = void>
		struct QStandardItemMaker;

		/*! Write \p _data in \p _item. If the data model exists, the model will expand at \p _item's location.*/
		template <class Tdata>
		void toQStandardItem(const Tdata& _data, QStandardItem* _item, const Qt::ItemFlag _flag_additional = Qt::NoItemFlags);
		/*! Read a data from \p _item.*/
		template <class Tdata>
		Tdata fromQStandardItem(const QStandardItem* _item);
	}

}

#include "glv_QString.h"
#include <QStandardItem>

template <class Tdata, typename T>
struct glv::tdata::QStandardItemMaker {

	static void make(const Tdata& _data, QStandardItem* _item, const Qt::ItemFlag _flag_additional) {
		QString text = glv::toQString(_data);
		if (text != _item->text()) {
			_item->setText(text);
		}
	}

	static Tdata get_value(const QStandardItem* _item) {

		Tdata data = slv::string::string_to_value<Tdata>(_item->text().toStdString());
		return data;
	}

	static std::vector<int> get_coordinates(const QModelIndex& _index) {
		return std::vector<int>();
	}

};

#include "glv_QStandardItemModel.h"
#include "slv_flag.h"
/*! Specialization if there exists a specialization of glv::QStandardItemModelMaker.*/
template <class Tdata>
struct glv::tdata::QStandardItemMaker<Tdata, typename std::enable_if<glv::tdata::QStandardItemModelMaker<Tdata>::is_specialized>::type> {

	static void make(const Tdata& _data, QStandardItem* _item, const Qt::ItemFlag _flag_additional) {

		QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(_item->model());
		if (model) {
			glv::tdata::toQStandardItemModel(_data, model, _item->index(), _flag_additional);
		} else {
			slv::flag::ISSUE(slv::flag::Critical, "make() : QStandardItem must already have a model");
		}

	}

	static Tdata get_value(const QStandardItem* _item) {

		Tdata data;

		QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(_item->model());
		if (model) {
			data = glv::tdata::fromQStandardItemModel<Tdata>(model, _item->index());
		} else {
			slv::flag::ISSUE(slv::flag::Critical, "get_value() : QStandardItem must already have a model");
		}

		return data;
	}

	static std::vector<int> get_coordinates(QModelIndex& _index) {

		return glv::tdata::QStandardItemModelMaker<Tdata>::get_coordinates(_index);

	}

};

template <class Tdata>
void glv::tdata::toQStandardItem(const Tdata& _data, QStandardItem* _item, const Qt::ItemFlag _flag_additional) {

	glv::tdata::QStandardItemMaker<Tdata>::make(_data, _item, _flag_additional);
}

template <class Tdata>
Tdata glv::tdata::fromQStandardItem(const QStandardItem* _item) {

	return glv::tdata::QStandardItemMaker<Tdata>::get_value(_item);
}



