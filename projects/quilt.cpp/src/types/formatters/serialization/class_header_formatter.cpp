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
#include <typeinfo>
#include <boost/make_shared.hpp>
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/class_header_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/class_header_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace serialization {

std::string class_header_formatter::static_formatter_name() {
    return traits::class_header_formatter_name();
}

std::string class_header_formatter::id() const {
    static auto r(ownership_hierarchy().formatter_name());
    return r;
}

annotations::ownership_hierarchy
class_header_formatter::ownership_hierarchy() const {
    static annotations::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            class_header_formatter::static_formatter_name());
    return r;
}

std::type_index class_header_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(yarn::object)));
    return r;
}

std::list<std::string> class_header_formatter::inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& f,
    const yarn::element& e) const {
    const auto& o(assistant::as<yarn::object>(static_formatter_name(), e));
    auto builder(f.make());
    builder.add(o.name(), types::traits::class_header_formatter_name());

    using ic = inclusion_constants;
    builder.add(ic::boost::serialization::split_free());

    if (o.is_parent())
        builder.add(ic::boost::serialization::assume_abstract());

    if (!o.is_parent() && o.is_child())
        builder.add(ic::boost::type_traits::is_virtual_base_of());

    return builder.build();
}

inclusion_support_types class_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path class_header_formatter::inclusion_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_formatter_name());
}

boost::filesystem::path class_header_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_formatter_name());
}

dogen::formatters::artefact class_header_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, ownership_hierarchy(), true/*requires_header_guard*/, id);
    const auto& o(a.as<yarn::object>(static_formatter_name(), e));
    const auto r(class_header_formatter_stitch(a, o));
    return r;
}

} } } } }
