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

#include "GlvCLI.h"

#include "GlvProgressMgr.h"

glvm_staticVariable_impl(, SlvPoolFactory<SlvProgressionQt COMMA slv::lbl::Name>, GlvApp, progressions, {});

SlvProgressionQt* GlvApp::get_progression(const slv::lbl::Name& _name) {

	return progressions().get(_name);;

}

void GlvApp::show(const SlvStatus& _status, bool _l_wait) {

	status() = _status;

	if (status_mgr()) {

		/*! Check if a QApplication was instantiated. So that method can still be used even if GLOVE_APP is not used.*/
		QApplication* application = qobject_cast<QApplication*>(QCoreApplication::instance());
		if (application) {
			// Freeze status mgr in this thread. Too slow to freeze in slot connected to display otherwise.
			if (_l_wait) {
				status_mgr()->set_frozen();
			}
			status_mgr()->display();
		}

		while (!status_mgr()->proceeed()) {}

	}

}
