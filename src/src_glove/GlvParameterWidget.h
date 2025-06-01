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

#include "GlvDescribedWidget.h"
#include "GlvParameterRuleAbiding_specs.h"

/*! Widget managing SlvParameter.*/
class GlvParameterWidget_base : public QObject {

    Q_OBJECT

protected:

    GlvParameterWidget_base() {}
    virtual ~GlvParameterWidget_base() {}

signals:
    /*! Emitted when the widget interface related to the value of the parameter is modified.*/
    void parameterChanged(std::string _parameter_name);

private slots:
    virtual void valueChanged_slot() = 0;

};

#include "SlvParameter.h"

/*! Widget managing SlvParameter.*/
template <class Tparam>
class GlvParameterWidget : public GlvDescribedWidget<Tparam>, public GlvParameterWidget_base {

public:

    GlvParameterWidget(const SlvParameter<Tparam>& _parameter, bool l_editable = true, QWidget* _parent = 0);
    ~GlvParameterWidget();

    /*! Set value.*/
    void set(const SlvParameter<Tparam>& _parameter);
    /*! Set as editable or not.*/
    void set_editable(bool l_editable);
    /*! Apply all rules of \p _parameter.*/
    void abide_rules(const SlvParameter<Tparam>& _parameter);

private:
    /*! Apply \p _parameter_rule.*/
    void abide_rule(const SlvParameterRuleT<Tparam>& _parameter_rule);
    void valueChanged_slot();
    /*! Get description of rules. One rule description per line.*/
    std::string get_rules_description(const SlvParameter<Tparam>& _parameter) const;

};

template <class Tparam>
GlvParameterWidget<Tparam>::GlvParameterWidget(const SlvParameter<Tparam>& _parameter, bool l_editable, QWidget* _parent) :GlvDescribedWidget<Tparam>(_parameter.get_value(), std::is_same_v<Tparam, std::nullptr_t> ? "" : _parameter.get_name(), std::is_same_v<Tparam, std::nullptr_t> ? "" : _parameter.get_description(), l_editable, _parent) {

    QObject::connect(this->data_widget, SIGNAL(valueChanged()), static_cast<GlvParameterWidget_base*>(this), SLOT(valueChanged_slot()));

    abide_rules(_parameter);

    GlvDescribedWidget<Tparam>::append_tool_tip(get_rules_description(_parameter));

}

template <class Tparam>
GlvParameterWidget<Tparam>::~GlvParameterWidget() {

}

template <class Tparam>
void GlvParameterWidget<Tparam>::set(const SlvParameter<Tparam>& _parameter) {

    this->data_widget->set_value(_parameter.get_value());
}

template <class Tparam>
void GlvParameterWidget<Tparam>::set_editable(bool l_editable) {

    this->data_widget->set_editable(l_editable);
}

template <class Tparam>
void GlvParameterWidget<Tparam>::abide_rules(const SlvParameter<Tparam>& _parameter) {

    for (unsigned int r = 0; r < _parameter.get_rules().size(); r++) {
        abide_rule(_parameter.get_rules()[r]);
    }
}

template <class Tparam>
void GlvParameterWidget<Tparam>::abide_rule(const SlvParameterRuleT<Tparam>& _parameter_rule) {

    GlvParameterRuleAbiding<Tparam>::abide(_parameter_rule, this->data_widget->get_widget());

}

template <class Tparam>
void GlvParameterWidget<Tparam>::valueChanged_slot() {

    emit parameterChanged(this->data_name);

}

template <class Tparam>
std::string GlvParameterWidget<Tparam>::get_rules_description(const SlvParameter<Tparam>& _parameter) const {

    std::string description;

    std::vector<std::string> descriptions = _parameter.get_rules_description();

    for (typename std::vector<std::string>::const_iterator it = descriptions.begin(); it != descriptions.end(); ++it) {
        description += *it;
        if (std::next(it) != descriptions.end() && !it->empty()) {
            description += "\n";
        }
    }

    return description;
}