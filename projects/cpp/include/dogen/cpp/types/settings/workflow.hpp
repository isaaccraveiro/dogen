/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
#ifndef DOGEN_CPP_TYPES_SETTINGS_WORKFLOW_HPP
#define DOGEN_CPP_TYPES_SETTINGS_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <forward_list>
#include <unordered_map>
#include "dogen/config/types/cpp_options.hpp"
#include "dogen/dynamic/schema/types/indexer.hpp"
#include "dogen/dynamic/schema/types/field_definition.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/formatters/types/general_settings.hpp"
#include "dogen/cpp/types/settings/cpp_settings.hpp"
#include "dogen/cpp/types/settings/global_facet_settings.hpp"
#include "dogen/cpp/types/settings/local_settings.hpp"
#include "dogen/cpp/types/settings/global_settings.hpp"
#include "dogen/cpp/types/settings/local_formatter_settings.hpp"
#include "dogen/cpp/types/settings/global_formatter_settings.hpp"
#include "dogen/formatters/types/general_settings_factory.hpp"
#include "dogen/cpp/types/settings/settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Orchestrator for the settings workflow.
 */
class workflow {
public:
    workflow();

private:
    /**
     * @brief Returns the model's module.
     *
     * @pre there must exacly one model module
     */
    sml::module obtain_model_module(const sml::model& m) const;

private:
    /**
     * @brief Creates the general settings.
     */
    dogen::formatters::general_settings
    create_general_settings(const dynamic::schema::object& o) const;

    /**
     * @brief Create the c++ settings.
     */
    cpp_settings create_cpp_settings(const config::cpp_options& co,
        const dynamic::schema::object& o) const;

    /**
     * @brief Create the facet settings.
     */
    std::unordered_map<std::string, global_facet_settings>
    create_global_facet_settings(const dynamic::schema::indexer& idx,
        const dynamic::schema::object& o) const;

    /**
     * @brief Create the global formatter settings.
     */
    std::unordered_map<std::string, global_formatter_settings>
    create_global_formatter_settings(const dynamic::schema::indexer& idx,
        const dynamic::schema::object& o) const;

private:
    /**
     * @brief Creates the global settings.
     */
    global_settings create_global_settings_activity(
        const config::cpp_options& co, const dynamic::schema::indexer& idx,
        const sml::model& m) const;

    /**
     * @brief Creates the local settings for all types.
     */
    std::unordered_map<std::string, local_settings>
    create_local_settings_activity(const dynamic::schema::indexer& idx,
        const sml::model& m) const;

public:
    /**
     * @brief Generates the top-level settings from the supplied
     * model.
     */
    settings execute(const config::cpp_options& co,
        const std::forward_list<dynamic::schema::field_definition>& fds,
        const sml::model& m) const;

private:
    dogen::formatters::general_settings_factory general_settings_factory_;
};

} } }

#endif
