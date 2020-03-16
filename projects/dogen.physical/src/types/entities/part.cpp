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
#include "dogen.physical/types/entities/part.hpp"

namespace dogen::physical::entities {

part::part(
    const std::string& directory_name,
    const dogen::physical::entities::location& location,
    const std::string& description,
    const dogen::physical::entities::path_configuration& path_configuration,
    const std::unordered_map<std::string, dogen::physical::entities::facet>& facets,
    const std::unordered_map<std::string, dogen::physical::entities::archetype>& archetypes)
    : directory_name_(directory_name),
      location_(location),
      description_(description),
      path_configuration_(path_configuration),
      facets_(facets),
      archetypes_(archetypes) { }

void part::swap(part& other) noexcept {
    using std::swap;
    swap(directory_name_, other.directory_name_);
    swap(location_, other.location_);
    swap(description_, other.description_);
    swap(path_configuration_, other.path_configuration_);
    swap(facets_, other.facets_);
    swap(archetypes_, other.archetypes_);
}

bool part::operator==(const part& rhs) const {
    return directory_name_ == rhs.directory_name_ &&
        location_ == rhs.location_ &&
        description_ == rhs.description_ &&
        path_configuration_ == rhs.path_configuration_ &&
        facets_ == rhs.facets_ &&
        archetypes_ == rhs.archetypes_;
}

part& part::operator=(part other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& part::directory_name() const {
    return directory_name_;
}

std::string& part::directory_name() {
    return directory_name_;
}

void part::directory_name(const std::string& v) {
    directory_name_ = v;
}

void part::directory_name(const std::string&& v) {
    directory_name_ = std::move(v);
}

const dogen::physical::entities::location& part::location() const {
    return location_;
}

dogen::physical::entities::location& part::location() {
    return location_;
}

void part::location(const dogen::physical::entities::location& v) {
    location_ = v;
}

void part::location(const dogen::physical::entities::location&& v) {
    location_ = std::move(v);
}

const std::string& part::description() const {
    return description_;
}

std::string& part::description() {
    return description_;
}

void part::description(const std::string& v) {
    description_ = v;
}

void part::description(const std::string&& v) {
    description_ = std::move(v);
}

const dogen::physical::entities::path_configuration& part::path_configuration() const {
    return path_configuration_;
}

dogen::physical::entities::path_configuration& part::path_configuration() {
    return path_configuration_;
}

void part::path_configuration(const dogen::physical::entities::path_configuration& v) {
    path_configuration_ = v;
}

void part::path_configuration(const dogen::physical::entities::path_configuration&& v) {
    path_configuration_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::facet>& part::facets() const {
    return facets_;
}

std::unordered_map<std::string, dogen::physical::entities::facet>& part::facets() {
    return facets_;
}

void part::facets(const std::unordered_map<std::string, dogen::physical::entities::facet>& v) {
    facets_ = v;
}

void part::facets(const std::unordered_map<std::string, dogen::physical::entities::facet>&& v) {
    facets_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::archetype>& part::archetypes() const {
    return archetypes_;
}

std::unordered_map<std::string, dogen::physical::entities::archetype>& part::archetypes() {
    return archetypes_;
}

void part::archetypes(const std::unordered_map<std::string, dogen::physical::entities::archetype>& v) {
    archetypes_ = v;
}

void part::archetypes(const std::unordered_map<std::string, dogen::physical::entities::archetype>&& v) {
    archetypes_ = std::move(v);
}

}