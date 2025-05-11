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

class QLineEdit;
class QPushButton;
class QLabel;
#include <QWidget>
#include <QString>
#include <QIODevice>
#include "filestream/SlvFile.h"

/*! Widget for selecting a file.
* By default the widget is set to manage a file for read only.
* Toggle Read/Write button to change mode.*/
class GlvOpenFile : public QWidget {

    Q_OBJECT

private:

    QLineEdit* line_edit;
    QPushButton* push_button_read;
    QPushButton* push_button_write;
    QPushButton* button_rw;
    SlvFileExtensions allowed_extensions;
    /*! File filter for QFileDialog.*/
    QString file_filter;
    QStringList file_filters;
    QLabel* read_status;
    QLabel* write_status;

    /*! Input/output mode for the widget. Set once at construction.
    * If IO::Any, both read an write are allowed.*/
    const SlvFile::IO io_mode;

    /*! Whether a valid file has been selected or not.*/
    std::map<QIODevice::OpenMode, bool> l_ready;

public:

    /*! \p _file : default file.*/
    GlvOpenFile(SlvFile _file, QWidget* _parent = 0);
    /*! \p _default : default file path.*/
    GlvOpenFile(QString _default = "", QWidget* _parent = 0);
    /*! File filter, description as \p _description and extensions as \p _allowed_extensions/*/
    GlvOpenFile(const std::string& _description, const SlvFileExtensions& _allowed_extensions, QWidget* _parent = 0);
    ~GlvOpenFile();

    /*! Return file instance. Check if is_ready() before using returned value.*/
    SlvFile get_file() const;

    /*! Whether a valid file has been selected or not for mode \p _mode.*/
    bool is_ready(QIODevice::OpenMode _mode) const;
    /*! Makes line edit read-only or not. Shows/hides the open directory button.*/
    void set_editable(bool l_editable);
    /*! Set the file filter for QFileDialog.*/
    void set_file_filter(QString _file_filter = QString(tr("All Files (*)")));

private:

    /*! Return the file filter for QFileDialog based on \p _file properties (allowed extensions, etc).*/
    static QString get_file_filter(const SlvFile& _file);
    static QString get_file_filter(const std::string& _description, const SlvFileExtensions& _allowed_extensions);
    /*! Return separate file filters for QFileDialog based on \p _file allowed extensions.*/
    static QStringList get_file_filters(const SlvFile& _file);


    /*! Check if file instance is ready for read and write.*/
    void update_readiness();

    static bool is_valid_read_file(const QString& _path);
    static bool is_valid_write_file(const QString& _path);

public slots:
    /*! Opens QFileDialog to select a file. Read only. Returns true if a file was selected. Returns false if cancelled.*/
    bool getOpenFileName();
    /*! Opens QFileDialog to select a file. Write only.*/
    void getSaveFileName();
    /*! Set file instance by editing QLineEdit. If file is valid, sets instance as ready.
    * Also set file filter based on the new \p _file.*/
    void set_file(const SlvFile& _file);

    /*! Changes read/write mode.*/
    void change_mode(bool _l_write);

private slots:

    void file_changed_slot(const QString& _file_name);

signals:

    /*! Emitted when QLineEdit changes.*/
    void file_changed(const QString& _file_name);

};
