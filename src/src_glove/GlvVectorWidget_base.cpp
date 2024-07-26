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

#include "GlvVectorWidget_base.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include "glv_widget.h"//for make_scrollable
#include <QScrollArea>

GlvVectorWidget_base::GlvVectorWidget_base(QWidget* _parent) : QWidget(_parent) {

    QString info;

    buttons_widget = new QWidget;
    QVBoxLayout* buttons_layout = new QVBoxLayout;
    buttons_widget->setLayout(buttons_layout);
    buttons_widget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    QWidget* pushpop_widget = new QWidget;
    QHBoxLayout* pushpop_layout = new QHBoxLayout;
    pushpop_widget->setLayout(pushpop_layout);
    button_push = new QPushButton(tr("Push"));
    info = QString(tr("Add a new element at the end of the vector"));
    button_push->setWhatsThis(info);
    button_push->setToolTip(info);
    pushpop_layout->addWidget(button_push);
    button_pop = new QPushButton(tr("Pop"));
    button_pop->setEnabled(false);
    info = QString(tr("Remove the element at the end of the vector"));
    button_pop->setWhatsThis(info);
    button_pop->setToolTip(info);
    pushpop_layout->addWidget(button_pop);
    buttons_layout->addWidget(pushpop_widget);

    QWidget* insert_widget = new QWidget;
    QHBoxLayout* insert_layout = new QHBoxLayout;
    insert_widget->setLayout(insert_layout);
    button_insert = new QPushButton(tr("Insert"));
    info = QString(tr("Insert an element at the specified index"));
    button_insert->setWhatsThis(info);
    button_insert->setToolTip(info);
    insert_layout->addWidget(button_insert);
    index_spinbox = new QSpinBox;
    info = QString(tr("Index where to insert an element"));
    index_spinbox->setWhatsThis(info);
    index_spinbox->setToolTip(info);
    insert_layout->addWidget(index_spinbox);
    buttons_layout->addWidget(insert_widget);
    buttons_layout->setContentsMargins(0, 9, 0, 0);

    pushpop_layout->setContentsMargins(0, 0, 0, 0);
    insert_layout->setContentsMargins(0, 0, 0, 0);

    index_spinbox->setMinimum(0);

    widget_scroll = new QWidget;
    layout_items = new QVBoxLayout;

    widget_scroll->setLayout(layout_items);
    connect(button_push, SIGNAL(clicked()), this, SLOT(pushValue()));
    connect(button_pop, SIGNAL(clicked()), this, SLOT(popValue()));
    connect(button_insert, SIGNAL(clicked()), this, SLOT(insertValue()));

    QWidget* widget_vector = new QWidget;
    QScrollArea* scroll_area = glv::widget::make_scrollable(widget_scroll, widget_vector);
    scroll_area->setFrameShape(QFrame::Panel);
    widget_vector->layout()->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(widget_vector);
    layout->addWidget(buttons_widget, 0, Qt::AlignTop);
    setLayout(layout);

    layout->setContentsMargins(0, 0, 0, 0);
}

GlvVectorWidget_base::~GlvVectorWidget_base() {

}

void GlvVectorWidget_base::set_editable(bool l_editable) {
    QWidget::setEnabled(l_editable);
}

void GlvVectorWidget_base::insertValue() {

    insertValue(index_spinbox->value());

}