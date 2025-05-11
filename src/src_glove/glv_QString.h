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

#pragma once

#include <QString>
#include "std_vector.h"
class QStringListModel;

namespace glv {

	/*! Get QString from a template \p _value.*/
	template <class T>
	QString toQString(const T& _value);
	/*! Get QStringListModel from a vector of template type. Uses toQString.*/
	template <class T>
	QStringListModel* toQStringListModel(const std::vector<T>& _vector);

}

template <>
QString glv::toQString<std::string>(const std::string& _value);
template <>
QString glv::toQString<double>(const double& _value);
template <>
QString glv::toQString<float>(const float& _value);
template <>
QString glv::toQString<int>(const int& _value);
template <>
QString glv::toQString<unsigned int>(const unsigned int& _value);
template <>
QString glv::toQString<unsigned long>(const unsigned long& _value);

#include "slv_string.h"

template <class T>
QString glv::toQString(const T& _value) {
	return QString(slv::string::to_string(_value).c_str());
}

#include <QStringListModel>
template <class T>
QStringListModel* glv::toQStringListModel(const std::vector<T>& _vector) {

	QStringList vector_list;
	for (unsigned int i = 0; i < _vector.size(); i++) {
		vector_list << toQString(_vector[i]);
	}
	QStringListModel* vector_model = new QStringListModel(vector_list);

	return vector_model;

}
