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
class QLineEdit;
class QPushButton;
class QLabel;
class QHBoxLayout;
#include "filestream/SlvDirectory.h"

/*! Widget for selecting a directory.*/
class GlvOpenDirectory : public QWidget {

    Q_OBJECT

private:

    QLineEdit* line_edit;
    QPushButton* push_button;
    QLabel* status;
    /*! Whether a valid directory has been selected or not.*/
    bool l_ready;

public:

    /*! \p _directory : default directory.*/
    GlvOpenDirectory(SlvDirectory _directory, QWidget* _parent = 0);
    /*! \p _default : default directory path.*/
    GlvOpenDirectory(QString _default = "", QWidget* _parent = 0);
    ~GlvOpenDirectory();

    /*! Return directory item. Check if is_ready() before using returned value.*/
    SlvDirectory get_directory() const;

    /*! Whether a valid directory has been selected or not.*/
    bool is_ready() const;
    /*! Makes line edit read-only or not. Shows/hides the open directory button.*/
    void set_editable(bool l_editable);

private:

    /*! Check if directory is valid.*/
    void update_readiness();

public slots:
    /*! Opens QFileDialog to select a directory.*/
    void getExistingDirectory();
    /*! Set directory item by editing QLineEdit. If directory is valid, sets instance as ready.*/
    void set_directory(const SlvDirectory& _directory);

private slots:

    void directory_changed_slot(const QString& _directory_path);

signals:

    /*! Emitted when QLineEdit changes.*/
    void directory_changed(const QString& _directory_path);

};
