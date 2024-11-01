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
#include "glv_QString.h"

bool glv::flag::showQMessageBox(const SlvStatus& _status, bool _l_show_all, QWidget* _parent) {

	return showQMessageBox("", _status, _l_show_all, _parent);
}

bool glv::flag::showQMessageBox(const QString& _message, const SlvStatus& _status, bool _l_show_all, QWidget* _parent) {

	QString message;
	if (_status.get_type() != SlvStatus::statusType::ok) {
		if (!_message.isEmpty()) {
			message = _message;
			message += "\n";
		}
		message += glv::toQString(_status.to_string(_l_show_all));
	}

	QMessageBox::StandardButton button = QMessageBox::StandardButton::NoButton;
	if (_status.get_type() == SlvStatus::statusType::information) {
		button = QMessageBox::information(_parent, "", message);
	} else if (_status.get_type() == SlvStatus::statusType::warning) {
		button = QMessageBox::warning(_parent, "", message);
	} else if (_status.get_type() == SlvStatus::statusType::critical) {
		button = QMessageBox::critical(_parent, "", message);
	}

	return (button == QMessageBox::StandardButton::Ok);
}

void glv::flag::BREAK(std::string warning_message, QWidget* _parent) {

	showQMessageBox(SlvStatus(SlvStatus::statusType::critical, warning_message), false, _parent);
	slv::flag::ISSUE(slv::flag::Critical, warning_message);

}

void glv::flag::INFO(std::string warning_message, QWidget* _parent) {

	showQMessageBox(SlvStatus(SlvStatus::statusType::information, warning_message), false, _parent);

}
