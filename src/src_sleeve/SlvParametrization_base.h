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

#include "SlvVirtualGetName.h"
#include "SlvMacrosDeclarations.h"
#include "std_vector.h"
#include "SlvParameter_base.h"
#include "SlvIOS.h"

class SlvParametrization_base : virtual public SlvVirtualGetName, virtual public SlvIOS {

protected:

	/* Copy of the pointer of the parameters set in SlvParametrization**.
	* Convenient to call virtual methods on all the parameters without neededing to known the parameter template type.*/
	std::vector<const SlvParameter_base*> parameters;

	/*! Whether param_init() method is called each time a parameter's value is modified.*/
	bool l_param_init_auto;

public:

	/*! Separate static name of the class to parameters. ex: name@[param1,param2,param3].*/
	glvm_staticVariable(const, char, separator, '@');

protected:
	SlvParametrization_base();
public:
	virtual ~SlvParametrization_base();

	/*! Whether param_init() method is called each time a parameter's value is modified.
	* Either by SlvParametrization**::operator=
	* Or SlvParametrization**::set_***(value).
	* Default is true.*/
	bool is_param_init_auto() const;
	/*! Set whether param_init() method is called each time a parameter's value is modified.
	* Either by SlvParametrization**::operator=
	* Or SlvParametrization**::set_***(value).
	* Default is true.*/
	void set_param_init_auto(bool _l_param_init_auto);

	/*! Get string identification of the parametrization.*/
	std::string get_id_str() const;
	/*! Get a name of the instance plus string identification of the parametrization.*/
	std::string get_full_name() const;

	/*! Check parameters rules.*/
	virtual SlvStatus check_parameters() const = 0;

	/*! Check if the parametrization has rules or not.*/
	bool has_rules() const;
	/*! Returns false if the rules were not abided, meaning there was a modification of the parametrization.
	* Returns true if rules are abided, meaning there was no modification of the parameterization.*/
	virtual bool abide_rules() = 0;

	/*! Process of parameters at construction.
	* Usefull to call after a param_cast() assignment.
	* When definition of param_init() is needed, must be reimplemented in the parametrization class inheriting from SlvParametrization.
	* Ex: private parameter deriving from other ones.*/
	virtual void param_init();

	/*! Recursively find the parameters which name is \p _parameter_name.
	* If \p _l_parametrizations is true, parameters which type is a parametrization can be counted.
	* If false, they are excluded (but recursivity still applies).*/
	std::vector<const SlvParameter_base*> find(std::string _parameter_name, bool _l_parametrizations) const;
	/*! Recursively find the frist parameter which name is \p _parameter_name.
	* If \p _l_parametrizations is true, parameters which type is a parametrization can be counted.
	* If false, they are excluded (but recursivity still applies).
	* Returns NULL if none found.*/
	const SlvParameter_base* find_first(std::string _parameter_name, bool _l_parametrizations) const;

	/*! Set parameter values using >> operator by providing parameter name and corresponding value as string.
	* Returns :
	* First of pair: the conflicts corresponding to multiple parameters with the same name. Ie: assignment ambiguity.
	* Second of pair : parameter names that could not be found in the parametrization.*/
	std::pair< std::map<std::string, int>, std::vector<std::string> > set_stream_values(const std::map<std::string, std::string>& _stream_values, bool _l_parametrizations);

private:
	/*! Get a vector (one element per parameter) of strings. Each string is the slv::string::to_id_str of the parameter value.
	* The marker value is used to discriminate which parameters are being converted to string.
	* Setting the marker value of a parameter is possible in the macro classParameter.*/
	virtual std::vector<std::string> get_vector_id_str(unsigned int _marker = SlvParameter_base::default_marker_value()) const = 0;
};

