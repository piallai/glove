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

#include "std_vector.h"
#include <QVector>

//tricky to include using Clang. Used for debug mostly

template <class T>
std::ostream& operator<<(std::ostream& _os, const QVector<T>& _vector) {

    _os << _vector.toStdVector();

    return _os;
}

template <class T>
std::istream& operator>>(std::istream& _is, QVector<T>& _vector) {

    std::vector<T> _std_vector;
    _is >> _std_vector;
    _vector.fromStdVector(_std_vector);

    return _is;
}
