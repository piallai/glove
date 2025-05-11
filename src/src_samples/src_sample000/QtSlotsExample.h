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

#include <QObject>
#include <iostream>
#include <QDebug>

class QtSlotsExample : public QObject {
	Q_OBJECT
public:
	QtSlotsExample() {}
public slots:
	void get() {
		std::cout << "QtSlotsExample::get" << std::endl;
	}
	void get(double _value) {
		std::cout << "QtSlotsExample::get " << _value << std::endl;
	}
	void get(std::string _value) {
		std::cout << "QtSlotsExample::get " << _value << std::endl;
	}
	void get(QString _value) {
		qDebug() << "QtSlotsExample::get " << _value;
	}
};
