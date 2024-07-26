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
#include "SlvParameter_base.h"

/*! Enable if not of specified type in an other file. For instance SlvParameterRuleT_spec_ParameterArithmetic.h*/
#define Tenable typename std::enable_if<\
(!slv::ts::is_arithmetic<Tparam>::value || \
std::is_same<Tparam, bool>::value)\
>::type

/*! Rule that a parameter SlvParameter is supposed to abide.
* Same as SlvParameterRuleT_spec_Arithmetic, but instead of using static values for rule, uses a dynamic value in a SlvParameter. See dynamic_rules in SlvParameter.*/
template <class Tparam>
class SlvParameterRuleT<SlvParameter<Tparam>, Tenable> {

public:
	enum RuleType { valid, exception };

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

	return std::string();

}

template <class Tparam>
SlvStatus SlvParameterRuleT<SlvParameter<Tparam>, Tenable>::is_abided(const SlvParameter<Tparam>* _parameter) const {

	return SlvStatus();
}

template <class Tparam>
bool SlvParameterRuleT<SlvParameter<Tparam>, Tenable>::abide(SlvParameter<Tparam>* _parameter) const {
	return true;
}

#undef Tenable
