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

class SlvParametrization_base;
#include "SlvStatus.h"
#include <QDialog>
class QDialogButtonBox;
class QVBoxLayout;
class GlvParametersWidget_base;
class QPushButton;

/*! Dialog widget managing parametrization widget.
* This is the main widget (with GlvParametrizationWidget) to use for parametrization management in the framework.
* Accept : set the parametrization has the one configured by the widget.
* Reject : does not modify the parametrization. */
class GlvParametrizationDialog_base : public QDialog {

    Q_OBJECT

protected:

    QDialogButtonBox* button_box;
    QPushButton* abide_rules_button;
    bool l_dialog;//whether has buttons. if so, parent's activation depends on "this" state. Also QDialog::accept/reject is activated
    SlvParametrization_base* parametrization_base;//usefull to cast to correct child type (see macros)
    QVBoxLayout* m_layout;

    GlvParametrizationDialog_base(bool _l_dialog, QWidget* _parent);
public:
    virtual ~GlvParametrizationDialog_base();

    /*! Returns base pointer to the stored parameterization, so it can be casted to the real parametrization provided its type is known.*/
    const SlvParametrization_base* get_parametrization_base() const;
    void addWidget(QWidget* _widget);

    /*! Show or hide the button controlling rules complying, next to 'Ok' and 'Cancel'.*/
    void enable_abide_rules_button(bool _l_enable);

public slots:
    /*! Apply parametrization widget. QDialog's accept slot only if l_dialog is true.*/
    virtual void accept() = 0;
    /*! Reset parametrization widget with current parametrization value. QDialog's reject slot only if l_dialog is true.*/
    virtual void reject() = 0;
    /*! Apply parametrization widget and check parameters.*/
    virtual SlvStatus apply() = 0;

private slots:
    /*! Update parametrization according to current values contained in parametrization_widget*/
    virtual void update_parametrization() = 0;
    void parametrizationChanged_slot(std::string _parameter_name);
    void abide_slot();
protected slots:
    // Check parameters by updating parametrization before
    void check_parameters_slot();
signals:
    void parametrizationChanged(std::string _parameter_name);

private:
    /*! Returns true if the parametrization has rules.*/
    virtual bool has_rules() = 0;
    virtual bool abide_rules() = 0;
    virtual const SlvParametrization_base* new_parametrization_base() const = 0;

};
