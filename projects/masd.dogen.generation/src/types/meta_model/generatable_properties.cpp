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
#include "masd.dogen.generation/types/meta_model/generatable_properties.hpp"

namespace masd::dogen::generation::meta_model {

generatable_properties::generatable_properties(
    const masd::dogen::extraction::decoration_properties& decoration_properties,
    const std::unordered_map<std::string, masd::dogen::generation::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, masd::dogen::generation::meta_model::local_archetype_location_properties>& archetype_location_properties)
    : decoration_properties_(decoration_properties),
      artefact_properties_(artefact_properties),
      archetype_location_properties_(archetype_location_properties) { }

void generatable_properties::swap(generatable_properties& other) noexcept {
    using std::swap;
    swap(decoration_properties_, other.decoration_properties_);
    swap(artefact_properties_, other.artefact_properties_);
    swap(archetype_location_properties_, other.archetype_location_properties_);
}

bool generatable_properties::operator==(const generatable_properties& rhs) const {
    return decoration_properties_ == rhs.decoration_properties_ &&
        artefact_properties_ == rhs.artefact_properties_ &&
        archetype_location_properties_ == rhs.archetype_location_properties_;
}

generatable_properties& generatable_properties::operator=(generatable_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const masd::dogen::extraction::decoration_properties& generatable_properties::decoration_properties() const {
    return decoration_properties_;
}

masd::dogen::extraction::decoration_properties& generatable_properties::decoration_properties() {
    return decoration_properties_;
}

void generatable_properties::decoration_properties(const masd::dogen::extraction::decoration_properties& v) {
    decoration_properties_ = v;
}

void generatable_properties::decoration_properties(const masd::dogen::extraction::decoration_properties&& v) {
    decoration_properties_ = std::move(v);
}

const std::unordered_map<std::string, masd::dogen::generation::meta_model::artefact_properties>& generatable_properties::artefact_properties() const {
    return artefact_properties_;
}

std::unordered_map<std::string, masd::dogen::generation::meta_model::artefact_properties>& generatable_properties::artefact_properties() {
    return artefact_properties_;
}

void generatable_properties::artefact_properties(const std::unordered_map<std::string, masd::dogen::generation::meta_model::artefact_properties>& v) {
    artefact_properties_ = v;
}

void generatable_properties::artefact_properties(const std::unordered_map<std::string, masd::dogen::generation::meta_model::artefact_properties>&& v) {
    artefact_properties_ = std::move(v);
}

const std::unordered_map<std::string, masd::dogen::generation::meta_model::local_archetype_location_properties>& generatable_properties::archetype_location_properties() const {
    return archetype_location_properties_;
}

std::unordered_map<std::string, masd::dogen::generation::meta_model::local_archetype_location_properties>& generatable_properties::archetype_location_properties() {
    return archetype_location_properties_;
}

void generatable_properties::archetype_location_properties(const std::unordered_map<std::string, masd::dogen::generation::meta_model::local_archetype_location_properties>& v) {
    archetype_location_properties_ = v;
}

void generatable_properties::archetype_location_properties(const std::unordered_map<std::string, masd::dogen::generation::meta_model::local_archetype_location_properties>&& v) {
    archetype_location_properties_ = std::move(v);
}

}
