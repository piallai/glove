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

#include "GlvStatusMgr.h"

#include "slv_vector.h"
#include "glv_flag.h"

GlvStatusMgr::GlvStatusMgr() {

	connect(this, SIGNAL(display()), this, SLOT(show_status()));

	l_continue = true;

}

GlvStatusMgr::~GlvStatusMgr() {

}

void GlvStatusMgr::clear() {

	statuses.clear();

}

void GlvStatusMgr::add(const SlvStatus* _status) {

	if (!slv::vector::find(_status, statuses)) {

		statuses.push_back(_status);

	}

}

void GlvStatusMgr::set_frozen() {

	l_continue = false;

}

bool  GlvStatusMgr::proceeed() const {

	return l_continue;

}

void GlvStatusMgr::show_status() {

	bool l_ok = true;
	for (std::vector<const SlvStatus*>::const_iterator it = statuses.begin(); it != statuses.end(); ++it) {
		l_ok &= glv::flag::showQMessageBox(**it, true);
	}

	l_continue = l_ok;
}
