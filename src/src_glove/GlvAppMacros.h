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

/*! Optional: Forces use of glove (ie: -glove is set by default).*/
#define GLOVE_APP_AUTO false

/*! Optional: Disable program execution in a separate thread. Progressions and status display can not be managed in this mode, only input parametrization can.
* Can be convenient if one wants to execute the program in the closest conditions as the initial program is.
* The program being 'gloved' remains fully compliant with thread mode deactivated.
* Default is : true.
* To be set just before calling GLOVE_APP.*/
#define GLOVE_APP_THREAD_MODE true

/*! Optional: Set application in recurrent mode. The program will be launched again upon acceptance.
* Applies only if GLOVE_APP_THREAD_MODE is set to true.*/
#define GLOVE_APP_RECURRENT_MODE false
#define GLOVE_APP_RECURRENT_TYPE_DEFAULT int
/*! Must be castable to bool. The returned boolean value accounts for the auto repeat mode to be enabled or not.*/
#define GLOVE_APP_RECURRENT_TYPE GLOVE_APP_RECURRENT_TYPE_DEFAULT
/*! Used only if GLOVE_APP_RECURRENT_MODE is left to false.*/
static GLOVE_APP_RECURRENT_TYPE glove_recurrent_var = 0;
/*! To set a title to the application. Must be defined in main, before calling the GLOVE_APP macro.*/
#define GLOVE_APP_TITLE(title) GlvApp::set_title(title);
/*! To set the application as a main window with a menu bar.*/
#define GLOVE_APP_MENU true
/*! To add an helper (result of -h or --help) to the application.*/
#define GLOVE_APP_MENU_HELP(enable) GlvApp::set_helper(enable);
/*! To set an 'About' text to the application. Must be defined in main, before calling the GLOVE_APP macro. Used only if GLOVE_APP_MENU is true*/
#define GLOVE_APP_MENU_ABOUT(about) GlvApp::set_about(about);
/*! Add the license of a component (ex: a library). Rich text is managed: compatible with hyperlinks. The licensed components will be referenced in 'About'.*/
#define GLOVE_APP_MENU_LICENSE_ADD(component_name, license_name, component_text, component_url) GlvApp::add_component_license(component_name, license_name, component_text, component_url);

#define glvm_pv_GLOVE_APP(Tparametrization, _l_auto_glove) \
return GlvApp::main<Tparametrization>(argc, argv, _l_auto_glove, GLOVE_APP_MENU, GLOVE_APP_THREAD_MODE, GLOVE_APP_RECURRENT_MODE, glove_recurrent_var);\
}\
template <>\
int glv_cli_main(int argc, char* argv[], bool is_glove, const Tparametrization& glove_parametrization, bool is_glove_recurrent, GLOVE_APP_RECURRENT_TYPE& glove_recurrent_var) {

#define GLOVE_APP_MSVC_NO_CONSOLE \
comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
