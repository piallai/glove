/*
* This file is part of the Glove distribution (https://github.com/piallai/glove).
* Copyright (C) 2024 - 2026 Pierre Allain.
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

#include "GlvAppObject.h"

#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QPushButton>
#include "GlvWidgetSaveLoad_base.h"
#include "filestream/SlvFile.h"
#include "GlvApp.h"

GlvAppObject::GlvAppObject() {

	helper_label = new QLabel;
	helper_label->setTextInteractionFlags(Qt::TextSelectableByMouse);

	helper_scroll_area = new QScrollArea;
	helper_scroll_area->setWidget(helper_label);
	helper_scroll_area->setWidgetResizable(true);

	helper_widget = new QWidget;
	helper_widget->setWindowTitle("Help");
	QVBoxLayout* helper_layout = new QVBoxLayout;
	helper_widget->setLayout(helper_layout);
	helper_widget->setWindowModality(Qt::WindowModal);
	helper_widget->setMinimumWidth(300);
	helper_widget->setMinimumHeight(200);

	helper_layout->addWidget(helper_scroll_area);

	about_label = new QLabel;
	about_label->setTextInteractionFlags(Qt::TextSelectableByMouse);
	//about_label->setAlignment(Qt::AlignCenter);
	about_label->setTextFormat(Qt::RichText);
	about_label->setTextInteractionFlags(Qt::TextBrowserInteraction);
	about_label->setOpenExternalLinks(true);
	about_label->setMinimumWidth(300);
	about_label->setMinimumHeight(200);
	about_widget = new QWidget;
	about_widget->setWindowTitle("About");
	QVBoxLayout* about_layout = new QVBoxLayout;
	about_widget->setLayout(about_layout);
	about_widget->setWindowModality(Qt::WindowModal);
	about_layout->setSizeConstraint(QLayout::SetFixedSize);
	about_layout->addWidget(about_label);

}

GlvAppObject::~GlvAppObject() {

}

void GlvAppObject::set_widget_general(GlvParametrizationDialog_base* _dialog, GlvWidgetSaveLoad_base* _save_load_widget) {

	menu_bar = new QMenuBar;
	_dialog->layout()->setMenuBar(menu_bar);

	QMenu* menu_file = menu_bar->addMenu("File");
	menu_file->setToolTipsVisible(true);

	QAction* load_action = new QAction("Open");
	load_action->setToolTip(tr("Open a parametrization"));
	load_action->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
	menu_file->addAction(load_action);
	QObject::connect(load_action, SIGNAL(triggered(bool)), _save_load_widget, SLOT(load()));
	QAction* save_action = new QAction("Save");
	save_action->setToolTip(tr("Save the parametrization"));
	save_action->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
	menu_file->addAction(save_action);
	QObject::connect(save_action, SIGNAL(triggered(bool)), _save_load_widget, SLOT(save()));

	QAction* clear_action = new QAction("Clear");
	clear_action->setToolTip(tr("Clear the cached parametrization file located at execution directory"));
	menu_file->addAction(clear_action);
	QObject::connect(clear_action, SIGNAL(triggered(bool)), this, SLOT(clear_cached()));

	_save_load_widget->setVisible(false);

	if (!helper_label->text().isEmpty() || !about_label->text().isEmpty()) {
		menu_help = menu_bar->addMenu("Help");
		menu_help->setToolTipsVisible(true);
		if (!helper_label->text().isEmpty()) {
			QAction* help_action = new QAction("Help");
			help_action->setToolTip(tr("-h or --help"));
			menu_help->addAction(help_action);
			QObject::connect(help_action, SIGNAL(triggered(bool)), this, SLOT(show_help()));
		}

		if (!about_label->text().isEmpty()) {
			QAction* about_action = new QAction("About");
			menu_help->addAction(about_action);
			QObject::connect(about_action, SIGNAL(triggered(bool)), this, SLOT(show_about()));
		}
	}

	_dialog->get_cancel_button()->setVisible(false);

	app_widget = _dialog;

}

void GlvAppObject::set_menu_memory() {

	QMenu* menu_memory = new QMenu("Memory");
	menu_bar->insertMenu(menu_help->menuAction(), menu_memory);
	menu_memory->setToolTipsVisible(true);
	QAction* clear_recurrent = new QAction("Clear shared");
	clear_recurrent->setToolTip(tr("Clear memory shared across runs"));
	menu_memory->addAction(clear_recurrent);
	QObject::connect(clear_recurrent, SIGNAL(triggered(bool)), this, SLOT(clear_recurrent()));

}

void GlvAppObject::set_helper(const std::string& _helper) {

	helper_label->setText(QString::fromStdString(_helper));

}

void GlvAppObject::set_about(const std::string& _about) {

	const std::string rich_ret = "<br>";
	const std::string rich_tab = "&nbsp;&nbsp;&nbsp;&nbsp;";

	std::string about = _about;
	if (!GlvApp::component_licenses().empty()) {
		about += rich_ret + "____________________________";
		about += rich_ret + rich_ret + "License notices:";
	}
	for (auto lic = GlvApp::component_licenses().begin(); lic != GlvApp::component_licenses().end(); ++lic) {
		about += rich_ret + rich_ret + rich_tab + "<b>" + lic->component_name + "</b>" + rich_tab + lic->license;
		about += rich_ret + rich_tab + rich_tab + "<i>" + lic->component_text + (lic->component_text.empty() ? "" : rich_tab);
		about += "<a href=\"" + lic->component_url + "\">" + lic->component_url + "</a>" + "</i>";
	}
	about_label->setText(QString::fromStdString(about));

}

void GlvAppObject::show_help() {

	helper_widget->show();

}

void GlvAppObject::show_about() {

	about_widget->show();

}

void GlvAppObject::clear_cached() {

	bool l_cleared = false;

	SlvFile file(GlvApp::autosave_file_name());
	if (file.exists()) {
		int result = std::remove(GlvApp::autosave_file_name().c_str());
		if (!result) {
			l_cleared = true;
		}
	}

	if (l_cleared) {
		glv::flag::INFO("Succesfully removed " + file.get_path());
	} else {
		glv::flag::INFO("No parametrization file to clear");
	}

}

void GlvAppObject::clear_recurrent() {

	SlvStatus status = GlvApp::recurrent_clearer()->clear();
	glv::flag::showQMessageBox(tr("Problem clearing the memory"), status, true);

}