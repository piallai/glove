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

#include "slv_is_arithmetic.h"
#include "SlvParameterRuleT.h"

/*! Enable if type is arithmetic but not bool.*/
#define Tenable typename std::enable_if<\
(slv::ts::is_arithmetic<Tparam>::value && \
!std::is_same<Tparam, bool>::value)\
>::type

/*! Rule that a parameter SlvParameter is supposed to abide. Specialization for template type which is arithmetic.
* Same as SlvParameterRuleT_spec_Arithmetic, but instead of using static values for rule, uses a dynamic value in a SlvParameter. See dynamic_rules in SlvParameter.*/
template <class Tparam>
class SlvParameterRuleT<SlvParameter<Tparam>, Tenable> {

public:
	enum RuleType { valid, exception, min, max, min_exception, max_exception };

private:
	RuleType rule_type;
	const SlvParameter<Tparam>* rule_parameter;

public:
	SlvParameterRuleT();
	SlvParameterRuleT(RuleType _rule_type, const SlvParameter<Tparam>* _rule_parameter);
	~SlvParameterRuleT();

	/*! Get rule type of this parameter. Only one per rule instance.*/
	const RuleType& get_rule_type() const;
	/*! Return value the parameter this rule is associated to.*/
	const Tparam& get_rule_value() const;

	/*! Get string description of the rule.*/
	std::string get_rule_description() const;

	/*! Whether \p _parameter abides the rule or not.*/
	SlvStatus is_abided(const SlvParameter<Tparam>* _parameter) const;
	/*! Enforce rule to \p _parameter. Return true if the parameters was abiding the rule. Return false if the parameter was changed.*/
	bool abide(SlvParameter<Tparam>* _parameter) const;
};

#include "slv_string.h"

template <class Tparam>
SlvParameterRuleT<SlvParameter<Tparam>, Tenable>::SlvParameterRuleT() :SlvParameterRuleT(valid, 0) {

}

template <class Tparam>
SlvParameterRuleT<SlvParameter<Tparam>, Tenable>::SlvParameterRuleT(RuleType _rule_type, const SlvParameter<Tparam>* _rule_parameter) {

	rule_type = _rule_type;
	rule_parameter = _rule_parameter;
}

template <class Tparam>
SlvParameterRuleT<SlvParameter<Tparam>, Tenable>::~SlvParameterRuleT() {

}

template <class Tparam>
const typename SlvParameterRuleT<SlvParameter<Tparam>, Tenable>::RuleType& SlvParameterRuleT<SlvParameter<Tparam>, Tenable>::get_rule_type() const {

	return rule_type;
}

template <class Tparam>
const Tparam& SlvParameterRuleT<SlvParameter<Tparam>, Tenable>::get_rule_value() const {
	return rule_parameter->get_value();
}

template <class Tparam>
std::string SlvParameterRuleT<SlvParameter<Tparam>, Tenable>::get_rule_description() const {

	if (rule_type == valid) {
		return std::string();
	} else if (rule_type == exception) {
		return "Can not equal " + slv::string::to_string(rule_parameter->get_value());
	} else if (rule_type == min) {
		return ">= " + slv::string::to_string(rule_parameter->get_value());
	} else if (rule_type == max) {
		return "<= " + slv::string::to_string(rule_parameter->get_value());
	} else if (rule_type == min_exception) {
		return "> " + slv::string::to_string(rule_parameter->get_value());
	} else if (rule_type == max_exception) {
		return "< " + slv::string::to_string(rule_parameter->get_value());
	} else {
		slv::flag::ISSUE(slv::flag::Critical, "Wrong rule type");
		return std::string();
	}

}

template <class Tparam>
SlvStatus SlvParameterRuleT<SlvParameter<Tparam>, Tenable>::is_abided(const SlvParameter<Tparam>* _parameter) const {

	if (rule_type == valid) {
		return SlvStatus();
	} else if (rule_type == exception) {
		if (_parameter->get_value() != rule_parameter->get_value()) {
			return SlvStatus();
		} else {
			return SlvStatus(SlvStatus::statusType::warning, "Parameter " + _parameter->get_name() + " can not be equal to " + slv::string::to_string(rule_parameter->get_name()));
		}
	} else if (rule_type == min) {
		if (_parameter->get_value() >= rule_parameter->get_value()) {
			return SlvStatus();
		} else {
			return SlvStatus(SlvStatus::statusType::warning, "Parameter " + _parameter->get_name() + " can not be lower than " + slv::string::to_string(rule_parameter->get_name()));
		}
	} else if (rule_type == max) {
		if (_parameter->get_value() <= rule_parameter->get_value()) {
			return SlvStatus();
		} else {
			return SlvStatus(SlvStatus::statusType::warning, "Parameter " + _parameter->get_name() + " can not be greater than " + slv::string::to_string(rule_parameter->get_name()));
		}
	} else if (rule_type == min_exception) {
		if (_parameter->get_value() > rule_parameter->get_value()) {
			return SlvStatus();
		} else {
			return SlvStatus(SlvStatus::statusType::warning, "Parameter " + _parameter->get_name() + " can not be lower/eq than " + slv::string::to_string(rule_parameter->get_name()));
		}
	} else if (rule_type == max_exception) {
		if (_parameter->get_value() < rule_parameter->get_value()) {
			return SlvStatus();
		} else {
			return SlvStatus(SlvStatus::statusType::warning, "Parameter " + _parameter->get_name() + " can not be greater/eq than " + slv::string::to_string(rule_parameter->get_name()));
		}
	} else {
		slv::flag::ISSUE(slv::flag::Critical, "Wrong rule type");
		return SlvStatus();
	}
}

template <class Tparam>
bool SlvParameterRuleT<SlvParameter<Tparam>, Tenable>::abide(SlvParameter<Tparam>* _parameter) const {

	bool l_abide = true;

	if (rule_type == valid) {

	} else if (rule_type == exception) {
		if (_parameter->get_value() == rule_parameter->get_value()) {
			l_abide = false;
			Tparam value = _parameter->get_value();
			if (_parameter->get_value() > Tparam()) {
				--value;
			} else if (_parameter->get_value() < Tparam()) {
				++value;
			} else {
				++value;
			}
			_parameter->set_value(value);// set replacement value
		}
	} else if (rule_type == min) {
		if (_parameter->get_value() < rule_parameter->get_value()) {
			l_abide = false;
			_parameter->set_value(rule_parameter->get_value());
		}
	} else if (rule_type == max) {
		if (_parameter->get_value() > rule_parameter->get_value()) {
			l_abide = false;
			_parameter->set_value(rule_parameter->get_value());
		}
	} else if (rule_type == min_exception) {
		if (_parameter->get_value() <= rule_parameter->get_value()) {
			l_abide = false;
			_parameter->set_value(rule_parameter->get_value());
		}
	} else if (rule_type == max_exception) {
		if (_parameter->get_value() >= this->rule_value) {
			l_abide = false;
			_parameter->set_value(rule_parameter->get_value());
		}
	} else {
		slv::flag::ISSUE(slv::flag::Critical, "Wrong rule type");
	}

	return l_abide;
}

#undef Tenable
