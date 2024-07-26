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

#include "SlvFileName.h"
#include "SlvFileMgr.h"
#include "filestream/slv_rw.h"

SlvFileName::SlvFileName() {

}

SlvFileName::SlvFileName(const SlvFileStem& _stem, const SlvFileExtension& _extension) {
    stem = _stem;
    extension = _extension;
}

SlvFileName::SlvFileName(const std::string& _string) {
    stem = SlvFileMgr::get_file_name_str(_string, false);
    extension = SlvFileMgr::get_extension(_string);
}

SlvFileName::~SlvFileName() {

}

std::string SlvFileName::get_total_name() const {
    if (extension.size() > 0) {
        return stem + extension;
    } else {
        return stem;
    }
}

bool SlvFileName::operator==(const SlvFileName& _file_name) const {

    return stem == _file_name.stem \
        && extension == _file_name.extension;

}

bool SlvFileName::readB(std::ifstream& _input_file) {

    bool l_read = slv::rw::readB(stem, _input_file);
    if (l_read) l_read = slv::rw::readB(extension, _input_file);
    return l_read;

}

void SlvFileName::writeB(std::ofstream& _output_file) const {

    slv::rw::writeB(stem, _output_file);
    slv::rw::writeB(extension, _output_file);

}