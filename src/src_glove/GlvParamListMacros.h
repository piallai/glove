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

/*! Used when a list "List" (class_name) is defined, along with its macro: glvm_List_instruction_name_to_type.*/
#define glvm_instruction_base_to_dcast(class_name, instruction_front, parametization_base, instruction_end) \
glvm_##class_name##_instruction_name_to_type(instruction_front dynamic_cast<, parametization_base->get_name(), *>(parametization_base) instruction_end)

/*! Used when a list "List" (class_name) is defined, along with its macro: glvm_List_instruction_name_to_type.*/
#define glvm_instruction_base_to_dcast_const(class_name, instruction_front, parametization_base, instruction_end) \
glvm_##class_name##_instruction_name_to_type(instruction_front dynamic_cast<const, parametization_base->get_name(), *>(parametization_base) instruction_end)
