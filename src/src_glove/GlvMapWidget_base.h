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

#include <QWidget>
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QGroupBox;

class GlvMapWidget_base : public QWidget {

    Q_OBJECT

private:

    QWidget* widget_items;
    QPushButton* button_insert;
    QWidget* insert_widget;
    QGroupBox* map_widget;

protected:

    QGroupBox* buttons_widget;
    QVBoxLayout* layout_items;
    QHBoxLayout* insert_layout;

    QWidget* insert_key_widget;

    GlvMapWidget_base(QWidget* _parent = 0);
    virtual ~GlvMapWidget_base();

public:

    void set_editable(bool _l_editable);
    /*! Possibility to hide vector elements or not using checkable button.*/
    void set_checkable(bool _l_checkable);
    /*! Show/hide vector elements by collapsing the group box.*/
    void set_checked(bool _l_checked);
    /*! Align vector items to top. Default is false.*/
    void set_items_top_aligment(bool _l_top);

protected :

    /*! To avoid to include QGroupBox in GlvMapWidget*/
    void edit_set_checked(bool l_check);

protected slots:

    virtual void valueChanged_slot() = 0;

private slots:

    virtual void insertValue() = 0;
    void show_map_items(bool _l_show);
    void show_map_edit(bool _l_show);
    
signals:
    /*! Emitted when the value of the \p index-th widget is modified.*/
    void valueChanged(int _index);
};

