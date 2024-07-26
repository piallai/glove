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

#include <QString>
class GlvTableView_base;

namespace glv {
	/*! Methods managing View widgets.*/
	namespace view {
		/*! Get text of \p _table_view at coordinates \p i \p j*/
		QString get_string(const GlvTableView_base* _table_view, unsigned int i, unsigned j = 0);
		/*! Set text of \p _table_view at coordinates \p i \p j*/
		void set_string(GlvTableView_base* _table_view, const QString& _string, unsigned int i, unsigned j = 0);
	}
}
