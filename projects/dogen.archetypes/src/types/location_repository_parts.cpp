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
#include "dogen.archetypes/types/location_repository_parts.hpp"

namespace dogen::archetypes {

location_repository_parts::location_repository_parts(
    const std::list<dogen::archetypes::location>& all,
    const std::unordered_map<std::string, dogen::archetypes::locations_group>& by_meta_name,
    const std::unordered_map<std::string, std::list<dogen::archetypes::location> >& by_family,
    const std::unordered_map<std::string, std::list<dogen::archetypes::location> >& by_intra_backend_segment)
    : all_(all),
      by_meta_name_(by_meta_name),
      by_family_(by_family),
      by_intra_backend_segment_(by_intra_backend_segment) { }

void location_repository_parts::swap(location_repository_parts& other) noexcept {
    using std::swap;
    swap(all_, other.all_);
    swap(by_meta_name_, other.by_meta_name_);
    swap(by_family_, other.by_family_);
    swap(by_intra_backend_segment_, other.by_intra_backend_segment_);
}

bool location_repository_parts::operator==(const location_repository_parts& rhs) const {
    return all_ == rhs.all_ &&
        by_meta_name_ == rhs.by_meta_name_ &&
        by_family_ == rhs.by_family_ &&
        by_intra_backend_segment_ == rhs.by_intra_backend_segment_;
}

location_repository_parts& location_repository_parts::operator=(location_repository_parts other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::archetypes::location>& location_repository_parts::all() const {
    return all_;
}

std::list<dogen::archetypes::location>& location_repository_parts::all() {
    return all_;
}

void location_repository_parts::all(const std::list<dogen::archetypes::location>& v) {
    all_ = v;
}

void location_repository_parts::all(const std::list<dogen::archetypes::location>&& v) {
    all_ = std::move(v);
}

const std::unordered_map<std::string, dogen::archetypes::locations_group>& location_repository_parts::by_meta_name() const {
    return by_meta_name_;
}

std::unordered_map<std::string, dogen::archetypes::locations_group>& location_repository_parts::by_meta_name() {
    return by_meta_name_;
}

void location_repository_parts::by_meta_name(const std::unordered_map<std::string, dogen::archetypes::locations_group>& v) {
    by_meta_name_ = v;
}

void location_repository_parts::by_meta_name(const std::unordered_map<std::string, dogen::archetypes::locations_group>&& v) {
    by_meta_name_ = std::move(v);
}

const std::unordered_map<std::string, std::list<dogen::archetypes::location> >& location_repository_parts::by_family() const {
    return by_family_;
}

std::unordered_map<std::string, std::list<dogen::archetypes::location> >& location_repository_parts::by_family() {
    return by_family_;
}

void location_repository_parts::by_family(const std::unordered_map<std::string, std::list<dogen::archetypes::location> >& v) {
    by_family_ = v;
}

void location_repository_parts::by_family(const std::unordered_map<std::string, std::list<dogen::archetypes::location> >&& v) {
    by_family_ = std::move(v);
}

const std::unordered_map<std::string, std::list<dogen::archetypes::location> >& location_repository_parts::by_intra_backend_segment() const {
    return by_intra_backend_segment_;
}

std::unordered_map<std::string, std::list<dogen::archetypes::location> >& location_repository_parts::by_intra_backend_segment() {
    return by_intra_backend_segment_;
}

void location_repository_parts::by_intra_backend_segment(const std::unordered_map<std::string, std::list<dogen::archetypes::location> >& v) {
    by_intra_backend_segment_ = v;
}

void location_repository_parts::by_intra_backend_segment(const std::unordered_map<std::string, std::list<dogen::archetypes::location> >&& v) {
    by_intra_backend_segment_ = std::move(v);
}

}
