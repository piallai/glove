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

#include "GlvParameterRuleAbiding.h"

#define Tparam bool

/*! Class to manage rules of parameters of type bool.*/
template <>
class GlvParameterRuleAbiding<Tparam> {

public:
    template <class Twidget>
    static void abide(const SlvParameterRuleT<Tparam>& _rule, Twidget* _widget) {

        if (_rule.get_rule_type() == SlvParameterRuleT<Tparam>::valid) {

#if SlvParameterRuleT_exception==1
        } else if (_rule.get_rule_type() == SlvParameterRuleT<Tparam>::exception) {

            if (_rule.get_rule_value()) {
                _widget->setChecked(!_rule.get_rule_value());
            } else {
                _widget->setChecked(!_rule.get_rule_value());
            }
            _widget->setEnabled(false);
#endif
        } else {
            slv::flag::ISSUE(slv::flag::Critical, "Wrong rule type");
        }


    }
};
#undef Tparam
