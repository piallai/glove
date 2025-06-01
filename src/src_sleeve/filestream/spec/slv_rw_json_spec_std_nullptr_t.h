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

#pragma once

// For slv::rw::json::ReadWrite::l_valid. But does nothing.
// Usefull for parameter of type std::nullptr_t.
// slv::rw::json::ReadWrite<Tparametrization>::l_valid is true if one of the parameters is of type std::nullptr_t
template <>
inline void slv::rw::json::writeJson_spec<std::nullptr_t>(const std::nullptr_t& _value, nlohmann::json& _json) {
	
}

template <>
inline SlvStatus slv::rw::json::readJson_spec<std::nullptr_t>(std::nullptr_t& _value, const nlohmann::json& _json) {
	return SlvStatus();
}
