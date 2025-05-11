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

#include "SlvParameterRuleT.h"
#include <type_traits>
class SlvParametrization_base;
#include <string>

/*! Rule that a parameter SlvParameter is supposed to abide. Specialization for template type which is a SlvParametrization.*/
template <class Tparam>
class SlvParameterRuleT<Tparam, typename std::enable_if<std::is_base_of<SlvParametrization_base, Tparam>::value>::type> {


public:
    SlvParameterRuleT() {}
    ~SlvParameterRuleT() {}

    /*! Whether \p _parameter abides the rule or not.*/
    SlvStatus is_abided(const SlvParameter<Tparam>* _parameter) const {
        return _parameter->get_value().check_parameters();
    }
    /*! Enforce rule to \p _parameter. Return true if the parameters was abiding the rule. Return false if the parameter was changed.*/
    bool abide(SlvParameter<Tparam>* _parameter) const {
        //return true;
        Tparam parametrization = _parameter->get_value();
        bool l_abide = parametrization.abide_rules();
        _parameter->set_value(parametrization);
        return l_abide;
    }

    /*! Get string description of the rule.*/
    std::string get_rule_description() const {
        return std::string();
    }

};
