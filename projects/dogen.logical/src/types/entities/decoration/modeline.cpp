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
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/io/entities/decoration/editor_io.hpp"
#include "dogen.logical/types/entities/decoration/modeline.hpp"
#include "dogen.logical/io/entities/decoration/modeline_field_io.hpp"
#include "dogen.logical/io/entities/decoration/modeline_location_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::logical::entities::decoration::modeline_field>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::logical::entities::decoration {

modeline::modeline()
    : editor_(static_cast<dogen::logical::entities::decoration::editor>(0)),
      location_(static_cast<dogen::logical::entities::decoration::modeline_location>(0)),
      technical_space_(static_cast<dogen::logical::entities::technical_space>(0)) { }

modeline::modeline(
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
    const dogen::logical::entities::decoration::editor editor,
    const dogen::logical::entities::decoration::modeline_location location,
    const std::list<dogen::logical::entities::decoration::modeline_field>& fields,
    const dogen::logical::entities::technical_space technical_space)
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
      editor_(editor),
      location_(location),
      fields_(fields),
      technical_space_(technical_space) { }

void modeline::accept(const element_visitor& v) const {
    v.visit(*this);
}

void modeline::accept(element_visitor& v) const {
    v.visit(*this);
    }

void modeline::accept(const element_visitor& v) {
    v.visit(*this);
}

void modeline::accept(element_visitor& v) {
    v.visit(*this);
}

void modeline::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::decoration::modeline\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"editor\": " << editor_ << ", "
      << "\"location\": " << location_ << ", "
      << "\"fields\": " << fields_ << ", "
      << "\"technical_space\": " << technical_space_
      << " }";
}

void modeline::swap(modeline& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(editor_, other.editor_);
    swap(location_, other.location_);
    swap(fields_, other.fields_);
    swap(technical_space_, other.technical_space_);
}

bool modeline::equals(const dogen::logical::entities::element& other) const {
    const modeline* const p(dynamic_cast<const modeline* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool modeline::operator==(const modeline& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        editor_ == rhs.editor_ &&
        location_ == rhs.location_ &&
        fields_ == rhs.fields_ &&
        technical_space_ == rhs.technical_space_;
}

modeline& modeline::operator=(modeline other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::logical::entities::decoration::editor modeline::editor() const {
    return editor_;
}

void modeline::editor(const dogen::logical::entities::decoration::editor v) {
    editor_ = v;
}

dogen::logical::entities::decoration::modeline_location modeline::location() const {
    return location_;
}

void modeline::location(const dogen::logical::entities::decoration::modeline_location v) {
    location_ = v;
}

const std::list<dogen::logical::entities::decoration::modeline_field>& modeline::fields() const {
    return fields_;
}

std::list<dogen::logical::entities::decoration::modeline_field>& modeline::fields() {
    return fields_;
}

void modeline::fields(const std::list<dogen::logical::entities::decoration::modeline_field>& v) {
    fields_ = v;
}

void modeline::fields(const std::list<dogen::logical::entities::decoration::modeline_field>&& v) {
    fields_ = std::move(v);
}

dogen::logical::entities::technical_space modeline::technical_space() const {
    return technical_space_;
}

void modeline::technical_space(const dogen::logical::entities::technical_space v) {
    technical_space_ = v;
}

}
