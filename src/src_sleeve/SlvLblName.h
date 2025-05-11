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
#include "SlvOS.h"
#include "SlvVirtualGetName.h"

/*! Convenience class to label as name (std::string) using dedicated class SlvLabeling.*/
class SlvLblName : public SlvLabeling<slv::lbl::Name>, virtual public SlvOS, virtual public SlvVirtualGetName {

public:

	SlvLblName(std::string _name);
	virtual ~SlvLblName();

	/*! Reimplementation of get_label() as get_name().*/
	const std::string& get_name() const;

private:

	void ostream(std::ostream& _os) const;

};
