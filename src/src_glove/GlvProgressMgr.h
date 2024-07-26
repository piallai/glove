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
#include "std_vector.h"
class GlvProgression;
class SlvProgressionQt;
class QVBoxLayout;

/*! Widget to manage easily and directly SlvProgressionQt.*/
class GlvProgressMgr : public QWidget {

    Q_OBJECT

private:

    std::vector<GlvProgression*> progressions;
    QVBoxLayout* m_layout;

public:

    GlvProgressMgr(QWidget* _parent = 0);
    ~GlvProgressMgr();

    /*! Add progression. Optional: hide the progression when over. Not recommended if the progression is meant to end and start over (update issue when mouse is not on the widget).*/
    GlvProgression* add_progression(const SlvProgressionQt* _progression, bool _l_hide_when_over = false);
    /*! Clear progressions.*/
    void clear();

    /*! Reimplementation to keep every progressions at the same width.*/
    void setFixedWidth(int _width);

private:

    void remove_progression(GlvProgression* _progression);

    friend class GlvProgression;
};
