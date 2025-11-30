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

#include "SlvCLI.h"
#include "SlvMacros.h"
#include "slv_vector.h"
#include <cstring>
#include "slv_string.h"

SlvCLI::Arguments::Arguments(int _argc, char* _argv[]) {

	parse(_argc, _argv);

}

SlvCLI::Arguments::Arguments(const std::string& _args, std::vector<std::string> _arg_names, std::vector<std::string> _solo_arg_names) {

	parse(_args, _arg_names, _solo_arg_names);

}

SlvStatus SlvCLI::Arguments::get_status() const {

	return status;

}

std::vector<std::string> SlvCLI::Arguments::get_arguments_name() const {

	std::vector<std::string> arguments_name;
	for (auto it = parameter_arguments.begin(); it != parameter_arguments.end(); ++it) {
		arguments_name.push_back(it->first);
	}
	for (auto it = solo_arguments.begin(); it != solo_arguments.end(); ++it) {
		arguments_name.push_back(*it);
	}

	return arguments_name;
}

bool SlvCLI::has_glove(int _argc, char* _argv[]) {

	bool l_found = false;
	int i;
	for (i = 1; i < _argc && !l_found; i++) {
		l_found = !std::strcmp(_argv[i], "-glove");
	}

	return l_found;
}

int SlvCLI::find_json_file(int _argc, char* _argv[]) {

	static const std::string json_ext = ".json";
	bool l_found = false;
	int i;
	for (i = 1; i < _argc && !l_found; i++) {

		size_t len = strlen(_argv[i]);
		if (len >= json_ext.size()) {
			char* str = (char*)_argv[i] + (len - json_ext.size());
			l_found = !std::strcmp(str, json_ext.c_str());
		}

	}

	if (l_found) {
		return i - 1;
	} else {
		return -1;
	}

}

bool SlvCLI::Arguments::is_empty() const {

	return parameter_arguments.empty() && solo_arguments.empty();

}

const std::vector<std::string>& SlvCLI::Arguments::get_solo_arguments() const {

	return solo_arguments;

}

const SlvCLI::Arguments::Tparameters& SlvCLI::Arguments::get_parameter_arguments() const {

	return parameter_arguments;

}

const std::string& SlvCLI::Arguments::get_glove_argument() const {

	return glove_argument;

}

void SlvCLI::Arguments::parse(int _argc, char* _argv[]) {

	status = SlvStatus();

	parameter_arguments.clear();
	solo_arguments.clear();

	for (int i = 1; i < _argc; i++) {
		bool l_parameter = false;
		if (_argv[i][0] == '-') {

			bool l_value = i < _argc - 1;
			if (l_value) {
				bool l_value2 = _argv[i + 1][0] != '-';// if front of next argument has no '-'
				bool l_value_dash = _argv[i + 1][0] == '-';// if front of next argument is '-', then check for value
				bool l_value_number = false;
				if (l_value_dash) {
					l_value_number = (std::isdigit(_argv[i + 1][1]) || (std::strcmp(_argv[i + 1], "-inf") == 0));
				}
				l_value &= (l_value2 || (l_value_dash && l_value_number));
			}

			if (l_value) {

				if (std::strcmp(_argv[i], "-glove")) {
					parameter_arguments[_argv[i]].push_back(_argv[i + 1]);
				} else {
					glove_argument = _argv[i + 1];
				}
				l_parameter = true;
			}
		}

		if (!l_parameter) {
			if (std::strcmp(_argv[i], "-glove")) {
				solo_arguments.push_back(_argv[i]);
			}
		} else {
			i++;
		}
	}

}

void SlvCLI::aggregate_quotes(std::vector<std::string>& _args, bool _l_remove_quotes) {

	for (auto it = _args.begin(); it != _args.end(); ++it) {
		if (it->front() == '\"') {
			std::string sum;
			auto it2 = it;
			bool l_found_end = false;
			while (!l_found_end && it2 != _args.end()) {
				if (!sum.empty()) sum += " ";
				sum += *it2;
				l_found_end = (it2->back() == '\"');
				++it2;
			}
			if (l_found_end) {

				if (_l_remove_quotes) {
					sum.erase(sum.begin());
					sum.erase(std::prev(sum.end()));
				}

				it = _args.erase(it, it2);
				it = _args.insert(it, sum);
			}
		}
	}

}

void SlvCLI::Arguments::parse(const std::string& _args, std::vector<std::string> _arg_names, std::vector<std::string> _solo_arg_names) {

	status = SlvStatus();

	// If the argument names are not provided, then the arguments are implicitly considered to be alternatively: name/value
	bool l_consecutive_arguments = (_arg_names.empty() && _solo_arg_names.empty());

	bool l_conflict = false;
	for (auto it = _arg_names.begin(); it != _arg_names.end(); ++it) {
		if (slv::vector::find(*it, _solo_arg_names)) {
			if (_args.find(*it) != std::string::npos) {// if the conflicting parameter is involved in the arguments
				status += SlvStatus(SlvStatus::statusType::warning, "Parameter " + *it + " is both a value and an activation (boolean).");
				l_conflict = true;
			}
		}
	}

	if (!l_conflict) {
		std::vector<std::string> args = slv::string::read_datas_line<std::string>(_args, " ");

		aggregate_quotes(args, true);

		for (auto it = args.begin(); it != args.end(); ++it) {
			if (l_consecutive_arguments || slv::vector::find(*it, _arg_names)) {
				if (std::next(it) != args.end()) {
					parameter_arguments[*it].push_back(*++it);
				} // else: problem with arguments. l_consecutive_arguments likely to be false instead of true.
			} else if (slv::vector::find(*it, _solo_arg_names)) {
				solo_arguments.push_back(*it);
			}
		}
	}

}

void SlvCLI::Arguments::filter(const std::vector<std::string>& _arguments_remaining) {

	for (Tparameters::const_iterator it = parameter_arguments.begin(); it != parameter_arguments.end();) {

		if (!slv::vector::find(it->first, _arguments_remaining)) {
			it = parameter_arguments.erase(it);
		} else {
			++it;
		}

	}

	for (std::vector<std::string>::const_iterator it = solo_arguments.begin(); it != solo_arguments.end();) {

		if (!slv::vector::find(*it, _arguments_remaining)) {
			it = solo_arguments.erase(it);
		} else {
			++it;
		}

	}

}

std::pair<int, char**> SlvCLI::get_arguments(const std::vector< std::pair<std::string, std::string> >& _parameter_arguments, const std::vector<std::string>& _solo_arguments, bool _l_CLI_mode) {

	std::vector< std::pair<std::string, std::string> > parameter_arguments;
	for (std::vector< std::pair<std::string, std::string> >::const_iterator it = _parameter_arguments.begin(); it != _parameter_arguments.end(); ++it) {
		if (it->first.front() == '-' || !_l_CLI_mode) {
			parameter_arguments.push_back(*it);
		}
	}

	std::vector<std::string> solo_arguments;
	for (std::vector<std::string>::const_iterator it = _solo_arguments.begin(); it != _solo_arguments.end(); ++it) {
		if (it->front() == '-' || !_l_CLI_mode) {
			solo_arguments.push_back(*it);
		}
	}


	int Nfilled_parameters = 0;
	for (int i = 0; i < parameter_arguments.size(); i++) {
		if (!parameter_arguments[i].second.empty()) {
			Nfilled_parameters++;
		}
	}

	int argc = 2 * Nfilled_parameters + (int)solo_arguments.size() + 1;
	char** argv = new char* [argc];

	int k_arg = 0;
	for (int i = 0; i < parameter_arguments.size(); i++) {

		if (!parameter_arguments[i].second.empty()) {

			argv[1 + k_arg] = new char[parameter_arguments[i].first.size() + 1];
#ifdef COMPILER_GCC
			strcpy(argv[1 + k_arg], parameter_arguments[i].first.c_str());
#else
			strcpy_s(argv[1 + k_arg], parameter_arguments[i].first.size() + 1, parameter_arguments[i].first.c_str());
#endif
			k_arg++;

			argv[1 + k_arg] = new char[parameter_arguments[i].second.size() + 1];
#ifdef COMPILER_GCC
			strcpy(argv[1 + k_arg], parameter_arguments[i].second.c_str());
#else
			strcpy_s(argv[1 + k_arg], parameter_arguments[i].second.size() + 1, parameter_arguments[i].second.c_str());
#endif
			k_arg++;

		}

	}

	for (int i = 0; i < solo_arguments.size(); i++) {
		argv[1 + 2 * Nfilled_parameters + i] = new char[solo_arguments[i].size() + 1];
#ifdef COMPILER_GCC
		strcpy(argv[1 + 2 * Nfilled_parameters + i], solo_arguments[i].c_str());
#else
		strcpy_s(argv[1 + 2 * Nfilled_parameters + i], solo_arguments[i].size() + 1, solo_arguments[i].c_str());
#endif
	}

	return { argc, argv };

}
