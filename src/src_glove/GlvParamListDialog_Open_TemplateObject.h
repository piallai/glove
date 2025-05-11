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

#include "GlvListDialogTlist.h"
#include "GlvParametrizationDialog.h"

template <class Tbase, class Tsublist, class Toption>
class GlvParamListDialog_Open_TemplateObject;

/*! Specialization with Tlist to use dedicated macro. Use by GlvParamListDialog_Open_TemplateObject.*/
template <class Tsublist>
struct GlvParamListDialog_Open_TemplateObject_Spec {
    template <class Tbase, class Toption>
    static bool build_parametrization_templated(GlvParametrizationDialog_base*& _configure_window, std::string _item_name, const Toption* _option, bool _l_show, QWidget* _parent);
    /*! Calls and return GlvParamListDialog_Open_TemplateObject::cast_check.
    * Only replace preprocessor macro.
    * Not implemented, just provides method signature.*/
    template <class Tbase, class Toption>
    static GlvParametrizationDialog_base* cast_check(std::string _item_name, const GlvParamListDialog_Open_TemplateObject<Tbase, Tsublist, Toption>* _list);
    /*! Creates new GlvParametrizationDialog.
    * Only replace preprocessor macro.
    * Not implemented, just provides method signature.*/
    template <class Tbase, class Toption>
    static GlvParametrizationDialog_base* build_parametrization(std::string _item_name, QWidget* _parent);
    /*! Applies changes to the created parametrization widget.
    * Not implemented, just provides method signature.*/
    template <class Tbase, class Toption>
    static void configuration(std::string _item_name, const GlvParamListDialog_Open_TemplateObject<Tbase, Tsublist, Toption>* _list);
};


/*! List to select the type among Tsublist.
Tbase: base type of the template object. Tbase::Tderived<Telement, Toption> to be the 'real' type.*/
template <class Tbase, class Tsublist, class Toption>
class GlvParamListDialog_Open_TemplateObject : public GlvListDialogTlist<Tsublist> {

private:
    /*! Pointer to the reference parametrization widget.*/
    GlvParametrizationDialog_base*& parametrization_dialog;
    /*! Whether the parametrization widget is shown or not.*/
    const bool l_show_parametrization_dialog;
    /*! Option.*/
    const Toption* option;
public:
    /*! Whether a parametrization widget has been created or not.*/
    bool l_created = false;
public:
    GlvParamListDialog_Open_TemplateObject(QWidget* _parent, GlvParametrizationDialog_base*& _parametrization_dialog, const Toption* _option, bool _l_show_parametrization_dialog);
    ~GlvParamListDialog_Open_TemplateObject();

    /*! Casts parametrization widget with a type (Targ) of the list.*/
    template <class Targ>
    GlvParametrizationDialog_base* cast_check() const;

    /*! Rejects QDialog and sets parametrization widget creation status to false.*/
    void reject();
    /*! Accepts the selected type of the list, and creates the parametrization widget.
    * Sets parametrization widget creation status to true.*/
    void accept();

    friend struct GlvParamListDialog_Open_TemplateObject_Spec<Tsublist>;
};

template <class Tbase, class Tsublist, class Toption>
GlvParamListDialog_Open_TemplateObject<Tbase, Tsublist, Toption>::GlvParamListDialog_Open_TemplateObject(QWidget* _parent, GlvParametrizationDialog_base*& _parametrization_dialog, const Toption* _option, bool _l_show_parametrization_dialog)
    :GlvListDialogTlist<Tsublist>(_parent), parametrization_dialog(_parametrization_dialog), l_show_parametrization_dialog(_l_show_parametrization_dialog) {

    option = _option;
}

template <class Tbase, class Tsublist, class Toption>
GlvParamListDialog_Open_TemplateObject<Tbase, Tsublist, Toption>::~GlvParamListDialog_Open_TemplateObject() {}

template <class Tbase, class Tsublist, class Toption>
template <class Targ>
GlvParametrizationDialog_base* GlvParamListDialog_Open_TemplateObject<Tbase, Tsublist, Toption>::cast_check() const {

    GlvParametrizationDialog_base* parametrization_dialog_cast_check;
    parametrization_dialog_cast_check = dynamic_cast<GlvParametrizationDialog<typename Tbase::template Tderived<Targ, Toption> >*>(parametrization_dialog);

    return parametrization_dialog_cast_check;
}

template <class Tbase, class Tsublist, class Toption>
void GlvParamListDialog_Open_TemplateObject<Tbase, Tsublist, Toption>::reject() {
    GlvListDialogTlist<Tsublist>::reject();

    l_created = false;
}

template <class Tbase, class Tsublist, class Toption>
void GlvParamListDialog_Open_TemplateObject<Tbase, Tsublist, Toption>::accept() {

    l_created = false;

    GlvListDialogTlist<Tsublist>::accept();
    std::string item_name = this->get_currentText();

    if (Tsublist::is_templated(item_name)) {

        l_created = GlvParamListDialog_Open_TemplateObject_Spec<Tsublist>::template build_parametrization_templated<Tbase, Toption>(parametrization_dialog, item_name, option, l_show_parametrization_dialog, this);

    } else {

        GlvParametrizationDialog_base* parametrization_dialog_cast_check;

        parametrization_dialog_cast_check = GlvParamListDialog_Open_TemplateObject_Spec<Tsublist>::template cast_check<Tbase, Toption>(item_name, this);

        if (parametrization_dialog_cast_check) {
            //means that parametrization type hasn't change from previously created parametrization_dialog

        } else {
            //means that parametrization type has changed, or simply that there was no parametrization_dialog created yet

            if (parametrization_dialog) {
                delete parametrization_dialog;
            }

            parametrization_dialog = GlvParamListDialog_Open_TemplateObject_Spec<Tsublist>::template build_parametrization<Tbase, Toption>(item_name, this->parentWidget());

            l_created = true;

            GlvParamListDialog_Open_TemplateObject_Spec<Tsublist>::configuration(item_name, this);

        }

        if (l_show_parametrization_dialog) parametrization_dialog->show();

    }

}

