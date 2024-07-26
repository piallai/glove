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

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "GlvProgressMgr.h"
#else
#include "glove.h"
#endif

// Simple wrapper to clear and hide GlvProgressMgr instance
class FutureWrapper : public QObject {

	Q_OBJECT

	GlvProgressMgr* progress_mgr;

public:

	FutureWrapper(GlvProgressMgr* _progress_mgr) { progress_mgr = _progress_mgr; }

public slots :

	void hide() {
		progress_mgr->clear();
		progress_mgr->hide();
	}

};
