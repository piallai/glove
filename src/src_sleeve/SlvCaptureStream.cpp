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

#include "SlvCaptureStream.h"

SlvCaptureStream::SlvCaptureStream(std::ostream& _stream, std::string* _captured) : stream(_stream) {
    captured = _captured;
    buff = _stream.rdbuf();
    _stream.rdbuf(this);
}

SlvCaptureStream::~SlvCaptureStream() {

    if (!string.empty()) {
        *captured += string;
    }

    stream.rdbuf(buff);
}

std::basic_streambuf<char>::int_type SlvCaptureStream::overflow(int_type _ch) {

    if (_ch == '\n') {
        *captured += '\n';
        *captured += string;
        string.erase(string.begin(), string.end());
    } else {
        string += _ch;
    }

    return _ch;
}

std::streamsize SlvCaptureStream::xsputn(const char* _string, std::streamsize _n) {

    string.append(_string, _string + _n);

    size_t pos = 0;
    while (pos != std::string::npos) {
        pos = string.find('\n');
        if (pos != std::string::npos) {
            std::string tmp(string.begin(), string.begin() + pos);
            *captured += '\n';
            *captured += tmp;
            string.erase(string.begin(), string.begin() + pos + 1);
        }
    }

    return _n;
}