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

#include "SlvMacrosDeclarations.h"// for parameter macro declaration
#include "SlvParameterRuleT.h"
#include "std_vector.h"
#include "SlvParameter_base.h"
class SlvParametrization_base;
#if OPTION_USE_THIRDPARTY_JSON==1
#include "filestream/slv_rw_json.h"
#endif

/*! Parameter class. Is inherited by parameters created in SlvParametrization**.*/
template <class Tparam>
class SlvParameter : public SlvParameter_base {

private:

    /*! Parameter value.*/
    Tparam value;
    /*! Rules depending on another parameter.*/
    std::vector< SlvParameterRuleT< SlvParameter<Tparam> > > dynamic_rules;

protected:

    SlvParameter(SlvParametrization_base* _parametrization, Tparam _value);
public:
    ~SlvParameter();

    virtual SlvParameter<Tparam>* clone(SlvParametrization_base* _parametrization) const = 0;

    /*! Assign parameter value. In case Tparam derives from SlvParametrization, only the parameters are set.*/
    void operator=(const SlvParameter<Tparam>& _parameter);

    /*! Get parameter value.*/
    const Tparam& get_value() const;
    /*! Set parameter value. In case Tparam derives from SlvParametrization, if \p _l_param_only is true, then only the parameters are set.*/
    void set_value(const Tparam& _value, bool _l_param_only = true);
    /*! Get default value as set by the static parameter.*/
    virtual const Tparam& get_default_value() const = 0;

    /*! Check if rules are abided for this parameter. Rules can either depend only the parameter or either depend on other ones.*/
    SlvStatus check_rules() const;

    /*! Abide the rules of the parameter. Its value can change.*/
    bool abide_rules();

    bool operator==(const SlvParameter<Tparam>& _parameter) const;
    bool operator!=(const SlvParameter<Tparam>& _parameter) const;

    /*! Add a dynamic rule depending on other paramters.*/
    void add_dynamic_rule(const SlvParameterRuleT< SlvParameter<Tparam> >& _dynamic_rule);

    /*! Get rules depending only on this parameter.*/
    virtual const std::vector< SlvParameterRuleT<Tparam> >& get_rules() const = 0;
    /*! Get rules depending on other parameters.*/
    const std::vector< SlvParameterRuleT< SlvParameter<Tparam> > >& get_dynamic_rules() const;
    /*! Get description of each rule of the parameter.*/
    std::vector<std::string> get_rules_description() const;

    bool readB(std::ifstream& _input_file);
    void writeB(std::ofstream& _output_file) const;

#if OPTION_USE_THIRDPARTY_JSON==1
    void writeJson(nlohmann::json& _json) const;
    SlvStatus readJson(const nlohmann::json& _json);
#endif

protected:

    void istream(std::istream& _is);
    void ostream(std::ostream& _os) const;

private:

    /*! Static cast attempt of parameter value. Returns NULL if the parameter value is not a parametrization.*/
    const SlvParametrization_base* parametrization_cast() const;

};

#include "filestream/slv_rw.h"
#include "misc/SlvDataName.h"
#include "misc/slv_parse.h"

template <class Tparam>
struct SlvParameterSpecSerialization {
    static std::pair< std::vector< std::pair<std::string, std::string> >, std::vector< std::pair<std::string, bool> > > get_string_serialization_bool(const SlvParameter<Tparam>& _parameter);
};

template <>
struct SlvParameterSpecSerialization<bool>;


template <class Tparam, typename = void>
struct SlvParameterSpec {
    static void assign(Tparam& _parameter_value1, const Tparam& _parameter_value2, bool _l_param_only) {
        _parameter_value1 = _parameter_value2;
    }
    static bool readB(Tparam& _parameter_value, std::ifstream& _input_file) {
        return slv::rw::readB(_parameter_value, _input_file);
    }
    static void writeB(const Tparam& _parameter_value, std::ofstream& _output_file) {
        slv::rw::writeB(_parameter_value, _output_file);
    }
#if OPTION_USE_THIRDPARTY_JSON==1
    static void writeJson(const Tparam& _parameter_value, const std::string& _parameter_name, nlohmann::json& _json) {
        slv::rw::json::writeJson(_parameter_value, _json[_parameter_name]);
    }
    static SlvStatus readJson(Tparam& _parameter_value, const std::string& _parameter_name, const nlohmann::json& _json) {
        return slv::rw::json::readJson(_parameter_value, _parameter_name, _json);
    }
#endif
    static void istream(Tparam& _parameter_value, std::istream& _is) {
        _is >> _parameter_value;
    }
    static void ostream(const Tparam& _parameter_value, std::ostream& _os) {
        _os << _parameter_value;
    }
    static void parse(Tparam& _parameter_value, const std::string& _string) {
        slv::parse(_string, _parameter_value);
    }
    static bool is_equal(const Tparam& _parameter_value1, const Tparam& _parameter_value2) {
        return _parameter_value1 == _parameter_value2;
    }
    static std::vector< std::pair<std::string, std::string> > get_string_serialization(const SlvParameter<Tparam>& _parameter) {
        std::vector< std::pair<std::string, std::string> > serialization;
        serialization.push_back({ _parameter.get_name(), slv::string::to_string(_parameter.get_value()) });
        if (!_parameter.get_alias().empty()) {
            serialization.push_back({ _parameter.get_alias(), slv::string::to_string(_parameter.get_value()) });
        }
        return serialization;
    }
    static std::pair< std::vector< std::pair<std::string, std::string> >, std::vector< std::pair<std::string, bool> > > get_string_serialization_bool(const SlvParameter<Tparam>& _parameter) {
        return SlvParameterSpecSerialization<Tparam>::get_string_serialization_bool(_parameter);
    }
    static const SlvParametrization_base* parametrization_cast(const Tparam& _parameter_value) {
        return NULL;
    }
};

#define Tparam std::nullptr_t
/*! Disable parameter operations for type std::nullptr_t*/
template <>
struct SlvParameterSpec<Tparam> {
    static void assign(Tparam& _parameter_value1, const Tparam& _parameter_value2, bool _l_param_only) {
    }
    static bool readB(Tparam& _parameter_value, std::ifstream& _input_file) {
        return true;
    }
    static void writeB(const Tparam& _parameter_value, std::ofstream& _output_file) {
    }
#if OPTION_USE_THIRDPARTY_JSON==1
    static void writeJson(const Tparam& _parameter_value, const std::string& _parameter_name, nlohmann::json& _json) {
    }
    static SlvStatus readJson(Tparam& _parameter_value, const std::string& _parameter_name, const nlohmann::json& _json) {
        return SlvStatus();
    }
#endif
    static void istream(Tparam& _parameter_value, std::istream& _is) {
    }
    static void ostream(const Tparam& _parameter_value, std::ostream& _os) {
    }
    static void parse(Tparam& _parameter_value, const std::string& _string) {
    }
    static bool is_equal(const Tparam& _parameter_value1, const Tparam& _parameter_value2) {
        return true;
    }
    static std::vector< std::pair<std::string, std::string> > get_string_serialization(const SlvParameter<Tparam>& _parameter) {
        return {};
    }
    static std::pair< std::vector< std::pair<std::string, std::string> >, std::vector< std::pair<std::string, bool> > > get_string_serialization_bool(const SlvParameter<Tparam>& _parameter) {
        return {};
    }
    static const SlvParametrization_base* parametrization_cast(const Tparam& _parameter_value) {
        return NULL;
    }
};
#undef Tparam

template <class Tparam>
std::pair< std::vector< std::pair<std::string, std::string> >, std::vector< std::pair<std::string, bool> > > SlvParameterSpecSerialization<Tparam>::get_string_serialization_bool(const SlvParameter<Tparam>& _parameter) {
    return { { SlvParameterSpec<Tparam>::get_string_serialization(_parameter) }, {} };
}

template <>
struct SlvParameterSpecSerialization<bool> {
    static std::pair< std::vector< std::pair<std::string, std::string> >, std::vector< std::pair<std::string, bool> > > get_string_serialization_bool(const SlvParameter<bool>& _parameter) {
        std::pair< std::vector< std::pair<std::string, std::string> >, std::vector< std::pair<std::string, bool> > > serialization;
        serialization.second.push_back({ _parameter.get_name(), _parameter.get_value()});
        if (!_parameter.get_alias().empty()) {
            serialization.second.push_back({ _parameter.get_name(), _parameter.get_value() });
        }
        return serialization;
    }
};

#include "SlvIsParametrization.h"
template <class Tparam>
struct SlvParameterSpec<Tparam, typename std::enable_if<SlvIsParametrization<Tparam>::value>::type> {
    static void assign(Tparam& _parameter_value1, const Tparam& _parameter_value2, bool _l_param_only) {
        if (_l_param_only) {
            _parameter_value1.param_assign(_parameter_value2);
        } else {
            _parameter_value1 = _parameter_value2;
        }
    }
    static bool readB(Tparam& _parameter_value, std::ifstream& _input_file) {
        bool l_read = slv::rw::readB(_parameter_value.param_cast(), _input_file);// param only
        _parameter_value.param_init();
        return l_read;
    }
    static void writeB(const Tparam& _parameter_value, std::ofstream& _output_file) {
        slv::rw::writeB(_parameter_value.param_cast(), _output_file);// param only
    }
#if OPTION_USE_THIRDPARTY_JSON==1
    static void writeJson(const Tparam& _parameter_value, const std::string& _parameter_name, nlohmann::json& _json) {
        slv::rw::json::writeJson(_parameter_value, _json[_parameter_name]);
    }
    static SlvStatus readJson(Tparam& _parameter_value, const std::string& _parameter_name, const nlohmann::json& _json) {
        return slv::rw::json::readJson(_parameter_value, _parameter_name, _json);
    }
#endif
    static void istream(Tparam& _parameter_value, std::istream& _is) {
        _is >> _parameter_value.param_cast();
    }
    static void ostream(const Tparam& _parameter_value, std::ostream& _os) {
        _os << _parameter_value.param_cast();
    }
    static void parse(Tparam& _parameter_value, const std::string& _string) {
        // No string parsing for parametrization
    }
    static bool is_equal(const Tparam& _parameter_value1, const Tparam& _parameter_value2) {
        return _parameter_value1.param_cast() == _parameter_value2.param_cast();
    }
    static std::vector< std::pair<std::string, std::string> > get_string_serialization(const SlvParameter<Tparam>& _parameter) {
        return _parameter.get_value().param_cast().get_string_serialization();
    }
    static std::pair< std::vector< std::pair<std::string, std::string> >, std::vector< std::pair<std::string, bool> > > get_string_serialization_bool(const SlvParameter<Tparam>& _parameter) {
        return _parameter.get_value().param_cast().get_string_serialization_bool();
    }
    static const SlvParametrization_base* parametrization_cast(const Tparam& _parameter_value) {
        return static_cast<const SlvParametrization_base*>(&_parameter_value);
    }
};

#include "SlvParametrization_base.h"

template <class Tparam>
SlvParameter<Tparam>::SlvParameter(SlvParametrization_base* _parametrization, Tparam _value) :value(_value), SlvParameter_base(_parametrization) {

}

template <class Tparam>
SlvParameter<Tparam>::~SlvParameter() {

}

template <class Tparam>
void SlvParameter<Tparam>::operator=(const SlvParameter<Tparam>& _parameter) {
    set_value(_parameter.value, true);
}

template <class Tparam>
const Tparam& SlvParameter<Tparam>::get_value() const {
    return value;
}

template <class Tparam>
void SlvParameter<Tparam>::set_value(const Tparam& _value, bool _l_param_only) {
    bool l_diff = !SlvParameterSpec<Tparam>::is_equal(_value, value);
    if (l_diff) {
        SlvParameterSpec<Tparam>::assign(value, _value, _l_param_only);
        if (this->is_param_init_auto()) parametrization->param_init();
    }
}

template <class Tparam>
SlvStatus SlvParameter<Tparam>::check_rules() const {
    SlvStatus status;
    for (unsigned int r = 0; r < get_rules().size(); r++) {
        status += get_rules()[r].is_abided(this);
    }
    for (unsigned int r = 0; r < get_dynamic_rules().size(); r++) {
        status += get_dynamic_rules()[r].is_abided(this);
    }
    return status;
}

template <class Tparam>
bool SlvParameter<Tparam>::abide_rules() {

    bool l_abide_global = true;

    // Maximum attemps
    int Nmax_loops = 20;

    // If one rules need abiding, then all rules are checked again.
    bool l_abide = false;// for initialization
    int i = 0;
    while (!l_abide && i < Nmax_loops) {
        l_abide = true;

        for (unsigned int r = 0; r < get_rules().size(); r++) {
            l_abide &= get_rules()[r].abide(this);
        }

        i++;
        l_abide_global &= l_abide;//if l_abide is false at some point, l_abide_global will be too
    }

    return l_abide_global;
}

template <class Tparam>
bool SlvParameter<Tparam>::operator==(const SlvParameter<Tparam>& _parameter) const {
    return SlvParameterSpec<Tparam>::is_equal(value, _parameter.value);
}

template <class Tparam>
bool SlvParameter<Tparam>::operator!=(const SlvParameter<Tparam>& _parameter) const {
    return !(*this == _parameter);
}

template <class Tparam>
void SlvParameter<Tparam>::add_dynamic_rule(const SlvParameterRuleT< SlvParameter<Tparam> >& _dynamic_rule) {
    dynamic_rules.push_back(_dynamic_rule);
}

template <class Tparam>
const std::vector< SlvParameterRuleT< SlvParameter<Tparam> > >& SlvParameter<Tparam>::get_dynamic_rules() const {
    return dynamic_rules;
}

template <class Tparam>
std::vector<std::string> SlvParameter<Tparam>::get_rules_description() const {

    std::vector<std::string> descriptions;
    for (typename std::vector< SlvParameterRuleT<Tparam> >::const_iterator it = get_rules().begin(); it != get_rules().end(); ++it) {
        descriptions.push_back((*it).get_rule_description());
    }
    return descriptions;

}

template <class Tparam>
const SlvParametrization_base* SlvParameter<Tparam>::parametrization_cast() const {

    return SlvParameterSpec<Tparam>::parametrization_cast(value);

}

template <class Tparam>
bool SlvParameter<Tparam>::readB(std::ifstream& _input_file) {

    return SlvParameterSpec<Tparam>::readB(value, _input_file);

}

template <class Tparam>
void SlvParameter<Tparam>::writeB(std::ofstream& _output_file) const {

    SlvParameterSpec<Tparam>::writeB(value, _output_file);

}

#if OPTION_USE_THIRDPARTY_JSON==1
template <class Tparam>
void SlvParameter<Tparam>::writeJson(nlohmann::json& _json) const {

    SlvParameterSpec<Tparam>::writeJson(value, get_name(), _json);

}

template <class Tparam>
SlvStatus SlvParameter<Tparam>::readJson(const nlohmann::json& _json) {

    Tparam value_ = get_default_value();
    SlvStatus status = SlvParameterSpec<Tparam>::readJson(value_, get_name(), _json);
    set_value(value_);
    return status;

}
#endif

template <class Tparam>
void SlvParameter<Tparam>::istream(std::istream& _is) {

    std::cout << "Enter value of " << get_name() << " (type: " << SlvDataName<Tparam>::name() << ") : ";
    SlvParameterSpec<Tparam>::istream(value, _is);

}

template <class Tparam>
void SlvParameter<Tparam>::ostream(std::ostream& _os) const {

    _os << get_name() << " : ";
    SlvParameterSpec<Tparam>::ostream(value, _os);

}

#define glvm_pv_get_macro_parameter(_1,_2,_3,_4,_5,_6,_7,macro,...) macro
#define glvm_parameter(...) EXPAND( glvm_pv_get_macro_parameter(__VA_ARGS__, glvm_pv_parameter7, glvm_pv_parameter6, glvm_pv_parameter5, glvm_pv_parameter4)(__VA_ARGS__) )//EXPAND because of msvc bug

#define glvm_pv_parameter4(parameter_number, class_name, class_type, parameter_name) \
glvm_pv_parameter5(parameter_number, class_name, class_type, parameter_name, "")

#define glvm_pv_parameter5(parameter_number, class_name, class_type, parameter_name, parameter_description) \
glvm_pv_parameter6(parameter_number, class_name, class_type, parameter_name, parameter_description, class_type())

#define glvm_pv_parameter6(parameter_number, class_name, class_type, parameter_name, parameter_description, _default_value) \
glvm_pv_parameter7(parameter_number, class_name, class_type, parameter_name, parameter_description, _default_value, SlvParameter<class_type>::default_marker_value())

#include "SlvMacroSpecialize.h"

#define TYPE_NULLPTR_T nullptr_t
#define MACSPEC_COMPARE_nullptr_t(x) x
#define IS_TYPE_NULLPTR_T(type) MACSPEC_COMPARE(type, TYPE_NULLPTR_T)

// glvm_pv_parameter_core are common to unruled and ruled parameters

#define glvm_pv_parameter_core1(class_name, class_type, parameter_name, parameter_description, _default_value, marker_value) \
private:\
class SlvPvClassParam_##class_name : public SlvParameter<class_type> {\
public:\
SlvPvClassParam_##class_name(SlvParametrization_base* _parametrization, class_type _value = default_value()):SlvParameter<class_type>(_parametrization, _value){}\
~SlvPvClassParam_##class_name(){}\
virtual SlvPvClassParam_##class_name* clone(SlvParametrization_base* _parametrization) const {\
SlvPvClassParam_##class_name* clone_parameter = new SlvPvClassParam_##class_name(*this);\
clone_parameter->parametrization = _parametrization;\
return clone_parameter;\
}\
private:\
    static std::string parse_parameter_alias_name(const std::string _name) {\
        std::string name = _name;\
        size_t pos = _name.find(SlvParametrization_base::alias_delimiter());\
        if (pos != std::string::npos) {\
            name = _name.substr(0, pos);\
            alias() = _name.substr(pos + SlvParametrization_base::alias_delimiter().size());\
        }\
        return name;\
}\
glvm_staticVariable(, std::string, alias, )\
const std::string& get_alias() const { return alias(); }\
glvm_staticVariable_const_get(std::string, name, parse_parameter_alias_name(parameter_name))\
glvm_staticVariable_const_get(std::string, description, parameter_description)\
glvm_staticVariable_const_get(class_type, default_value, _default_value)\
glvm_staticVariable_const_get(std::vector< SlvParameterRuleT<class_type> >, rules, create_rules())\
unsigned int get_Nrules() const { return (unsigned int)rules().size(); }\
glvm_staticVariable_const_get(unsigned int, marker, marker_value)\
typedef class_type Tparam;

#define glvm_pv_parameter_core2(class_type) \
private:\
void set_stream_value(const std::string& _string, bool _l_param_only) {\
class_type value_tmp(default_value()); SlvParameterSpec<class_type>::parse(value_tmp, _string);\
this->set_value(value_tmp, _l_param_only);\
}\
std::string get_stream_value(bool _l_param_only) const {\
std::ostringstream oss; oss << this->get_value(); return oss.str();\
}\
static std::vector< SlvParameterRuleT<class_type> > create_rules() {\
std::vector< SlvParameterRuleT<class_type> > rules;\

#define glvm_pv_parameter7(parameter_number, class_name, class_type, parameter_name, parameter_description, _default_value, marker_value) \
MACSPEC_IIF(IS_TYPE_NULLPTR_T(class_type))(glvm_pv_parameter7_nullptr_t, glvm_pv_parameter7_general)(parameter_number, class_name, class_type, parameter_name, parameter_description, _default_value, marker_value)

#define glvm_pv_parameter7_parameter(parameter_number, class_name, class_type, parameter_name, parameter_description, _default_value, marker_value) \
glvm_pv_parameter_core1(class_name, class_type, parameter_name, parameter_description, _default_value, marker_value)\
glvm_staticVariable_const_get(bool, has_rules, false)\
glvm_pv_parameter_core2(class_type)\
rules.push_back(SlvParameterRuleT<class_type>());/*default rule*/\
return rules;}\
};

#define glvm_pv_parameter7_nullptr_t(parameter_number, class_name, class_type, parameter_name, parameter_description, _default_value, marker_value) \
private:\
glvm_pv_parameter7_parameter(parameter_number, class_name, class_type, parameter_name, parameter_description, _default_value, marker_value)\
protected:\
typedef SlvPvClassParam_##class_name Tpv_parameter##parameter_number;\
private:

#define glvm_pv_parameter7_general(parameter_number, class_name, class_type, parameter_name, parameter_description, _default_value, marker_value) \
private:\
glvm_pv_parameter7_parameter(parameter_number, class_name, class_type, parameter_name, parameter_description, _default_value, marker_value)\
protected:\
typedef SlvPvClassParam_##class_name Tpv_parameter##parameter_number;\
public:\
const class_type& get_##class_name() const {return this->get_parameter##parameter_number().get_value();}\
void set_##class_name(const class_type& _class_name, bool _l_param_only = true) {\
this->set_parameter##parameter_number##_value(_class_name, _l_param_only);\
}\
static const std::string& get_##class_name##_pname() { return SlvPvClassParam_##class_name::name(); }\
private:


//RULED//
#define glvm_pv_get_macro_parameter_ruled(_1,_2,_3,_4,_5,_6,_7,macro,...) macro
#define glvm_parameter_ruled(...) EXPAND( glvm_pv_get_macro_parameter_ruled(__VA_ARGS__, glvm_pv_parameter_ruled7, glvm_pv_parameter_ruled6, glvm_pv_parameter_ruled5, glvm_pv_parameter_ruled4)(__VA_ARGS__) )//EXPAND because of msvc bug

#define glvm_pv_parameter_ruled4(parameter_number, class_name, class_type, parameter_name) \
glvm_pv_parameter_ruled5(parameter_number, class_name, class_type, parameter_name, "")

#define glvm_pv_parameter_ruled5(parameter_number, class_name, class_type, parameter_name, parameter_description) \
glvm_pv_parameter_ruled6(parameter_number, class_name, class_type, parameter_name, parameter_description, class_type())

#define glvm_pv_parameter_ruled6(parameter_number, class_name, class_type, parameter_name, parameter_description, _default_value) \
glvm_pv_parameter_ruled7(parameter_number, class_name, class_type, parameter_name, parameter_description, _default_value, SlvParameter<class_type>::default_marker_value())

//open macro
#define glvm_pv_parameter_ruled7(parameter_number, class_name, class_type, parameter_name, parameter_description, _default_value, marker_value) \
private:\
class SlvPvClassParam_##class_name;/*forward declaration to let upcoming implementation 'open'*/\
protected:\
typedef SlvPvClassParam_##class_name Tpv_parameter##parameter_number;\
public:\
const class_type& get_##class_name() const {return this->get_parameter##parameter_number().get_value();}\
private:\
void set_##class_name##_unruled_pv(const class_type& _class_name, bool _l_param_only, bool _l_param_init) {\
this->set_parameter##parameter_number##_value(_class_name, _l_param_only);}\
public:\
void set_##class_name##_unruled(const class_type& _class_name, bool _l_param_only = true) { set_##class_name##_unruled_pv(_class_name, _l_param_only, true);}\
static const std::string& get_##class_name##_pname() { return SlvPvClassParam_##class_name::name(); }\
SlvStatus set_##class_name(const class_type& _class_name, bool _l_param_only = true) {\
class_type value_tmp = get_##class_name();\
set_##class_name##_unruled_pv(_class_name, _l_param_only, false);\
SlvStatus status = this->get_parameter##parameter_number().check_rules();\
if (!status) { set_##class_name##_unruled(value_tmp, _l_param_only); }\
return status;\
;}\
glvm_pv_parameter_core1(class_name, class_type, parameter_name, parameter_description, _default_value, marker_value)\
glvm_staticVariable_const_get(bool, has_rules, rules().size() > 1)\
glvm_pv_parameter_core2(class_type)\
rules.push_back(SlvParameterRuleT<Tparam>());

#define glvm_parameter_add_rule(rule_type, rule_value) \
rules.push_back(SlvParameterRuleT<Tparam>(SlvParameterRuleT<Tparam>::rule_type, rule_value));

#define glvm_parameter_end return rules;}};\
private:

/*! Add a dynamic rule linking two parameters. Has to be called in parameterized class's constructor.*/
#define glvm_parameter_addRuleParameter(parameter_name1, type, rule_type, parameter_name2) \
parameter_name1##_parameter().add_dynamic_rule(SlvParameterRuleT<SlvPvClassParam_##parameter_name1::Tparameter>(SlvParameterRuleT<ClassParam_##parameter_name1::Tparameter>::rule_type, &parameter_name2##_parameter()));
