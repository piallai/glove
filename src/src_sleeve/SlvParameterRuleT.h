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

#include "SlvParameterRuleValue.h"
#include "SlvStatus.h"
#include "SlvParameterRuleValidation.h"
#include "slv_flag.h"

template <class Tparam>
class SlvParameter;

/*! Option to enable exception management for any type.
* It requires Tparam to have == and != operators implemented.
* This is why it is hard-disabled by default.*/
#define SlvParameterRuleT_exception 0

/*! Rule that a parameter SlvParameter is supposed to abide.*/
template <class Tparam, typename = void>
class SlvParameterRuleT : public SlvParameterRuleValue<Tparam> {


public:
    /*! Possible rule types for this type (template) of paramter.*/
    enum RuleType {
        valid
#if SlvParameterRuleT_exception==1
        , exception
#endif
    };

private:
    RuleType rule_type;

public:
    SlvParameterRuleT();
    SlvParameterRuleT(RuleType _rule_type, Tparam _rule_value);
    ~SlvParameterRuleT();

    /*! Get rule type of this parameter. Only one per rule instance.*/
    const RuleType& get_rule_type() const;

    /*! Get string description of the rule.*/
    std::string get_rule_description() const;

    /*! Whether \p _parameter abides the rule or not.*/
    SlvStatus is_abided(const SlvParameter<Tparam>* _parameter) const;
    /*! Enforce rule to \p _parameter. Return true if the parameters was abiding the rule. Return false if the parameter was changed.*/
    bool abide(SlvParameter<Tparam>* _parameter) const;

};

#include "SlvParameterRuleT_impl.h"

#undef SlvParameterRuleT_exception

#include "SlvParameterRuleT_spec_Arithmetic.h"
#include "SlvParameterRuleT_spec_SlvParametrization.h"
#include "SlvParameterRuleT_spec_Parameter.h"
#include "SlvParameterRuleT_spec_ParameterArithmetic.h"
