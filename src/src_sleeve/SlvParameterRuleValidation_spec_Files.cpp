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

#include "SlvParameterRuleValidation_spec_Files.h"
#include "filestream/SlvFileMgr.h"

#include "SlvParameter.h"
SlvStatus SlvParameterRuleValidation<SlvFile>::is_valid(const SlvParameter<SlvFile>* _parameter) {
	SlvFile::IO io_mode = _parameter->get_value().get_io_mode();
	if (io_mode == SlvFile::IO::Read && SlvFileMgr::test_file(_parameter->get_value(), std::ios::in)) {
		return SlvStatus();
	} else if (io_mode == SlvFile::IO::Write && SlvFileMgr::test_file(_parameter->get_value(), std::ios::out)) {
		return SlvStatus();
	} else if (io_mode == SlvFile::IO::Any) {// No test for Any
		return SlvStatus();
	} else {
		return SlvStatus(SlvStatus::statusType::warning, _parameter->get_name() + " : can't open file  " + SlvFileMgr::get_path(_parameter->get_value()));
	}
}

SlvStatus SlvParameterRuleValidation<SlvDirectory>::is_valid(const SlvParameter<SlvDirectory>* _parameter) {
	if (_parameter->get_value().exists()) {
		return SlvStatus();
	} else {
		return SlvStatus(SlvStatus::statusType::warning, _parameter->get_name() + " : no such directory " + slv::string::to_string(_parameter->get_value()));
	}
}