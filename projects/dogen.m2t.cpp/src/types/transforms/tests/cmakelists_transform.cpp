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
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/build/cmakelists.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/tests/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/tests/cmakelists_transform.hpp"

namespace dogen::m2t::cpp::transforms::tests {

std::string cmakelists_transform::static_id() {
    return tests::traits::cmakelists_archetype_qn();
}

std::string cmakelists_transform::id() const {
    return static_id();
}

physical::entities::meta_name
cmakelists_transform::physical_meta_name() const {
    using physical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make(cpp::traits::backend_sn(),
        traits::facet_sn(), tests::traits::cmakelists_archetype_sn()));
    return r;
}

const logical::entities::name& cmakelists_transform::logical_meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_build_cmakelists_name());
    return r;
}

inclusion_support_types cmakelists_transform::
inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path cmakelists_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    using namespace dogen::m2t::cpp::transforms;
    static logger lg(logger_factory(cmakelists_transform::static_id()));

    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path cmakelists_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_tests_cmakelists(n, static_id());
}

std::list<std::string> cmakelists_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const logical::entities::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

void cmakelists_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, physical_meta_name(), false/*requires_header_guard*/, a);
    using logical::entities::build::cmakelists;
    const auto& c(ast.as<cmakelists>(e));

    {

        const auto ts(logical::entities::technical_space::cmake);
        ast.make_decoration_preamble(e, ts);
        const auto model_name(ast.get_dot_separated_model_name(c.name()));
        const auto product_name(ast.get_product_name(c.name()));
ast.stream() << "set(name \"" << model_name << "\")" << std::endl;
ast.stream() << "set(lib_target_name ${name}.lib)" << std::endl;
ast.stream() << "set(tests_binary_name ${name}." << c.tests_directory_name() << ")" << std::endl;
ast.stream() << "set(tests_target_name ${name}." << c.tests_directory_name() << ")" << std::endl;
ast.stream() << std::endl;
ast.stream() << "set(files \"\")" << std::endl;
ast.stream() << "file(GLOB_RECURSE files RELATIVE" << std::endl;
ast.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/\"" << std::endl;
ast.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/*." << c.implementation_file_extension() << "\")" << std::endl;
ast.stream() << std::endl;
ast.stream() << "add_executable(${tests_target_name} ${files})" << std::endl;
ast.stream() << std::endl;
ast.stream() << "set_target_properties(${tests_target_name} PROPERTIES" << std::endl;
        if (ast.is_cpp_standard_98()) {
ast.stream() << "    CXX_STANDARD 98" << std::endl;
        }
ast.stream() << "    OUTPUT_NAME ${tests_binary_name})" << std::endl;
ast.stream() << std::endl;
        if (ast.is_cpp_standard_98()) {
ast.stream() << "target_compile_options(${tests_target_name} PRIVATE" << std::endl;
ast.stream() << "    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:" << std::endl;
ast.stream() << "    -Wno-c99-extensions>)" << std::endl;
        }
ast.stream() << std::endl;
ast.stream() << "target_link_libraries(${tests_target_name}" << std::endl;
ast.stream() << "    ${lib_target_name}" << std::endl;
ast.stream() << "    ${CMAKE_REQUIRED_LIBRARIES}" << std::endl;
ast.stream() << "    ${CMAKE_THREAD_LIBS_INIT}" << std::endl;
ast.stream() << "    ${Boost_LIBRARIES})" << std::endl;
ast.stream() << std::endl;
ast.stream() << "set(command $<TARGET_FILE:${tests_target_name}> ${boost_test_parameters})" << std::endl;
ast.stream() << std::endl;
ast.stream() << "add_custom_target(run_${tests_target_name}" << std::endl;
ast.stream() << "    COMMENT \"Running ${tests_target_name}\" VERBATIM" << std::endl;
ast.stream() << "    COMMAND ${command}" << std::endl;
ast.stream() << "    WORKING_DIRECTORY ${stage_bin_dir}" << std::endl;
ast.stream() << "    DEPENDS ${tests_target_name})" << std::endl;
ast.stream() << std::endl;
ast.stream() << "add_dependencies(run_all_tests run_${tests_target_name})" << std::endl;
ast.stream() << std::endl;
ast.stream() << "if(WITH_BENCHMARKS)" << std::endl;
ast.stream() << "    set(benchmark_file" << std::endl;
ast.stream() << "        ${benchmark_directory}/${benchmark_prefix}${tests_target_name}.csv)" << std::endl;
ast.stream() << "    add_custom_target(benchmark_${tests_target_name}" << std::endl;
ast.stream() << "        COMMENT \"Benchmarking testing ${tests_target_name}\" VERBATIM" << std::endl;
ast.stream() << "        COMMAND ${benchmark_command} ${benchmark_repeats} ${benchmark_file}" << std::endl;
ast.stream() << "        ${command}" << std::endl;
ast.stream() << "        WORKING_DIRECTORY ${stage_bin_dir}" << std::endl;
ast.stream() << "        DEPENDS ${tests_target_name})" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    add_dependencies(benchmark_all benchmark_${tests_target_name})" << std::endl;
ast.stream() << "endif()" << std::endl;
ast.stream() << std::endl;
ast.stream() << "add_boost_tests(${tests_binary_name} ${files})" << std::endl;
ast.stream() << std::endl;
ast.stream() << "install(TARGETS ${tests_target_name} RUNTIME DESTINATION bin COMPONENT tests)" << std::endl;
    } // sbf
    ast.update_artefact();
}
}
