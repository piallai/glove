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
class QPushButton;
class QSpinBox;

class GlvVectorWidget_base : public QWidget {

    Q_OBJECT

private:

    QWidget* widget_scroll;
    QPushButton* button_push;
    QPushButton* button_insert;
    QSpinBox* index_spinbox;

protected:

    QWidget* buttons_widget;
    QVBoxLayout* layout_items;
    QPushButton* button_pop;

    GlvVectorWidget_base(QWidget* _parent = 0);
    virtual ~GlvVectorWidget_base();

public:

    void set_editable(bool l_editable);

protected slots:

    virtual void valueChanged_slot() = 0;

private slots:

    virtual void pushValue() = 0;
    virtual void popValue() = 0;
    void insertValue();
    virtual void insertValue(const unsigned int i) = 0;

signals:
    /*! Emitted when the value of the \p i -th widget is modified.*/
    void valueChanged(int _index);
};

