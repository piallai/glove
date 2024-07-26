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

#include "SlvProgressionQt.h"

SlvProgressionQt::SlvProgressionQt(std::string _name) :SlvName(_name) {

	counter = NULL;
	l_was_canceled = false;
}

SlvProgressionQt::~SlvProgressionQt() {

	counter_finish();
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	emit final_signal();
#endif

}

SlvProgressionQt& SlvProgressionQt::operator=(const SlvProgressionQt& _progression) {

	set_name(_progression.get_name());
	return *this;

}

bool SlvProgressionQt::is_over() const {

	if (counter) {
		return is_over(*counter, Ncounter);
	} else {
		return false;
	}

}

bool SlvProgressionQt::has_counter() const {

	return counter;

}

bool SlvProgressionQt::is_over(unsigned int _counter, unsigned int _Ncounter) {

	return _counter >= _Ncounter - 1;

}

void SlvProgressionQt::emit_start(std::string _info) const {

	const_cast<SlvProgressionQt*>(this)->l_was_canceled = false;
	const_cast<SlvProgressionQt*>(this)->counter = NULL;
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	emit const_cast<SlvProgressionQt*>(this)->start_signal(_info);
#endif

}

void SlvProgressionQt::emit_start(std::string _info, unsigned int* _counter, const unsigned int _Ncounter) const {

	const_cast<SlvProgressionQt*>(this)->l_was_canceled = false;
	const_cast<SlvProgressionQt*>(this)->counter = _counter;
	const_cast<SlvProgressionQt*>(this)->Ncounter = _Ncounter;
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	emit const_cast<SlvProgressionQt*>(this)->start_signal(_info);
#endif

}

bool SlvProgressionQt::emit_progress() const {

	if (counter && Ncounter) {
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
		int value = 100 * (*counter + 1) / Ncounter;
		emit const_cast<SlvProgressionQt*>(this)->progress_signal(value);
#endif
		if (is_over()) {
			emit_end();
		}
		return true;
	} else {
		return false;
	}

}

void SlvProgressionQt::emit_progress(int _value) const {

#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	emit const_cast<SlvProgressionQt*>(this)->progress_signal(_value);
#endif
	if (is_over(_value, 100)) {
		emit_end();
	}

}

void SlvProgressionQt::emit_end() const {

	const_cast<SlvProgressionQt*>(this)->counter_finish();
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	emit const_cast<SlvProgressionQt*>(this)->end_signal();
#endif

	const_cast<SlvProgressionQt*>(this)->counter = NULL;
}

void SlvProgressionQt::emit_final() const {

	const_cast<SlvProgressionQt*>(this)->counter_finish();
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	emit const_cast<SlvProgressionQt*>(this)->final_signal();
#endif

	const_cast<SlvProgressionQt*>(this)->counter = NULL;
}

void SlvProgressionQt::cancel() {

	counter_finish();
	l_was_canceled = true;

}

bool SlvProgressionQt::was_canceled() const {

	return l_was_canceled;

}

void SlvProgressionQt::counter_finish() {

	/*! Triggers end of loop. If finished is called when the counter has not reach Ncounter yet, then it sets l_stopped = true. Means the progression has been stopped before then end.*/
	if (counter) {
		if (*counter != Ncounter) {
			*counter = Ncounter;
		}
	}

}
