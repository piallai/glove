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

#include "SlvStatus.h"
#include "SlvCombo.h"
#include <algorithm>
#include "slv_vector.h"
#include "slv_string.h"

SlvStatus::SlvStatus(statusType _type, std::string _message) {

    status_signals = new std::vector<SlvStatusSignal>;

    push(_type, _message);

}

SlvStatus::SlvStatus(statusType _type, const char* _format, ...) {

    std::va_list args;
    va_start(args, _format);
    std::string string{ slv::string::format_va_list(_format, args) };
    va_end(args);

    status_signals = new std::vector<SlvStatusSignal>;
    push(_type, string);

}

SlvStatus::SlvStatus(const SlvStatus& _status) {

    status_signals = new std::vector<SlvStatusSignal>(*_status.status_signals);

    for (const_iterator_sub it = _status.begin_sub(); it != _status.end_sub(); ++it) {
        add_sub_status(**it);
    }

}


SlvStatus::~SlvStatus() {

    delete status_signals;
    clear_sub_status();

}

void SlvStatus::clear_sub_status() {

    for (const_iterator_sub it = begin_sub(); it != end_sub(); ++it) {
        delete* it;
    }
    sub_status.clear();

}

bool SlvStatus::sortStatusSignal(SlvStatusSignal _signal1, SlvStatusSignal _signal2) {
    return _signal1.value > _signal2.value;
}

void SlvStatus::push(const statusType& _type, const std::string& _message) {

    SlvStatusSignal signal(_message, _type);
    if (!slv::vector::find(signal, *status_signals)) {
        if (status_signals->empty() || _type != statusType::ok) {//do not add multiple 'ok' status
            status_signals->push_back(signal);
        }
        std::sort(status_signals->begin(), status_signals->end(), SlvStatus::sortStatusSignal);
        // Remove 'ok' if more critical signals exist
        if (status_signals->size() > 1 && status_signals->back().value == statusType::ok) {
            status_signals->pop_back();
        }
    }

}

SlvStatus::const_iterator SlvStatus::begin() const {

    return status_signals->begin();

}

SlvStatus::const_iterator SlvStatus::end() const {

    return status_signals->end();

}

SlvStatus::const_iterator_sub SlvStatus::begin_sub() const {

    return sub_status.begin();

}

SlvStatus::const_iterator_sub SlvStatus::end_sub() const {

    return sub_status.end();

}

size_t SlvStatus::size() const {

    return status_signals->size();

}

const SlvStatus::statusType& SlvStatus::get_type() const {

    return get_status_signal().value;
}

const std::string& SlvStatus::get_message() const {

    return get_status_signal().data;

}

const SlvStatus::SlvStatusSignal& SlvStatus::get_status_signal() const {

    if (!has_sub_status()) {
        return (*status_signals)[0];
    } else {
        if ((*status_signals)[0].value > sub_status[0]->get_status_signal().value) {
            return (*status_signals)[0];
        } else {
            return sub_status[0]->get_status_signal();
        }
    }

}

const SlvStatus::statusType& SlvStatus::get_type(const unsigned int i) const {
    return (*status_signals)[i].value;
}

const std::string& SlvStatus::get_message(const unsigned int i) const {
    return (*status_signals)[i].data;
}

SlvStatus::operator bool() const {

    return (get_type() == statusType::ok);
}

SlvStatus& SlvStatus::operator=(const SlvStatus& _status) {

    *status_signals = *_status.status_signals;
    clear_sub_status();

    for (const_iterator_sub it = _status.begin_sub(); it != _status.end_sub(); ++it) {
        add_sub_status(**it);
    }

    return *this;
}

SlvStatus& SlvStatus::operator+=(const SlvStatus& _status) {

    for (unsigned int i = 0; i < _status.size(); i++) {
        push(_status.get_type(i), _status.get_message(i));
    }

    for (const_iterator_sub it = _status.begin_sub(); it != _status.end_sub(); ++it) {
        add_sub_status(**it);
    }

    return *this;
}

size_t SlvStatus::size_sub() const {

    return sub_status.size();

}

bool SlvStatus::has_sub_status() const {

    return !sub_status.empty();

}

const SlvStatus& SlvStatus::get_sub_status(const unsigned int i) const {

    return *sub_status[i];

}

bool SlvStatus::sortStatus(const SlvStatus* _status1, const SlvStatus* _status2) {

    return _status1->get_type() > _status2->get_type();

}

void SlvStatus::add_sub_status(const SlvStatus& _status) {

    if (!_status) {
        sub_status.push_back(new SlvStatus(_status));
    }

    std::sort(sub_status.begin(), sub_status.end(), SlvStatus::sortStatus);

}

void SlvStatus::ostream(std::ostream& _os) const {

    _os << to_string(true);

}

std::string SlvStatus::to_string(bool _l_show_all) const {

    return to_string(_l_show_all, 0);

}

std::string SlvStatus::to_string(bool _l_show_all, int _depth) const {

    std::string message;
    if (!_l_show_all) {
        message = get_message();
    } else {

        std::string indent;
        if (_depth > 0) {
            if (_depth % 2 == 1) indent = "- ";
            else if (_depth % 2 == 0) indent = "* ";
        }

        for (SlvStatus::const_iterator it = begin(); it != end(); ++it) {
            if (it->value != SlvStatus::statusType::ok) {
                message += std::string(_depth * 4, ' ') + indent + slv::string::to_string(it->value) + " : " + it->data.c_str();
                if (std::next(it) != end()) {
                    message += "\n";
                }
            }
        }

        if (has_sub_status()) {
            message += "\n";
        }

        for (SlvStatus::const_iterator_sub it = begin_sub(); it != end_sub(); ++it) {
            message += (*it)->to_string(_l_show_all, _depth + 1);
            if (std::next(it) != end_sub()) {
                message += "\n";
            }
        }

    }

    return message;

}
