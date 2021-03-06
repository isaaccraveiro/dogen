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
#include <ostream>
#include <boost/io/ios_state.hpp>
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"

namespace dogen::logical::entities::structural {

builtin::builtin()
    : is_default_enumeration_type_(static_cast<bool>(0)),
      is_floating_point_(static_cast<bool>(0)),
      can_be_enumeration_underlier_(static_cast<bool>(0)),
      can_be_primitive_underlier_(static_cast<bool>(0)) { }

builtin::builtin(
    const dogen::logical::entities::name& name,
    const std::string& documentation,
    const dogen::logical::entities::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::logical::entities::name& meta_name,
    const dogen::logical::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& enablement_properties,
    const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const bool is_default_enumeration_type,
    const bool is_floating_point,
    const bool can_be_enumeration_underlier,
    const bool can_be_primitive_underlier)
    : dogen::logical::entities::element(
      name,
      documentation,
      origin_type,
      origin_sha1_hash,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      artefact_properties,
      enablement_properties,
      decoration),
      is_default_enumeration_type_(is_default_enumeration_type),
      is_floating_point_(is_floating_point),
      can_be_enumeration_underlier_(can_be_enumeration_underlier),
      can_be_primitive_underlier_(can_be_primitive_underlier) { }

void builtin::accept(const element_visitor& v) const {
    v.visit(*this);
}

void builtin::accept(element_visitor& v) const {
    v.visit(*this);
    }

void builtin::accept(const element_visitor& v) {
    v.visit(*this);
}

void builtin::accept(element_visitor& v) {
    v.visit(*this);
}

void builtin::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::structural::builtin\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"is_default_enumeration_type\": " << is_default_enumeration_type_ << ", "
      << "\"is_floating_point\": " << is_floating_point_ << ", "
      << "\"can_be_enumeration_underlier\": " << can_be_enumeration_underlier_ << ", "
      << "\"can_be_primitive_underlier\": " << can_be_primitive_underlier_
      << " }";
}

void builtin::swap(builtin& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(is_default_enumeration_type_, other.is_default_enumeration_type_);
    swap(is_floating_point_, other.is_floating_point_);
    swap(can_be_enumeration_underlier_, other.can_be_enumeration_underlier_);
    swap(can_be_primitive_underlier_, other.can_be_primitive_underlier_);
}

bool builtin::equals(const dogen::logical::entities::element& other) const {
    const builtin* const p(dynamic_cast<const builtin* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool builtin::operator==(const builtin& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        is_default_enumeration_type_ == rhs.is_default_enumeration_type_ &&
        is_floating_point_ == rhs.is_floating_point_ &&
        can_be_enumeration_underlier_ == rhs.can_be_enumeration_underlier_ &&
        can_be_primitive_underlier_ == rhs.can_be_primitive_underlier_;
}

builtin& builtin::operator=(builtin other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool builtin::is_default_enumeration_type() const {
    return is_default_enumeration_type_;
}

void builtin::is_default_enumeration_type(const bool v) {
    is_default_enumeration_type_ = v;
}

bool builtin::is_floating_point() const {
    return is_floating_point_;
}

void builtin::is_floating_point(const bool v) {
    is_floating_point_ = v;
}

bool builtin::can_be_enumeration_underlier() const {
    return can_be_enumeration_underlier_;
}

void builtin::can_be_enumeration_underlier(const bool v) {
    can_be_enumeration_underlier_ = v;
}

bool builtin::can_be_primitive_underlier() const {
    return can_be_primitive_underlier_;
}

void builtin::can_be_primitive_underlier(const bool v) {
    can_be_primitive_underlier_ = v;
}

}
