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

#include "GlvParametrizationDialog_base.h"
#include "GlvParametrizationWidget.h"

/*! Dialog widget managing parametrization widget.
* Tparametrization is a class inheriting from SlvParametrization.
* Member values not belonging to SlvParametrization are ignored here (constructor values).
* This is the main widget (with GlvParametrizationWidget) to use for parametrization management in the framework.
* Accept : set the parametrization has the one configured by the widget.
* Reject : does not modify the parametrization. */
template <class Tparametrization>
class GlvParametrizationDialog : public GlvParametrizationDialog_base {

private:

    /*! Widget managing SlvParametrization to widget, and vice versa.*/
    GlvParametrizationWidget<Tparametrization>* parametrization_widget;

public:

    /*! \p _parametrization : Initial parametrization.
    * \p _l_dialog: Whether the widget enables QDialog properties or not, such as button box, and related signals.*/
    GlvParametrizationDialog(Tparametrization _parametrization = Tparametrization(), bool _l_dialog = true, QWidget* _parent = NULL);
    GlvParametrizationDialog(bool _l_dialog, QWidget* _parent = NULL);
    GlvParametrizationDialog(QWidget* _parent);
    ~GlvParametrizationDialog();

    /*! Get current parametrization.*/
    const Tparametrization& get_parametrization() const;
    /*! Set parameterization. If \p _l_param_only is true, then only the parameters are set. If false, the whole instance is assigned (not recommended, must be a special case).*/
    void set_parametrization(const Tparametrization& _parametrization, bool _l_param_only = true);

    /*! Get the widget managing the parametrization interface.*/
    GlvParametrizationWidget<Tparametrization>* get_parametrization_widget();

    /*! Apply parametrization widget and check parameters.*/
    SlvStatus apply();

    /*! Apply parametrization widget. QDialog's accept slot only if l_dialog is true.*/
    void accept();
    /*! Reset parametrization widget with current parametrization value. QDialog's reject slot only if l_dialog is true.*/
    void reject();
    /*! Closing the widget means rejection.*/
    void closeEvent(QCloseEvent* _event);

private:

    /*! Update parametrization according to current values contained in parametrization_widget*/
    void update_parametrization();
    /*! Returns true if the parametrization has rules.*/
    bool has_rules();
    /*! Returns false if the rules were not abided, meaning there was a modification of the parametrization*/
    /*! Returns true if rules are abided, meaning there was no modification of the parameterization*/
    bool abide_rules();
    /*! Create a new parametrization instance from the parametrization widget. Deletion must be managed after using this method.*/
    const SlvParametrization_base* new_parametrization_base() const;

};

#include "glv_flag.h"

template <class Tparametrization>
GlvParametrizationDialog<Tparametrization>::GlvParametrizationDialog(Tparametrization _parametrization, bool _l_dialog, QWidget* _parent) :GlvParametrizationDialog_base(_l_dialog, _parent) {

    parametrization_base = new Tparametrization;
    parametrization_widget = new GlvParametrizationWidget<Tparametrization>;
    set_parametrization(_parametrization);

    connect(parametrization_widget, SIGNAL(parameterChanged(std::string)), this, SLOT(parametrizationChanged_slot(std::string)));
    addWidget(parametrization_widget);

    // Rules are actually static, but rtti is needed to access the actual parameters
    enable_abide_rules_button(parametrization_base->has_rules());

}

template <class Tparametrization>
GlvParametrizationDialog<Tparametrization>::GlvParametrizationDialog(bool _l_dialog, QWidget* _parent) :GlvParametrizationDialog(Tparametrization(), _l_dialog, _parent) {

}

template <class Tparametrization>
GlvParametrizationDialog<Tparametrization>::GlvParametrizationDialog(QWidget* _parent) : GlvParametrizationDialog(Tparametrization(), true, _parent) {

}

template <class Tparametrization>
GlvParametrizationDialog<Tparametrization>::~GlvParametrizationDialog() {

}

template <class Tparametrization>
const Tparametrization& GlvParametrizationDialog<Tparametrization>::get_parametrization() const {

    return (*dynamic_cast<Tparametrization*>(parametrization_base));

}

template <class Tparametrization>
void GlvParametrizationDialog<Tparametrization>::set_parametrization(const Tparametrization& _parametrization, bool _l_param_only) {

    if (_l_param_only) {
        dynamic_cast<Tparametrization*>(parametrization_base)->param_assign(_parametrization);
    } else {
        (*dynamic_cast<Tparametrization*>(parametrization_base)) = _parametrization;
    }
    dynamic_cast<GlvParametrizationWidget<Tparametrization>*>(parametrization_widget)->set_parametrization(_parametrization);
    check_parameters_slot();

}

template <class Tparametrization>
void GlvParametrizationDialog<Tparametrization>::update_parametrization() {

    // no param_cast() assignment here because the updated parametrization is supposed to be equal to an instance freshly created
    (*dynamic_cast<Tparametrization*>(parametrization_base)) = dynamic_cast<GlvParametrizationWidget<Tparametrization>*>(parametrization_widget)->get_parametrization();

}

template <class Tparametrization>
bool GlvParametrizationDialog<Tparametrization>::has_rules() {

    return Tparametrization::has_rules();

}

template <class Tparametrization>
bool GlvParametrizationDialog<Tparametrization>::abide_rules() {

    // Update parametrization
    update_parametrization();
    // Abide rules
    bool l_abide = parametrization_base->abide_rules();

    // If rules were not abided (parametrization was modified)
    if (!l_abide) {
        // Assign to widget
        dynamic_cast<GlvParametrizationWidget<Tparametrization>*>(parametrization_widget)->set_parametrization(*dynamic_cast<Tparametrization*>(parametrization_base));
    }

    return l_abide;
}

template <class Tparametrization>
GlvParametrizationWidget<Tparametrization>* GlvParametrizationDialog<Tparametrization>::get_parametrization_widget() {

    return dynamic_cast<GlvParametrizationWidget<Tparametrization>*>(parametrization_widget);

}

template <class Tparametrization>
const SlvParametrization_base* GlvParametrizationDialog<Tparametrization>::new_parametrization_base() const {

    Tparametrization* parametrization = new Tparametrization;
    *parametrization = dynamic_cast<GlvParametrizationWidget<Tparametrization>*>(parametrization_widget)->get_parametrization();
    return parametrization;
}

template <class Tparametrization>
void GlvParametrizationDialog<Tparametrization>::accept() {

    SlvStatus status = apply();

    if (status) {

        if (l_dialog) {
            QDialog::accept();
        }

    }

}

template <class Tparametrization>
void GlvParametrizationDialog<Tparametrization>::reject() {

    // Set previous parametrization
    dynamic_cast<GlvParametrizationWidget<Tparametrization>*>(parametrization_widget)->set_parametrization(*dynamic_cast<Tparametrization*>(parametrization_base));
    if (l_dialog) QDialog::reject();
}

template <class Tparametrization>
SlvStatus GlvParametrizationDialog<Tparametrization>::apply() {

    update_parametrization();

    SlvStatus status = parametrization_base->check_parameters();
    if (!status) {
        glv::flag::showQMessageBox(status, false, this);
    }
    return status;
}


template <class Tparametrization>
void GlvParametrizationDialog<Tparametrization>::closeEvent(QCloseEvent* _event) {

    reject();

}

