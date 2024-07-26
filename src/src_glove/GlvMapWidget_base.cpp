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

#include "GlvMapWidget_base.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include "glv_widget.h"//for make_scrollable
#include <QScrollArea>

GlvMapWidget_base::GlvMapWidget_base(QWidget* _parent) : QWidget(_parent) {

    QString info;

    QWidget* buttons_widget = new QWidget;
    QVBoxLayout* buttons_layout = new QVBoxLayout;
    buttons_widget->setLayout(buttons_layout);
    buttons_widget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    QWidget* insert_widget = new QWidget;
    insert_layout = new QHBoxLayout;
    insert_widget->setLayout(insert_layout);
    button_insert = new QPushButton(tr("Insert"));
    info = QString(tr("Insert an element at the specified key"));
    button_insert->setWhatsThis(info);
    button_insert->setToolTip(info);
    insert_layout->addWidget(button_insert);
    buttons_layout->addWidget(insert_widget);
    buttons_layout->setContentsMargins(0, 9, 0, 0);

    insert_layout->setContentsMargins(0, 0, 0, 0);

    widget_scroll = new QWidget;
    layout_items = new QVBoxLayout;

    widget_scroll->setLayout(layout_items);
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

GlvMapWidget_base::~GlvMapWidget_base() {

}

void GlvMapWidget_base::set_editable(bool l_editable) {
    QWidget::setEnabled(l_editable);
}
