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

class GlvWidgetSaveLoad_base;

class GlvSaveLoad {

protected:

	GlvWidgetSaveLoad_base* save_load_widget;

public:
	GlvSaveLoad();
	~GlvSaveLoad();

	/*! Delete the save/load widget. Return true if the widget existed and was deleted, false otherwise.*/
	bool delete_save_load_widget();

};