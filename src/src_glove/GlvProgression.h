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

#include <QProgressDialog>
class QPushButton;
class SlvProgressionQt;
class GlvProgressMgr;
#include "SlvMacrosDeclarations.h"

/*! Widget managing progress a SlvProgressionQt.*/
class GlvProgression : public QProgressDialog {

    Q_OBJECT

private:

    /*! Watching the instance belongs to.*/
    GlvProgressMgr* progress_mgr;
    SlvProgressionQt* progression;
    QPushButton* cancel_button;

    /*! Automatically hide the progression once ended.*/
    const bool l_auto_hide;
    /*! Show before the progress has started.*/
    const bool l_show_before_start;
    /*! Whether progress has started or not.*/
    bool l_has_started;
    /*! If progress is not cancelable, keep cancel request for end.*/
    bool l_cancel_requested;

public:

    GlvProgression(GlvProgressMgr* _progress_mgr, SlvProgressionQt* _progression = 0, bool _l_auto_hide = false, bool _l_show_before_start = false, QWidget* _parent = 0);
    ~GlvProgression();

    /*! Associate progression to this progress instance.*/
    void set_progression(SlvProgressionQt* _progression);
    /*! Get progression.*/
    const SlvProgressionQt* get_progression() const;

    /*! Whether the progression has reached its maximum or not.*/
    bool is_over() const;

    /*! Whether the progression is showable based on start status or shoability before start.
    * Workaround to manage QProgressDialog::minimumDuration().*/
    bool is_showable() const;

public slots:

    void cancel();

private slots:

    /*! Start/reset GlvProgression.
    * Enable or diable Cancel button depending on the attached progression..*/
    void start();
    /*! Auto hide if enabled.*/
    void end();
    /*! Remove or hide progression from GlvProgressMgr.*/
    void final(bool _l_remove);

};
