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

/*! File to include for GlvItemDelegate.
* Includes both general case and modeled specialization.*/

#include <QLineEdit>
template <class Tdata>
struct GlvLineEdit : public QLineEdit {

};

template <class Tdata, template <class _Tdata, template <class __Tdata> class _Twidget, bool _IsPersistent> class Tview, template <class _Tdata> class Twidget, bool IsPersistent, typename = void>
class GlvItemDelegate;

#include "GlvItemDelegate_spec_General.h"
#include "GlvItemDelegate_spec_Widget.h"
#include "GlvItemDelegate_spec_Modeled.h"
