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

#define get_iterator_ptr_value \
iterator_type == IteratorType::Int ? *static_cast<int*>(iterator_ptr) : (\
iterator_type == IteratorType::UnsignedInt ? *static_cast<unsigned int*>(iterator_ptr) : (\
iterator_type == IteratorType::Size_t ? *static_cast<std::size_t*>(iterator_ptr) : (\
0)))
#define assign_iterator_ptr_value(value) \
iterator_type == IteratorType::Int ? *static_cast<int*>(iterator_ptr) = value : (\
iterator_type == IteratorType::UnsignedInt ? *static_cast<unsigned int*>(iterator_ptr) = value : (\
iterator_type == IteratorType::Size_t ? *static_cast<std::size_t*>(iterator_ptr) = value : (\
0)))

SlvProgressionQt::SlvProgressionQt(std::string _name, bool _l_recurrent) :SlvLblName(_name), l_recurrent(_l_recurrent) {

	clear();
}

SlvProgressionQt::SlvProgressionQt(const SlvProgressionQt& _progression) : SlvProgressionQt(_progression.get_name(), _progression.is_recurrent()) {

}

SlvProgressionQt::~SlvProgressionQt() {

	iterator_finish();
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	emit finished();
#endif

}

void SlvProgressionQt::clear() {

	clear_progress();
	message.clear();

}

void SlvProgressionQt::clear_progress() {

	iterator_ptr = NULL;
	l_iterating = false;
	l_was_canceled = false;

	iterator = 0;
	Niterations = 0;
	l_started = false;
	l_no_feedback_ended = false;

}

SlvProgressionQt& SlvProgressionQt::operator=(const SlvProgressionQt& _progression) {

	return *this;

}

void SlvProgressionQt::set_recurrent(bool _l_recurrent) {

	l_recurrent = _l_recurrent;

}

bool SlvProgressionQt::is_recurrent() const {

	return l_recurrent;

}

bool SlvProgressionQt::is_over() const {

	if (l_started) {
		if (iterator_ptr) {
			return is_iterator_ptr_over((unsigned int)(get_iterator_ptr_value), Niterations);
		} else if (l_iterating) {
			return is_iterator_over(iterator, Niterations);
		} else {
			return l_no_feedback_ended;
		}
	} else {
		return true;
	}

}

bool SlvProgressionQt::has_iterator_ptr() const {

	return iterator_ptr;

}

bool SlvProgressionQt::is_iterating() const {

	return l_iterating;

}

bool SlvProgressionQt::is_cancelable() const {

	return Niterations;

}

bool SlvProgressionQt::is_iterator_ptr_over(unsigned int _iterator_value, unsigned int _Niterations) {

	return _iterator_value >= _Niterations - 1;

}

bool SlvProgressionQt::is_iterator_over(std::size_t _iterator, unsigned int _Niterations) {

	return _iterator >= _Niterations;

}

void SlvProgressionQt::start() {

	clear_progress();
	l_started = true;
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	emit started();
#endif

}

void SlvProgressionQt::start(const unsigned int _Niterations) {

	clear_progress();

	start_pv(_Niterations);

}

template <>
void SlvProgressionQt::start(int* _iterator_ptr, const unsigned int _Niterations) {

	iterator_type = IteratorType::Int;

	clear_progress();

	iterator_ptr = _iterator_ptr;
	
	start_pv(_Niterations);

}

template <>
void SlvProgressionQt::start(unsigned int* _iterator_ptr, const unsigned int _Niterations) {

	iterator_type = IteratorType::UnsignedInt;

	clear_progress();

	iterator_ptr = _iterator_ptr;
	
	start_pv(_Niterations);

}

template <>
void SlvProgressionQt::start(std::size_t* _iterator_ptr, const unsigned int _Niterations) {

	iterator_type = IteratorType::Size_t;

	clear_progress();

	iterator_ptr = _iterator_ptr;
	
	start_pv(_Niterations);

}

void SlvProgressionQt::start_pv(const unsigned int _Niterations) {

	l_started = true;
	Niterations = _Niterations;

#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	emit started();
#endif

}

bool SlvProgressionQt::update() {

	if (Niterations) {
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
		int value = -1;
		if (iterator_ptr) {
			value = int(100 * (get_iterator_ptr_value + 1) / Niterations);
		} else if (l_iterating) {
			value = int(100 * (iterator) / Niterations);
		}
		if (value >= 0) {
			emit updated(value);
			if (is_over()) {
				end();
			}
			return true;
		} else {
			return false;
		}
#endif
	} else {
		return false;
	}

}

bool SlvProgressionQt::update(int _value) {

	if (Niterations) {
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
		int value = 100 * (_value + 1) / Niterations;
		if (value >= 0) {
			emit updated(value);
			if (is_iterator_ptr_over(_value, Niterations)) {
				end();
			}
			return true;
		} else {
			return false;
		}
#endif
	} else {
		return false;
	}

}

void SlvProgressionQt::end() {

	l_started = false;

	iterator_finish();
	if (!is_cancelable()) {
		l_no_feedback_ended = true;
	}
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	emit ended();
#endif

	iterator_ptr = NULL;
	l_iterating = false;
	Niterations = 0;

}

void SlvProgressionQt::finish() {

	iterator_finish();
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	emit finished();
#endif

	clear();

}

void SlvProgressionQt::cancel() {

	iterator_finish();
	l_was_canceled = true;

}

bool SlvProgressionQt::was_canceled() const {

	return l_was_canceled;

}

void SlvProgressionQt::iterator_finish() {

	/*! Triggers end of loop. If finished is called when the iterator has not reach Niterations yet, then it sets l_stopped = true. Means the progression has been stopped before then end.*/
	if (iterator_ptr) {
		if (get_iterator_ptr_value != Niterations) {
			assign_iterator_ptr_value(Niterations);
		}
	} else if (l_iterating) {
		if (iterator != Niterations) {
			iterator = Niterations;
		}
	}

}

SlvProgressionQt::operator std::size_t() const {

	return iterator;

}

SlvProgressionQt& SlvProgressionQt::operator=(const std::size_t _iterator) {

	clear_progress();

	l_started = true;

	iterator = _iterator;
	l_iterating = true;

#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	emit started();
#endif
	return *this;
}

bool SlvProgressionQt::operator<<(std::size_t _Niterations) {

	if (l_iterating) {
		Niterations = (unsigned int)_Niterations;
		return iterator < _Niterations;
	} else {
		return false;
	}

}

bool SlvProgressionQt::operator<<(int _Niterations) {

	return *this << std::size_t(_Niterations);

}

bool SlvProgressionQt::operator<<(unsigned int _Niterations) {

	return *this << std::size_t(_Niterations);

}

bool SlvProgressionQt::operator<<=(std::size_t _Niterations) {

	if (l_iterating) {
		Niterations = (unsigned int)(_Niterations - 1);
		return iterator <= _Niterations;
	} else {
		return false;
	}

}

bool SlvProgressionQt::operator<<=(int _Niterations) {

	return *this <<= std::size_t(_Niterations);

}

bool SlvProgressionQt::operator<<=(unsigned int _Niterations) {

	return *this <<= std::size_t(_Niterations);

}

SlvProgressionQt& SlvProgressionQt::operator++() {

	if (l_iterating) {
		++iterator;
		update();
	}
	return *this;
}

SlvProgressionQt SlvProgressionQt::operator++(int) {

	if (l_iterating) {
		iterator++;
		update();
	}
	SlvProgressionQt progression = *this;
	return progression;
}
