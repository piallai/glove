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

#include "GlvProgression.h"

#include "SlvProgression.h"
#include "glv_QString.h"
#include <QThread>
#include <QVBoxLayout>
#include "GlvProgressMgr.h"
#include <QPushButton>

GlvProgression::GlvProgression(GlvProgressMgr* _progress_mgr, SlvProgressionQt* _progression, bool _l_auto_hide, QWidget* _parent) :QProgressDialog(_parent) {

    qRegisterMetaType<std::string>();

    l_auto_hide = _l_auto_hide;
    progress_mgr = _progress_mgr;

    QProgressDialog::setAutoReset(false);
    QProgressDialog::setAutoClose(false);// does not seem to work

    progression = NULL;
    set_progression(_progression);

    cancel_button = new QPushButton(tr("Cancel"));
    QProgressDialog::setCancelButton(cancel_button);
    cancel_button->setEnabled(false);

}

GlvProgression::~GlvProgression() {

}

void GlvProgression::set_progression(SlvProgressionQt* _progression) {

    if (_progression) {

        if (progression) {
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
            progression->disconnect();
#endif
        }

        QProgressDialog::setLabelText(glv::toQString(_progression->get_name()));

        progression = _progression;

#if OPTION_ENABLE_SLV_QT_PROGRESS==1
        connect(progression, SIGNAL(start_signal(std::string)), this, SLOT(start(std::string)));
        // thread safe. In case executed slot doesn't have time to go through.
        connect(progression, SIGNAL(progress_signal(int)), this, SLOT(setValue(int)), Qt::BlockingQueuedConnection);
        connect(progression, SIGNAL(end_signal()), this, SLOT(end()));
        connect(progression, SIGNAL(final_signal()), this, SLOT(final()));
#endif

    }

}

const SlvProgressionQt* GlvProgression::get_progression() const {

    return progression;
}

bool GlvProgression::is_over() const {

    return progression->is_over();
}

void GlvProgression::start(std::string _message) {

    std::string text = progression->get_name();
    if (!text.empty()) {
        text += " : ";
    }
    text += _message;

    QProgressDialog::setLabelText(glv::toQString(text));

    if (progression->has_counter()) {
        cancel_button->setEnabled(true);
        connect(this, SIGNAL(canceled()), this, SLOT(cancel()), Qt::ConnectionType::UniqueConnection);
    } else {
        disconnect(this, SIGNAL(canceled()), this, SLOT(cancel()));
    }

    show();
}

void GlvProgression::end() {

    if (l_auto_hide) {
        hide();
    }

}

void GlvProgression::final() {

    progress_mgr->remove_progression(this);

}

void GlvProgression::cancel() {

    // Since QProgressDialog::cancel() is not virtual, QProgressDialog::canceled() signal will trigger both QProgressDialog::cancel() and GlvProgression::cancel()
    if (!QProgressDialog::wasCanceled()) {
        QProgressDialog::cancel();
    }

    end();
    progression->cancel();

}

