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

#define Variadic_templates template <class T> typename... Types

/*! Convenience class to build a Ok/Cancel QDialog widget. Twidget can be data display widget such as GlvWidgetData, GlvTableView, or GlvTreeView.*/
template <template <class _Tdata, Variadic_templates> class Twidget, class Tdata>
class GlvDialogData : public QDialog {

private:

	Twidget<Tdata>* widget;
	QDialogButtonBox* button_box;

public:

	GlvDialogData(const Tdata _data = Tdata());
	~GlvDialogData();

	/*! Return the widget managing the data.*/
	Twidget<Tdata>* get_widget();

	/*! Get value currently displayed in the widget.*/
	Tdata get_value() const;
	/*! Set value to the widget.*/
	void set_value(const Tdata& _data);

};


#include <QDialogButtonBox>
#include <QVBoxLayout>

template <template <class _Tdata, Variadic_templates> class Twidget, class Tdata>
GlvDialogData<Twidget, Tdata>::GlvDialogData(const Tdata _data) {

	QVBoxLayout* layout = new QVBoxLayout;
	this->setLayout(layout);
	widget = new Twidget<Tdata>(_data);
	layout->addWidget(widget);

	button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	connect(button_box, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
	layout->addWidget(button_box);

}

template <template <class _Tdata, Variadic_templates> class Twidget, class Tdata>
GlvDialogData<Twidget, Tdata>::~GlvDialogData() {

}

template <template <class _Tdata, Variadic_templates> class Twidget, class Tdata>
Twidget<Tdata>* GlvDialogData<Twidget, Tdata>::get_widget() {

	return widget;

}

template <template <class _Tdata, Variadic_templates> class Twidget, class Tdata>
Tdata GlvDialogData<Twidget, Tdata>::get_value() const {

	return widget->get_value();

}

template <template <class _Tdata, Variadic_templates> class Twidget, class Tdata>
void GlvDialogData<Twidget, Tdata>::set_value(const Tdata& _data) {

	widget->set_value();

}

#undef Variadic_templates
