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

#include "slv_string.h"

template <class Tparam, typename T>
SlvParameterRuleT<Tparam, T>::SlvParameterRuleT() :SlvParameterRuleT(valid, Tparam()) {

}

template <class Tparam, typename T>
SlvParameterRuleT<Tparam, T>::SlvParameterRuleT(RuleType _rule_type, Tparam _rule_value) : SlvParameterRuleValue<Tparam>(_rule_value) {

    rule_type = _rule_type;
}

template <class Tparam, typename T>
SlvParameterRuleT<Tparam, T>::~SlvParameterRuleT() {

}

template <class Tparam, typename T>
const typename SlvParameterRuleT<Tparam, T>::RuleType& SlvParameterRuleT<Tparam, T>::get_rule_type() const {
    return rule_type;
}

template <class Tparam, typename T>
std::string SlvParameterRuleT<Tparam, T>::get_rule_description() const {
    return std::string();
}

template <class Tparam, typename T>
SlvStatus SlvParameterRuleT<Tparam, T>::is_abided(const SlvParameter<Tparam>* _parameter) const {
    if (rule_type == valid) {

        return SlvParameterRuleValidation<Tparam>::is_valid(_parameter);

#if SlvParameterRuleT_exception==1
    } else if (rule_type == exception) {
        if (_parameter->get_value() != this->rule_value) {
            return SlvStatus();
        } else {
            return SlvStatus(SlvStatus::statusType::warning, "Parameter " + _parameter->get_name() + " can not be equal to " + slv::string::to_string(this->rule_value));
        }
#endif
    } else {
        slv::flag::ISSUE(slv::flag::Critical, "Wrong rule type");
        return SlvStatus();
    }
}

template <class Tparam, typename T>
bool SlvParameterRuleT<Tparam, T>::abide(SlvParameter<Tparam>* _parameter) const {

    bool l_abide = true;

    if (rule_type == valid) {

#if SlvParameterRuleT_exception==1
    } else if (rule_type == exception) {
        if (_parameter->get_value() == this->rule_value) {
            l_abide = false;
            _parameter->set_value(Tparam());
        }
#endif
    } else {
        slv::flag::ISSUE(slv::flag::Critical, "Wrong rule type");
    }

    return l_abide;
}
