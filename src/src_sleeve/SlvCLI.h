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

	/*! Returns true if \p _argv contains "-glove".*/
	static bool has_glove(int _argc, char* _argv[]);

	/*! Returns index of the argument being a json file. Found by file extension.*/
	static int find_json_file(int _argc, char* _argv[]);

	/*! Create argc/argv based on provided arguments.*/
	static std::pair<int, char**> get_arguments(const std::vector< std::pair<std::string, std::string> >& _parameter_arguments, const std::vector<std::string>& _solo_arguments);

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

	public:

		Arguments(int _argc, char* _argv[]);
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
		
	};

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
