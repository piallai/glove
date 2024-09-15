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

////////////ACCESSORS/////////////////////////////////

/*! Define an accessor to variable \p name.*/
#define glvm_GetVariable(const, type, name)\
const type& get_##name() const {return name;}
/*! Define a static accessor to variable \p name.*/
#define glvm_staticGetVariable(const, type, name)\
static const type& get_##name() {return name();}
/*! Define an accessor to variable \p name of type bool.*/
#define glvm_GetVariable_bool(name)\
bool is_##name() const {return l_##name;}
/*! Define a static accessor to variable \p name of type bool.*/
#define glvm_staticGetVariable_bool(name)\
static bool is_##name() {return l_##name();}
////////////MODIFIERS/////////////////////////////////
/*! Define an accessor to variable \p name.*/
#define glvm_SetVariable(type, name)\
void set_##name(const type& _arg) {name = _arg;}
/*! Define a static accessor to variable \p name.*/
#define glvm_staticSetVariable(type, name)\
static void set_##name(const type& _arg) {name() = _arg;}
/*! Define an accessor to variable \p name of type bool.*/
#define glvm_SetVariable_bool(name)\
void set_##name(bool _arg) {l_##name = _arg;}
/*! Define a static accessor to variable \p name of type bool.*/
#define glvm_staticSetVariable_bool(name)\
static void set_##name(bool _arg) {l_##name() = _arg;}

////////////BOTH//////////////////////////////////////

/*! Define a variable named \p name and of type \p type with accessors.*/
#define glvm_GetSetVariable(type, name)\
private: type name;\
public: glvm_GetVariable(const, type, name)\
public: glvm_SetVariable(type, name)
/*! Define a variable named \p name and of type bool with accessors.*/
#define glvm_GetSetVariable_bool(name)\
private: bool l_##name;\
public: glvm_GetVariable_bool(name)\
public: glvm_SetVariable_bool(name)

//////////////////////////////////////////////////////
///////////////STATIC/////////////////////////////////
//////////////////////////////////////////////////////

/*! Define a static variable.*/
#define glvm_staticVariable(const, type, name, value)\
static const type& name(){static const type* name = new type(value);return *name;}

#define glvm_staticVariable_def(const, type, name)\
static const type& name();
#define glvm_staticVariable_impl(const, type, encaspulation, name, value)\
const type& encaspulation::name(){static const type* name = new type(value);return *name;}

/*! Define a static variable with static get/set accessors.*/
#define glvm_staticVariableGetSet(type, name, init_value)\
private: glvm_staticVariable(, type, name, init_value)\
public: glvm_staticGetVariable(const, type, name)\
public: glvm_staticSetVariable(type, name)

/*! Define a static variable of type bool with static is/set accessors.*/
#define glvm_staticVariableGetSet_bool(name, init_value)\
private: glvm_staticVariable(, bool, l_##name, init_value)\
public: glvm_staticGetVariable_bool(name)\
public: glvm_staticSetVariable_bool(name)

/*! Same as staticVariable, but with buff suffix to indicate it is a static buffer.*/
#define glvm_staticVariable_buff(type, name, value)\
glvm_staticVariable(, type, name, value)

/*! Define a static variable with a non static accessor.
* Macros are explicitly written because of macro inclusion limitation.*/
#define glvm_staticVariable_const_get(type, name, value)\
public: static const type& name(){static const type* name = new type(value);return *name;}\
public: const type& get_##name() const {return name();}
// Equivalent to:
// public: glvm_staticVariable(, type, name, value)\
// public: glvm_GetVariable(const, type, name)
