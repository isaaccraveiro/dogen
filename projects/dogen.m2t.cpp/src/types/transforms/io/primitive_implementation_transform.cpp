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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/hash/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/io/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/io/inserter_implementation_helper.hpp"
#include "dogen.m2t.cpp/types/transforms/io/primitive_implementation_transform.hpp"

namespace dogen::m2t::cpp::transforms::io {

std::string primitive_implementation_transform::static_id() {
    return traits::primitive_implementation_archetype_qn();
}

std::string primitive_implementation_transform::id() const {
    return static_id();
}

physical::entities::meta_name
primitive_implementation_transform::physical_meta_name() const {
    using physical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make(cpp::traits::backend_sn(),
        traits::facet_sn(), traits::primitive_implementation_archetype_sn()));
    return r;
}

const logical::entities::name& primitive_implementation_transform::logical_meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_primitive_name());
    return r;
}

inclusion_support_types primitive_implementation_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path primitive_implementation_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(primitive_implementation_transform::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path primitive_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
}

std::list<std::string>
primitive_implementation_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    using logical::entities::structural::primitive;
    const auto& p(assistant::as<primitive>(e));
    auto builder(f.make());
    const auto ph_fn(traits::primitive_header_archetype_qn());
    builder.add(p.name(), ph_fn);

    const auto io_carch(transforms::io::traits::canonical_archetype());
    const auto self_fn(primitive_implementation_transform::static_id());
    const bool io_enabled(builder.is_enabled(p.name(), self_fn));

    if (!io_enabled)
        return builder.build();

    const auto os(inclusion_constants::std::ostream());
    builder.add(os);
    builder.add(p.value_attribute().parsed_type().current(), io_carch);

    return builder.build();
}

void primitive_implementation_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, physical_meta_name(), false/*requires_header_guard*/, a);
    const auto& p(ast.as<logical::entities::structural::primitive>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        ast.add_helper_methods(p.name().qualified().dot());

        {
            const auto ns(ast.make_namespaces(p.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            const auto sn(p.name().simple());
            const auto qn(ast.get_qualified_name(p.name()));
            const auto attr(p.value_attribute());
ast.stream() << std::endl;
ast.stream() << "std::ostream& operator<<(std::ostream& s, const " << sn << "& v) {" << std::endl;
            if (ast.requires_stream_manipulators()) {
ast.stream() << "    boost::io::ios_flags_saver ifs(s);" << std::endl;
ast.stream() << "    s.setf(std::ios_base::boolalpha);" << std::endl;
ast.stream() << "    s.setf(std::ios::fixed, std::ios::floatfield);" << std::endl;
ast.stream() << "    s.precision(6);" << std::endl;
ast.stream() << "    s.setf(std::ios::showpoint);" << std::endl;
            }

            const std::string variable_name = "v." + attr.getter_setter_name() + "()";
ast.stream() << std::endl;
ast.stream() << "    s << \" { \"" << std::endl;
ast.stream() << "      << \"\\\"__type__\\\": \" << \"\\\"" << qn << "\\\"\" << \", \"" << std::endl;
ast.stream() << "      << \"\\\"" << attr.name().simple() << "\\\": \" << " << ast.streaming_for_type(attr.parsed_type().current(), variable_name) << std::endl;
ast.stream() << "      << \" }\";" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    return s;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        } // snf
    } // sbf
    ast.update_artefact();
}
}
