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

#include "GlvParamListDialog_base.h"
#include "GlvParametrizationDialog_base.h"
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>

GlvParamListDialog_base::GlvParamListDialog_base(const std::vector<std::string>& _names, const std::string _list_name, QWidget* _parent, bool _l_dialog, bool _l_visible_config) :\
GlvListDialog(_names, _list_name, _parent, _l_dialog) {

	l_visible_config = _l_visible_config;

	parametrization_dialog = NULL;

	if (l_visible_config) {
		QPushButton* configure_button = new QPushButton(QString(tr("Configure")));
		configure_button->setMinimumHeight(23);
		list_layout->addWidget(configure_button, 2, 1);

		connect(configure_button, SIGNAL(clicked()), this, SLOT(make_parametrization_dialog()));
	} else {
		//auto open config when combo selection changes
		connect(combo_list, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(make_parametrization_dialog(const QString&)));
	}
}

GlvParamListDialog_base::~GlvParamListDialog_base() {
	if (parametrization_dialog) {
		delete parametrization_dialog;
	}
}

void GlvParamListDialog_base::delete_parametrization_dialog() {

	if (parametrization_dialog) {
		delete parametrization_dialog;
		parametrization_dialog = NULL;
	}

}

GlvParametrizationDialog_base* GlvParamListDialog_base::get_parametrization_dialog_base() {

	return parametrization_dialog;

}

const SlvParametrization_base* GlvParamListDialog_base::get_parametrization_base() const {

	if (parametrization_dialog) {
		return parametrization_dialog->get_parametrization_base();
	} else {
		// Reasons can be : List wasn't accepted, or Tlist is empty
		return NULL;
	}

}
