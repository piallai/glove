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

#include "GlvProgressMgr.h"

#include <QVBoxLayout>
#include <QPushButton>
#include "GlvProgression.h"
#include "glv_widget.h"

GlvProgressMgr::GlvProgressMgr(QWidget* _parent) :QWidget(_parent) {

    m_layout = new QVBoxLayout;
    this->setLayout(m_layout);
    //layout->setSizeConstraint(QLayout::SetFixedSize);

    // Add dummy widget so that when all progressions are being removed, GlvProgressMgr instance is not empty and does not send message "setGeometry: Unable to set geometry"
    QWidget* widget = new QWidget;
    widget->setFixedHeight(2);
    m_layout->addWidget(widget);

}

GlvProgressMgr::~GlvProgressMgr() {

}

GlvProgression* GlvProgressMgr::add_progression(const SlvProgressionQt* _progression, bool _l_hide_when_over) {

    unsigned int i = 0;
    while (i < progressions.size() && _progression != progressions[i]->get_progression()) {
        i++;
    }

    if (i == progressions.size()) {

        GlvProgression* progression = new GlvProgression(this, const_cast<SlvProgressionQt*>(_progression), _l_hide_when_over);
        m_layout->addWidget(progression);
        progressions.push_back(progression);
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

void GlvProgressMgr::setFixedWidth(int _width) {

    for (int i = 0; i < progressions.size(); i++) {
        progressions[i]->setFixedWidth(_width);
    }

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
