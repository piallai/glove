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
class QHBoxLayout;
#include "GlvSaveLoad.h"

class GlvWidget_base : public QWidget, public GlvSaveLoad {

    Q_OBJECT

public:
    class GlvWidgetConnector;

private:

    std::vector<QWidget*> optional_widgets;

protected:

    /*! Main data widget. Is a GlvWidgetData in general, unless there is a GlvWidgetMaker specialization.*/
    QWidget* data_widget;
    QHBoxLayout* layout;
    GlvWidgetConnector* connector;

protected:

    GlvWidget_base(QWidget* _parent = 0);
public:
    virtual ~GlvWidget_base();

    /*! Remove and delete optional widget from layout.
    * Return corresponding iterator in vector of optional widgets.*/
    std::vector<QWidget*>::iterator delete_optional_widget(QWidget* _widget);
    /*! Remove and delete all optional widgets.*/
    void delete_optional_widgets();
    /*! Get the data widget. Is a GlvWidgetData in general.*/
    QWidget* get_data_widget() const;

protected:

    /*! Set save/load widget. Called in GlvParametrizationSaveLoad.*/
    void set_save_load_widget(GlvWidgetSaveLoad_base* _save_load_widget);

    void resizeEvent(QResizeEvent* _resize_event);
    /*! Set data_widget to layout.*/
    void set_widget();

private:

    /*! Add optional widget to layout.
    * Takes ownership of the widget. Caution when deleting the instance.*/
    void add_optional_widget(QWidget* _widget);

    template <class Tvalue>
    friend struct GlvWidgetMaker;

    template <class T>
    friend class GlvWidgetSaveLoad;

signals:
    /*! Emitted whenever the value of the widget has changed.*/
    void valueChanged();
    /*! Emitted whenever the size of the widget has changed.*/
    void sizeChanged();

};
