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
class QGridLayout;
class QLabel;
class GlvParametersWidget_base;

/*! Widget displaying data interface with name and tool tip description.*/
class GlvDescribedWidget_base : public QWidget {

    Q_OBJECT

public :

    /*! Get the name of the data.*/
    const std::string& get_data_name() const;
    /*! Get the secondary name of the data.*/
    std::string get_data_alias() const;
    /*! Get the data widget. Is a GlvWidgetData in general.*/
    virtual QWidget* get_data_widget() const = 0;

protected:

    QGridLayout* layout;
    QLabel* data_name_label;
    QLabel* optional_text_label;

    const std::string data_name;

    GlvDescribedWidget_base(const std::string& _data_name);
    virtual ~GlvDescribedWidget_base();

    /*! Alias related to name (ie: secondary name).*/
    void set_alias(const std::string& _alias);

    /*! Manage display of data type in 'WhatsThis'*/
    virtual void enable_data_type_info(bool _l_enable) = 0;

    void set_data_widget(QWidget* _data_widget, const QString& _optional_text_str);
    /*! \p _data_widget is is added to the instance layout. In case it was set in the layout of GlvParametersWidget (grid).*/
    void reclaim_widgets_ownership(QWidget* _data_widget);

    /*! For grid layout of parameters. Allows external ownership of data_name_label and optional_text.*/
    friend GlvParametersWidget_base;

signals:
    /*! Emits signal when value of widget has changed.*/
    void valueChanged();

};
