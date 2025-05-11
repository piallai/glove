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
class SlvStatus;

/*! Class for status message display using message boxes.*/
class GlvStatusMgr : public QObject {

	Q_OBJECT

private:

	std::vector<const SlvStatus*> statuses;
	/*! Manage state of returned message boxes accpetance.*/
	bool l_continue;

public:

	GlvStatusMgr();
	~GlvStatusMgr();

	/*! Clear statuses from the instance.*/
	void clear();

	void add(const SlvStatus* _status);

	/*! Forbid continuation.*/
	void set_frozen();
	/*! Whether continue is possible or not.*/
	bool proceeed() const;

private slots:

	/*! Show all status messages as Qt message boxes.*/
	void show_status();

signals:

	/*! Signal request to show all status messages. Convenient for threads context.*/
	void display();


};