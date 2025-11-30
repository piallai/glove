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
* Provide four additional variables:
* - bool is_glove : whether -glove cli argument was used or not.
* - Tparametrization glove_parametrization : the parametrization configured in the gui. If is_glove is false, then this parametrization is the default one.
* - bool is_glove_recurrent : whether glove app is being relaunched recurrently or not.
* - GLOVE_APP_RECURRENT_TYPE glove_recurrent_var : variable kept along all recurrent runs.*/
#define GLOVE_APP_PARAM(Tparametrization) \
glvm_pv_GLOVE_APP(Tparametrization, GLOVE_APP_AUTO)

/*! Same as GLOVE_APP_PARAM, but with no input parametrization.*/
#define GLOVE_APP \
glvm_pv_GLOVE_APP(GLOVE_APP_default_parametrization, GLOVE_APP_AUTO)

#include "param/SlvParametrizationMacro.h"
glvm_parametrization(GLOVE_APP_default_parametrization, "default");

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
/*! Must be castable to bool. The returned boolean value accounts for the auto repeat mode to be enabled or not.*/
#define GLOVE_APP_RECURRENT_TYPE int
/*! Used only if GLOVE_APP_RECURRENT_MODE is left to false.*/
static GLOVE_APP_RECURRENT_TYPE glove_recurrent_var = 0;


#define glvm_pv_GLOVE_APP(Tparametrization, _l_auto_glove) \
return GlvApp::main<Tparametrization>(argc, argv, _l_auto_glove, GLOVE_APP_THREAD_MODE, GLOVE_APP_RECURRENT_MODE, glove_recurrent_var);\
}\
template <>\
int glv_cli_main(int argc, char* argv[], bool is_glove, const Tparametrization& glove_parametrization, bool is_glove_recurrent, GLOVE_APP_RECURRENT_TYPE& glove_recurrent_var) {

template <class Tparametrization, class Trecurrent>
int glv_cli_main(int argc, char* argv[], bool _l_gloved, const Tparametrization& _parametrization, bool _l_recurrent, Trecurrent & _recurrent_var);//forward declare for gcc

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
#include "SlvMacros.h"

#ifdef GLOVE_APP_SHARED
#if defined(OS_WIN)
#ifdef GLOVE_APP_SHARED_EXPORT
#define GLOVE_APP_SHARED_API __declspec(dllexport)
#else
#define GLOVE_APP_SHARED_API __declspec(dllimport)
#endif
#else
#define GLOVE_APP_SHARED_API
#endif
#else
#define GLOVE_APP_SHARED_API
#endif

#include <QFutureWatcher>

class GLOVE_APP_SHARED_API GlvApp {
	
private :

	class RecurrentWrapper;
	template <class Tparametrization, class Trecurrent>
	class RecurrentWrapperT;

	struct Interface {
		QFuture<int> future;
		QFutureWatcher<int> future_watcher;
		RecurrentWrapper* recurrent_wrapper = NULL;
	};

public:

	template <class Tparametrization, class Trecurrent>
	static int main(int _argc, char* _argv[], bool _l_auto_glove, bool _l_threaded, bool _l_recurrent, Trecurrent& _recurrent);
	template <class Tparametrization, class Trecurrent>
	static int main_recurrent(int _argc, char* _argv[], bool _l_threaded, Interface& _interface, bool _l_recurrent, Trecurrent& _recurrent);

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
	glvm_staticVariable(, GlvProgressMgr*, progress_mgr, NULL);
	glvm_staticVariable(, GlvStatusMgr*, status_mgr, NULL);
	glvm_staticVariable(, Interface, interface, );

public :

	static SlvProgressionQt* get_progression(const slv::lbl::Name& _name);
	/*! Show a status widget as a QMesssageBox. Does nothing if GLOVE_APP is not used.
	* \p _l_wait : if true, the program will not continue until 'Ok' is clicked.
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

class GlvApp::RecurrentWrapper : public QObject {

	Q_OBJECT

protected:

	RecurrentWrapper() {}
	~RecurrentWrapper() {}

public slots:
	virtual void relaunch() = 0;

};

template <class Tparametrization, class Trecurrent>
class GlvApp::RecurrentWrapperT : public GlvApp::RecurrentWrapper {

private:

	int argc;
	char** argv;
	Trecurrent* recurrent_var;
	Interface* interface = NULL;

public:

	RecurrentWrapperT() {}

	void set(int _argc, char** _argv, Trecurrent* _recurrent_var) {
		argc = _argc;
		argv = _argv;
		recurrent_var = _recurrent_var;
	}

	void set_interface(Interface* _interface) {
		interface = _interface;
	}

	void relaunch() {
		bool l_threaded = true;
		bool l_recurrent = true;
		GlvApp::main_recurrent<Tparametrization, Trecurrent>(argc, argv, l_threaded, *interface, l_recurrent, *recurrent_var);
	}

};

template <class Tparametrization, class Trecurrent>
int GlvApp::main_recurrent(int _argc, char* _argv[], bool _l_threaded, Interface& _interface, bool _l_recurrent, Trecurrent& _recurrent_var) {

	std::string autosave_file_name = SlvFileMgr::replace_forbidden_file_characters(Tparametrization::name(), '_', true, true);
#if OPTION_USE_THIRDPARTY_JSON==1
	autosave_file_name += ".json";
#endif

	if (progress_mgr()) {
		progress_mgr()->hide();
	}

	GlvParametrizationDialog<Tparametrization> dialog;
	dialog.get_parametrization_widget()->set_options_enabled(true);
	GlvParametrizationSaveLoad<Tparametrization>* save_load_widget = new GlvParametrizationSaveLoad<Tparametrization>(dialog.get_parametrization_widget());

	SlvCLI::Arguments arguments(_argc, _argv);

	if (!arguments.get_glove_argument().empty()) {

		save_load_widget->load(arguments.get_glove_argument());// Load parametrization file

	} else if (SlvFile(autosave_file_name).exists()) {

		save_load_widget->load(autosave_file_name);

	}

	if (!arguments.is_empty()) {

		Tparametrization parametrization = dialog.get_parametrization_widget()->get_parametrization();
		SlvStatus status;

		status = SlvCLI::parse(parametrization, arguments);

		glv::flag::showQMessageBox(QObject::tr("Arguments conflict"), status, true);

		dialog.set_parametrization(parametrization);

	}

	int result;
	if (Tparametrization::Nparameters() > 0 && !(bool)_recurrent_var) {
		result = dialog.exec();
	} else {
		result = QDialog::Accepted;
	}

	if (result == QDialog::Accepted) {

		save_load_widget->save(autosave_file_name);

		SlvDirectory directory(ParamOutput<Tparametrization>::get_path(dialog.get_parametrization()));
		if (directory.exists() && !directory.is_current()) {// do not save again if the directory is current
			save_load_widget->save(SlvFile(directory, autosave_file_name).get_path());
		}

		std::vector< std::pair<std::string, std::string> > parameter_arguments = dialog.get_parametrization().get_string_serialization_bool().first;
		for (SlvCLI::Arguments::Tparameters::const_iterator it = arguments.get_parameter_arguments().begin(); it != arguments.get_parameter_arguments().end(); ++it) {
			parameter_arguments.push_back({ it->first, it->second[0] });
		}

		std::vector< std::pair<std::string, bool> > solo_arguments = dialog.get_parametrization().get_string_serialization_bool().second;
		std::vector<std::string> solo_arguments_active;
		for (auto it = solo_arguments.begin(); it != solo_arguments.end(); ++it) {
			if (it->second) {
				solo_arguments_active.push_back(it->first);
			}
		}
		slv::vector::add(solo_arguments_active, arguments.get_solo_arguments());


		std::pair<int, char**> cli_arguments = SlvCLI::get_arguments(parameter_arguments, solo_arguments_active);
		cli_arguments.second[0] = _argv[0];

		if (_l_threaded) {

			if (_l_recurrent) {
				dynamic_cast<RecurrentWrapperT<Tparametrization, Trecurrent>*>(_interface.recurrent_wrapper)->set(cli_arguments.first, cli_arguments.second, &_recurrent_var);
			}

#if QT_VERSION_MAJOR < 6
			_interface.future = QtConcurrent::run(std::bind(&glv_cli_main<Tparametrization, Trecurrent>, cli_arguments.first, cli_arguments.second, true, dialog.get_parametrization(), _l_recurrent, std::ref(_recurrent_var)));
#else
			_interface.future = QtConcurrent::run(&glv_cli_main<Tparametrization, Trecurrent>, cli_arguments.first, cli_arguments.second, true, dialog.get_parametrization(), _l_recurrent, std::ref(_recurrent_var));
#endif
			_interface.future_watcher.setFuture(_interface.future);

			if (progress_mgr()) {
				progress_mgr()->show();
			}

			return 0;

		} else {
			status_mgr() = NULL;
			return glv_cli_main(cli_arguments.first, cli_arguments.second, true, dialog.get_parametrization(), _l_recurrent, _recurrent_var);
		}

	} else {
		QCoreApplication::quit();
		return 1;
	}


}

#if OPTION_USE_THIRDPARTY_JSON==1
#include "json.hpp"
#endif

template <class Tparametrization, class Trecurrent>
int GlvApp::main(int _argc, char* _argv[], bool _l_auto_glove, bool _l_threaded, bool _l_recurrent, Trecurrent& _recurrent_var) {

	if (SlvCLI::has_glove(_argc, _argv) || _l_auto_glove) {

		QApplication q_app(_argc, _argv);
		if (_l_recurrent) {
			q_app.setQuitOnLastWindowClosed(false);
		}

		if (_l_threaded) {

			status_mgr() = new GlvStatusMgr;
			status_mgr()->add(&GlvApp::status());

			if (!progressions().empty()) {
				progress_mgr() = new GlvProgressMgr;
				for (int i = 0; i < progressions().psize(); i++) {
					bool l_hide_when_over = !progressions()[i]->is_recurrent();
					progress_mgr()->add_progression(progressions()[i], l_hide_when_over);
				}
			}

			if (!_l_recurrent) {
				QObject::connect(&interface().future_watcher, &QFutureWatcher<int>::finished, &q_app, &QCoreApplication::quit, Qt::QueuedConnection);
			} else {
				RecurrentWrapperT<Tparametrization, Trecurrent>* recurrent_wrapper = new RecurrentWrapperT<Tparametrization, Trecurrent>;
				recurrent_wrapper->set_interface(&interface());
				interface().recurrent_wrapper = recurrent_wrapper;
				QObject::connect(&interface().future_watcher, SIGNAL(finished()), interface().recurrent_wrapper, SLOT(relaunch()));
			}

		}

		int exit = main_recurrent<Tparametrization>(_argc, _argv, _l_threaded, interface(), _l_recurrent, _recurrent_var);

		if (!exit && _l_threaded) {

			return q_app.exec();

		} else {

			return exit;
		}

	} else {

		Tparametrization parametrization;

#if OPTION_USE_THIRDPARTY_JSON==1
		if (SlvCLI::find_json_file(_argc, _argv) >= 0) {

			std::ifstream file_stream_input;
			std::string file_name = _argv[SlvCLI::find_json_file(_argc, _argv)];

			SlvStatus status = SlvFileMgr::open_file(file_stream_input, file_name);

			if (status) {

				nlohmann::json json_value;
				file_stream_input >> json_value;
				if (!json_value.empty()) {
					parametrization.readJson(json_value);
				}

			}

		}
#endif

		SlvCLI::Arguments arguments(_argc, _argv);

		if (!arguments.is_empty()) {

			SlvStatus status = SlvCLI::parse(parametrization, arguments);
			if (!status) {
				std::cout << status << std::endl;
			}

		}

		return glv_cli_main(_argc, _argv, false, parametrization, false, _recurrent_var);

	}

}
