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
#include "SlvIOS.h"
class SlvParametrization_base;

/*! Parent class of SlvParameter<T> to handle vectors of parameters.*/
class SlvParameter_base : virtual public SlvIOS {

protected:

	SlvParametrization_base* parametrization;

protected:

	SlvParameter_base(SlvParametrization_base* _parametrization);
	virtual ~SlvParameter_base();

	bool is_param_init_auto() const;

public:

	/*! Set parameter value using >> operator.*/
	virtual void set_stream_value(const std::string& _string, bool _l_param_only = true) = 0;
	/*! Get parameter value using << operator.*/
	virtual std::string get_stream_value(bool _l_param_only = true) const = 0;

	/*! Get parameter name.*/
	virtual const std::string& get_name() const = 0;
	virtual const std::string& get_alias() const = 0;
	/*! Get parameter description.*/
	virtual const std::string& get_description() const = 0;
	/*! Get parameter marker.*/
	virtual const unsigned int& get_marker() const = 0;

	/*! Check if rules are abided for this parameter. Rules can either depend only the parameter or either depend on other ones.*/
	virtual SlvStatus check_rules() const = 0;

	glvm_staticVariable(const, unsigned int, default_marker_value, 0)

	/*! Get the number of rules.*/
	virtual unsigned int get_Nrules() const = 0;

private:
	/*! Static cast attempt of parameter value. Returns NULL if the parameter value is not a parametrization.*/
	virtual const SlvParametrization_base* parametrization_cast() const = 0;


	friend class SlvParametrization_base;//for parametrization_cast

};
