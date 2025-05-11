/*
* This file is part of the Glove distribution (https://github.com/piallai/glove).
* Copyright (C) 2024 - 2025 Pierre Allain.
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

#include "param/SlvParametrization0.h"
#include "filestream/slv_rw.h"

SlvParametrization0::SlvParametrization0() {

}

SlvParametrization0::SlvParametrization0(const SlvParametrization0& _parametrization) {

}

SlvParametrization0::~SlvParametrization0() {

}

void SlvParametrization0::operator=(const SlvParametrization0& _parametrization) {

}

void SlvParametrization0::param_assign_rec(const SlvParametrization0& _parametrization) {

}

void SlvParametrization0::set_parameter_values(bool _l_param_only) {

}

SlvStatus SlvParametrization0::check_parameters() const {
	return SlvStatus();
}

bool SlvParametrization0::abide_rules() {
	return true;
}

bool SlvParametrization0::operator==(const SlvParametrization0& _parametrization) const {
	return true;
}

bool SlvParametrization0::operator!=(const SlvParametrization0& _parametrization) const {
	return !(*this == _parametrization);
}

std::vector<std::string> SlvParametrization0::get_vector_id_str(unsigned int _marker) const {
	std::vector<std::string> vector_id_str;
	return vector_id_str;
}

std::vector< std::pair<std::string, std::string> > SlvParametrization0::get_string_serialization(unsigned int _marker) const {
	std::vector< std::pair<std::string, std::string> > serialization;
	return serialization;
}

std::pair< std::vector< std::pair<std::string, std::string> >, std::vector<std::string> > SlvParametrization0::get_string_serialization_bool(unsigned int _marker) const {
	std::pair< std::vector< std::pair<std::string, std::string> >, std::vector<std::string> > serialization;
	return serialization;
}

void SlvParametrization0::ostream(std::ostream& _os) const {

}

void SlvParametrization0::istream_rec(std::istream& _is) {

}

void SlvParametrization0::istream(std::istream& _is) {

}

void SlvParametrization0::writeB(std::ofstream& _output_file) const {
	slv::rw::writeB(get_name(), _output_file);
}

bool SlvParametrization0::readB_rec(std::ifstream& _input_file) {
	std::string name;
	bool l_read = slv::rw::readB(name, _input_file);
	if (l_read && name != get_name()) {
		slv::flag::ISSUE(slv::flag::Warning, "In SlvParametrization0, static names are different : name = ", name, ", get_name() = ", get_name());
		return false;
	} else {
		return l_read;
	}
}

bool SlvParametrization0::readB(std::ifstream& _input_file) {
	return readB_rec(_input_file);
}

#if OPTION_USE_THIRDPARTY_JSON==1
void SlvParametrization0::writeJson(nlohmann::json& _json) const {
	_json[get_name()];
}

SlvStatus SlvParametrization0::readJson(const nlohmann::json& _json) {
	nlohmann::json::const_iterator it = _json.find(get_name());
	if (it != _json.end()) {
		return SlvStatus();
	} else {
		return SlvStatus(SlvStatus::statusType::critical, "Can not find parametrization : " + get_name() + "\nJson is not suited for this parametrization.");
	}
}
#endif

SlvParametrization0::Tparametrization& SlvParametrization0::param_cast() {
	return *this;
}

const SlvParametrization0::Tparametrization& SlvParametrization0::param_cast() const {
	return *this;
}