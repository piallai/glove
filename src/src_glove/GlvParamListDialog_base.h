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

#include "GlvListDialog.h"
class GlvParametrizationDialog_base;
class SlvParametrization_base;

class GlvParamListDialog_base : public GlvListDialog {

	Q_OBJECT

protected:
	/*! \p _names : List of names to fill the combo list.
	* \p _list_name : name of the list used for display.
	* \p _l_dialog: Whether QDialog functionalities are activated or not (buttons, accept/reject).
	* \p _l_visible_config : If true, configure button is displayed. Otherwise, parametrization is triggered when changing QComboBox item.*/
	GlvParamListDialog_base(const std::vector<std::string>& _names, const std::string _list_name, QWidget* _parent, bool _l_dialog, bool _l_visible_config);
public:
	virtual ~GlvParamListDialog_base();
protected:

	/*! Whether configuration is displayed below list, or accessible by configure button.*/
	bool l_visible_config;

	/*! Parametrization widget.*/
	GlvParametrizationDialog_base* parametrization_dialog;

	/*! Delete parametrization widget.*/
	void delete_parametrization_dialog();

public:

	/*! Get base parametrization widget.*/
	GlvParametrizationDialog_base* get_parametrization_dialog_base();
	/*! Get base parametrization.*/
	const SlvParametrization_base* get_parametrization_base() const;

private slots:

	virtual void make_parametrization_dialog() = 0;
	virtual void make_parametrization_dialog(const QString& _item_name) = 0;

signals:
	/*! Emitted when a parametrization widget is requested in GlvParamListDialog (ex: creation).*/
	void configure(QString _item_name);

};
