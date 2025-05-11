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

#include "GlvParametrizationDialog_base.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include "GlvParametersWidget_base.h"
#include "glv_widget.h"
#include "SlvParametrization_base.h"

GlvParametrizationDialog_base::GlvParametrizationDialog_base(bool _l_dialog, bool _l_deny_invalid_parameters, QWidget* _parent) :QDialog(_parent, Qt::WindowContextHelpButtonHint | Qt::WindowCloseButtonHint) {

    if (_parent) this->setModal(true);

    l_dialog = _l_dialog;
    l_deny_invalid_parameters =_l_deny_invalid_parameters;
    parametrization_base = NULL;

    // To avoid sending message "setGeometry: Unable to set geometry"
    setMinimumSize(10, 10);

    m_layout = new QVBoxLayout;
    m_layout->setSizeConstraint(QLayout::SetMinimumSize);

    if (l_dialog) {
        button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        connect(button_box, SIGNAL(accepted()), this, SLOT(accept()));
        connect(button_box, SIGNAL(rejected()), this, SLOT(reject()));

        abide_rules_button = button_box->addButton(tr("Abide rules"), QDialogButtonBox::ButtonRole::ApplyRole);
        connect(abide_rules_button, SIGNAL(clicked(bool)), this, SLOT(abide_slot()));

        connect(this, SIGNAL(parametrizationChanged(std::string)), this, SLOT(check_parameters_slot()));

        m_layout->addWidget(button_box);
    } else {
        button_box = NULL;
        abide_rules_button = NULL;
    }

    this->setLayout(m_layout);
}

GlvParametrizationDialog_base::~GlvParametrizationDialog_base() {

    delete parametrization_base;

}

void GlvParametrizationDialog_base::enable_abide_rules_button(bool _l_enable) {

    if (abide_rules_button) {
        if (_l_enable) {
            abide_rules_button->show();
        } else {
            abide_rules_button->hide();
        }
    }

}

void GlvParametrizationDialog_base::set_parameters_widget_base(GlvParametersWidget_base* _parameters_widget_base) {

    parameters_widget_base = _parameters_widget_base;
    connect(parameters_widget_base, SIGNAL(heightChanged()), this, SLOT(maximum_height_slot()));

}

void GlvParametrizationDialog_base::parametrizationChanged_slot(std::string _parameter_name) {
    emit parametrizationChanged(_parameter_name);
}

const SlvParametrization_base* GlvParametrizationDialog_base::get_parametrization_base() const {

    return parametrization_base;

}

void GlvParametrizationDialog_base::addWidget(QWidget* _widget) {
    m_layout->insertWidget(m_layout->count() - 1, _widget);
}

void GlvParametrizationDialog_base::abide_slot() {

    bool l_abide_rules = abide_rules();

    if (!l_abide_rules) {
        QMessageBox::warning(this, tr("Abide rules"), tr("Rules have been abided."));
    }

}

void GlvParametrizationDialog_base::check_parameters_slot() {

    if (l_dialog && has_rules()) {
        const SlvParametrization_base* parametrization_tmp = new_parametrization_base();
        SlvStatus status = parametrization_tmp->check_parameters();
        if (status) {
            abide_rules_button->setEnabled(false);
            abide_rules_button->setToolTip(tr("Abide rules of each parameter (exceptions, dependencies..)\nDisabled if the parameterization complies with the rules."));
        } else {
            abide_rules_button->setEnabled(true);
            abide_rules_button->setToolTip(glv::toQString(status.get_message()));
        }

        delete parametrization_tmp;
    }
    
}

void GlvParametrizationDialog_base::resizeEvent(QResizeEvent* _event) {

    if (parameters_widget_base->is_fully_visible()) {
        // !parameters_widget_base->has_height_decreased() : What makes max height to be saved after collapsing a widget
        // maximumHeight() == QWIDGETSIZE_MAX : if no max height is defined yet, ignores the first condition. Useful in case a widghet collpase occured before first max height to be set
        if (!parameters_widget_base->has_height_decreased() || maximumHeight() == QWIDGETSIZE_MAX) {

            int height = parameters_widget_base->size().height();
            height += button_box->size().height();
            height += this->layout()->contentsMargins().top() + this->layout()->contentsMargins().bottom();
            height += m_layout->spacing();
            setMaximumHeight(height);

        }
    }
}

void GlvParametrizationDialog_base::maximum_height_slot() {

    if (!parameters_widget_base->is_fully_visible()) {
        setMaximumHeight(QWIDGETSIZE_MAX);
    }

}
