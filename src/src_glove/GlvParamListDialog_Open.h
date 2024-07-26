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

#include <string>
class GlvParametrizationDialog_base;
class QWidget;

/*! Specialization with Tlist to use dedicated macro. Use by GlvParamListDialog_Open.*/
template <class Tlist>
struct GlvParamListDialog_Open_Spec {
    /*! Creates new GlvParametrizationDialog.
    * Only replace preprocessor macro.
    * Not implemented, just provides method signature.*/
    template <class Toption>
    static bool build_parametrization_templated(GlvParametrizationDialog_base*& _parametrization_dialog, std::string _item_name, const Toption* _option, bool _l_show_parametrization_dialog, QWidget* _parent);
    /*! Creates new GlvParametrizationDialog.
    * Only replace preprocessor macro.
    * Not implemented, just provides method signature.*/
    template <class Toption>
    static GlvParametrizationDialog_base* build_parametrization(std::string _item_name, QWidget* _parent);
    /*! Applies changes to the created parametrization widget.
    * Not implemented, just provides method signature.*/
    template <class Toption>
    static void configuration(GlvParametrizationDialog_base* _parametrization_dialog, std::string _item_name, const Toption* _option);
};

#include "GlvParametrizationDialog.h"//inherited build_parametrization method
#include "SlvParametrization_base.h"

/*! Needs specialization for each Tlist, because a macro in charge of mapping names to types should go with it.*/
template <class Tlist, class Toption = void>
struct GlvParamListDialog_Open {
    /*! Returns true if a new parametrization widget has been created.
    No implementation. Specialization has to be provided to map type names listed into types.
    See provided example: sample003.*/
    static bool open(GlvParametrizationDialog_base*& _parametrization_dialog, const std::string& _parametrization_name, const Toption* _option, bool _l_show_parametrization_dialog, QWidget* _parent) {

        bool l_created = false;

        if (Tlist::is_templated(_parametrization_name)) {

            l_created = GlvParamListDialog_Open_Spec<Tlist>::template build_parametrization_templated<Toption>(_parametrization_dialog, _parametrization_name, _option, _l_show_parametrization_dialog, _parent);

        } else {

            if (_parametrization_dialog && _parametrization_dialog->get_parametrization_base()->get_name() == _parametrization_name) {
                // nothing to do
            } else {
                if (_parametrization_dialog) delete _parametrization_dialog;

                _parametrization_dialog = GlvParamListDialog_Open_Spec<Tlist>::template build_parametrization<Toption>(_parametrization_name, _parent);

                l_created = true;

                GlvParamListDialog_Open_Spec<Tlist>::template configuration<Toption>(_parametrization_dialog, _parametrization_name, _option);
            }

            if (_l_show_parametrization_dialog) {
                _parametrization_dialog->show();
            }

        }

        return l_created;
    }
};
