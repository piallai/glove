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

#include "glv_QString.h"
#include "slv_string.h"

template <>
QString glv::toQString<std::string>(const std::string& _value) {
	return QString(_value.c_str());
}
template <>
QString glv::toQString<double>(const double& _value) {
	return QString(slv::string::value_to_string(_value).c_str());
}
template <>
QString glv::toQString<float>(const float& _value) {
	return QString(slv::string::value_to_string(_value).c_str());
}
template <>
QString glv::toQString<int>(const int& _value) {
	return QString(slv::string::number_to_string_auto(_value).c_str());
}
template <>
QString glv::toQString<unsigned int>(const unsigned int& _value) {
	return QString(slv::string::number_to_string_auto(_value).c_str());
}
template <>
QString glv::toQString<unsigned long>(const unsigned long& _value) {
	return QString(slv::string::number_to_string_auto(_value).c_str());
}
