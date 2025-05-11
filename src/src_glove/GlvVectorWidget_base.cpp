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

#include "GlvVectorWidget_base.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QScrollArea>
#include <QGroupBox>
#include <QEvent>
#include <QScrollBar>
#include <QApplication>
#include <QStyle>
#include <QScreen>
#include <QResizeEvent>

GlvVectorWidget_base::GlvVectorWidget_base(QWidget* _parent) : QWidget(_parent) {

    QString info;

    buttons_group_box = new QGroupBox(tr("Size"));
    buttons_group_box->setFlat(true);
    buttons_group_box->setCheckable(true);
    connect(buttons_group_box, SIGNAL(toggled(bool)), this, SLOT(show_vector_edit(bool)));
    QVBoxLayout* buttons_group_box_layout = new QVBoxLayout;
    buttons_group_box->setLayout(buttons_group_box_layout);
    buttons_group_box->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    pushpop_widget = new QWidget;
    QHBoxLayout* pushpop_layout = new QHBoxLayout;
    pushpop_layout->setSpacing(3);
    pushpop_widget->setLayout(pushpop_layout);
    button_push = new QPushButton(tr("+"));
    info = QString(tr("Push: add a new element at the end of the vector"));
    button_push->setWhatsThis(info);
    button_push->setToolTip(info);
    pushpop_layout->addWidget(button_push);
    button_pop = new QPushButton(tr("-"));
    button_pop->setEnabled(false);
    info = QString(tr("Pop : remove the element at the end of the vector"));
    button_pop->setWhatsThis(info);
    button_pop->setToolTip(info);
    pushpop_layout->addWidget(button_pop);
    buttons_group_box_layout->addWidget(pushpop_widget);

    insert_widget = new QWidget;
    QHBoxLayout* insert_layout = new QHBoxLayout;
    insert_layout->setSpacing(3);
    insert_widget->setLayout(insert_layout);
    button_insert = new QPushButton(tr("<"));
    info = QString(tr("Insert an element at the specified index"));
    button_insert->setWhatsThis(info);
    button_insert->setToolTip(info);
    insert_layout->addWidget(button_insert);
    insert_spinbox = new QSpinBox;
    insert_spinbox->setMinimum(0);
    info = QString(tr("Index where to insert an element"));
    insert_spinbox->setWhatsThis(info);
    insert_spinbox->setToolTip(info);
    insert_layout->addWidget(insert_spinbox);
    buttons_group_box_layout->addWidget(insert_widget);

    resize_widget = new QWidget;
    QHBoxLayout* resize_layout = new QHBoxLayout;
    resize_layout->setSpacing(3);
    resize_widget->setLayout(resize_layout);
    button_resize = new QPushButton(tr("[]"));
    info = QString(tr("Resize the vector"));
    button_resize->setWhatsThis(info);
    button_resize->setToolTip(info);
    resize_layout->addWidget(button_resize);
    resize_spinbox = new QSpinBox;
    resize_spinbox->setMinimum(0);
    info = QString(tr("Size of the vector"));
    resize_spinbox->setWhatsThis(info);
    resize_spinbox->setToolTip(info);
    resize_layout->addWidget(resize_spinbox);
    buttons_group_box_layout->addWidget(resize_widget);

    buttons_group_box_layout->setSpacing(3);
    buttons_group_box_layout->setContentsMargins(0, 3, 0, 0);

    pushpop_layout->setContentsMargins(0, 0, 0, 0);
    insert_layout->setContentsMargins(0, 0, 0, 0);
    resize_layout->setContentsMargins(0, 0, 0, 0);


    button_push->setFixedWidth(insert_spinbox->sizeHint().width());
    button_pop->setFixedWidth(insert_spinbox->sizeHint().width());
    button_insert->setFixedWidth(insert_spinbox->sizeHint().width());
    button_resize->setFixedWidth(insert_spinbox->sizeHint().width());

    widget_items = new QWidget;
    layout_items = new QVBoxLayout;
    layout_items->setContentsMargins(6, 3, 6, 3);// vertical margin makes checking/unchecking the group box have the same size if content is empty
    widget_items->setLayout(layout_items);

    connect(button_push, SIGNAL(clicked()), this, SLOT(pushValue()));
    connect(button_pop, SIGNAL(clicked()), this, SLOT(popValue()));
    connect(button_insert, SIGNAL(clicked()), this, SLOT(insertValue()));
    connect(button_resize, SIGNAL(clicked()), this, SLOT(resizeVector()));

    vector_group_box = new QGroupBox;
    QVBoxLayout* layout_group = new QVBoxLayout;
    layout_group->setContentsMargins(0, 0, 0, 0);
    layout_group->addWidget(widget_items);
    vector_group_box->setLayout(layout_group);

    vector_group_box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    set_checkable(false);

    connect(vector_group_box, SIGNAL(toggled(bool)), this, SLOT(show_vector_items(bool)));

    buttons_group_box->setChecked(false);

    set_Nelements_max(999);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(vector_group_box);
    layout->addWidget(buttons_group_box, 0, Qt::AlignTop);
    setLayout(layout);

    layout->setContentsMargins(0, 0, 0, 0);
}

GlvVectorWidget_base::~GlvVectorWidget_base() {

}

void GlvVectorWidget_base::set_editable(bool _l_editable) {
    QWidget::setEnabled(_l_editable);
}

void GlvVectorWidget_base::set_checkable(bool _l_checkable) {

    vector_group_box->setCheckable(_l_checkable);
    QString title;
    if (_l_checkable) {
        title = tr("vector");
    }
    vector_group_box->setTitle(title);

}

void GlvVectorWidget_base::set_checked(bool _l_checked) {

    vector_group_box->setChecked(_l_checked);

}

void GlvVectorWidget_base::set_Nelements_max(const unsigned int _N) {

    Nelements_max = _N;

    insert_spinbox->setMaximum(Nelements_max);
    resize_spinbox->setMaximum(Nelements_max);

}

void GlvVectorWidget_base::set_items_top_aligment(bool _l_top) {

    if (_l_top) {
        layout_items->setAlignment(Qt::AlignTop);
    } else {
        layout_items->setAlignment(Qt::AlignVCenter);
    }

}

void GlvVectorWidget_base::insertValue() {

    insertValue(insert_spinbox->value());

}

void GlvVectorWidget_base::resizeVector() {

    resizeVector(resize_spinbox->value());

}

void GlvVectorWidget_base::show_vector_items(bool _l_show) {

    widget_items->setVisible(_l_show);

}

void GlvVectorWidget_base::show_vector_edit(bool _l_show) {

    pushpop_widget->setVisible(_l_show);
    insert_widget->setVisible(_l_show);
    resize_widget->setVisible(_l_show);

}
