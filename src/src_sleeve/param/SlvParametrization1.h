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

#include "SlvParameter.h"
#include "SlvMacros.h"
#include "filestream/slv_rw.h"

#include "param/SlvParametrization0.h"

/*! Parametrization for 1 parameters.*/
template <class T1>
class SlvParametrization1 : public SlvParametrization0 {

	SlvParameter<T1>* parameter1;

public:

	typedef SlvParametrization1<T1> Tparametrization;
	typedef SlvParametrization0 Tparametrization_lower;

protected: 

	SlvParametrization1(SlvParameter<T1>* _parameter1) :Tparametrization_lower(), parameter1(_parameter1) {
		SlvParametrization_base::parameters.push_back(parameter1);
	}

	SlvParametrization1(const SlvParametrization1& _parametrization) :Tparametrization_lower(_parametrization) {
		parameter1 =  _parametrization.get_parameter1().clone();
		SlvParametrization_base::parameters.push_back(parameter1);
	}

	~SlvParametrization1() {
		delete parameter1;
	}

public: 

	Tparametrization& operator=(const SlvParametrization1& _parametrization) {
		param_assign_rec(_parametrization);
		if (this->is_param_init_auto()) this->param_init();
		return *this;
	}

protected:
	void param_assign_rec(const SlvParametrization1& _parametrization) {
		Tparametrization_lower::param_assign_rec(_parametrization);
		*parameter1 = _parametrization.get_parameter1();
	}
public:

	/*! Set parameter values all at once.*/
	void set_parameter_values(T1 _val1, bool _l_param_only = true) {
		Tparametrization_lower::set_parameter_values(_l_param_only);
		set_parameter1_value(_val1, _l_param_only);
	}

protected:
	void set_parameter1_value(const T1& _val1, bool _l_param_only = true) {
		parameter1->set_value(_val1, _l_param_only);
	}
public:

	const SlvParameter<T1>& get_parameter1() const {
		return *parameter1;
	}

	SlvStatus check_parameters() const {
		SlvStatus status = Tparametrization_lower::check_parameters();
		status += parameter1->check_rules();
		return status;
	}

	glvm_pv_SlvParametrization_abide(1, Tparametrization_lower)

	bool operator==(const SlvParametrization1& _parametrization) const {
		return *parameter1 == *_parametrization.parameter1 && *static_cast<const Tparametrization_lower*>(this) == _parametrization;
	}

	bool operator!=(const SlvParametrization1& _parametrization) const {
		return !(*this == _parametrization);
	}

	/*! Get a vector (one element per parameter) of strings. Each string is the slv::string::to_id_str of the parameter value.
	* The marker value is used to discriminate which parameters are being converted to string.
	* Setting the marker value of a parameter is possible in the macro glvm_parameter.*/
	std::vector<std::string> get_vector_id_str(unsigned int _marker = SlvParameter_base::default_marker_value()) const {
		std::vector<std::string> vector_id_str = Tparametrization_lower::get_vector_id_str(_marker);
		if (_marker == parameter1->get_marker()) {
			vector_id_str.push_back(slv::string::to_id_str(parameter1->get_value()));
		}
		return vector_id_str;
	}

	/*! Get string serialization of the parametrization. Each vector element contains a parameter name and the corresponding parameter value as string using operator <<.
	* Parameters of nested parametrizations are simply added. Ie: there is no record of intermediate parametrizations.*/
	std::vector< std::pair<std::string, std::string> > get_string_serialization(unsigned int _marker = SlvParameter_base::default_marker_value()) const {
		std::vector< std::pair<std::string, std::string> > serialization = Tparametrization_lower::get_string_serialization(_marker);
		if (_marker == parameter1->get_marker()) {
			slv::vector::add(serialization, SlvParameterSpec<T1>::get_string_serialization(*parameter1));
		}
		return serialization;
	}

	/*! Same as get_string_serialization, but bool parameters are treated appart.
	* If bool parameter is true, the parameter name is added to the second vector, if false it is not.*/
	std::pair< std::vector< std::pair<std::string, std::string> >, std::vector<std::string> > get_string_serialization_bool(unsigned int _marker = SlvParameter_base::default_marker_value()) const {
		std::pair< std::vector< std::pair<std::string, std::string> >, std::vector<std::string> > serialization = Tparametrization_lower::get_string_serialization_bool(_marker);
		if (_marker == parameter1->get_marker()) {
			std::pair< std::vector< std::pair<std::string, std::string> >, std::vector<std::string> > serialization_parameter = SlvParameterSpec<T1>::get_string_serialization_bool(*parameter1);
			slv::vector::add(serialization.first, serialization_parameter.first);
			slv::vector::add(serialization.second, serialization_parameter.second);
		}
		return serialization;
	}

protected:
	void ostream(std::ostream& _os) const {
		Tparametrization_lower::ostream(_os);
		glvm_pv_SlvParametrization_ostream(1)
	}
	void istream_rec(std::istream& _is) {
		Tparametrization_lower::istream_rec(_is);
		glvm_pv_SlvParametrization_istream(1)
	}
	void istream(std::istream& _is) {
		istream_rec(_is);
		if (this->is_param_init_auto()) this->param_init();
	}
public:
	void writeB(std::ofstream& _output_file) const {
		Tparametrization_lower::writeB(_output_file);
		glvm_pv_SlvParametrization_writeB(1);
	}
protected:
	bool readB_rec(std::ifstream& _input_file) {
		bool l_read = Tparametrization_lower::readB_rec(_input_file);
		if (l_read) l_read = glvm_pv_SlvParametrization_readB(1);
		return l_read;
	}
public:
	bool readB(std::ifstream& _input_file) {
		bool l_read = readB_rec(_input_file);
		if (l_read && this->is_param_init_auto()) this->param_init();
		return l_read;
	}

#if OPTION_USE_THIRDPARTY_JSON==1
	void writeJson(nlohmann::json& _json) const {
		Tparametrization_lower::writeJson(_json);
		glvm_pv_SlvParametrization_writeJson(1)
	}
	SlvStatus readJson(const nlohmann::json& _json) {
		SlvStatus status = Tparametrization_lower::readJson(_json);
		glvm_pv_SlvParametrization_readJson(1)
		return status;
	}
#endif

	/*! Cast to SlvParametrization.*/
	Tparametrization& param_cast() {
		return *this;
	}

	/*! Cast to SlvParametrization.*/
	const Tparametrization& param_cast() const {
		 return *this;
	}

	/*! Assignment at parametrization level.
	* Equivalent to: param_cast() = 
	* Assign parameters from another parametrization class. Manages parameters initialization.
	* The class inheriting from this one is supposed to be Tprametrization.
	* There is no guarantee though, and the method will apply as long as SlvParametrization types are the same.*/
	template <class Tparametrization>
	void param_assign(const Tparametrization& _parametrization) {
		*this = _parametrization;
	}

};

#if OPTION_USE_THIRDPARTY_JSON==1
template <class T1>
struct slv::rw::json::typemgr::IsJsonManageableParametrizationExplicit<SlvParametrization1<T1>, typename std::enable_if<!slv::rw::json::ReadWrite<T1>::l_valid || !slv::rw::json::typemgr::IsJsonManageableParametrizationExplicit<SlvParametrization0>::l_valid>::type> {
	static constexpr bool l_valid = false;
};
#endif
