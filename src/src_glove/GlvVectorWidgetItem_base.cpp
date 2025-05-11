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

#include "GlvVectorWidgetItem_base.h"
#include <QHBoxLayout>
#include <QPushButton>

GlvVectorWidgetItem_base::GlvVectorWidgetItem_base() {

	layout = new QHBoxLayout;
	setLayout(layout);
	layout->setContentsMargins(0, 0, 0, 0);

}

GlvVectorWidgetItem_base::~GlvVectorWidgetItem_base() {

}

void GlvVectorWidgetItem_base::show_remove_button(bool _l_show) {

	if (_l_show) {
		remove_button->show();
	} else {
		remove_button->hide();
	}

}
