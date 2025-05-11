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

#include <QDialog>
class QVBoxLayout;
class QGridLayout;
class QComboBox;
class QLabel;
class QDialogButtonBox;

class GlvListDialog_base : public QDialog {

    Q_OBJECT

protected:

    /*! Whether QDialog functionalities are activated or not (buttons, accept/reject).*/
    bool l_dialog;

    /*! Main layout.*/
    QVBoxLayout* layout;
    QGridLayout* list_layout;

    QLabel* text_widget;
    QLabel* list_name_widget;
    QComboBox* combo_list;
    QDialogButtonBox* button_box;

    /*! \p _parent : If not NULL, then the widget is modal.
    * \p _l_dialog : Whether the list enables QDialog properties or not, such as button box, and related signals.*/
    GlvListDialog_base(QWidget* _parent, bool _l_dialog);
    virtual ~GlvListDialog_base();

public:

    /*! Get combo's current text.*/
    std::string get_currentText();
    /*! Set combo's current index to the one corresponding to \p _name. If \p _name is not found, returns false.*/
    bool set_currentText(const std::string& _name);

    /*! Set descriptive text of the widget.*/
    void set_text(const QString& _text);

    /*! Add \p _widget to the main layout while keeping QDialogButtonBox on the bottom.*/
    void addWidget(QWidget* _widget);

    /*! QDialog's accept slot only if l_dialog is true.*/
    void accept();
    /*! QDialog's reject slot only if l_dialog is true.*/
    void reject();

protected:
    /*! Enables or disables Ok button (if dialog button box is activated).
    * Usefull to clear items which have been filtered by GlvParamListDialog_Filtering.*/
    void setOkButtonEnabled(bool _l_enable);

public slots:

    /*! Enables all items in the QComboBox list.*/
    void enable_combo_items();

};
