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

class QHBoxLayout;
class QLabel;
class QPushButton;

/*! Item widget for GlvMapWidget.*/
class GlvMapWidgetItem_base : public QWidget {

    Q_OBJECT

protected:

    QHBoxLayout* layout;
    /*! Index of the widget in its GlvMapWidget.*/
    unsigned int index;
    QPushButton* remove_button;

    GlvMapWidgetItem_base();
    virtual ~GlvMapWidgetItem_base();

protected slots:

    virtual void remove() = 0;

signals:
    void valueChanged();
};
