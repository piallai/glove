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

#include <QWidget>
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;

class GlvMapWidget_base : public QWidget {

    Q_OBJECT

private:

    QWidget* widget_scroll;
    QPushButton* button_insert;

protected:

    QVBoxLayout* layout_items;
    QHBoxLayout* insert_layout;

    GlvMapWidget_base(QWidget* _parent = 0);
    virtual ~GlvMapWidget_base();

public:

    void set_editable(bool l_editable);

protected slots:

    virtual void valueChanged_slot() = 0;

private slots:

    virtual void insertValue() = 0;

signals:
    /*! Emitted when the value of the \p index-th widget is modified.*/
    void valueChanged(int _index);
};

