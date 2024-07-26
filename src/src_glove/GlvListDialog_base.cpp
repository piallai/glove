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

#include "GlvListDialog_base.h"
#include "glv_QString.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>
#include <QStandardItemModel>
#include <QDialogButtonBox>
#include <QPushButton>

GlvListDialog_base::GlvListDialog_base(QWidget* _parent, bool _l_dialog) :QDialog(_parent) {

    if (_parent) this->setModal(true);

    l_dialog = _l_dialog;

    layout = new QVBoxLayout;

    QWidget* configuration_widget = new QWidget();
    list_layout = new QGridLayout();
    list_layout->setContentsMargins(0, 0, 0, 0);

    text_widget = NULL;

    list_name_widget = new QLabel;
    list_layout->addWidget(list_name_widget, 1, 0);

    combo_list = new QComboBox;;
    list_layout->addWidget(combo_list, 2, 0);

    configuration_widget->setLayout(list_layout);

    layout->addWidget(configuration_widget);

    if (l_dialog) {
        button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        connect(button_box, SIGNAL(accepted()), this, SLOT(accept()));
        connect(button_box, SIGNAL(rejected()), this, SLOT(reject()));
        layout->addWidget(button_box);
    }

    this->setLayout(layout);
}

GlvListDialog_base::~GlvListDialog_base() {

}

void GlvListDialog_base::addWidget(QWidget* _widget) {
    layout->insertWidget(layout->count() - l_dialog, _widget);
}

std::string GlvListDialog_base::get_currentText() {

    return combo_list->currentText().toStdString();
}

bool GlvListDialog_base::set_currentText(const std::string& _name) {

    int index = combo_list->findText(glv::toQString(_name));
    combo_list->setCurrentIndex(index);

    return (index != -1);
}

void GlvListDialog_base::enable_combo_items() {

    for (int i = 0; i < combo_list->count(); i++) {
        qobject_cast<QStandardItemModel*>(combo_list->model())->item(i)->setEnabled(true);
    }

}

void GlvListDialog_base::set_text(const QString& _text) {

    if (!text_widget) {
        text_widget = new QLabel;
        list_layout->addWidget(text_widget, 0, 0);
    }

    text_widget->setText(_text);

}

void GlvListDialog_base::accept() {

    if (l_dialog) QDialog::accept();

}

void GlvListDialog_base::reject() {

    if (l_dialog) QDialog::reject();

}

void GlvListDialog_base::setOkButtonEnabled(bool _l_enable) {

    button_box->button(QDialogButtonBox::Ok)->setEnabled(_l_enable);

}
