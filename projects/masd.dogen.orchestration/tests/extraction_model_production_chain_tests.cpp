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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include "masd.dogen/types/mock_configuration_factory.hpp"
#include "masd.dogen.utility/types/test/logging.hpp"
#include "masd.dogen.utility/types/test_data/dogen_generation.hpp"
#include "masd.dogen.extraction/io/meta_model/operation_io.hpp"
#include "masd.dogen.orchestration/types/transforms/scoped_context_manager.hpp"
#include "masd.dogen.orchestration/types/transforms/extraction_model_production_chain.hpp"

/*
 * Comment these out as required if testing only one frontend. These
 * should all be enabled in git, do not check them in commented out by
 * mistake.
 */
#define ENABLE_DIA_TESTS
#define ENABLE_JSON_TESTS

namespace  {

const std::string run_activity("extraction_production");
const std::string test_module("masd.dogen.orchestration.tests");
const std::string test_suite("extraction_model_production_chain_tests");

/*
 * Set this flag to true if you want to dump tracing information for
 * all tests. It should normally be set to false, unless we are
 * diagnosing some kind of problem. Don't check it in as true.
 */
const bool enable_tracing_globally(false);

void print_lines(const std::string& content, const unsigned int total,
    std::ostream& os) {

    unsigned int i(0);
    std::string line;
    std::istringstream is(content);
    while (std::getline(is, line) && (i < total)) {
        os << line << std::endl;
        ++i;
    }
}

bool check_for_differences(const boost::filesystem::path& output_dir,
    const masd::dogen::extraction::meta_model::model& m) {

    unsigned int diffs_found(0);
    for (const auto& a : m.artefacts()) {
        using namespace masd::dogen::extraction::meta_model;
        /*
         * FIXME: we seem to be generating empty paths. Needs to be
         * investigated. Hack for now
         */
        if (a.path().empty())
            continue;

        if (a.operation().type() != operation_type::write &&
            a.operation().type() != operation_type::remove)
            continue;

        if (diffs_found == 0) {
            std::cout << "Differences found. Outputting first five."
                      << std::endl;
        }

        ++diffs_found;
        if (diffs_found > 5)
            break;

        if (a.operation().type() == operation_type::remove) {
            std::cout << "Unexpected file: "
                      << a.path().lexically_relative(output_dir)
                      << std::endl;
        } else if (a.operation().type() == operation_type::write) {
            if (a.operation().reason() == operation_reason::newly_generated) {
                std::cout << "New file: "
                          << a.path().lexically_relative(output_dir)
                          << std::endl;
            } else
                print_lines(a.unified_diff(), 20, std::cout);
        }
    }
    return diffs_found == 0;
}

bool test_extraction_model_production(const boost::filesystem::path& target,
    const boost::filesystem::path& output_dir, bool enable_tracing_locally) {
    using masd::dogen::mock_configuration_factory;
    /*
     * Create the context.
     */
    const bool et(enable_tracing_globally || enable_tracing_locally);
    const auto cfg(mock_configuration_factory::make(target, et, run_activity));

    using namespace masd::dogen::orchestration::transforms;
    scoped_context_manager sco(cfg, output_dir);
    const auto ctx(sco.context());

    /*
     * Produce the extraction model.
     */
    const auto m(extraction_model_production_chain::transform(ctx, target));

    /*
     * Locate any differences.
     */
    return check_for_differences(output_dir, m);
}

}

BOOST_AUTO_TEST_SUITE(extraction_model_production_chain_tests)

#ifdef ENABLE_DIA_TESTS

BOOST_AUTO_TEST_CASE(masd_dogen_annotations_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_annotations_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_annotations_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_cli_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_cli_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_cli_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_coding_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_coding_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_coding_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_dia_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_dia_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_dia_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_extraction_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_extraction_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_extraction_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_generation_cpp_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_cpp_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_generation_cpp_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_generation_csharp_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_csharp_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_generation_csharp_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_generation_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_generation_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_injection_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_injection_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_injection_dia_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_injection_dia_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_injection_dia_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_injection_json_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_injection_json_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_injection_json_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_orchestration_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_orchestration_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_orchestration_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_templating_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_templating_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_templating_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_tracing_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_tracing_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_tracing_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_utility_dia_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_utility_dia_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_utility_dia());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

#endif // ENABLE_DIA_TESTS

#ifdef ENABLE_JSON_TESTS

BOOST_AUTO_TEST_CASE(masd_dogen_annotations_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_annotations_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_annotations_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_cli_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_cli_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_cli_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_coding_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_coding_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_coding_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_dia_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_dia_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_dia_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_extraction_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_extraction_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_extraction_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_generation_cpp_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_cpp_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_generation_cpp_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_generation_csharp_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_csharp_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_generation_csharp_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_generation_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_generation_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_injection_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_generation_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_injection_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_injection_dia_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_injection_dia_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_injection_dia_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_injection_json_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_injection_json_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_injection_json_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_orchestration_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_orchestration_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_orchestration_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_templating_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_templating_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_templating_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_tracing_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_tracing_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_tracing_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

BOOST_AUTO_TEST_CASE(masd_dogen_utility_json_produces_expected_model) {
    SETUP_TEST_LOG("masd_dogen_utility_json_produces_expected_model");
    using masd::dogen::utility::test_data::dogen_generation;
    const bool ep(false/*enable tracing locally*/);
    const auto t(dogen_generation::input_masd_dogen_utility_json());
    const auto od(dogen_generation::project_directory());
    BOOST_CHECK(test_extraction_model_production(t, od, ep));
}

#endif // ENABLE_JSON_TESTS

BOOST_AUTO_TEST_SUITE_END()