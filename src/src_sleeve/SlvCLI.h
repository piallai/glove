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

#include "SlvStatus.h"
#include "std_pair.h"

struct SlvCLI {

	/*! Parse \p _argc and \p _argv and return the corresponding parametrization.*/
	template <class Tparametrization>
	static Tparametrization parse(int _argc, char* _argv[]);

	struct Arguments;

	/*! Parse \p _argc and \p _argv and apply to \p _parametrization.*/
	template <class Tparametrization>
	static std::pair<Arguments, SlvStatus> parse(Tparametrization& _parametrization, int _argc, char* _argv[]);
	/*! Apply \p _arguments to \p _parametrization.
	* If conflicts exist in the arguments, they are being filtered out of \p _arguments. Ex: redundant multiple parameter name correspondences.*/
	template <class Tparametrization>
	static SlvStatus parse(Tparametrization& _parametrization, Arguments& _arguments);

	/*! Get the CLI line of arguments from a parametrization. If \p _l_CLI_mode is true : solo arguments (booleans) are parsed without 0/1 value.*/
	template <class Tparametrization>
	static std::string get_CLI(const Tparametrization& _parametrization, bool _l_CLI_mode);

	/*! Returns true if \p _argv contains "-glove".*/
	static bool has_glove(int _argc, char* _argv[]);

	/*! Returns index of the argument being a json file. Found by file extension.*/
	static int find_json_file(int _argc, char* _argv[]);

	/*! Create argc/argv based on provided arguments.
	* \p _l_CLI_mode : if true, '-' is necessary for name of the arguments. */
	static std::pair<int, char**> get_arguments(const std::vector< std::pair<std::string, std::string> >& _parameter_arguments, const std::vector<std::string>& _solo_arguments, bool _l_CLI_mode = true);

	struct Arguments {

	public :

		/*! Parameter identifier (starting with '-') and corresponding value.*/
		typedef std::map<std::string, std::vector<std::string> > Tparameters;

	private:

		/*! Parameter identifier (starting with '-') and corresponding value.*/
		Tparameters parameter_arguments;
		/*! Arguments that are not parameters.*/
		std::vector<std::string> solo_arguments;
		/*! Single argument of the -glove cli input. Used for loading a parametrization.*/
		std::string glove_argument;
		/*! Parse arguments.*/
		void parse(int _argc, char* _argv[]);
		/*! Parse arguments, without '-' prefix indication for parameters name.
		* This is why the name of the arguments \p _arg_names and \p _solo_arg_names must be provided.
		* If they are not provided, then the arguments will be implicitly considered to be alternatively: name/value.*/
		void parse(const std::string& _args, std::vector<std::string> _arg_names, std::vector<std::string> _solo_arg_names);
		/*! Parsing status.*/
		SlvStatus status;

	public:

		Arguments(int _argc, char* _argv[]);
		Arguments(const std::string& _args, std::vector<std::string> _arg_names, std::vector<std::string> _solo_arg_names);
		/*! Get arguments that are not parameters. Ex: "-option".*/
		const std::vector<std::string>& get_solo_arguments() const;
		/*! Get list of arguments and their corresponding value. Ex: "-param 17".
		* Each parameter argument cas be accessed by its name (ex: "-param"), and return a vector of associated values.
		* A vector is used in case multiple identical arguments are provided (ex: "-param -17 -param 5").*/
		const Tparameters& get_parameter_arguments() const;
		/*! Get single argument of the -glove cli input. Used for loading a parametrization.*/
		const std::string& get_glove_argument() const;
		/*! Return true if the instance does not store any parameter.*/
		bool is_empty() const;
		/*! Remove all arguments except those which name is in \p _arguments_remaining.*/
		void filter(const std::vector<std::string>& _arguments_remaining);
		/*! Get status of parsing.*/
		SlvStatus get_status() const;
		/*! Return the name of all the arguments (including solo arguments).*/
		std::vector<std::string> get_arguments_name() const;
	};

private:

	/*! Aggregate arguments using " ".*/
	static void aggregate_quotes(std::vector<std::string>& _args, bool _l_remove_quotes);

};

#include "slv_string.h"

template <class Tparametrization>
Tparametrization SlvCLI::parse(int _argc, char* _argv[]) {

	Tparametrization parametrization;
	parse(parametrization, _argc, _argv);

	return parametrization;
}

template <class Tparametrization>
std::pair<SlvCLI::Arguments, SlvStatus> SlvCLI::parse(Tparametrization& _parametrization, int _argc, char* _argv[]) {

	Arguments arguments(_argc, _argv);

	SlvStatus status = parse(_parametrization, arguments);

	return { arguments, status };
}

template <class Tparametrization>
SlvStatus SlvCLI::parse(Tparametrization& _parametrization, Arguments& _arguments) {

	SlvStatus status;

	if (!_arguments.is_empty()) {

		std::map<std::string, std::string> stream_values;
		for (Arguments::Tparameters::const_iterator it = _arguments.get_parameter_arguments().begin(); it != _arguments.get_parameter_arguments().end(); ++it) {
			stream_values[it->first] = it->second[0];
		}

		for (std::vector<std::string>::const_iterator it = _arguments.get_solo_arguments().begin(); it != _arguments.get_solo_arguments().end(); ++it) {
			stream_values[*it] = "1";
		}

		std::pair< std::map<std::string, int>, std::vector<std::string> > conflicts_missing = _parametrization.set_stream_values(stream_values, false);
		if (!conflicts_missing.first.empty()) {
			status += SlvStatus(SlvStatus::statusType::warning, "Multiple parameter correspondences in parametrization.");

			for (std::map<std::string, int>::const_iterator it = conflicts_missing.first.begin(); it != conflicts_missing.first.end(); ++it) {

				status.add_sub_status(SlvStatus(SlvStatus::statusType::warning, it->first + " : " + slv::string::to_string(it->second) + " correspondences"));

			}

		}

		_arguments.filter(conflicts_missing.second);

	}

	return status;
}

template <class Tparametrization>
std::string SlvCLI::get_CLI(const Tparametrization& _parametrization, bool _l_CLI_mode) {

	std::string CLI_line;

	std::pair< std::vector< std::pair<std::string, std::string> >, std::vector< std::pair<std::string, bool> > > serialization = _parametrization.get_string_serialization_bool();

	if (_l_CLI_mode) {
		serialization = _parametrization.get_string_serialization_bool();
	} else {
		serialization.first = _parametrization.get_string_serialization();
	}

	std::pair<int, char**> cli_arguments = SlvCLI::get_arguments(serialization.first, serialization.second, false);

	for (int i = 1; i < cli_arguments.first; i++) {
		CLI_line += cli_arguments.second[i];
		if (i < cli_arguments.first - 1) {
			CLI_line += " ";
		}
	}

	return CLI_line;
}
