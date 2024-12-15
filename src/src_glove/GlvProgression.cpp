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
#include <QVBoxLayout>
#include "GlvProgressMgr.h"
#include <QPushButton>
#include <QProgressBar>

GlvProgression::GlvProgression(GlvProgressMgr* _progress_mgr, SlvProgressionQt* _progression, bool _l_auto_hide, bool _l_show_before_start, QWidget* _parent) :QProgressDialog(_parent), l_auto_hide(_l_auto_hide), l_show_before_start(_l_show_before_start) {
    
    setValue(0);
    setMaximum(100);

    l_has_started = false;
    l_cancel_requested = false;

    progress_mgr = _progress_mgr;

    QProgressDialog::setAutoReset(false);
    QProgressDialog::setAutoClose(false);

    progression = NULL;
    set_progression(_progression);

    cancel_button = new QPushButton(tr("Cancel"));
    QProgressDialog::setCancelButton(cancel_button);
    cancel_button->setEnabled(false);

    setSizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::MinimumExpanding);

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
        connect(progression, SIGNAL(started()), this, SLOT(start()));
        // thread safe. In case executed slot doesn't have time to go through.
        connect(progression, SIGNAL(updated(int)), this, SLOT(setValue(int)), Qt::BlockingQueuedConnection);
        connect(progression, SIGNAL(ended()), this, SLOT(end()));
        connect(progression, SIGNAL(finished(bool)), this, SLOT(final(bool)));
#endif

    }

}

const SlvProgressionQt* GlvProgression::get_progression() const {

    return progression;
}

bool GlvProgression::is_showable() const {

    return l_has_started || l_show_before_start;

}

bool GlvProgression::is_over() const {

    return progression->is_over();
}

void GlvProgression::start() {

    QProgressDialog::reset();//to reset wasCanceled
    setValue(0);

    l_has_started = true;

    std::string text = progression->get_name();
    if (!text.empty() && !progression->get_message().empty()) {
        text += " : ";
    }
    // Update QProgressDialog::text with message.
    text += progression->get_message();

    QProgressDialog::setLabelText(glv::toQString(text));

    if (progression->has_iterator_ptr() || progression->is_iterating()) {
        cancel_button->setEnabled(true);
        setMaximum(100);
        connect(this, SIGNAL(canceled()), this, SLOT(cancel()), Qt::ConnectionType::UniqueConnection);
    } else {
        cancel_button->hide();
        setMaximum(0);
        findChild<QProgressBar*>()->setTextVisible(false);
        disconnect(this, SIGNAL(canceled()), this, SLOT(cancel()));
    }

    show();
}

void GlvProgression::end() {

    if (!QProgressDialog::wasCanceled() && l_cancel_requested) {
        QProgressDialog::cancel();
        l_cancel_requested = false;
    }

    if (l_auto_hide) {
        hide();
    }

}

void GlvProgression::final(bool _l_remove) {

    if (_l_remove) {
        progress_mgr->remove_progression(this);
    } else {
        hide();
    }

}

void GlvProgression::cancel() {

    // Since QProgressDialog::cancel() is not virtual, QProgressDialog::canceled() signal will trigger both QProgressDialog::cancel() and GlvProgression::cancel()
    if (!QProgressDialog::wasCanceled()) {
        if (progression->is_cancelable()) {// if control on progress is possible
            QProgressDialog::cancel();
            end();
        } else {
            l_cancel_requested = true;
        }
    }
    
    progression->cancel();

}

