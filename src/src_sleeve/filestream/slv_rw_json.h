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

#include "GloveOptions.h"
#if OPTION_USE_THIRDPARTY_JSON==1

#include "json.hpp"
#include "SlvStatus.h"

namespace slv {
    namespace rw {
        /*! Json save/load methods. For public use:
        * writeJson
        * readJson
        * specialization of writeJson_spec
        * specialization of readJson_spec*/
        namespace json {

            /*! Function to specialize for json writing.*/
            template <class Tdat>
            void writeJson_spec(const Tdat& _value, nlohmann::json& _json) = delete;

            /*! Private namespace.*/
            namespace typemgr {
                template <class Tdat, class = void>
                struct is_write_specialized : std::false_type {};

                template <class Tdat>
                struct is_write_specialized<Tdat, decltype(slv::rw::json::writeJson_spec<Tdat>(std::declval<const Tdat&>(), std::declval<nlohmann::json&>()), void())> : std::true_type {};
            
                /*! Use json library IO or not.*/
                template <class Tdat, typename = void>
                struct JsonRW {
                    static void writeJson(const Tdat& _value, nlohmann::json& _json) {
                        _json = _value;
                    }
                    static SlvStatus readJson(Tdat& _value, const nlohmann::json& _json) {
                        _value = _json.get<Tdat>();
                        return SlvStatus();
                    }
                };
            }

            /*! Write \p _value in \p _json. May not compile if Tdat is not managed.*/
            template <class Tdat>
            typename std::enable_if<!typemgr::is_write_specialized<Tdat>::value>::type writeJson(const Tdat& _value, nlohmann::json& _json) {
                typemgr::JsonRW<Tdat>::writeJson(_value, _json);//default if no specialization
            }
            /*! Write \p _value in \p _json. May not compile if Tdat is not managed.*/
            template <class Tdat>
            typename std::enable_if<typemgr::is_write_specialized<Tdat>::value>::type writeJson(const Tdat& _value, nlohmann::json& _json) {
                writeJson_spec<Tdat>(_value, _json);// use specialization
            }

            //////

            /*! Function to specialize for json reading.*/
            template <class Tdat>
            SlvStatus readJson_spec(Tdat& _value, const nlohmann::json& _json) = delete;

            namespace typemgr {
                template <class Tdat, class = void>
                struct is_read_specialized : std::false_type {};

                template <class Tdat>
                struct is_read_specialized<Tdat, decltype(slv::rw::json::readJson_spec<Tdat>(std::declval<Tdat&>(), std::declval<const nlohmann::json&>()), void())> : std::true_type {};
            }

            /*! Read \p _value from \p _json. May not compile if Tdat is not managed.*/
            template <class Tdat>
            typename std::enable_if<!typemgr::is_read_specialized<Tdat>::value, SlvStatus>::type readJson(Tdat& _value, const nlohmann::json& _json) {
                return typemgr::JsonRW<Tdat>::readJson(_value, _json);//default if no specialization
            }
            /*! Read \p _value from \p _json. May not compile if Tdat is not managed.*/
            template <class Tdat>
            typename std::enable_if<typemgr::is_read_specialized<Tdat>::value, SlvStatus>::type readJson(Tdat& _value, const nlohmann::json& _json) {
                return readJson_spec<Tdat>(_value, _json);// use specialization
            }

        }
    }
}

#include "SlvHasMethod.h"
glvm_SlvHasMethod(SlvHas_writeJson, writeJson)
glvm_SlvHasMethod(SlvHas_readJson, readJson)

namespace slv {
    namespace rw {
        namespace json {
            namespace typemgr {

                /*! Use methods writeJson and readJson if they exist for type Tdat.*/
                template <class Tdat, typename = void>
                struct JsonRW_use_readwriteJson {
                    static constexpr bool l_valid = false;
                    static void writeJson(const Tdat& _value, nlohmann::json& _json) {}
                    static SlvStatus readJson(Tdat& _value, const nlohmann::json& _json) { return SlvStatus(); }
                };
                template <class Tdat>
                struct JsonRW_use_readwriteJson<Tdat, typename std::enable_if<SlvHas_writeJson<Tdat>::value&& SlvHas_readJson<Tdat>::value>::type> {
                    static constexpr bool l_valid = true;
                    static void writeJson(const Tdat& _value, nlohmann::json& _json) {
                        _value.writeJson(_json);
                    }
                    static SlvStatus readJson(Tdat& _value, const nlohmann::json& _json) {
                        return _value.readJson(_json);
                    }
                };

            }
        }
    }
}

#include "SlvHasMethod.h"
glvm_SlvHasMethod(SlvHas_ofstream, ofstream)
glvm_SlvHasMethod(SlvHas_ifstream, ifstream)

namespace slv {
    namespace rw {
        namespace json {
            namespace typemgr {

                /*! Use methods ofstream and ifstream if they exist (public) for type Tdat.*/
                template <class Tdat, typename = void>
                struct JsonRW_use_iofstream {
                    static constexpr bool l_valid = false;
                    static void writeJson(const Tdat& _value, nlohmann::json& _json) {}
                    static SlvStatus readJson(Tdat& _value, const nlohmann::json& _json) { return SlvStatus(); }
                };
                template <class Tdat>
                struct JsonRW_use_iofstream<Tdat, typename std::enable_if<SlvHas_ofstream<Tdat>::value&& SlvHas_ifstream<Tdat>::value>::type> {
                    static constexpr bool l_valid = true;
                    static void writeJson(const Tdat& _value, nlohmann::json& _json) {
                        std::ostringstream oss;
                        _value.ofstream(oss);
                        _json = oss.str();
                    }
                    static SlvStatus readJson(Tdat& _value, const nlohmann::json& _json) {
                        std::istringstream iss(_json.get<std::string>());
                        _value.ifstream(iss);
                        return SlvStatus();
                    }
                };

            }
        }
    }
}

#include "SlvHasMethod.h"
glvm_SlvHasMethod(SlvHas_ostream, ostream)
glvm_SlvHasMethod(SlvHas_istream, istream)

namespace slv {
    namespace rw {
        namespace json {
            namespace typemgr {

                /*! Use methods ostream and istream if they exist (public) for type Tdat.*/
                template <class Tdat, typename = void>
                struct JsonRW_use_iostream {
                    static constexpr bool l_valid = false;
                    static void writeJson(const Tdat& _value, nlohmann::json& _json) {}
                    static SlvStatus readJson(Tdat& _value, const nlohmann::json& _json) { return SlvStatus(); }
                };
                template <class Tdat>
                struct JsonRW_use_iostream<Tdat, typename std::enable_if<SlvHas_ostream<Tdat>::value&& SlvHas_istream<Tdat>::value>::type> {
                    static constexpr bool l_valid = true;
                    static void writeJson(const Tdat& _value, nlohmann::json& _json) {
                        std::ostringstream oss;
                        _value.ostream(oss);
                        _json = oss.str();
                    }
                    static SlvStatus readJson(Tdat& _value, const nlohmann::json& _json) {
                        std::istringstream iss(_json.get<std::string>());
                        _value.istream(iss);
                        return SlvStatus();
                    }
                };

            }
        }
    }
}

namespace slv {
    namespace rw {
        namespace json {
            namespace typemgr {

                /*! Use writeJson_spec and readJson_spec if they exist. No reimplementation, will be caught in slv:rw::json::writeJson and slv::rw::json::readJson.*/
                template <class Tdat, typename = void>
                struct JsonRW_use_specialization {
                    static constexpr bool l_valid = false;
                };
                template <class Tdat>
                struct JsonRW_use_specialization<Tdat, typename std::enable_if<is_write_specialized<Tdat>::value&& is_read_specialized<Tdat>::value>::type> {
                    static constexpr bool l_valid = true;
                };

            }
        }
    }
}

namespace slv {
    namespace rw {
        namespace json {
            namespace typemgr {

                /*! Containers managed by default by the json library.*/
                template <typename T>
                struct is_json_container {
                    static const bool value = false;
                };
                template <typename T>
                struct is_json_container< std::vector<T> > {
                    static const bool value = true;
                };
                template <typename Tkey, typename Tvalue>
                struct is_json_container< std::map<Tkey, Tvalue> > {
                    static const bool value = true;
                };

            }
        }
    }
}


namespace slv {
    namespace rw {
        namespace json {
            namespace typemgr {

                /*! Use operators << and >> if they are available for type Tdat.*/
                template <class Tdat, typename = void>
                struct JsonRW_use_chevrons {
                    static constexpr bool l_valid = false;
                    static void writeJson(const Tdat& _value, nlohmann::json& _json) {}
                    static SlvStatus readJson(Tdat& _value, const nlohmann::json& _json) { return SlvStatus(); }
                };

            }
        }
    }
}

#include "SlvHasOstreamOperator.h"
#include "SlvHasIstreamOperator.h"
#include "SlvIOS.h"
#include "SlvIOFS.h"
/* Types enabling << >> operators. Containers managed by the json library are excluded.
* Such exclusion is not required for other type checkers, assuming no type managed intrisically by the json library has any method writeJson/readJson/ostream/istream/ofstream/ifstream.*/
#define Tenable_chevrons \
(SlvHasOstreamOperator<Tdat>::value || std::is_base_of<SlvOS, Tdat>::value || std::is_base_of<SlvOFS, Tdat>::value) &&\
(SlvHasIstreamOperator<Tdat>::value || std::is_base_of<SlvIS, Tdat>::value || std::is_base_of<SlvIFS, Tdat>::value)\
&& (std::is_class<Tdat>::value || std::is_enum<Tdat>::value)\
&& !slv::rw::json::typemgr::is_json_container<Tdat>::value

namespace slv {
    namespace rw {
        namespace json {
            namespace typemgr {

                template <class Tdat>
                struct JsonRW_use_chevrons<Tdat, typename std::enable_if<Tenable_chevrons>::type> {
                    static constexpr bool l_valid = true;
                    static void writeJson(const Tdat& _value, nlohmann::json& _json) {
                        std::ostringstream oss;
                        oss << _value;
                        _json = oss.str();
                    }
                    static SlvStatus readJson(Tdat& _value, const nlohmann::json& _json) {
                        std::istringstream iss(_json.get<std::string>());
                        iss >> _value;
                        return SlvStatus();
                    }
                };

            }
        }
    }
}

#define Tenable_manageable_by_library \
JsonRW_use_specialization<Tdat>::l_valid \
|| JsonRW_use_readwriteJson<Tdat>::l_valid\
|| JsonRW_use_iofstream<Tdat>::l_valid\
|| JsonRW_use_iostream<Tdat>::l_valid\
|| JsonRW_use_chevrons<Tdat>::l_valid

namespace slv {
    namespace rw {
        namespace json {
            namespace typemgr {

                /*! Types that are manageable independently of the json library.*/
                template <class Tdat, typename = void>
                struct IsJsonManageableByImplementation {
                    static constexpr bool l_valid = false;
                };
                template <class Tdat>
                struct IsJsonManageableByImplementation<Tdat, typename std::enable_if<Tenable_manageable_by_library>::type> {
                    static constexpr bool l_valid = true;
                };

                /*! If Tdat is manageable by implementation, then json is handled here. Otherwise default json IO will be used for the type Tdat.*/
                template <class Tdat>
                struct JsonRW<Tdat, typename std::enable_if<IsJsonManageableByImplementation<Tdat>::l_valid>::type> {
                    static void writeJson(const Tdat& _value, nlohmann::json& _json) {

                        if (JsonRW_use_readwriteJson<Tdat>::l_valid) {
                            JsonRW_use_readwriteJson<Tdat>::writeJson(_value, _json);
                        } else if (JsonRW_use_iofstream<Tdat>::l_valid) {
                            JsonRW_use_iofstream<Tdat>::writeJson(_value, _json);
                        } else if (JsonRW_use_iostream<Tdat>::l_valid) {
                            JsonRW_use_iostream<Tdat>::writeJson(_value, _json);
                        } else if (JsonRW_use_chevrons<Tdat>::l_valid) {
                            JsonRW_use_chevrons<Tdat>::writeJson(_value, _json);
                        }

                    }
                    static SlvStatus readJson(Tdat& _value, const nlohmann::json& _json) {

                        if (JsonRW_use_readwriteJson<Tdat>::l_valid) {
                            return JsonRW_use_readwriteJson<Tdat>::readJson(_value, _json);
                        } else if (JsonRW_use_iofstream<Tdat>::l_valid) {
                            return JsonRW_use_iofstream<Tdat>::readJson(_value, _json);
                        } else if (JsonRW_use_iostream<Tdat>::l_valid) {
                            return JsonRW_use_iostream<Tdat>::readJson(_value, _json);
                        } else if (JsonRW_use_chevrons<Tdat>::l_valid) {
                            return JsonRW_use_chevrons<Tdat>::readJson(_value, _json);
                        } else {
                            return SlvStatus(SlvStatus::statusType::warning, "Json : no reader available. Should not happen (architecture issue).");
                        }

                    }
                };

            }
        }
    }
}

namespace slv {
    namespace rw {
        namespace json {
            namespace typemgr {

                /*! Types manageable by the json library.*/
                template <class Tdat, typename = void>
                struct IsJsonManageableByJsonLibrary {
                    static constexpr bool l_valid = false;
                };

                template <class Tdat>
                struct IsJsonManageableByJsonLibrary<Tdat, typename std::enable_if<std::is_arithmetic<Tdat>::value || std::is_enum<Tdat>::value || std::is_same<Tdat, std::string>::value || slv::rw::json::typemgr::is_json_container<Tdat>::value>::type> {
                    static constexpr bool l_valid = true;
                };

                ////////////////

                /*! Parametrizations that are manageable.*/
                template <class Tdat, typename = void>
                struct IsJsonManageableParametrizationExplicit {
                    static constexpr bool l_valid = true;
                };

                /*! Types that are manageable if they are parametrizations.*/
                template <class Tdat, typename = void>
                struct IsJsonManageableParametrization {
                    static constexpr bool l_valid = true;//true by default for types that are not parametrizations
                };

            }
        }
    }
}

#include "SlvIsParametrization.h"

namespace slv {
    namespace rw {
        namespace json {
            namespace typemgr {

                template <class Tdat>
                struct IsJsonManageableParametrization<Tdat, typename std::enable_if<SlvIsParametrization<Tdat>::value>::type> {
                    static constexpr bool l_valid = IsJsonManageableParametrizationExplicit<typename Tdat::Tparametrization>::l_valid;
                };
            }


            /*! Types manageable (ultimately). Either by json library or by implementation. Recommended for public use.*/
            template <class Tdat, typename = void>
            struct ReadWrite {
                static constexpr bool l_valid = false;
                static void writeJson(const Tdat& _value, nlohmann::json& _json) {}
                static SlvStatus readJson(Tdat& _value, const nlohmann::json& _json) {
                    return SlvStatus(SlvStatus::statusType::warning, "The type can not be managed for json IO.");
                }
            };

            /*! Types manageable (ultimately). Either by json library or by implementation. Special case for parametrization.*/
            template <class Tdat>
            struct ReadWrite<Tdat, typename std::enable_if<(typemgr::IsJsonManageableByJsonLibrary<Tdat>::l_valid || typemgr::IsJsonManageableByImplementation<Tdat>::l_valid) && typemgr::IsJsonManageableParametrization<Tdat>::l_valid>::type> {
                static constexpr bool l_valid = true;
                static void writeJson(const Tdat& _value, nlohmann::json& _json) {
                    slv::rw::json::writeJson(_value, _json);
                }
                static SlvStatus readJson(Tdat& _value, const nlohmann::json& _json) {
                    return slv::rw::json::readJson(_value, _json);
                }
            };

        }
    }
}

#endif
