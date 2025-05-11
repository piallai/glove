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
class QPushButton;
class QSpinBox;
class QGroupBox;

class GlvVectorWidget_base : public QWidget {

    Q_OBJECT

private:

    QWidget* widget_items;
    
    QPushButton* button_resize;
    QWidget* pushpop_widget;
    QWidget* insert_widget;
    QWidget* resize_widget;
    QSpinBox* insert_spinbox;
    QGroupBox* vector_group_box;

protected:

    unsigned int Nelements_max;

    QGroupBox* buttons_group_box;
    QVBoxLayout* layout_items;
    QPushButton* button_push;
    QPushButton* button_pop;
    QPushButton* button_insert;
    QSpinBox* resize_spinbox;

    GlvVectorWidget_base(QWidget* _parent = 0);
    virtual ~GlvVectorWidget_base();

public:

    void set_editable(bool _l_editable);
    /*! Possibility to hide vector elements or not using checkable button.*/
    void set_checkable(bool _l_checkable);
    /*! Show/hide vector elements by collapsing the group box.*/
    void set_checked(bool _l_checked);
    /*! Define the maximum number of elements for the vector. Default is 999.*/
    void set_Nelements_max(const unsigned int _N);
    /*! Align vector items to top. Default is false.*/
    void set_items_top_aligment(bool _l_top);

protected slots:

    virtual void valueChanged_slot() = 0;

private slots:

    virtual void pushValue() = 0;
    virtual void popValue() = 0;
    void insertValue();
    virtual void insertValue(const unsigned int i) = 0;
    void resizeVector();
    virtual void resizeVector(const unsigned int i) = 0;

    void show_vector_items(bool _l_show);
    void show_vector_edit(bool _l_show);

signals:
    /*! Emitted when the value of the \p i -th widget is modified.*/
    void valueChanged(int _index);
};
