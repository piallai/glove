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

#include "SlvParametrization_base.h"
#include "slv_string.h"
#include "slv_vector.h"

SlvParametrization_base::SlvParametrization_base() {

	l_param_init_auto = true;

}

SlvParametrization_base::~SlvParametrization_base() {

}

bool SlvParametrization_base::is_param_init_auto() const {
	return l_param_init_auto;
}

void SlvParametrization_base::set_param_init_auto(bool _l_param_init_auto) {
	l_param_init_auto = _l_param_init_auto;
}

std::string SlvParametrization_base::get_id_str() const {
	return slv::string::to_string(get_vector_id_str());
}
std::string SlvParametrization_base::get_full_name() const {
	return get_name() + separator() + get_id_str();
}

bool SlvParametrization_base::has_rules() const {

	bool l_has_rules = false;

	for (int i = 0; i < parameters.size() && !l_has_rules; i++) {

		l_has_rules = (parameters[i]->get_Nrules() > 1);// 1 because a default rule is added for every parameter to manage recursive rules of parametrizations

	}

	return l_has_rules;
}

void SlvParametrization_base::param_init() {

}

std::vector<const SlvParameter_base*> SlvParametrization_base::find(std::string _parameter_name, bool _l_parametrizations) const {

	std::vector<const SlvParameter_base*> parameters_found;

	for (std::vector<const SlvParameter_base*>::const_iterator it = parameters.begin(); it != parameters.end(); ++it) {

		const SlvParametrization_base* parametrization_cast = (*it)->parametrization_cast();

		if ((_l_parametrizations || !parametrization_cast) && (*it)->get_name() == _parameter_name) {

			parameters_found.push_back(*it);

		} else if (parametrization_cast) {

			slv::vector::add(parameters_found, parametrization_cast->find(_parameter_name, _l_parametrizations));

		}

	}

	return parameters_found;
}

const SlvParameter_base* SlvParametrization_base::find_first(std::string _parameter_name, bool _l_parametrizations) const {

	std::vector<const SlvParameter_base*> parameters_found = find(_parameter_name, _l_parametrizations);
	if (!parameters_found.empty()) {
		return parameters_found.front();
	} else {
		return NULL;
	}

}

std::pair< std::map<std::string, int>, std::vector<std::string> > SlvParametrization_base::set_stream_values(const std::map<std::string, std::string>& _stream_values, bool _l_parametrizations) {

	std::pair< std::map<std::string, int>, std::vector<std::string> > conflicts_missing;

	for (std::map<std::string, std::string>::const_iterator it = _stream_values.begin(); it != _stream_values.end(); ++it) {

		std::vector<const SlvParameter_base*> parameters_found = find(it->first, _l_parametrizations);

		if (!parameters_found.empty()) {

			if (parameters_found.size() > 1) {
				conflicts_missing.first[it->first] = (int)parameters_found.size();
			}

			for (int p = 0; p < parameters_found.size(); p++) {
				const_cast<SlvParameter_base*>(parameters_found[p])->set_stream_value(it->second);
			}

		} else {

			conflicts_missing.second.push_back(it->first);

		}
		
	}

	return conflicts_missing;
}