/* -*- MODE: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_CPP_TYPES_SETTINGS_CPP_SETTINGS_FACTORY_HPP
#define DOGEN_CPP_TYPES_SETTINGS_CPP_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/config/types/cpp_options.hpp"
#include "dogen/cpp/types/settings/cpp_settings.hpp"
#include "dogen/dynamic/schema/types/object.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Generates the C++ settings from dynamic extensions.
 */
class cpp_settings_factory {
public:
    cpp_settings_factory(const cpp_settings_factory&) = default;
    cpp_settings_factory(cpp_settings_factory&&) = default;
    ~cpp_settings_factory() = default;

public:
    cpp_settings_factory();

private:
    /**
     * @brief Returns a default value version of the C++ settings.
     */
    cpp_settings create_default_settings() const;

    /**
     * @brief Populates the settings with values from the dynamic
     * object.
     */
    void populate(const dynamic::schema::object& o, cpp_settings& s) const;

    /**
     * @brief Populates the settings with values from the config
     * options.
     */
    void populate(const config::cpp_options& co, cpp_settings& s) const;

public:
    /**
     * @brief Creates the C++ settings from the dynamic object
     * properties. The missing values are defaulted.
     */
    cpp_settings
    make(const config::cpp_options& co, const dynamic::schema::object& o) const;

private:
    cpp_settings default_settings_;
};

} } }

#endif
