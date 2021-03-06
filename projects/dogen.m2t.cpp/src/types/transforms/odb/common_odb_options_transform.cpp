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
#include <boost/algorithm/string/case_conv.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/orm/common_odb_options.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/odb/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/odb/common_odb_options_transform.hpp"

namespace dogen::m2t::cpp::transforms::odb {

std::string common_odb_options_transform::static_id() {
    return traits::common_odb_options_archetype_qn();
}

std::string common_odb_options_transform::id() const {
    static auto r(static_id());
    return r;
}

physical::entities::meta_name
common_odb_options_transform::physical_meta_name() const {
    using physical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make(cpp::traits::backend_sn(),
        traits::facet_sn(), traits::common_odb_options_archetype_sn()));
    return r;
}

const logical::entities::name& common_odb_options_transform::logical_meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_orm_common_odb_options_name());
    return r;
}

inclusion_support_types
common_odb_options_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path common_odb_options_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {
    using namespace dogen::utility::log;
    static logger
        lg(logger_factory("m2t.cpp.transforms.odb.common_odb_options_transform"));

    const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path common_odb_options_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_odb_options(n, static_id());
}

std::list<std::string> common_odb_options_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const logical::entities::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

void common_odb_options_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, physical_meta_name(), false/*requires_header_guard*/, a);
    using logical::entities::orm::common_odb_options;
    const auto& o(ast.as<common_odb_options>(e));

    {
        const auto ts(logical::entities::technical_space::odb);
        ast.make_decoration_preamble(e, ts);

        if (!ast.is_cpp_standard_98()) {
ast.stream() << "# enable C++11" << std::endl;
ast.stream() << "--std c++11" << std::endl;
ast.stream() << std::endl;
        }

        if (!o.sql_name_case().empty()) {
ast.stream() << "# casing" << std::endl;
ast.stream() << "--sql-name-case " << o.sql_name_case() << std::endl;
ast.stream() << std::endl;
        }

        if (o.databases().size() > 1) {
ast.stream() << "# enable multi-database support" << std::endl;
ast.stream() << "--multi-database static" << std::endl;
ast.stream() << std::endl;
        }

        if (!o.databases().empty()) {
ast.stream() << "# target databases" << std::endl;

            for (const auto& d : o.databases())
ast.stream() << "--database " << d << std::endl;
ast.stream() << std::endl;
        }
ast.stream() << "# use the boost profile" << std::endl;
ast.stream() << "--profile boost" << std::endl;
ast.stream() << std::endl;
ast.stream() << "# generate queries and embedded schemas" << std::endl;
ast.stream() << "--generate-query" << std::endl;
ast.stream() << "--generate-schema" << std::endl;
ast.stream() << "--schema-format embedded" << std::endl;
ast.stream() << std::endl;
ast.stream() << "# force odb extensions to be different from dogen ones just in case." << std::endl;
ast.stream() << "--ixx-suffix .ixx" << std::endl;
ast.stream() << "--hxx-suffix .hxx" << std::endl;
ast.stream() << "--cxx-suffix .cxx" << std::endl;
ast.stream() << std::endl;
ast.stream() << "# debug regexes" << std::endl;
ast.stream() << "# --include-regex-trace" << std::endl;
    } // sbf
    ast.update_artefact();
}
}
