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
#include "dogen/types/model_processing_configuration.hpp"

namespace dogen {

model_processing_configuration::model_processing_configuration()
    : compatibility_mode_enabled_(static_cast<bool>(0)),
      dry_run_mode_enabled_(static_cast<bool>(0)) { }

model_processing_configuration::model_processing_configuration(
    const bool compatibility_mode_enabled,
    const bool dry_run_mode_enabled)
    : compatibility_mode_enabled_(compatibility_mode_enabled),
      dry_run_mode_enabled_(dry_run_mode_enabled) { }

void model_processing_configuration::swap(model_processing_configuration& other) noexcept {
    using std::swap;
    swap(compatibility_mode_enabled_, other.compatibility_mode_enabled_);
    swap(dry_run_mode_enabled_, other.dry_run_mode_enabled_);
}

bool model_processing_configuration::operator==(const model_processing_configuration& rhs) const {
    return compatibility_mode_enabled_ == rhs.compatibility_mode_enabled_ &&
        dry_run_mode_enabled_ == rhs.dry_run_mode_enabled_;
}

model_processing_configuration& model_processing_configuration::operator=(model_processing_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool model_processing_configuration::compatibility_mode_enabled() const {
    return compatibility_mode_enabled_;
}

void model_processing_configuration::compatibility_mode_enabled(const bool v) {
    compatibility_mode_enabled_ = v;
}

bool model_processing_configuration::dry_run_mode_enabled() const {
    return dry_run_mode_enabled_;
}

void model_processing_configuration::dry_run_mode_enabled(const bool v) {
    dry_run_mode_enabled_ = v;
}

}