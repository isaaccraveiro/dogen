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
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/build/cmakelists.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/build/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/build/include_cmakelists_transform.hpp"

namespace dogen::m2t::cpp::transforms::build {

std::string include_cmakelists_transform::static_id() {
    return traits::include_cmakelists_archetype_qn();
}

std::string include_cmakelists_transform::id() const {
    return static_id();
}

physical::entities::meta_name
include_cmakelists_transform::physical_meta_name() const {
    using physical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make(cpp::traits::backend_sn(),
        traits::facet_sn(), traits::include_cmakelists_archetype_sn()));
    return r;
}

const logical::entities::name& include_cmakelists_transform::logical_meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_build_cmakelists_name());
    return r;
}

inclusion_support_types include_cmakelists_transform::
inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path include_cmakelists_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    using namespace dogen::m2t::cpp::transforms;
    static logger lg(logger_factory(include_cmakelists_transform::static_id()));

    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path include_cmakelists_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_include_cmakelists(n, static_id());
}

std::list<std::string> include_cmakelists_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const logical::entities::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

void include_cmakelists_transform::apply(const context& ctx,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    assistant ast(ctx, e, physical_meta_name(), false/*requires_header_guard*/, a);
    using logical::entities::build::cmakelists;
    const auto& c(ast.as<cmakelists>(e));

    {
        const auto ts(logical::entities::technical_space::cmake);
        ast.make_decoration_preamble(e, ts);
ast.stream() << "add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/" << c.source_directory_name() << ")" << std::endl;
       if (ast.is_tests_enabled()) {
ast.stream() << "add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/" << c.tests_directory_name() << ")" << std::endl;
       }
ast.stream() << std::endl;
ast.stream() << "install(" << std::endl;
ast.stream() << "    DIRECTORY " << c.include_directory_path() << "/" << std::endl;
ast.stream() << "    DESTINATION " << c.include_directory_path() << "/" << std::endl;
ast.stream() << "    COMPONENT headers" << std::endl;
ast.stream() << "    FILES_MATCHING PATTERN \"*." << c.header_file_extension() << "\")" << std::endl;
    } // sbf
    ast.update_artefact();
}
}
