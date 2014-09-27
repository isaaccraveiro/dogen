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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/frontend/types/registrar_error.hpp"
#include "dogen/frontend/types/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("sml.meta_data.registrar"));

const std::string exension_registerd_more_than_once(
    "Extension was registered more than once");
const std::string no_sources("No sources provided.");
const std::string no_source_for_extension("No available for extension: ");
const std::string null_source("Source provided is null");

}

namespace dogen {
namespace frontend {

void registrar::validate() const {
    if (source_for_extension_.empty()) {
        BOOST_LOG_SEV(lg, error) << no_sources;
        BOOST_THROW_EXCEPTION(registrar_error(no_sources));
    }
}

void registrar::register_source_for_extension(const std::string& ext,
    std::shared_ptr<source_interface> s) {

    if (!s) {
        BOOST_LOG_SEV(lg, error) << null_source;
        BOOST_THROW_EXCEPTION(registrar_error(null_source));
    }

    const auto i(source_for_extension_.insert(std::make_pair(ext, s)));
    if (i.second) {
        BOOST_LOG_SEV(lg, error) << no_sources;
        BOOST_THROW_EXCEPTION(registrar_error(no_sources));
    }
}

std::shared_ptr<source_interface> registrar::
source_for_extension(const std::string& ext) {
    const auto i(source_for_extension_.find(ext));
    if (i == source_for_extension_.end()) {
        BOOST_LOG_SEV(lg, error) << no_source_for_extension << ext;
        BOOST_THROW_EXCEPTION(registrar_error(no_source_for_extension + ext));
    }
    return i->second;
}

} }
