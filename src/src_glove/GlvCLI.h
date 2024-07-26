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

#include <vector>
#include <map>
#include <string>

#define GLOVE_CLI(Tparametrization) \
return GlvCLI::main<Tparametrization>(argc, argv);\
}\
int glv_cli_main(int argc, char* argv[]) {

int glv_cli_main(int argc, char* argv[]);//forward declare for gcc

struct GlvCLI {

public:
	template <class Tparam>
	static int main(int _argc, char* _argv[]);

private:

	/*! Returns true if \p _argv contains "-glove".*/
	static bool has_glove(int _argc, char* _argv[]);
	struct Arguments {
		Arguments(int _argc, char* _argv[]) { parse(_argc, _argv); }
		/*! Parameter identifier (starting with '-') and corresponding value.*/
		typedef std::map<std::string, std::vector<std::string> > Tparameters;
		Tparameters parameter_arguments;
		/*! Arguments that are not parameters.*/
		std::vector<std::string> solo_arguments;
		/*! Parse arguments.*/
		void parse(int _argc, char* _argv[]);
		/*! Remove all arguments except those which name is in \p _arguments_remaining.*/
		void filter(const std::vector<std::string>& _arguments_remaining);
	};
	/*! Create argc/argv based on provided arguments.*/
	static std::pair<int, char**> get_arguments(const std::vector< std::pair<std::string, std::string> >& _parameter_arguments, const std::vector<std::string>& _solo_arguments);

};

#include <QApplication>
#include "GlvParametrizationDialog.h"
#include "GlvParametrizationSaveLoad.h"
#include <QMessageBox>

template <class Tparam>
int GlvCLI::main(int _argc, char* _argv[]) {

	if (has_glove(_argc, _argv)) {

		QApplication app(_argc, _argv);

		GlvParametrizationDialog<Tparam> dialog;
		GlvParametrizationSaveLoad<Tparam>* save_load_widget = new GlvParametrizationSaveLoad<Tparam>(dialog.get_parametrization_widget());

		Tparam parametrization;
		Arguments arguments(_argc, _argv);

		std::map<std::string, std::string> stream_values;
		for (Arguments::Tparameters::const_iterator it = arguments.parameter_arguments.begin(); it != arguments.parameter_arguments.end(); ++it) {
			stream_values[it->first] =  it->second[0];
		}

		for (std::vector<std::string>::const_iterator it = arguments.solo_arguments.begin(); it != arguments.solo_arguments.end(); ++it) {
			stream_values[*it] = "1";
		}

		std::pair< std::map<std::string, int>, std::vector<std::string> > conflicts_missing = parametrization.set_stream_values(stream_values, false);
		if (!conflicts_missing.first.empty()) {
			QString message(QObject::tr("Multiple parameter correspondences in parametrization."));
			for (std::map<std::string, int>::const_iterator it = conflicts_missing.first.begin(); it != conflicts_missing.first.end(); ++it) {
				message += QString("\n") + it->first.c_str() + " : " + QString::number(it->second) + QObject::tr(" correspondences");
			}
			QMessageBox::warning(&dialog, QObject::tr("Arguments conflict"), message);
		}
		arguments.filter(conflicts_missing.second);

		dialog.set_parametrization(parametrization);

		int result = dialog.exec();
		if (result == QDialog::Accepted) {

			std::vector< std::pair<std::string, std::string> > parameter_arguments = dialog.get_parametrization().get_string_serialization_bool().first;
			for (Arguments::Tparameters::const_iterator it = arguments.parameter_arguments.begin(); it != arguments.parameter_arguments.end(); ++it) {
				parameter_arguments.push_back({ it->first, it->second[0] });
			}

			std::vector<std::string> solo_arguments = dialog.get_parametrization().get_string_serialization_bool().second;
			slv::vector::add(solo_arguments, arguments.solo_arguments);


			std::pair<int, char**> cli_arguments = get_arguments(parameter_arguments, solo_arguments);
			cli_arguments.second[0] = _argv[0];

			return glv_cli_main(cli_arguments.first, cli_arguments.second);

		} else {
			return 0;
		}

	} else {
		return glv_cli_main(_argc, _argv);
	}

}
