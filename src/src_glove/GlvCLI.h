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

#include "SlvCLI.h"

/*! Use a parameter named \p parameter_name of the CLI parametrization as a location where to save the configuration file.
* If such a parameter does not exist, return empty string.*/
#define GLOVE_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY(Tparametrization, parameter_name)\
template <>\
struct GlvCLI::ParamOutput<Tparametrization> {\
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
#define GLOVE_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL(Tparametrization, ...) EXPAND( glvm_pv_get_GLOVE_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL(__VA_ARGS__, glvm_pv_GLOVE_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL4, glvm_pv_GLOVE_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL3, glvm_pv_GLOVE_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL2, glvm_pv_GLOVE_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL1)(Tparametrization, __VA_ARGS__))
#define EXPAND(arg) arg
#define glvm_pv_get_GLOVE_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL(_1, _2, _3, _4, macro_arg, ...) macro_arg
#define glvm_pv_GLOVE_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL1(Tparametrization, parameter_name)\
template <>\
struct GlvCLI::ParamOutput<Tparametrization> {\
		static std::string get_path(const Tparametrization& _parametrization) {\
			std::ostringstream stream;\
			stream << _parametrization.get_##parameter_name();\
			return stream.str();\
	}\
};

#define glvm_pv_GLOVE_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL2(Tparametrization, parameter_name1, parameter_name2)\
template <>\
struct GlvCLI::ParamOutput<Tparametrization> {\
		static std::string get_path(const Tparametrization& _parametrization) {\
			std::ostringstream stream;\
			stream << _parametrization.get_##parameter_name1().get_##parameter_name2();\
			return stream.str();\
	}\
};

#define glvm_pv_GLOVE_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL3(Tparametrization, parameter_name1, parameter_name2, parameter_name3)\
template <>\
struct GlvCLI::ParamOutput<Tparametrization> {\
		static std::string get_path(const Tparametrization& _parametrization) {\
			std::ostringstream stream;\
			stream << _parametrization.get_##parameter_name1().get_##parameter_name2().get_##parameter_name3();\
			return stream.str();\
	}\
};

#define glvm_pv_GLOVE_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL4(Tparametrization, parameter_name1, parameter_name2, parameter_name3, parameter_name4)\
template <>\
struct GlvCLI::ParamOutput<Tparametrization> {\
		static std::string get_path(const Tparametrization& _parametrization) {\
			std::ostringstream stream;\
			stream << _parametrization.get_##parameter_name1().get_##parameter_name2().get_##parameter_name3().get_##parameter_name4();\
			return stream.str();\
	}\
};

#define GLOVE_CLI(Tparametrization) \
return GlvCLI::main<Tparametrization>(argc, argv);\
}\
int glv_cli_main(int argc, char* argv[]) {

int glv_cli_main(int argc, char* argv[]);//forward declare for gcc

struct GlvCLI {

public:

	template <class Tparametrization>
	static int main(int _argc, char* _argv[]);

private:

	/*! Class to specialize to provide output path for parameters file.*/
	template <class Tparametrization>
	struct ParamOutput {
		static std::string get_path(const Tparametrization& _parametrization) {
			return "";
		}
	};

};

#include <QApplication>
#include "GlvParametrizationDialog.h"
#include "GlvParametrizationSaveLoad.h"
#include <QMessageBox>

template <class Tparametrization>
int GlvCLI::main(int _argc, char* _argv[]) {

	if (SlvCLI::has_glove(_argc, _argv)) {

		QApplication app(_argc, _argv);

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

		int result = dialog.exec();
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

			return glv_cli_main(cli_arguments.first, cli_arguments.second);

		} else {
			return 0;
		}

	} else {
		return glv_cli_main(_argc, _argv);
	}

}
