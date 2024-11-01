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

#include "SlvStatus.h"
class QWidget;
#include <QString>

namespace glv {
	/*! Flag functions for Glv*/
	namespace flag {
		/*! Calls QMessageBox according to \p _status most critical type.
		* \p _l_show_all : if false displays only most critical message (if any). If true displays all messages.
		* Return true if message box was being clicked its Ok button.*/
		bool showQMessageBox(const SlvStatus& _status, bool _l_show_all, QWidget* _parent = NULL);
		/*! Calls QMessageBox according to \p _status most critical type.
		* \p _message : preceding message.
		* \p _l_show_all : if false displays only most critical message (if any). If true displays all messages.
		* Return true if message box was being clicked its Ok button.*/
		bool showQMessageBox(const QString& _message, const SlvStatus& _status, bool _l_show_all, QWidget* _parent = NULL);
		/*! Calls QMessageBox::critical with message \p _message and breaks.*/
		void BREAK(std::string warning_message, QWidget* _parent = NULL);
		/*! Calls QMessageBox::information with message \p _message.*/
		void INFO(std::string warning_message, QWidget* _parent = NULL);
	}
}
