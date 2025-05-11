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

#include "GlvOpenDirectory.h"
#include "glv_QString.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include "filestream/SlvFileMgr.h"

GlvOpenDirectory::GlvOpenDirectory(SlvDirectory _directory, QWidget* _parent) {

    l_ready = false;

    line_edit = new QLineEdit;
    push_button = new QPushButton(QString(tr("Open directory")));

    QHBoxLayout* layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(line_edit);
    layout->addWidget(push_button);

    this->setLayout(layout);

    connect(push_button, SIGNAL(clicked()), this, SLOT(getExistingDirectory()));
    connect(line_edit, SIGNAL(textChanged(const QString&)), this, SLOT(directory_changed_slot(const QString&)));

    status = new QLabel("Ok");
    status->setToolTip(tr("Does the directory exist."));
    layout->addWidget(status);

    set_directory(_directory);
}

GlvOpenDirectory::GlvOpenDirectory(QString _default, QWidget* _parent) :GlvOpenDirectory(SlvDirectory(_default.toStdString()), _parent) {

}

GlvOpenDirectory::~GlvOpenDirectory() {

}

SlvDirectory GlvOpenDirectory::get_directory() const {

    std::string directory_path = line_edit->text().toStdString();
    if (!directory_path.empty() && directory_path.back() != '/') {
        directory_path.push_back('/');
    }
    SlvDirectory directory(directory_path);
    return directory;

}

void GlvOpenDirectory::set_directory(const SlvDirectory& _directory) {

    QString directory_string = glv::toQString(_directory.get_path());

    QDir directory_dir(directory_string);
#ifdef QT_DIRECTORY_EXISTS
    l_ready = directory_dir.exists();
#else
    l_ready = SlvDirectory(directory_string.toStdString()).exists();
#endif

    line_edit->setText(directory_string);

    directory_changed_slot(line_edit->text());
}

bool GlvOpenDirectory::is_ready() const {

    return l_ready;

}

void GlvOpenDirectory::set_editable(bool l_editable) {

    line_edit->setReadOnly(!l_editable);
    if (l_editable) {
        push_button->show();
    } else {
        push_button->hide();
    }

}

void GlvOpenDirectory::getExistingDirectory() {

    SlvDirectory directory = get_directory();

    QString default_directory_name = QString(SlvFileMgr::get_path(directory).c_str());
    QDir default_directory(default_directory_name);
    QString new_directory_name;
    if (default_directory.exists()) {
        new_directory_name = QFileDialog::getExistingDirectory(this, tr("Open directory"), default_directory_name);
    } else {
        new_directory_name = QFileDialog::getExistingDirectory(this, tr("Open directory"), qApp->applicationDirPath());
    }

    if (!new_directory_name.isEmpty()) {
        QDir new_directory(new_directory_name);
        if (!new_directory.exists()) {
            QMessageBox::information(this, tr("Unable to open directory"), new_directory.path());
        } else {
            l_ready = true;
            if (!new_directory_name.endsWith('/')) {
                new_directory_name.push_back('/');
            }
            line_edit->setText(new_directory_name);
            directory = SlvDirectory(new_directory_name.toStdString());
        }
    }

}

void GlvOpenDirectory::directory_changed_slot(const QString& _directory_path) {

    update_readiness();

    status->setEnabled(l_ready);

    emit directory_changed(_directory_path);

}

void GlvOpenDirectory::update_readiness() {

    QDir directory(line_edit->text());

    l_ready = directory.exists();

}
