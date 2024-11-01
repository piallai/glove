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

/*! Widget to manage easily and directly SlvProgressionQt.
* Closing the widget cancels the managed progressions.*/
class GlvProgressMgr : public QWidget {

    Q_OBJECT

private:

    std::vector<GlvProgression*> progressions;
    QVBoxLayout* m_layout;

    /*! Whether widget will close as soon as possible.*/
    bool l_close;

public:

    GlvProgressMgr(QWidget* _parent = 0);
    ~GlvProgressMgr();

    /*! Add progression. Optional: hide the progression when over. Not recommended if the progression is meant to end and start over (update issue when mouse is not on the widget).*/
    GlvProgression* add_progression(SlvProgressionQt* _progression, bool _l_hide_when_over = false);
    /*! Clear progressions.*/
    void clear();

private:

    void remove_progression(GlvProgression* _progression);

    /*! Check if all progressions are over.*/
    bool is_over() const;

    friend class GlvProgression;

protected:
    /*! Implemented as a workaround to QProgressDialog::setDuration.*/
    void paintEvent(QPaintEvent* _event);
    /*! Cancel progressions.*/
    void closeEvent(QCloseEvent* _event);

public slots:

    /*! Cancel all progressions.*/
    void cancel();

private slots:

    void check_close();

};
