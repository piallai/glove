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

#include "GlvCLI.h"
#include "SlvMacros.h"

bool GlvCLI::has_glove(int _argc, char* _argv[]) {

	bool l_found = false;
	int i;
	for (i = 1; i < _argc && !l_found; i++) {
		l_found = !std::strcmp(_argv[i], "-glove");
	}

	return l_found;
}

void GlvCLI::Arguments::parse(int _argc, char* _argv[]) {

	parameter_arguments.clear();
	solo_arguments.clear();

	for (int i = 1; i < _argc; i++) {
		bool l_parameter = false;
		if (_argv[i][0] == '-') {
			if (i < _argc - 1 && _argv[i + 1][0] != '-') {
				parameter_arguments[_argv[i]].push_back(_argv[i + 1]);
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

void GlvCLI::Arguments::filter(const std::vector<std::string>& _arguments_remaining) {

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

std::pair<int, char**> GlvCLI::get_arguments(const std::vector< std::pair<std::string, std::string> >& _parameter_arguments, const std::vector<std::string>& _solo_arguments) {

	int Nfilled_parameters = 0;
	for (int i = 0; i < _parameter_arguments.size(); i++) {
		if (!_parameter_arguments[i].second.empty()) {
			Nfilled_parameters++;
		}
	}

	int argc = 2 * Nfilled_parameters + (int)_solo_arguments.size() + 1;
	char** argv = new char* [argc];

	int k_arg = 0;
	for (int i = 0; i < _parameter_arguments.size(); i++) {

		if (!_parameter_arguments[i].second.empty()) {

			argv[1 + k_arg] = new char[_parameter_arguments[i].first.size() + 1];
#ifdef COMPILER_GCC
			strcpy(argv[1 + k_arg], _parameter_arguments[i].first.c_str());
#else
			strcpy_s(argv[1 + k_arg], _parameter_arguments[i].first.size() + 1, _parameter_arguments[i].first.c_str());
#endif
			k_arg++;

			argv[1 + k_arg] = new char[_parameter_arguments[i].second.size() + 1];
#ifdef COMPILER_GCC
			strcpy(argv[1 + k_arg], _parameter_arguments[i].second.c_str());
#else
			strcpy_s(argv[1 + k_arg], _parameter_arguments[i].second.size() + 1, _parameter_arguments[i].second.c_str());
#endif
			k_arg++;

		}
		
	}


	for (int i = 0; i < _solo_arguments.size(); i++) {
		argv[1 + 2 * Nfilled_parameters + i] = new char[_solo_arguments[i].size() + 1];
#ifdef COMPILER_GCC
		strcpy(argv[1 + 2 * Nfilled_parameters + i], _solo_arguments[i].c_str());
#else
		strcpy_s(argv[1 + 2 * Nfilled_parameters + i], _solo_arguments[i].size() + 1, _solo_arguments[i].c_str());
#endif
	}

	return { argc, argv };

}
