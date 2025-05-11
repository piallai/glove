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

#include "Foo.h"
#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "SlvParameterRuleT.h"
#else
#include "glove.h"
#endif

#define _Tparam_ Foo

template <>
class SlvParameterRuleT<_Tparam_> : public SlvParameterRuleValue<_Tparam_> {

public:
    enum RuleType { valid, exception, foo_special_rule };// foo special rule: value can not be equal to 11. Redundant with exception, but used for example.

private:
    RuleType rule_type;

public:
    SlvParameterRuleT();
    SlvParameterRuleT(RuleType _rule_type, _Tparam_ _rule_value);
    ~SlvParameterRuleT();

    const RuleType& get_rule_type() const;

    SlvStatus is_abided(const SlvParameter<_Tparam_>* _parameter) const;
    bool abide(SlvParameter<_Tparam_>* _parameter) const;
};

#include "slv_string.h"

inline SlvParameterRuleT<_Tparam_>::SlvParameterRuleT() :SlvParameterRuleT(valid, 0) {

}

inline SlvParameterRuleT<_Tparam_>::SlvParameterRuleT(RuleType _rule_type, _Tparam_ _rule_value) : SlvParameterRuleValue<_Tparam_>(_rule_value) {

    rule_type = _rule_type;
}

inline SlvParameterRuleT<_Tparam_>::~SlvParameterRuleT() {

}

inline const typename SlvParameterRuleT<_Tparam_>::RuleType& SlvParameterRuleT<_Tparam_>::get_rule_type() const {

    return rule_type;
}

inline SlvStatus SlvParameterRuleT<_Tparam_>::is_abided(const SlvParameter<_Tparam_>* _parameter) const {

    if (rule_type == valid) {
        return SlvStatus();
    } else if (rule_type == exception) {
        if (_parameter->get_value() != this->rule_value) {
            return SlvStatus();
        } else {
            return SlvStatus(SlvStatus::statusType::warning, "Parameter " + _parameter->get_name() + " can not be equal to " + slv::string::to_string(this->rule_value));
        }
    } else if (rule_type == foo_special_rule) {
        if (_parameter->get_value() != Foo(11)) {
            return SlvStatus();
        } else {
            return SlvStatus(SlvStatus::statusType::warning, "Parameter " + _parameter->get_name() + " has a special rule, Foo(11) is forbidden.");
        }
    } else {
        slv::flag::ISSUE(slv::flag::Critical, "Wrong rule type");
        return SlvStatus();
    }
}

inline bool SlvParameterRuleT<_Tparam_>::abide(SlvParameter<_Tparam_>* _parameter) const {
    
    bool l_abide = true;
    
    if (rule_type == valid) {

    } else if (rule_type == exception) {
        if (_parameter->get_value() == this->rule_value) {
            l_abide = false;
            Foo foo;
            foo.set_null();
            _parameter->set_value(foo);// example of exception management
        }
    } else if (rule_type == foo_special_rule) {
        if (_parameter->get_value() == Foo(11)) {
            l_abide = false;
            _parameter->set_value(Foo(10));// Example of special rule changing 11 to 10.
        }
    } else {
        slv::flag::ISSUE(slv::flag::Critical, "Wrong rule type");
    }

    return l_abide;
}

#undef _Tparam_

