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

#include "SlvParameterRuleT_spec_Arithmetic.h"
#include "GlvParameterRuleAbiding.h"

#define Tenable typename std::enable_if<slv::ts::is_arithmetic<Tparam>::value>::type

/*! Class to manage rules of parameters of arithmetic types.*/
template <class Tparam>
class GlvParameterRuleAbiding<Tparam, Tenable> {

public:
    template <class Twidget>
    static void abide(const SlvParameterRuleT<Tparam>& _rule, Twidget* _widget) {

        if (_rule.get_rule_type() == SlvParameterRuleT<Tparam>::valid) {

        } else if (_rule.get_rule_type() == SlvParameterRuleT<Tparam>::exception) {

            //would need to inherit widget (QSpinBox) for instance and create signal valueChanged(value_old, value_new)

        } else if (_rule.get_rule_type() == SlvParameterRuleT<Tparam>::min) {

            _widget->setMinimum(_rule.get_rule_value());

        } else if (_rule.get_rule_type() == SlvParameterRuleT<Tparam>::max) {

            _widget->setMaximum(_rule.get_rule_value());

        } else if (_rule.get_rule_type() == SlvParameterRuleT<Tparam>::min_exception) {

            _widget->setMinimum(_rule.get_rule_value());

        } else if (_rule.get_rule_type() == SlvParameterRuleT<Tparam>::max_exception) {

            _widget->setMaximum(_rule.get_rule_value());

        } else {
            slv::flag::ISSUE(slv::flag::Critical, "Wrong rule type");
        }


    }
};

#undef Tenable
