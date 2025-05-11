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

#include "SlvParametrization_base.h"
#include "SlvStatus.h"
#include "GloveOptions.h"
#if OPTION_USE_THIRDPARTY_JSON==1
#include "filestream/slv_rw_json.h"
#endif
#include "SlvIsParametrization.h"
#include "slv_vector.h"

/*! Parametrization for 0 parameter.
* All classes inheriting SlvParametrization** must have default constructor () */
class SlvParametrization0 : public SlvParametrization_base {

protected:

	SlvParametrization0();
	SlvParametrization0(const SlvParametrization0& _parametrization);
	~SlvParametrization0();

public:

	void operator=(const SlvParametrization0& _parametrization);
protected:
	void param_assign_rec(const SlvParametrization0& _parametrization);
public:
	void set_parameter_values(bool _l_param_only = true);

	SlvStatus check_parameters() const;
	bool abide_rules();

	bool operator==(const SlvParametrization0& _parametrization) const;
	bool operator!=(const SlvParametrization0& _parametrization) const;
	/*! Get a vector (one element per parameter) of strings. Each string is the slv::string::to_id_str of the parameter value.
	* The marker value is used to discriminate which parameters are being converted to string.
	* Setting the marker value of a parameter is possible in the macro classParameter.*/
	std::vector<std::string> get_vector_id_str(unsigned int _marker = SlvParameter_base::default_marker_value()) const;

	/*! Get string serialization of the parametrization. Each vector element contains a parameter name and the corresponding parameter value as string using operator <<.
	* Parameters of nested parametrizations are simply added. Ie: there is no record of intermediate parametrizations.*/
	std::vector< std::pair<std::string, std::string> > get_string_serialization(unsigned int _marker = SlvParameter_base::default_marker_value()) const;
	/*! Same as get_string_serialization, but bool parameters are treated appart.
	* If bool parameter is true, the parameter name is added to the second vector, if false it is not.*/
	std::pair< std::vector< std::pair<std::string, std::string> >, std::vector<std::string> > get_string_serialization_bool(unsigned int _marker = SlvParameter_base::default_marker_value()) const;
protected:
	void ostream(std::ostream& _os) const;
	void istream_rec(std::istream& _is);
	void istream(std::istream& _is);
public:
	void writeB(std::ofstream& _output_file) const;
protected:
	bool readB_rec(std::ifstream& _input_file);
public:
	bool readB(std::ifstream& _input_file);

#if OPTION_USE_THIRDPARTY_JSON==1
	void writeJson(nlohmann::json& _json) const;
	SlvStatus readJson(const nlohmann::json& _json);
#endif

	/* Static number of parameters.*/
	glvm_staticVariable(const, unsigned int, Nparameters, 0);
	typedef SlvParametrization0 Tparametrization;

	Tparametrization& param_cast();
	const Tparametrization& param_cast() const;

	/*! Assign parameters from another parametrization class. Manages parameters initialization.
	* The class inheriting from this one is supposed to be Taprametrization.
	* There is no guarantee though, and the method will apply as long as SlvParametrization types are the same.*/
	template <class Tparametrization>
	void param_assign(const Tparametrization& _parametrization) {}

};

#define glvm_pv_SlvParametrization_id_str(N, string) string += ", "+slv::string::to_id_str(parameter##N->get_value());
#define glvm_pv_SlvParametrization_ostream(N) _os << STRINGIFY(parameter##N) << " : " << *parameter##N << std::endl;
#define glvm_pv_SlvParametrization_istream(N) std::cout << STRINGIFY(parameter##N) << "; "; _is >> *const_cast<SlvParameter<T##N>*>(parameter##N);
#define glvm_pv_SlvParametrization_writeB(N) parameter##N->writeB(_output_file);
#define glvm_pv_SlvParametrization_readB(N) const_cast<SlvParameter<T##N>*>(parameter##N)->readB(_input_file)
#if OPTION_USE_THIRDPARTY_JSON==1
#define glvm_pv_SlvParametrization_writeJson(N) slv::rw::json::writeJson(parameter##N->get_value(), _json[this->get_name()][parameter##N->get_name()]);
#define glvm_pv_SlvParametrization_readJson(N)\
if (status.get_type() != SlvStatus::statusType::critical) {\
	nlohmann::json::const_iterator it_main = _json.find(this->get_name());\
	if (it_main != _json.end()) {\
		nlohmann::json::const_iterator it = it_main->find(parameter##N->get_name());\
		SlvStatus status_parameter;\
		if (it != it_main->end()) {\
			T##N value = parameter##N->get_default_value();\
			SlvStatus status_json = slv::rw::json::readJson(value, *it);\
			if (status_json) {\
				const_cast<SlvParameter<T##N>*>(parameter##N)->set_value(value);\
			} else {\
				status_parameter = SlvStatus(SlvStatus::statusType::warning, "Problem reading parameter : " + parameter##N->get_name());\
				status_parameter.add_sub_status(status_json);\
			}\
		} else {\
			status_parameter = SlvStatus(SlvStatus::statusType::warning, "Can not find parameter : " + parameter##N->get_name());\
		}\
		if (!status_parameter) {\
			status += SlvStatus(SlvStatus::statusType::warning, "Problem reading parametrization : " + this->get_name());\
			status.add_sub_status(status_parameter);\
		}\
	}\
}
#endif

#define glvm_pv_SlvParametrization_abide(current, previous_parametrization) \
bool abide_rules() {\
    bool l_abide_rules = previous_parametrization::abide_rules();\
    l_abide_rules &= const_cast<SlvParameter<T##current>*>(parameter##current)->abide_rules();\
	return l_abide_rules;\
}

#include "param/SlvParametrizationConstructorMacro.h"
