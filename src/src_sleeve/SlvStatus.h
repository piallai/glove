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

#include <string>
#include "SlvOS.h"
template <class Tdata, class Tvalue>
class SlvCombo;
#include "std_vector.h"

/*! Class containing one or multiple message associated with a level of criticity and automatically sorted to highlight the most critical one.
* Convenient to return possible errors.
* Practical use: create instances by setting an error type and a message.
* += instances to stack errors and return the overall status result.*/
class SlvStatus : public SlvOS {

public:

    /*! Possible types of status.*/
    enum class statusType { ok, information, warning, critical };

private:

    typedef SlvCombo<std::string, statusType> SlvStatusSignal;

    /*! Vector of status messages sorted by descending order so that the more a status is critical, the more it will be set to front.
    * int is for statusType to be treated as a numerical value.*/
    //SlvSortDescending< SlvStatusSignal, int >* status_signals;//pointer to just use forward decalaration
    std::vector<SlvStatusSignal>* status_signals;//pointer to just use forward decalaration

    /*! Add a status \p _type with a corresponding \p \message.*/
    void push(const statusType& _type, const std::string& _message);

public:

    SlvStatus(statusType _type = statusType::ok, std::string _message = "");
    SlvStatus(const SlvStatus& _status);
    ~SlvStatus();

    typedef typename std::vector<SlvStatusSignal>::const_iterator const_iterator;
    /*! Iterator to the first element.*/
    const_iterator begin() const;
    /*! Iterator to the last element.*/
    const_iterator end() const;

    /*! Number of status contained.*/
    size_t size() const;
    /*! Get the most critical status.*/
    const statusType& get_type() const;
    /*! Get the most critical message.*/
    const std::string& get_message() const;
    /*! Get status number \p i.*/
    const statusType& get_type(const unsigned int i) const;
    /*! Get message number \p i.*/
    const std::string& get_message(const unsigned int i) const;

    /*! Check operator. Return true if the most critical status is equal to statusType::ok.*/
    operator bool() const;

    SlvStatus& operator=(const SlvStatus& _status);
    /*! Sum status and reordrer them.*/
    SlvStatus& operator+=(const SlvStatus& _status);

private:

    static bool sortStatus(SlvStatusSignal _signal1, SlvStatusSignal _signal2);
    void ostream(std::ostream& _os) const;
};

#include "SlvEnum.h"
glvm_SlvEnum_implementation(SlvStatus::statusType, ok, information, warning, critical)
