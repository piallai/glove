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

#include "GlvParametersWidget_base.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include "GlvWidgetSaveLoad_base.h"
#include "glv_widget.h"
#include <QScrollArea>
#include <QScrollBar>
#include <QApplication>
#include <QStyle>
#include <QScreen>
#include <QResizeEvent>
#include <QPushButton>
#include "glv_flag.h"
#include "GlvParametersParserConfigDialog.h"
#include <QLabel>

glvm_staticVariable_impl(const, int, GlvParametersWidget_base, layout_margin, QApplication::style()->pixelMetric(QStyle::PM_LayoutLeftMargin));

class GlvParametersWidget_base::ScrollArea : public QScrollArea {
public:
	bool eventFilter(QObject* object, QEvent* event) {
		// Depending on content, sizeHint may change without resize event to be called. Ex: one expanding widget next to fixed size one wich may have different size (checkable for instance)
		// QEvent::Resize is not called as often as QEvent::Paint and is theoretically more suitable, but it may miss these cases.
		if (object == widget() && event->type() == QEvent::Paint) {

			int min_width = widget()->sizeHint().width();
			int max_width = QGuiApplication::primaryScreen()->geometry().width() - 100;
			if (min_width > max_width) {
				min_width = max_width;
			}
			if (widget()->size().height() > QScrollArea::size().height()) {
				min_width += QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent);
			}
			QScrollArea::setMinimumWidth(min_width);
		}
		return QWidget::eventFilter(object, event);
	}
	bool is_expanded_vertically() const {
		return widget()->size().height() > QScrollArea::size().height();
	}
};

GlvParametersWidget_base::GlvParametersWidget_base() {

	main_layout = new QVBoxLayout;
	main_layout->setContentsMargins(layout_margin(), layout_margin(), 0, layout_margin());
	this->setLayout(main_layout);

	options_widget = new QWidget;
	QHBoxLayout* options_layout = new QHBoxLayout;
	options_layout->setContentsMargins(0, 0, layout_margin(), 0);
	options_widget->setLayout(options_layout);
	main_layout->addWidget(options_widget, 0, Qt::AlignRight | Qt::AlignTop);

	QLineEdit* filter_parameters_widget = new QLineEdit;
	filter_parameters_widget->setPlaceholderText(tr("Filter parameters"));
	filter_parameters_widget->setToolTip(tr("Case sensitive filtering."));
	connect(filter_parameters_widget, SIGNAL(textChanged(QString)), this, SLOT(filter_parameters(QString)));
	options_layout->addWidget(filter_parameters_widget);

	parse_arguments_button = new QPushButton(tr("Parse"));
	parse_arguments_button->setToolTip(tr("Enter arguments as command line interface."));
	connect(parse_arguments_button, SIGNAL(clicked(bool)), this, SLOT(parse_arguments()));
	options_layout->addWidget(parse_arguments_button);

	parameters_widget = new QWidget;
	parameters_widget->installEventFilter(this);
	vertical_layout = new QVBoxLayout;
	parameters_widget->setLayout(vertical_layout);
	parameters_widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

	l_scrollable = false;
	scroll_area = NULL;
	main_layout->addWidget(parameters_widget);

	set_scrollable(true);
	set_options_enabled(false);

	l_height_decreased = false;
	l_adapt_max_height = false;

	save_load_widget = NULL;

}

GlvParametersWidget_base::~GlvParametersWidget_base() {

}

void GlvParametersWidget_base::set_layout_vertical() {

	set_layout_type(LayoutType::Vertical);

}

void GlvParametersWidget_base::set_layout_grid() {

	set_layout_type(LayoutType::Grid);

}

bool GlvParametersWidget_base::is_fully_visible() const {

	return !l_scrollable || !scroll_area->is_expanded_vertically();

}

void GlvParametersWidget_base::set_save_load_widget(GlvWidgetSaveLoad_base* _save_load_widget) {

	save_load_widget = _save_load_widget;
	if (save_load_widget) {
		save_load_widget->layout()->setContentsMargins(0, 0, layout_margin() - QApplication::style()->pixelMetric(QStyle::QStyle::PM_DefaultFrameWidth), 0);
		main_layout->addWidget(save_load_widget, 0, Qt::AlignRight | Qt::AlignBottom);
	}

}

void GlvParametersWidget_base::set_layout_type_protected(LayoutType _layout_type) {

	bool l_update_layout = false;
	if (layout_type != _layout_type) {
		l_update_layout = true;
	}
	layout_type = _layout_type;

	if (l_update_layout) {
		delete parameters_widget->layout();
		if (layout_type == LayoutType::Vertical) {
			vertical_layout = new QVBoxLayout;
			parameters_widget->setLayout(vertical_layout);
		} else if (layout_type == LayoutType::Grid) {
			grid_layout = new QGridLayout;
			grid_layout->setContentsMargins(0, 0, layout_margin(), 0);
			grid_layout->setHorizontalSpacing(grid_horizontal_spacing());
			parameters_widget->setLayout(grid_layout);
		}
	}

}

void GlvParametersWidget_base::add_parameter_widget_to_vertical_layout(QWidget* _parameter_widget) {

	vertical_layout->addWidget(_parameter_widget);

}

void GlvParametersWidget_base::add_parameter_widget_to_grid_layout(QWidget* _dataname_label, QWidget* _data_widget, QWidget* _optional_text_label, int i) {

	if (_dataname_label) {
		grid_layout->addWidget(_dataname_label, i, 0);
	}
	grid_layout->addWidget(_data_widget, i, 1);
	if (_optional_text_label) {
		grid_layout->addWidget(_optional_text_label, i, 2);
	}

}

void GlvParametersWidget_base::set_checkable_collapse(bool _l_checkable) {

	if (_l_checkable) {
		QGroupBox::setCheckable(true);
		connect(this, SIGNAL(toggled(bool)), this, SLOT(show_parameters(bool)));
		setChecked(false);
	} else {
		setChecked(true);
		disconnect(this, SIGNAL(toggled(bool)));
		QGroupBox::setCheckable(false);
	}
	

}

void GlvParametersWidget_base::set_scrollable(bool _l_scrollable) {

	if (!_l_scrollable && l_scrollable) {

		main_layout->insertWidget(0, parameters_widget);
		delete scroll_area;
		scroll_area = NULL;

	} else if (_l_scrollable && !l_scrollable) {

		scroll_area = new ScrollArea;
		scroll_area->setWidgetResizable(true);
		scroll_area->setWidget(parameters_widget);
		scroll_area->setFrameShape(QFrame::NoFrame);
		main_layout->addWidget(scroll_area, 0);

	}

	l_scrollable = _l_scrollable;


}

void GlvParametersWidget_base::set_adapt_max_height(bool _l_adapt) {

	l_adapt_max_height = _l_adapt;

}

void GlvParametersWidget_base::set_options_enabled(bool _l_enabled) {

	options_widget->setVisible(_l_enabled);
	if (_l_enabled) {
		main_layout->setContentsMargins(layout_margin(), 0, 0, layout_margin());
	} else {
		main_layout->setContentsMargins(layout_margin(), layout_margin(), 0, layout_margin());

	}

}

void GlvParametersWidget_base::show_parameters(bool _l_show) {

	parameters_widget->setVisible(_l_show);

	if (save_load_widget) {
		save_load_widget->setVisible(_l_show);
	}

}

void GlvParametersWidget_base::parse_arguments() {

	GlvParametersParserConfigDialog dialog;
	SlvParametersParserConfig parser_config;
	if (!CLI_arguments_line.empty()) {
		parser_config.set_arguments(CLI_arguments_line);
		parser_config.set_CLI_mode(true);
	}
	dialog.set_parametrization(parser_config);
	if (dialog.exec() == QDialog::Accepted) {
		if (dialog.get_parametrization().get_CLI_mode()) {
			// save CLI arguments
			CLI_arguments_line = dialog.get_parametrization().get_arguments();
		} else {
			CLI_arguments_line.clear();
		}
		SlvStatus status = parse_arguments(dialog.get_parametrization().get_arguments(), !dialog.get_parametrization().get_CLI_mode(), dialog.get_parametrization().get_CLI_mode());
		glv::flag::showQMessageBox(QObject::tr("Arguments conflict"), status, true);

		if (dialog.get_parametrization().get_show_parsed_argument_only()) {
			if (!CLI_parameters.empty()) {
				std::string exclude_string = std::to_string(std::nanl(""));
				filter_parameters(exclude_string, false, false);
			}
			for (auto it = CLI_parameters.begin(); it != CLI_parameters.end(); ++it) {
				filter_parameters(*it, true, true);
			}
		} else {
			filter_parameters("", false, false);
		}
	}

}

bool GlvParametersWidget_base::filter_parameters(QString _filter) {

	return filter_parameters(_filter.toStdString(), false, false);

}

bool GlvParametersWidget_base::filter_parameters(std::string _filter, bool _l_exact_match, bool _l_set_visible_only) {

	bool l_all_filtered = true;

	if (layout_type == LayoutType::Vertical) {

		for (int i = 0; i < vertical_layout->count(); i++) {
			GlvDescribedWidget_base* parameter_widget = dynamic_cast<GlvDescribedWidget_base*>(vertical_layout->itemAt(i)->widget());
			if (parameter_widget) {

				GlvParametersWidget_base* parametrization_widget = dynamic_cast<GlvParametersWidget_base*>(parameter_widget->get_data_widget());
				if (parametrization_widget) {
					bool l_all_filtered_rec = parametrization_widget->filter_parameters(_filter, _l_exact_match, _l_set_visible_only);
					if (!l_all_filtered_rec) {
						l_all_filtered = false;
					}
					if (!_l_set_visible_only || !l_all_filtered_rec) {
						parameter_widget->setVisible(!l_all_filtered_rec);
						if (!l_all_filtered_rec && !_filter.empty()) {
							parametrization_widget->setChecked(true);// open the parametrization widget
						}
					}
				} else {
					bool l_found;
					if (!_l_exact_match) {
						l_found = (parameter_widget->get_data_name().find(_filter) != std::string::npos);
						l_found |= (parameter_widget->get_data_alias().find(_filter) != std::string::npos);
					} else {
						l_found = (parameter_widget->get_data_name() == _filter);
						l_found |= (parameter_widget->get_data_alias() == _filter);
					}
					if (!_l_set_visible_only || l_found) {
						parameter_widget->setVisible(l_found);
					}
					if (l_found) l_all_filtered = false;
				}
				
			}
		}

	} else if (layout_type == LayoutType::Grid) {

		for (int i = 0; i < grid_layout->rowCount(); i++) {
			QLabel* parameter_label = dynamic_cast<QLabel*>(grid_layout->itemAtPosition(i, 0)->widget());
			if (parameter_label) {
				GlvWidget_base* widget_base = dynamic_cast<GlvWidget_base*>(grid_layout->itemAtPosition(i, 1)->widget());
				GlvParametersWidget_base* parametrization_widget = dynamic_cast<GlvParametersWidget_base*>(widget_base->get_data_widget());
				if (parametrization_widget) {

					bool l_all_filtered_rec = parametrization_widget->filter_parameters(_filter, _l_exact_match, _l_set_visible_only);
					if (!l_all_filtered_rec) {
						l_all_filtered = false;
					}
					if (!_l_set_visible_only || !l_all_filtered_rec) {
						parameter_label->setVisible(!l_all_filtered_rec);
						parametrization_widget->setVisible(!l_all_filtered_rec);
						if (!l_all_filtered_rec && !_filter.empty()) {
							parametrization_widget->setChecked(true);// open the parametrization widget
						}
						if (grid_layout->columnCount() == 3) {// if optional widget
							QLayoutItem* layout_item = grid_layout->itemAtPosition(i, 2);
							if (layout_item) layout_item->widget()->setVisible(!l_all_filtered_rec);
						}
					}
					
				} else {
					std::string name = parameter_label->text().toStdString();
					std::string alias = parameter_label->toolTip().toStdString();
					bool l_found;
					if (!_l_exact_match) {
						l_found = (name.find(_filter) != std::string::npos);
						l_found |= (alias.find(_filter) != std::string::npos);
					} else {
						l_found = (name == _filter);
						l_found |= (alias == _filter);
					}
					if (!_l_set_visible_only || l_found) {
						parameter_label->setVisible(l_found);
						for (int j = 1; j < grid_layout->columnCount(); j++) {
							QLayoutItem* layout_item = grid_layout->itemAtPosition(i, j);
							if (layout_item) layout_item->widget()->setVisible(l_found);
						}
					}
					if (l_found) l_all_filtered = false;
				}

			}
		}

	}

	return l_all_filtered;
}

bool GlvParametersWidget_base::has_height_decreased() const {

	return l_height_decreased;

}

bool GlvParametersWidget_base::eventFilter(QObject* object, QEvent* _event) {

	if (object == parameters_widget && _event->type() == QEvent::Resize) {

		QResizeEvent* resize_event = dynamic_cast<QResizeEvent*>(_event);
		if (resize_event->size().height() < resize_event->oldSize().height()) {
			l_height_decreased = true;
			emit heightChanged();
		} else if (resize_event->size().height() > resize_event->oldSize().height()) {
			l_height_decreased = false;
			emit heightChanged();
		} else if (l_adapt_max_height) {
			l_height_decreased = false;
		}

	}
	return false;

}
