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

#include <QDialog>
class QDialogButtonBox;

/*! Convenience class to build a ok / cancel QDialog widget. Twidget must inherit QWidget.*/
template <class Twidget>
class GlvDialog : public QDialog {

private:

	QDialogButtonBox* button_box;

public:

	Twidget* widget;

	GlvDialog();
	~GlvDialog();

};


#include <QDialogButtonBox>
#include <QVBoxLayout>

template <class Twidget>
GlvDialog<Twidget>::GlvDialog() {

	QVBoxLayout* layout = new QVBoxLayout;
	this->setLayout(layout);
	widget = new Twidget;
	layout->addWidget(widget);

	button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	connect(button_box, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
	layout->addWidget(button_box);

}

template <class Twidget>
GlvDialog<Twidget>::~GlvDialog() {

}
