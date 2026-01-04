/*
* This file is part of the Glove distribution (https://github.com/piallai/glove).
* Copyright (C) 2024 - 2026 Pierre Allain.
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

#include <iostream>
#include <streambuf>
#include <string>

/*! Capture a stream to a std::string*/
class SlvCaptureStream : public std::basic_streambuf<char> {

private:
    std::ostream& stream;
    std::streambuf* buff;
    std::string string;

    std::string* captured;

public:
    /*! \p _captured points to std::string to redirect the stream to.*/
    SlvCaptureStream(std::ostream& _stream, std::string* _captured);
    /*! Stops stream capture.*/
    ~SlvCaptureStream();

protected:

    virtual int_type overflow(int_type _ch);
    virtual std::streamsize xsputn(const char* _string, std::streamsize _n);

};