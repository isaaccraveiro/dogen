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
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.m2t.cpp/types/formattables/formattable.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::element>& lhs,
const boost::shared_ptr<dogen::logical::entities::element>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::physical::entities::artefact>& lhs,
const boost::shared_ptr<dogen::physical::entities::artefact>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::m2t::cpp::formattables {

formattable::formattable(
    const boost::shared_ptr<dogen::logical::entities::element>& element,
    const dogen::m2t::cpp::formattables::element_properties& element_properties,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> >& artefacts)
    : element_(element),
      element_properties_(element_properties),
      artefacts_(artefacts) { }

void formattable::swap(formattable& other) noexcept {
    using std::swap;
    swap(element_, other.element_);
    swap(element_properties_, other.element_properties_);
    swap(artefacts_, other.artefacts_);
}

bool formattable::operator==(const formattable& rhs) const {
    return element_ == rhs.element_ &&
        element_properties_ == rhs.element_properties_ &&
        artefacts_ == rhs.artefacts_;
}

formattable& formattable::operator=(formattable other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::logical::entities::element>& formattable::element() const {
    return element_;
}

boost::shared_ptr<dogen::logical::entities::element>& formattable::element() {
    return element_;
}

void formattable::element(const boost::shared_ptr<dogen::logical::entities::element>& v) {
    element_ = v;
}

void formattable::element(const boost::shared_ptr<dogen::logical::entities::element>&& v) {
    element_ = std::move(v);
}

const dogen::m2t::cpp::formattables::element_properties& formattable::element_properties() const {
    return element_properties_;
}

dogen::m2t::cpp::formattables::element_properties& formattable::element_properties() {
    return element_properties_;
}

void formattable::element_properties(const dogen::m2t::cpp::formattables::element_properties& v) {
    element_properties_ = v;
}

void formattable::element_properties(const dogen::m2t::cpp::formattables::element_properties&& v) {
    element_properties_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> >& formattable::artefacts() const {
    return artefacts_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> >& formattable::artefacts() {
    return artefacts_;
}

void formattable::artefacts(const std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> >& v) {
    artefacts_ = v;
}

void formattable::artefacts(const std::unordered_map<std::string, boost::shared_ptr<dogen::physical::entities::artefact> >&& v) {
    artefacts_ = std::move(v);
}

}
