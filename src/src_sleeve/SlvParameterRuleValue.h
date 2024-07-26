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

/*! Class inherited by SlvParameterRuleT managing the value of the rule if the template type requires one.*/
template <class Tparam>
class SlvParameterRuleValue {

protected:

    Tparam rule_value;

public:

    SlvParameterRuleValue(Tparam _rule_value);
    ~SlvParameterRuleValue();

    /*! Get rule value.*/
    const Tparam& get_rule_value() const;

};

template <class Tparam>
SlvParameterRuleValue<Tparam>::SlvParameterRuleValue(Tparam _rule_value) {
    rule_value = _rule_value;
}

template <class Tparam>
SlvParameterRuleValue<Tparam>::~SlvParameterRuleValue() {

}

template <class Tparam>
const Tparam& SlvParameterRuleValue<Tparam>::get_rule_value() const {
    return rule_value;
}