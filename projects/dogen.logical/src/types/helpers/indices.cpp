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
#include "dogen.logical/types/helpers/indices.hpp"

namespace dogen::logical::helpers {

indices::indices(
    const std::unordered_set<std::string>& objects_always_in_heap,
    const std::unordered_set<std::string>& elements_referable_by_attributes,
    const std::unordered_set<std::string>& primitive_underliers,
    const std::unordered_set<std::string>& enumeration_underliers,
    const std::unordered_set<std::string>& abstract_elements)
    : objects_always_in_heap_(objects_always_in_heap),
      elements_referable_by_attributes_(elements_referable_by_attributes),
      primitive_underliers_(primitive_underliers),
      enumeration_underliers_(enumeration_underliers),
      abstract_elements_(abstract_elements) { }

void indices::swap(indices& other) noexcept {
    using std::swap;
    swap(objects_always_in_heap_, other.objects_always_in_heap_);
    swap(elements_referable_by_attributes_, other.elements_referable_by_attributes_);
    swap(primitive_underliers_, other.primitive_underliers_);
    swap(enumeration_underliers_, other.enumeration_underliers_);
    swap(abstract_elements_, other.abstract_elements_);
}

bool indices::operator==(const indices& rhs) const {
    return objects_always_in_heap_ == rhs.objects_always_in_heap_ &&
        elements_referable_by_attributes_ == rhs.elements_referable_by_attributes_ &&
        primitive_underliers_ == rhs.primitive_underliers_ &&
        enumeration_underliers_ == rhs.enumeration_underliers_ &&
        abstract_elements_ == rhs.abstract_elements_;
}

indices& indices::operator=(indices other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_set<std::string>& indices::objects_always_in_heap() const {
    return objects_always_in_heap_;
}

std::unordered_set<std::string>& indices::objects_always_in_heap() {
    return objects_always_in_heap_;
}

void indices::objects_always_in_heap(const std::unordered_set<std::string>& v) {
    objects_always_in_heap_ = v;
}

void indices::objects_always_in_heap(const std::unordered_set<std::string>&& v) {
    objects_always_in_heap_ = std::move(v);
}

const std::unordered_set<std::string>& indices::elements_referable_by_attributes() const {
    return elements_referable_by_attributes_;
}

std::unordered_set<std::string>& indices::elements_referable_by_attributes() {
    return elements_referable_by_attributes_;
}

void indices::elements_referable_by_attributes(const std::unordered_set<std::string>& v) {
    elements_referable_by_attributes_ = v;
}

void indices::elements_referable_by_attributes(const std::unordered_set<std::string>&& v) {
    elements_referable_by_attributes_ = std::move(v);
}

const std::unordered_set<std::string>& indices::primitive_underliers() const {
    return primitive_underliers_;
}

std::unordered_set<std::string>& indices::primitive_underliers() {
    return primitive_underliers_;
}

void indices::primitive_underliers(const std::unordered_set<std::string>& v) {
    primitive_underliers_ = v;
}

void indices::primitive_underliers(const std::unordered_set<std::string>&& v) {
    primitive_underliers_ = std::move(v);
}

const std::unordered_set<std::string>& indices::enumeration_underliers() const {
    return enumeration_underliers_;
}

std::unordered_set<std::string>& indices::enumeration_underliers() {
    return enumeration_underliers_;
}

void indices::enumeration_underliers(const std::unordered_set<std::string>& v) {
    enumeration_underliers_ = v;
}

void indices::enumeration_underliers(const std::unordered_set<std::string>&& v) {
    enumeration_underliers_ = std::move(v);
}

const std::unordered_set<std::string>& indices::abstract_elements() const {
    return abstract_elements_;
}

std::unordered_set<std::string>& indices::abstract_elements() {
    return abstract_elements_;
}

void indices::abstract_elements(const std::unordered_set<std::string>& v) {
    abstract_elements_ = v;
}

void indices::abstract_elements(const std::unordered_set<std::string>&& v) {
    abstract_elements_ = std::move(v);
}

}
