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

#pragma once

#include <QObject>

#ifdef GLOVE_APP_SHARED
#if defined(OS_WIN)
#ifdef GLOVE_APP_SHARED_EXPORT
#define GLOVE_APP_SHARED_API_QT Q_DECL_IMPORT
#else
#define GLOVE_APP_SHARED_API_QT Q_DECL_EXPORT
#endif
#else
#define GLOVE_APP_SHARED_API_QT
#endif
#else
#define GLOVE_APP_SHARED_API_QT
#endif

class QMenuBar;
class QMenu;
class QLabel;
class QScrollArea;
class GlvWidgetSaveLoad_base;
class GlvParametrizationDialog_base;

class GLOVE_APP_SHARED_API_QT GlvAppObject : public QObject {
	Q_OBJECT
private:

	QMenuBar* menu_bar;
	QMenu* menu_help;

	QWidget* app_widget = NULL;
	QLabel* helper_label;
	QWidget* helper_widget;
	QScrollArea* helper_scroll_area;

	QLabel* about_label;
	QWidget* about_widget;

public:
	GlvAppObject();
	~GlvAppObject();

	/*! Set the parametrization dialog widget, along with its save/load widget. Also manage recurrent memory depending on Trecurrent.*/
	template <class Trecurrent>
	void set_widget(GlvParametrizationDialog_base* _dialog, GlvWidgetSaveLoad_base* _save_load_widget);
	/*! Set helper text.*/
	void set_helper(const std::string& _helper);
	/*! Set about text.*/
	void set_about(const std::string& _about);

private:
	/*! Set the parametrization dialog widget, along with its save/load widget.*/
	void set_widget_general(GlvParametrizationDialog_base* _dialog, GlvWidgetSaveLoad_base* _save_load_widget);
	/*! Set memory/recurrent menu.*/
	void set_menu_memory();

public slots:
	void show_help();
	void show_about();
	/*! Clear cached parametrization file.*/
	void clear_cached();
	/*! Clear recurrent memory.*/
	void clear_recurrent();
};

#include "GlvAppMacros.h"

template <class Trecurrent>
void GlvAppObject::set_widget(GlvParametrizationDialog_base* _dialog, GlvWidgetSaveLoad_base* _save_load_widget) {

	set_widget_general(_dialog, _save_load_widget);

	if (!std::is_same<Trecurrent, GLOVE_APP_RECURRENT_TYPE_DEFAULT>::value) {
		set_menu_memory();
	}
}
