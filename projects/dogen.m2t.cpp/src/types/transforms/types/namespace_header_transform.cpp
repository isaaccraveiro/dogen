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
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/types/namespace_header_transform.hpp"

namespace dogen::m2t::cpp::transforms::types {

std::string namespace_header_transform::static_id() {
    return traits::namespace_header_archetype();
}

std::string namespace_header_transform::id() const {
    return static_id();
}

physical::entities::location
namespace_header_transform::archetype_location() const {
    static physical::entities::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          cpp::traits::public_headers_part(), traits::facet(),
          namespace_header_transform::static_id());
    return r;
}

const logical::entities::name& namespace_header_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_module_name());
    return r;
}

inclusion_support_types namespace_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path namespace_header_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path namespace_header_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> namespace_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const logical::entities::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

physical::entities::artefact namespace_header_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location(), true/*requires_header_guard*/);
    const auto& m(a.as<logical::entities::structural::module>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            if (a.requires_nested_namespaces()) {
                a.comment(m.documentation());
                const auto ns(a.make_namespaces(e.name(),
                        false/*detect_model_name*/));
                auto snf(a.make_scoped_namespace_formatter(ns));
            } else {
                const auto ns(a.make_namespaces(m.name()));
                auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
                a.comment(m.documentation());
a.stream() << "namespace " << m.name().simple() << " {" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }
        } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}

}
