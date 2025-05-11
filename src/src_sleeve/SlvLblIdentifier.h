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

#include "slv_lbl.h"
#include "SlvLabeling.h"

/*! Convenience class to label as name (unsigned int)*/
class SlvLblIdentifier : public SlvLabeling<slv::lbl::Identifier> {

public:

	SlvLblIdentifier(slv::lbl::Identifier _Id);
	~SlvLblIdentifier();

	/*! Reimplementation of get_label() as get_Id().*/
	const slv::lbl::Identifier& get_Id() const;

};
