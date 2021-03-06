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
#include "dogen/types/reporting_configuration.hpp"

namespace dogen {

reporting_configuration::reporting_configuration()
    : style_(static_cast<dogen::reporting_style>(0)) { }

reporting_configuration::reporting_configuration(reporting_configuration&& rhs)
    : style_(std::move(rhs.style_)),
      output_directory_(std::move(rhs.output_directory_)) { }

reporting_configuration::reporting_configuration(
    const dogen::reporting_style style,
    const boost::filesystem::path& output_directory)
    : style_(style),
      output_directory_(output_directory) { }

void reporting_configuration::swap(reporting_configuration& other) noexcept {
    using std::swap;
    swap(style_, other.style_);
    swap(output_directory_, other.output_directory_);
}

bool reporting_configuration::operator==(const reporting_configuration& rhs) const {
    return style_ == rhs.style_ &&
        output_directory_ == rhs.output_directory_;
}

reporting_configuration& reporting_configuration::operator=(reporting_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::reporting_style reporting_configuration::style() const {
    return style_;
}

void reporting_configuration::style(const dogen::reporting_style v) {
    style_ = v;
}

const boost::filesystem::path& reporting_configuration::output_directory() const {
    return output_directory_;
}

boost::filesystem::path& reporting_configuration::output_directory() {
    return output_directory_;
}

void reporting_configuration::output_directory(const boost::filesystem::path& v) {
    output_directory_ = v;
}

void reporting_configuration::output_directory(const boost::filesystem::path&& v) {
    output_directory_ = std::move(v);
}

}
