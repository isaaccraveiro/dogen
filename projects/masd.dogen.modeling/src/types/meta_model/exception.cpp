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
#include "masd.dogen.modeling/io/meta_model/element_io.hpp"
#include "masd.dogen.modeling/types/meta_model/exception.hpp"
#include "masd.dogen.modeling/types/meta_model/element_visitor.hpp"

namespace masd::dogen::modeling::meta_model {

exception::exception(
    const masd::dogen::modeling::meta_model::name& name,
    const std::string& documentation,
    const masd::dogen::annotations::annotation& annotation,
    const masd::dogen::modeling::meta_model::origin_types origin_type,
    const boost::optional<masd::dogen::modeling::meta_model::name>& contained_by,
    const bool in_global_module,
    const std::list<masd::dogen::modeling::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const masd::dogen::modeling::meta_model::name& meta_name,
    const bool is_element_extension,
    const masd::dogen::formatting::decoration_properties& decoration_properties,
    const std::unordered_map<std::string, masd::dogen::modeling::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, masd::dogen::modeling::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::modeling::meta_model::opaque_properties> >& opaque_properties)
    : masd::dogen::modeling::meta_model::element(
      name,
      documentation,
      annotation,
      origin_type,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      is_element_extension,
      decoration_properties,
      artefact_properties,
      archetype_location_properties,
      opaque_properties) { }

void exception::accept(const element_visitor& v) const {
    v.visit(*this);
}

void exception::accept(element_visitor& v) const {
    v.visit(*this);
    }

void exception::accept(const element_visitor& v) {
    v.visit(*this);
}

void exception::accept(element_visitor& v) {
    v.visit(*this);
}

void exception::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::modeling::meta_model::exception\"" << ", "
      << "\"__parent_0__\": ";
    masd::dogen::modeling::meta_model::element::to_stream(s);
    s << " }";
}

void exception::swap(exception& other) noexcept {
    masd::dogen::modeling::meta_model::element::swap(other);

}

bool exception::equals(const masd::dogen::modeling::meta_model::element& other) const {
    const exception* const p(dynamic_cast<const exception* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool exception::operator==(const exception& rhs) const {
    return masd::dogen::modeling::meta_model::element::compare(rhs);
}

exception& exception::operator=(exception other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

}