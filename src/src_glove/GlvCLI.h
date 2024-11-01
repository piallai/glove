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

/*! Use a parameter named \p parameter_name of the CLI parametrization as a location where to save the configuration file.
* If such a parameter does not exist, return empty string.*/
#define GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY(Tparametrization, parameter_name)\
template <>\
struct GlvApp::ParamOutput<Tparametrization> {\
		static std::string get_path(const Tparametrization& _parametrization) {\
			const SlvParameter_base* parameter = _parametrization.find_first(parameter_name, false);\
			if (parameter) {\
				return parameter->get_stream_value();\
			} else {\
				return std::string();\
			}\
	}\
};


/*! Use a parameter of the CLI parametrization as a location where to save the configuration file.
* The parameter is defined by its declaration name.
* The parameter can be nested into other parameters. Can accept parameter nested up to 3 levels (ie: 4 parameter declarations specification).*/
#define GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL(Tparametrization, ...) EXPAND( glvm_pv_get_GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL(__VA_ARGS__, glvm_pv_GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL4, glvm_pv_GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL3, glvm_pv_GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL2, glvm_pv_GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL1)(Tparametrization, __VA_ARGS__))
#define EXPAND(arg) arg
#define glvm_pv_get_GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL(_1, _2, _3, _4, macro_arg, ...) macro_arg
#define glvm_pv_GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL1(Tparametrization, parameter_name)\
template <>\
struct GlvApp::ParamOutput<Tparametrization> {\
		static std::string get_path(const Tparametrization& _parametrization) {\
			std::ostringstream stream;\
			stream << _parametrization.get_##parameter_name();\
			return stream.str();\
	}\
};

#define glvm_pv_GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL2(Tparametrization, parameter_name1, parameter_name2)\
template <>\
struct GlvApp::ParamOutput<Tparametrization> {\
		static std::string get_path(const Tparametrization& _parametrization) {\
			std::ostringstream stream;\
			stream << _parametrization.get_##parameter_name1().get_##parameter_name2();\
			return stream.str();\
	}\
};

#define glvm_pv_GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL3(Tparametrization, parameter_name1, parameter_name2, parameter_name3)\
template <>\
struct GlvApp::ParamOutput<Tparametrization> {\
		static std::string get_path(const Tparametrization& _parametrization) {\
			std::ostringstream stream;\
			stream << _parametrization.get_##parameter_name1().get_##parameter_name2().get_##parameter_name3();\
			return stream.str();\
	}\
};

#define glvm_pv_GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL4(Tparametrization, parameter_name1, parameter_name2, parameter_name3, parameter_name4)\
template <>\
struct GlvApp::ParamOutput<Tparametrization> {\
		static std::string get_path(const Tparametrization& _parametrization) {\
			std::ostringstream stream;\
			stream << _parametrization.get_##parameter_name1().get_##parameter_name2().get_##parameter_name3().get_##parameter_name4();\
			return stream.str();\
	}\
};

/* ------------------------------
*  GLOVE_APP macro
*  ------------------------------
Transform a program into a GUI application. To be used at the very beginning of the main.
- GLOVE_APP : by setting -glove as CLI argument
- GLOVE_APP_AUTO : no need to set -glove => turn program into GUI as default
- GLOVE_APP_PARAM(Tparametrization) : same as GLOVE_APP, adds CLI arguments by-pass through a parametrization widget defined by Tparametrization.
- GLOVE_APP_PARAM_AUTO(Tparametrization) : same as GLOVE_APP_AUTO, adds CLI arguments by-pass through a parametrization widget defined by Tparametrization.
*/

/*! Transform a program into a GUI application by setting -glove as CLI argument. To be used at the very beginning of the main.
* Provide two additional variables:
* - bool is_glove : whether -glove cli argument was used or not.
* - Tparametrization glove_parametrization : the parametrization configured in the gui. If is_glove is false, then this parametrization is the default one.*/
#define GLOVE_APP_PARAM(Tparametrization) \
glvm_pv_GLOVE_APP(Tparametrization, false)

#define GLOVE_APP \
glvm_pv_GLOVE_APP(GLOVE_APP_default_parametrization, false)

/*! Same as GLOVE_APP macro, but forces use of glove (ie: -glove is set by default).
* Transform a program into a GUI application. To be used at the very beginning of the main.
* Provide two additional variables:
* - bool is_glove : whether -glove cli argument was used or not.
* - Tparametrization glove_parametrization : the parametrization configured in the gui. If is_glove is false, then this parametrization is the default one.*/
#define GLOVE_APP_PARAM_AUTO(Tparametrization) \
glvm_pv_GLOVE_APP(Tparametrization, true)

#define GLOVE_APP_AUTO \
glvm_pv_GLOVE_APP(GLOVE_APP_default_parametrization, true)

#include "param/SlvParametrizationMacro.h"
glvm_parametrization(GLOVE_APP_default_parametrization, "default");

/*! Optional: Disable program execution in a separate thread. Progressions and status display can not be managed in this mode, only input parametrization can.
* Can be convenient if one wants to execute the program in the closest conditions as the initial program is.
* The program being 'gloved' remains fully compliant with thread mode deactivated.
* Default is : true.
* To be set just before calling GLOVE_APP.*/
#define GLOVE_APP_THREAD_MODE true

#define glvm_pv_GLOVE_APP(Tparametrization, _l_auto_glove) \
return GlvApp::main<Tparametrization>(argc, argv, _l_auto_glove, GLOVE_APP_THREAD_MODE);\
}\
template <>\
int glv_cli_main(int argc, char* argv[], bool is_glove, const Tparametrization& glove_parametrization) {

template <class Tparametrization>
int glv_cli_main(int argc, char* argv[], bool _l_gloved, const Tparametrization& _parametrization);//forward declare for gcc

#define GLOVE_APP_MSVC_NO_CONSOLE \
comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

class GlvProgressMgr;
class GlvStatusMgr;
#include "SlvPoolFactory.h"
class SlvProgressionQt;
#include "slv_lbl.h"
#include "SlvMacros.h"
#include "SlvMacrosDeclarations.h"
#include "SlvStatus.h"

class GlvApp {
	
public:

	template <class Tparametrization>
	static int main(int _argc, char* _argv[], bool _l_auto_glove = false, bool _l_threaded = true);

private:

	/*! Class to specialize to provide output path for parameters file.*/
	template <class Tparametrization>
	struct ParamOutput {
		static std::string get_path(const Tparametrization& _parametrization) {
			return "";
		}
	};

	/*! Progressions managed by GLOVE_APP_CLI.*/
	glvm_staticVariable_def(, SlvPoolFactory<SlvProgressionQt COMMA slv::lbl::Name>, progressions);
	glvm_staticVariable(, SlvStatus, status, {});
	glvm_staticVariable(, GlvStatusMgr*, status_mgr, NULL);


public :

	static SlvProgressionQt* get_progression(const slv::lbl::Name& _name);
	/*! Show a status widget as a QMesssageBox. Does nothing if GLOVE_APP is not used.
	* \p _l_wait : if ture, the program will not continue until 'Ok' is clicked.
	* Caution, in case \p _l_wait is false, showing many QMessageBoxes (~40) altogether can produce an overflow.*/
	static void show(const SlvStatus& _status, bool _l_wait = true);

};

#include <QApplication>
#include "SlvCLI.h"
#include "GlvParametrizationDialog.h"
#include "GlvParametrizationSaveLoad.h"
#include "SlvProgressionQt.h"
#include <QMessageBox>
#include "GlvProgressMgr.h"
#include <QtConcurrent/QtConcurrentRun>
#include <QFutureWatcher>
#include "GlvStatusMgr.h"

template <class Tparametrization>
int GlvApp::main(int _argc, char* _argv[], bool _l_auto_glove, bool _l_threaded) {

	if (SlvCLI::has_glove(_argc, _argv) || _l_auto_glove) {

		QApplication q_app(_argc, _argv);

		std::string autosave_file_name = SlvFileMgr::replace_forbidden_file_characters(Tparametrization::name(), '_', true, true);
#if OPTION_USE_THIRDPARTY_JSON==1
		autosave_file_name += ".json";
#endif

		GlvParametrizationDialog<Tparametrization> dialog;
		GlvParametrizationSaveLoad<Tparametrization>* save_load_widget = new GlvParametrizationSaveLoad<Tparametrization>(dialog.get_parametrization_widget());

		SlvCLI::Arguments arguments(_argc, _argv);

		if (!arguments.get_glove_argument().empty()) {

			save_load_widget->load(arguments.get_glove_argument());

		}

		Tparametrization parametrization = dialog.get_parametrization_widget()->get_parametrization();
		SlvStatus status;

		if (!arguments.is_empty()) {

			status = SlvCLI::parse(parametrization, arguments);

			glv::flag::showQMessageBox(QObject::tr("Arguments conflict"), status, true);

			dialog.set_parametrization(parametrization);

		} else if (SlvFile(autosave_file_name).exists() && arguments.get_glove_argument().empty()) {

			save_load_widget->load(autosave_file_name);

		}

		int result;
		if (Tparametrization::Nparameters() > 0) {
			result = dialog.exec();
		} else {
			result = QDialog::Accepted;
		}

		if (result == QDialog::Accepted) {

			save_load_widget->save(autosave_file_name);
			
			SlvDirectory directory(ParamOutput<Tparametrization>::get_path(dialog.get_parametrization()));
			if (directory.exists()) {
				save_load_widget->save(SlvFile(directory, autosave_file_name).get_path());
			}

			std::vector< std::pair<std::string, std::string> > parameter_arguments = dialog.get_parametrization().get_string_serialization_bool().first;
			for (SlvCLI::Arguments::Tparameters::const_iterator it = arguments.get_parameter_arguments().begin(); it != arguments.get_parameter_arguments().end(); ++it) {
				parameter_arguments.push_back({ it->first, it->second[0] });
			}

			std::vector<std::string> solo_arguments = dialog.get_parametrization().get_string_serialization_bool().second;
			slv::vector::add(solo_arguments, arguments.get_solo_arguments());


			std::pair<int, char**> cli_arguments = SlvCLI::get_arguments(parameter_arguments, solo_arguments);
			cli_arguments.second[0] = _argv[0];

#ifdef GLOVE_DEBUG
			if (!_l_threaded && !GlvApp::progressions().empty()) {

				glv::flag::showQMessageBox(QObject::tr("Thread issue"), SlvStatus(SlvStatus::statusType::critical, "Can not manage progressions if thread mode is not active."), true);
				return 0;

			} else {
#endif

				if (_l_threaded) {

					status_mgr() = new GlvStatusMgr;
					status_mgr()->add(&GlvApp::status());

					GlvProgressMgr progress_mgr;
					for (int i = 0; i < progressions().psize(); i++) {
						bool l_hide_when_over = !progressions()[i]->is_recurrent();
						progress_mgr.add_progression(progressions()[i], l_hide_when_over);
					}
					progress_mgr.show();

					QFuture<int> future = QtConcurrent::run(&glv_cli_main<Tparametrization>, cli_arguments.first, cli_arguments.second, true, dialog.get_parametrization());
					QFutureWatcher<int> future_watcher;
					QObject::connect(&future_watcher, SIGNAL(finished()), &q_app, SLOT(closeAllWindows()));
					future_watcher.setFuture(future);

					return q_app.exec();
				} else {
					status_mgr() = NULL;
					return glv_cli_main(cli_arguments.first, cli_arguments.second, true, dialog.get_parametrization());
				}

#ifdef GLOVE_DEBUG
			}
#endif

		} else {
			return 0;
		}

	} else {
		return glv_cli_main(_argc, _argv, false, Tparametrization());
	}

}
