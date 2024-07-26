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

#include <QProgressDialog>
class QPushButton;

#include <QtGlobal>
#if QT_VERSION_MAJOR < 6
Q_DECLARE_METATYPE(std::string)
#endif
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
    bool l_auto_hide;

public:

    GlvProgression(GlvProgressMgr* _progress_mgr, SlvProgressionQt* _progression = 0, bool _l_auto_hide = false, QWidget* _parent = 0);
    ~GlvProgression();

    /*! Associate progression to this progress instance.*/
    void set_progression(SlvProgressionQt* _progression);
    /*! Get progression.*/
    const SlvProgressionQt* get_progression() const;

    /*! Whether the progression as reached its maximum or not.*/
    bool is_over() const;

private slots:

    /*! Start/reset GlvProgression. Update QProgressDialog::text with \p _message.
    * Enable or diable Cancel button depending on the attached progression..*/
    void start(std::string _message);
    /*! Auto hide if enabled.*/
    void end();
    /*! Remove progression from GlvProgressMgr.*/
    void final();

private slots:

    void cancel();

};
