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

SlvStatus::SlvStatus(statusType _type, std::string _message) {

    status_signals = new std::vector<SlvStatusSignal>;

    push(_type, _message);

}

SlvStatus::SlvStatus(const SlvStatus& _status) {

    status_signals = new std::vector<SlvStatusSignal>(*_status.status_signals);

}


SlvStatus::~SlvStatus() {

    delete status_signals;

}

bool SlvStatus::sortStatus(SlvStatusSignal _signal1, SlvStatusSignal _signal2) {
    return _signal1.value > _signal2.value;
}

void SlvStatus::push(const statusType& _type, const std::string& _message) {

    SlvStatusSignal signal(_message, _type);
    if (!slv::vector::find(signal, *status_signals)) {
        if (status_signals->empty() || _type != statusType::ok) {//do not add multiple 'ok' status
            status_signals->push_back(signal);
        }
        std::sort(status_signals->begin(), status_signals->end(), SlvStatus::sortStatus);
        // Remove 'ok' if more relevant signals exist
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

size_t SlvStatus::size() const {
    return status_signals->size();
}

const SlvStatus::statusType& SlvStatus::get_type() const {
    return (*status_signals)[0].value;
}

const std::string& SlvStatus::get_message() const {
    return (*status_signals)[0].data;
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
    return *this;
}

SlvStatus& SlvStatus::operator+=(const SlvStatus& _status) {

    for (unsigned int i = 0; i < _status.size(); i++) {
        push(_status.get_type(i), _status.get_message(i));
    }
    return *this;
}

void SlvStatus::ostream(std::ostream& _os) const {

    for (unsigned int s = 0; s < size(); s++) {
        _os << (*status_signals)[s];
        if (s < size() - 1) {
            _os << std::endl;
        }
    }

}
