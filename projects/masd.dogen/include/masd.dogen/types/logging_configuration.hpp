/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef MASD_DOGEN_TYPES_LOGGING_CONFIGURATION_HPP
#define MASD_DOGEN_TYPES_LOGGING_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "masd.dogen/types/log_level.hpp"

namespace masd::dogen {

/**
 * @brief Configuration related to logging.
 */
class logging_configuration final {
public:
    logging_configuration(const logging_configuration&) = default;
    ~logging_configuration() = default;

public:
    logging_configuration();

public:
    logging_configuration(logging_configuration&& rhs);

public:
    logging_configuration(
        const bool enabled,
        const boost::filesystem::path& output_directory,
        const masd::dogen::log_level level,
        const std::string& file_name,
        const bool output_to_console);

public:
    /**
     * @brief If true, the configurable aspect will be expressed.
     */
    /**@{*/
    bool enabled() const;
    logging_configuration& enabled(const bool v);
    /**@}*/

    /**
     * @brief Directory in which to place the output.
     */
    /**@{*/
    const boost::filesystem::path& output_directory() const;
    boost::filesystem::path& output_directory();
    logging_configuration& output_directory(const boost::filesystem::path& v);
    logging_configuration& output_directory(const boost::filesystem::path&& v);
    /**@}*/

    masd::dogen::log_level level() const;
    logging_configuration& level(const masd::dogen::log_level v);

    /**
     * @brief Name of the file to log into.
     */
    /**@{*/
    const std::string& file_name() const;
    std::string& file_name();
    logging_configuration& file_name(const std::string& v);
    logging_configuration& file_name(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, dumps the log into the console.
     */
    /**@{*/
    bool output_to_console() const;
    logging_configuration& output_to_console(const bool v);
    /**@}*/

public:
    bool operator==(const logging_configuration& rhs) const;
    bool operator!=(const logging_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(logging_configuration& other) noexcept;
    logging_configuration& operator=(logging_configuration other);

private:
    bool enabled_;
    boost::filesystem::path output_directory_;
    masd::dogen::log_level level_;
    std::string file_name_;
    bool output_to_console_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::logging_configuration& lhs,
    masd::dogen::logging_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif