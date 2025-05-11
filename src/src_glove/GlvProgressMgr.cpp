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

#include "GlvProgressMgr.h"

#include <QVBoxLayout>
#include <QPushButton>
#include "GlvProgression.h"
#include "SlvProgressionQt.h"
#include "glv_widget.h"
#include <QCloseEvent>

GlvProgressMgr::GlvProgressMgr(QWidget* _parent) :QWidget(_parent) {

    m_layout = new QVBoxLayout;
    this->setLayout(m_layout);
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setAlignment(Qt::AlignTop);

    // Add dummy widget so that when all progressions are being removed, GlvProgressMgr instance is not empty and does not send message "setGeometry: Unable to set geometry"
    QWidget* widget = new QWidget;
    widget->setFixedHeight(2);
    m_layout->addWidget(widget, 0, Qt::AlignTop);

    l_close = false;
}

GlvProgressMgr::~GlvProgressMgr() {

}

GlvProgression* GlvProgressMgr::add_progression(SlvProgressionQt* _progression, bool _l_hide_when_over) {

    unsigned int i = 0;
    while (i < progressions.size() && _progression != progressions[i]->get_progression()) {
        i++;
    }

    if (i == progressions.size()) {

        GlvProgression* progression = new GlvProgression(this, _progression, _l_hide_when_over, false);
        progression->setMinimumDuration(0);
        m_layout->addWidget(progression, 0, Qt::AlignTop);
        progressions.push_back(progression);
        if (!progression->is_showable()) {
            progression->hide();
        }
        
        connect(_progression, SIGNAL(ended()), this, SLOT(check_close()));

        return progression;

    } else {

        std::cout << "_progression already exists" << std::endl;
        return progressions[i];

    }

}

void GlvProgressMgr::clear() {

    for (unsigned int i = 0; i < progressions.size(); i++) {
        delete progressions[i];
    }
    progressions.clear();
}

void GlvProgressMgr::remove_progression(GlvProgression* _progression) {

    unsigned int i = 0;
    while (i < progressions.size() && _progression != progressions[i]) {
        i++;
    }

    if (i < progressions.size()) {

        glv::widget::remove_widget(m_layout, progressions[i]);
        progressions.erase(progressions.begin() + i);

    } else {
        std::cout << "This progression index doesn't exist" << std::endl;
    }

}

void GlvProgressMgr::closeEvent(QCloseEvent* _event) {

    cancel();
    l_close = true;

    if (is_over()) {
        QWidget::closeEvent(_event);
    } else {
        _event->ignore();
    }

}

bool GlvProgressMgr::is_over() const {

    bool l_over = true;
    for (std::vector<GlvProgression*>::const_iterator it = progressions.begin(); it != progressions.end(); ++it) {
        if (!(*it)->is_over()) {
            l_over = false;
        }
    }

    return l_over;
}

void GlvProgressMgr::check_close() {

    if (l_close && is_over()) {
        close();
    }

}

void GlvProgressMgr::cancel() {

    for (std::vector<GlvProgression*>::const_iterator it = progressions.begin(); it != progressions.end(); ++it) {

        (*it)->cancel();

    }

}

void GlvProgressMgr::paintEvent(QPaintEvent* _event) {

    int count = 0;
    GlvProgression* hint = NULL;
    int max_width = 0;
    for (int i = 0; i < progressions.size(); i++) {
        if (!progressions[i]->is_showable()) {
            progressions[i]->hide();
        } else if (progressions[i]->isVisible()) {
            count++;
            hint = progressions[i];
            if (progressions[i]->sizeHint().width() > max_width) {
                max_width = progressions[i]->sizeHint().width();
            }
        }
    }

    if (count > 0) {
        int height = hint->sizeHint().height() * count;
        height += layout()->spacing() * (count - 1);
        height += contentsMargins().top() + contentsMargins().bottom();
        height += layout()->itemAt(0)->widget()->height();
        setFixedHeight(height);
        if (minimumWidth() != maximumWidth()) {// If fixed width is not set
            setMinimumWidth(max_width);
        }
    }

}
