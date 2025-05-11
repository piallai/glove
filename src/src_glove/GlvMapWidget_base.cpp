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

#include "GlvMapWidget_base.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QScrollArea>
#include <QGroupBox>

GlvMapWidget_base::GlvMapWidget_base(QWidget* _parent) : QWidget(_parent) {

    QString info;

    buttons_widget = new QGroupBox(tr("Size"));
    buttons_widget->setFlat(true);
    buttons_widget->setCheckable(true);
    connect(buttons_widget, SIGNAL(toggled(bool)), this, SLOT(show_map_edit(bool)));
    QVBoxLayout* buttons_layout = new QVBoxLayout;
    buttons_widget->setLayout(buttons_layout);
    buttons_widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    insert_widget = new QWidget;
    insert_layout = new QHBoxLayout;
    insert_widget->setLayout(insert_layout);
    button_insert = new QPushButton(tr("<"));
    button_insert->setFixedWidth(30);
    info = QString(tr("Insert an element at the specified key"));
    button_insert->setWhatsThis(info);
    button_insert->setToolTip(info);
    connect(button_insert, SIGNAL(clicked()), this, SLOT(insertValue()));
    insert_layout->addWidget(button_insert);
    buttons_layout->addWidget(insert_widget);
    buttons_layout->setContentsMargins(0, 3, 0, 0);

    insert_layout->setContentsMargins(0, 0, 0, 0);

    widget_items = new QWidget;
    layout_items = new QVBoxLayout;
    layout_items->setContentsMargins(6, 3, 6, 3);// vertical margin makes checking/unchecking the group box have the same size if content is empty
    widget_items->setLayout(layout_items);

    map_widget = new QGroupBox;
    QVBoxLayout* layout_group = new QVBoxLayout;
    layout_group->setContentsMargins(0, 0, 0, 0);
    layout_group->addWidget(widget_items);
    map_widget->setLayout(layout_group);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(map_widget);
    layout->addWidget(buttons_widget, 0, Qt::AlignTop);
    setLayout(layout);

    layout->setContentsMargins(0, 0, 0, 0);

    set_checkable(false);
    connect(map_widget, SIGNAL(toggled(bool)), this, SLOT(show_map_items(bool)));
    buttons_widget->setChecked(false);

}

GlvMapWidget_base::~GlvMapWidget_base() {

}

void GlvMapWidget_base::set_editable(bool _l_editable) {
    QWidget::setEnabled(_l_editable);
}

void GlvMapWidget_base::set_checkable(bool _l_checkable) {
    map_widget->setCheckable(_l_checkable);
    QString title;
    if (_l_checkable) {
        title = tr("map");
    }
    map_widget->setTitle(title);
}

void GlvMapWidget_base::set_checked(bool _l_checked) {

    map_widget->setChecked(_l_checked);

}

void GlvMapWidget_base::set_items_top_aligment(bool _l_top) {

    if (_l_top) {
        layout_items->setAlignment(Qt::AlignTop);
    } else {
        layout_items->setAlignment(Qt::AlignVCenter);
    }

}

void GlvMapWidget_base::edit_set_checked(bool _l_checked) {

    buttons_widget->setChecked(_l_checked);

}

void GlvMapWidget_base::show_map_items(bool _l_show) {

    widget_items->setVisible(_l_show);

}

void GlvMapWidget_base::show_map_edit(bool _l_show) {

    insert_widget->setVisible(_l_show);

}
