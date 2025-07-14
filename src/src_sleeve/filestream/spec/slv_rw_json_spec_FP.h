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

#include <type_traits>

namespace slv {
    namespace rw {
        namespace json {
            namespace typemgr {
                template <class Tdat>
                struct JsonRW<Tdat, typename std::enable_if<std::is_floating_point<Tdat>::value>::type> {
                    static void writeJson(const Tdat& _value, nlohmann::json& _json) {
                        if (std::isfinite(_value)) {
                            _json = _value;
                        } else {
                            Tdat value;
                            if (_value > Tdat(0)) {
                                value = std::numeric_limits<Tdat>::max();
                            } else {
                                value = std::numeric_limits<Tdat>::lowest();
                            }
                            _json = value;
                        }
                    }
                    static SlvStatus readJson(Tdat& _value, const nlohmann::json& _json) {
                        SlvStatus status;
                        try {
                            _value = _json.get<Tdat>();
                            if (_value == std::numeric_limits<Tdat>::max()) {
                                _value = INFINITY;
                            } else if (_value == std::numeric_limits<Tdat>::lowest()) {
                                _value = -INFINITY;
                            }
                        } catch (std::exception) {
                            status = SlvStatus(SlvStatus::statusType::critical, "Can not read type " + SlvDataName<Tdat>::name());
                        }
                        return status;
                    }
                };
            }
        }
    }
}
