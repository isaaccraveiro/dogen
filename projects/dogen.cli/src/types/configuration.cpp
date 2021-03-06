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
#include "dogen.cli/types/configuration.hpp"

namespace dogen::cli {

configuration::configuration(configuration&& rhs)
    : logging_(std::move(rhs.logging_)),
      api_(std::move(rhs.api_)),
      cli_(std::move(rhs.cli_)) { }

configuration::configuration(
    const boost::optional<dogen::utility::log::logging_configuration>& logging,
    const dogen::configuration& api,
    const dogen::cli::cli_configuration& cli)
    : logging_(logging),
      api_(api),
      cli_(cli) { }

void configuration::swap(configuration& other) noexcept {
    using std::swap;
    swap(logging_, other.logging_);
    swap(api_, other.api_);
    swap(cli_, other.cli_);
}

bool configuration::operator==(const configuration& rhs) const {
    return logging_ == rhs.logging_ &&
        api_ == rhs.api_ &&
        cli_ == rhs.cli_;
}

configuration& configuration::operator=(configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<dogen::utility::log::logging_configuration>& configuration::logging() const {
    return logging_;
}

boost::optional<dogen::utility::log::logging_configuration>& configuration::logging() {
    return logging_;
}

void configuration::logging(const boost::optional<dogen::utility::log::logging_configuration>& v) {
    logging_ = v;
}

void configuration::logging(const boost::optional<dogen::utility::log::logging_configuration>&& v) {
    logging_ = std::move(v);
}

const dogen::configuration& configuration::api() const {
    return api_;
}

dogen::configuration& configuration::api() {
    return api_;
}

void configuration::api(const dogen::configuration& v) {
    api_ = v;
}

void configuration::api(const dogen::configuration&& v) {
    api_ = std::move(v);
}

const dogen::cli::cli_configuration& configuration::cli() const {
    return cli_;
}

dogen::cli::cli_configuration& configuration::cli() {
    return cli_;
}

void configuration::cli(const dogen::cli::cli_configuration& v) {
    cli_ = v;
}

void configuration::cli(const dogen::cli::cli_configuration&& v) {
    cli_ = std::move(v);
}

}
