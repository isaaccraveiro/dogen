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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/test_data/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/test_data/primitive_implementation_transform.hpp"

namespace dogen::m2t::cpp::transforms::test_data {

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

std::list<std::string> primitive_implementation_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    const auto& p(assistant::as<logical::entities::structural::primitive>(e));
    auto builder(f.make());
    builder.add(p.name(), traits::primitive_header_archetype_qn());

    const auto carch(traits::canonical_archetype());
    builder.add(p.value_attribute().parsed_type().current(), carch);

    return builder.build();
}

void primitive_implementation_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, physical_meta_name(), false/*requires_header_guard*/, a);
    const auto& p(ast.as<logical::entities::structural::primitive>(e));

    const auto sn(p.name().simple());
    const auto qn(ast.get_qualified_name(p.name()));
    {

        auto sbf(ast.make_scoped_boilerplate_formatter(e));
ast.stream() << "namespace {" << std::endl;
        ast.add_helper_methods(p.name().qualified().dot());
ast.stream() << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        {
            const auto attr(p.value_attribute());
            const auto ns(ast.make_namespaces(p.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));

            /*
             * Default constructor.
             */
ast.stream() << std::endl;
ast.stream() << sn << "_generator::" << sn << "_generator() : position_(0) { }" << std::endl;
            /*
             * Populate method.
             */
            if (!p.is_immutable()) {
ast.stream() << std::endl;
ast.stream() << "void " << sn << "_generator::" << std::endl;
ast.stream() << "populate(const unsigned int position, result_type& v) {" << std::endl;
ast.stream() << "    v." << attr.name().simple() << "(create_" << attr.parsed_type().qualified().identifiable() << "(position + 1));" << std::endl;
ast.stream() << "}" << std::endl;
            }

            /*
             * Create method.
             */
ast.stream() << std::endl;
ast.stream() << sn << "_generator::result_type" << std::endl;
ast.stream() << sn << "_generator::create(const unsigned int position) {" << std::endl;
            if (p.is_immutable()) {
ast.stream() << "    return " << sn << "(create_" << attr.parsed_type().qualified().identifiable() << "(position + 1));" << std::endl;
            } else {
ast.stream() << "    " << sn << " r;" << std::endl;
ast.stream() << "    " << sn << "_generator::populate(position, r);" << std::endl;
ast.stream() << "    return r;" << std::endl;
            }
ast.stream() << "}" << std::endl;
            /*
             * Create method ptr.
             */
ast.stream() << std::endl;
ast.stream() << sn << "_generator::result_type*" << std::endl;
ast.stream() << sn << "_generator::create_ptr(const unsigned int position) {" << std::endl;
            if (p.is_immutable())
ast.stream() << "    return new " << sn << "(create(position));" << std::endl;
            else {
ast.stream() << "    " << sn << "* r = new " << sn << "();" << std::endl;
ast.stream() << "    " << sn << "_generator::populate(position, *r);" << std::endl;
ast.stream() << "    return r;" << std::endl;
            }
ast.stream() << "}" << std::endl;
            /*
             * Function operator
             */
ast.stream() << std::endl;
ast.stream() << sn << "_generator::result_type" << std::endl;
ast.stream() << sn << "_generator::operator()() {" << std::endl;
ast.stream() << "    return create(position_++);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        } // snf
    } // sbf
    ast.update_artefact();
}
}
