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

#include "glv_flag.h"
#include "slv_flag.h"
#include <QMessageBox>
#include "SlvCombo.h"

void glv::flag::showQMessageBox(const SlvStatus& _status, bool _l_show_all, QWidget* _parent) {

	QString message;
	if (!_l_show_all) {
		message = QObject::tr(_status.get_message().c_str());
	} else {
		for (SlvStatus::const_iterator it = _status.begin(); it != _status.end(); ++it) {
			if (it->value != SlvStatus::statusType::ok) {
				message += QObject::tr(it->data.c_str());
				if (std::next(it) != _status.end()) {
					message += "\n";
				}
			}
		}
	}

	if (_status.get_type() == SlvStatus::statusType::ok) {

	} else if (_status.get_type() == SlvStatus::statusType::information) {
		QMessageBox::information(_parent, "", message);
	} else if (_status.get_type() == SlvStatus::statusType::warning) {
		QMessageBox::warning(_parent, "", message);
	} else if (_status.get_type() == SlvStatus::statusType::critical) {
		QMessageBox::critical(_parent, "", message);
	}
}

void glv::flag::BREAK(std::string warning_message, QWidget* _parent) {

	showQMessageBox(SlvStatus(SlvStatus::statusType::critical, warning_message), false, _parent);
	slv::flag::ISSUE(slv::flag::Critical, warning_message);

}

void glv::flag::INFO(std::string warning_message, QWidget* _parent) {

	showQMessageBox(SlvStatus(SlvStatus::statusType::information, warning_message), false, _parent);

}
