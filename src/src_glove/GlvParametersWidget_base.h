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

#include <QGroupBox>
class QVBoxLayout;
class QGridLayout;
template <class Tparam>
class GlvParameterWidget;
#include "GlvSaveLoad.h"
#include "SlvMacrosDeclarations.h"

/*! Widget managing the parameters of classes SlvParametrization**.*/
class GlvParametersWidget_base : public QGroupBox, public GlvSaveLoad {

	Q_OBJECT

private:
	glvm_staticVariable(const, int, grid_horizontal_spacing, 10);
	glvm_staticVariable_def(const, int, layout_margin);
private :
	/*! Whether the parameters are set in a scroll area or not.*/
	bool l_scrollable;
	class ScrollArea;
	/*! Scroll area of parameters.*/
	ScrollArea* scroll_area;
	/*! Whether last resize update was a height decrease.*/
	bool l_height_decreased;
	/*! If true, max height will apply whenever scroll bar appears.
	* If false (default), the widget can still be resized up to the last height before parameters size reduction.
	* i.e.: Update height hint to fit to parameters widget.*/
	bool l_adapt_max_height;
public:
	enum LayoutType { Vertical, Grid };
protected:
	LayoutType layout_type = LayoutType::Vertical;
	QVBoxLayout* vertical_layout;
	QGridLayout* grid_layout;
	QVBoxLayout* main_layout;
	QWidget* parameters_widget;

	GlvParametersWidget_base();
	virtual ~GlvParametersWidget_base();
public:

	/*! Set layout of parameters widget to vertical, ie a stack of the parameter widgets.
	* More intuitive, but lacks aligment of names and data widgets
	* It is possible to switch from set_layout_grid() to set_layout_vertical() and vice versa.*/
	void set_layout_vertical();
	/*! Set layout of parameters widget as a grid layout.Names and data widgets are aligned, but their ownsership is moved.
	* It is possible to switch from set_layout_grid() to set_layout_vertical() and vice versa.*/
	void set_layout_grid();
	/*! Set layout type either to LayoutType::Vertical or LayoutType::Grid.*/
	virtual void set_layout_type(LayoutType _layout_type) = 0;
	/*! Display or hide data type information in 'whatsthis'.*/
	virtual void enable_data_type_info(bool _l_enable) = 0;

	/*! Returns true if the parameters are fully visible (no scroll bars).*/
	bool is_fully_visible() const;
	/*! Returns true if the parameters widget last resize update was a height decrease.*/
	bool has_height_decreased() const;
	/*! Set parameters to be scrollable or not.
	* Default state is true.*/
	void set_scrollable(bool _l_scrollable);
	/*! Advanced setting.
	* If true, max height will apply whenever scroll bar appears.
	* If false (default), the widget can still be resized up to the last height before parameters size reduction.
	* i.e.: Update height hint to fit to parameters widget.*/
	void set_adapt_max_height(bool _l_adapt);

protected:
	/*! Add the parameter widget to the parameters.*/
	void add_parameter_widget_to_vertical_layout(QWidget* _parameter_widget);
	template <class Tdata>
	void set_parameter_widget_to_grid_layout(GlvParameterWidget<Tdata>* _parameter_widget, int i);
	/*! Set layout type, protected.*/
	void set_layout_type_protected(LayoutType _layout_type);
	/*! Set save/load widget. Called in GlvParametrizationSaveLoad.*/
	void set_save_load_widget(GlvWidgetSaveLoad_base* _save_load_widget);
	/*! Enable/disable possibility to show/hide parameters.*/
	void set_checkable_collapse(bool _l_checkable);
	
private:
	/*! Add to row \p i :
	* Column 0 : \p _dataname_label.
	* Column 1 : \p _data_widget.
	* Column 2 : \p _optional_text.*/
	void add_parameter_widget_to_grid_layout(QWidget* _dataname_label, QWidget* _data_widget, QWidget* _optional_text_label, int i);
	/*! Get number of parameters.*/
	virtual int get_Nparameters() const = 0;
	bool eventFilter(QObject* object, QEvent* _event);
private slots:
	/*! Show parameters or not.*/
	void show_parameters(bool _l_show);
signals:
	/*! Emitted when the parameter named \p _parameter_name has changed.*/
	void parameterChanged(std::string _parameter_name);
	/*! Emitted when the widget containing the parameters (only) is being resized vertically.*/
	void heightChanged();
};

#include "GlvParameterWidget.h"

template <class Tdata>
void GlvParametersWidget_base::set_parameter_widget_to_grid_layout(GlvParameterWidget<Tdata>* _parameter_widget, int i) {

	add_parameter_widget_to_grid_layout(reinterpret_cast<QWidget*>(_parameter_widget->data_name_label), \
		_parameter_widget->get_widget(), \
		reinterpret_cast<QWidget*>(_parameter_widget->optional_text_label), i);

}
