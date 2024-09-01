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

#include "GlvOpenFile.h"
#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include "glv_QString.h"
#include "filestream/SlvFileMgr.h"
#include <QLabel>

GlvOpenFile::GlvOpenFile(SlvFile _file, QWidget* _parent) :io_mode(_file.get_io_mode()) {

    l_ready[QIODevice::ReadOnly] = false;
    l_ready[QIODevice::WriteOnly] = false;

    allowed_extensions = _file.get_allowed_extensions();
    set_file_filter(get_file_filter(_file));

    line_edit = new QLineEdit;
    push_button_read = new QPushButton(QString(tr("Open")));
    push_button_read->setToolTip(tr("Select existing file"));
    push_button_write = new QPushButton(QString(tr("Open")));
    push_button_write->setToolTip(tr("Enter file location"));
    push_button_write->hide();

    button_rw = new QPushButton("Read");
    button_rw->setCheckable(true);
    button_rw->setToolTip(tr("Toggle to change read/write mode."));

    QHBoxLayout* layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(line_edit);
    layout->addWidget(push_button_read);
    layout->addWidget(push_button_write);
    layout->addWidget(button_rw);

    this->setLayout(layout);

    connect(push_button_read, SIGNAL(clicked()), this, SLOT(getOpenFileName()));
    connect(push_button_write, SIGNAL(clicked()), this, SLOT(getSaveFileName()));
    connect(button_rw, SIGNAL(toggled(bool)), this, SLOT(change_mode(bool)));
    connect(line_edit, SIGNAL(textChanged(const QString&)), this, SLOT(file_changed_slot(const QString&)));

    read_status = new QLabel("Ok");
    read_status->setToolTip(tr("Is the file valid for reading."));
    layout->addWidget(read_status);
    write_status = new QLabel("Ok");
    write_status->setToolTip(tr("Is the file valid for writing."));
    layout->addWidget(write_status);
    write_status->hide();

    set_file(_file);

    if (io_mode == SlvFile::IO::Read) {
        button_rw->setChecked(false);//not necessary theoretically
        button_rw->hide();
    } else if (io_mode == SlvFile::IO::Write) {
        button_rw->setChecked(true);
        button_rw->hide();
    }

}

GlvOpenFile::GlvOpenFile(QString _default, QWidget* _parent) :GlvOpenFile(SlvFile(_default.toStdString()), _parent) {

}

GlvOpenFile::GlvOpenFile(const std::string& _description, const SlvFileExtensions& _allowed_extensions, QWidget* _parent) :GlvOpenFile(SlvFile(_description, _allowed_extensions), _parent) {

}

GlvOpenFile::~GlvOpenFile() {

}

SlvFile GlvOpenFile::get_file() const {

    SlvFile file(line_edit->text().toStdString(), io_mode);
    file.add_allowed_extensions(allowed_extensions);
    return file;
}

void GlvOpenFile::set_file(const SlvFile& _file) {

    file_filter = get_file_filter(_file);
    file_filters = get_file_filters(_file);

    QString file_string = glv::toQString(_file.get_path());

    line_edit->setText(file_string);

    file_changed_slot(line_edit->text());

}

void GlvOpenFile::update_readiness() {

    l_ready[QIODevice::ReadOnly] = is_valid_read_file(line_edit->text());
    l_ready[QIODevice::WriteOnly] = is_valid_write_file(line_edit->text());

}

bool GlvOpenFile::is_valid_read_file(const QString& _path) {

#ifdef QT_FILE_EXISTS
    QFileInfo file_info(_path);
    return file_info.exists() && file_info.isFile();
#else
    return SlvFile(_path.toStdString()).exists();
#endif

}

bool GlvOpenFile::is_valid_write_file(const QString& _path) {

    QFileInfo file_info(_path);
    return file_info.absoluteDir().exists() && !file_info.fileName().isEmpty() && QFileInfo(file_info.absoluteDir().path()).isWritable();

}

bool GlvOpenFile::is_ready(QIODevice::OpenMode _mode) const {

    return l_ready.at(_mode);

}

void GlvOpenFile::set_editable(bool l_editable) {

    line_edit->setReadOnly(!l_editable);
    if (l_editable) {
        if (button_rw->isChecked()) {
            push_button_write->show();
        } else {
            push_button_read->show();
        }
    } else {
        push_button_read->hide();
        push_button_write->hide();
    }

}

void GlvOpenFile::set_file_filter(QString _file_filter) {

    if (_file_filter == QString("*")) {
        set_file_filter();
    } else {
        file_filter = _file_filter;
    }

}

QString GlvOpenFile::get_file_filter(const SlvFile& _file) {

    return get_file_filter(_file.get_description(), _file.get_allowed_extensions());
}

QString GlvOpenFile::get_file_filter(const std::string& _description, const SlvFileExtensions& _allowed_extensions) {

    QString file_filter;
    if (_description.size() > 0) {
        file_filter += QString(_description.c_str()) + " (";
    }
    if (_allowed_extensions.get().size() > 0) {
        for (unsigned int i_ext = 0; i_ext < _allowed_extensions.get().size(); i_ext++) {
            file_filter += "*" + QString(_allowed_extensions.get()[i_ext].c_str()) + " ";
        }
    } else {
        file_filter += "*";
    }
    if (_description.size() > 0) {
        file_filter += ")";
    }

    return file_filter;

}

QStringList GlvOpenFile::get_file_filters(const SlvFile& _file) {

    QStringList file_filters;

    SlvFileExtensions allowed_extensions = _file.get_allowed_extensions();

    for (std::vector<SlvFileExtension>::const_iterator it = allowed_extensions.get().begin(); it != allowed_extensions.get().end(); ++it) {
        file_filters.push_back(glv::toQString(*it));
    }

    return file_filters;
}

bool GlvOpenFile::getOpenFileName() {


    SlvFile file = get_file();

    QString default_file_name = QString(SlvFileMgr::get_path(file).c_str());
    QFile default_file(default_file_name);
    QString file_name;
    if (default_file.open(QIODevice::ReadOnly)) {
        file_name = QFileDialog::getOpenFileName(this, tr("Open file"), default_file_name, file_filter);
    } else {

        QString default_directory_name = QString(SlvFileMgr::get_path(file.get_directory()).c_str());
        QDir default_directory(default_directory_name);
        if (default_directory.exists()) {
            file_name = QFileDialog::getOpenFileName(this, tr("Open file"), default_directory_name, file_filter);
        } else {
            file_name = QFileDialog::getOpenFileName(this, tr("Open file"), qApp->applicationDirPath(), file_filter);
        }

    }

    if (!file_name.isNull()) {
        QFile qfile(file_name);
        if (!qfile.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"), qfile.errorString());
            return false;
        } else {
            l_ready[QIODevice::ReadOnly] = true;
            line_edit->setText(file_name);
            qfile.close();
            return true;
        }
    } else {
        return false;
    }

}

void GlvOpenFile::getSaveFileName() {

    QString default_directory_name = QString(SlvFileMgr::get_path(get_file().get_directory()).c_str());
    QDir default_directory(default_directory_name);
    QString file_name;
    QFileDialog file_dialog;
    file_dialog.setFileMode(QFileDialog::FileMode::AnyFile);
    file_dialog.setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
    file_dialog.setNameFilter(file_filter);
    if (!allowed_extensions.empty()) {
        file_dialog.setDefaultSuffix(glv::toQString(allowed_extensions[0]));
    }

    if (default_directory.exists()) {
        std::string file_path = SlvFileMgr::get_path(get_file());
        if (file_path == "./") {// convert empty path
            file_path = "";
        }
        file_dialog.setDirectory(glv::toQString(file_path));
    } else {
        file_dialog.setDirectory(qApp->applicationDirPath());
    }

    if (file_dialog.exec() == QDialog::Accepted) {
        file_name = file_dialog.selectedFiles().front();
        if (!file_name.isNull()) {
            if (is_valid_write_file(file_name)) {
                l_ready[QIODevice::WriteOnly] = true;
                line_edit->setText(file_name);
            } else {
                QMessageBox::information(this, tr("Unable to open file"), tr("Invalid file : ") + file_name);
            }
        }
    }



}

void GlvOpenFile::file_changed_slot(const QString& _file_name) {

    update_readiness();

    read_status->setEnabled(l_ready.at(QIODevice::ReadOnly));
    write_status->setEnabled(l_ready.at(QIODevice::WriteOnly));

    emit file_changed(_file_name);

}

void GlvOpenFile::change_mode(bool _l_write) {

    if (_l_write) {
        button_rw->setText(tr("Write"));
        push_button_read->hide();
        read_status->hide();
        push_button_write->show();
        write_status->show();
    } else {
        button_rw->setText(tr("Read"));
        push_button_write->hide();
        write_status->hide();
        push_button_read->show();
        read_status->show();
    }

}
