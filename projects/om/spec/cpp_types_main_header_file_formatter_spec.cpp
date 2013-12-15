/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/exception/utility_exception.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/meta_data_writer.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/module_io.hpp"
#include "dogen/sml/io/object_io.hpp"
#include "dogen/sml/io/enumeration_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/om/types/cpp_types_main_header_file_formatter.hpp"
#include "dogen/om/io/file_io.hpp"

namespace {

const std::string test_module("om");
const std::string test_suite("cpp_types_main_header_file_formatter_spec");

using dogen::sml::test::mock_model_factory;
const mock_model_factory factory(false/*tagged*/);

const std::string empty_marker;
const dogen::om::licence empty_licence = dogen::om::licence();
const dogen::om::modeline empty_modeline = dogen::om::modeline();
const dogen::om::annotation empty_annotation(
    empty_modeline, empty_licence, empty_marker);
const boost::filesystem::path empty_path;
const boost::filesystem::path non_empty_path("a/file.hpp");

const std::string enumeration_two_enumerators(R"(namespace some_model_0 {

/**
 * @brief Some documentation
 */
enum class some_type_0 : unsigned int {
    some_type_0 = 0, ///< Some documentation
    some_type_1 = 1 ///< Some documentation
};

}
)");

const std::string object_no_properties(R"(namespace some_model_0 {

/**
 * @brief Some documentation
 */
class some_type_0 final {
};

}
)");

const std::string parent_object(R"(namespace some_model_0 {

/**
 * @brief Some documentation
 */
class some_type_1 {
};

}
)");

const std::string leaf_child_object(R"(namespace some_model_0 {

/**
 * @brief Some documentation
 */
class some_type_0 final : public some_type_1 {
};

}
)");

const std::string non_leaf_child_object(R"(namespace some_model_0 {

/**
 * @brief Some documentation
 */
class some_type_1 : public some_type_2 {
};

}
)");

const std::string all_explicitly_defaulted_functions(R"(namespace some_model_0 {

class some_type_0 final {
public:
    some_type_0() = default;
    some_type_0(const some_type_0&) = default;
    some_type_0(some_type_0&&) = default;
    ~some_type_0() = default;
    some_type_0& operator=(const some_type_0&) = default;
};

}
)");

const std::string manual_default_constructor(R"(namespace some_model_0 {

class some_type_0 final {
public:
    some_type_0(const some_type_0&) = default;
    some_type_0(some_type_0&&) = default;
    ~some_type_0() = default;
    some_type_0& operator=(const some_type_0&) = default;

public:
    some_type_0();
};

}
)");

const std::string manual_move_constructor(R"(namespace some_model_0 {

class some_type_0 final {
public:
    some_type_0() = default;
    some_type_0(const some_type_0&) = default;
    ~some_type_0() = default;
    some_type_0& operator=(const some_type_0&) = default;
};

}
)");

const std::string module_in_named_model(R"(namespace some_model_0 {

/**
 * @brief Some documentation
 */
namespace some_module_0 {
} }
)");

/*
  FIXME: removed for now
  public:
  some_type_0(some_type_0&&);
 */

const std::string element_not_found("element not found: ");

const dogen::sml::object&
find_object(const dogen::sml::model& m, const unsigned int n) {
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (factory.type_name(n) == qn.simple_name())
            return *pair.second;
    }

    BOOST_THROW_EXCEPTION(
        dogen::utility::exception::exception(element_not_found +
            boost::lexical_cast<std::string>(n)));
}

dogen::sml::object& find_object(dogen::sml::model& m, const unsigned int n) {
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        if (factory.type_name(n) == qn.simple_name())
            return *pair.second;
    }

    BOOST_THROW_EXCEPTION(
        dogen::utility::exception::exception(element_not_found +
            boost::lexical_cast<std::string>(n)));
}

}

using namespace dogen::om;
using namespace dogen::utility::test;
typedef dogen::sml::test::mock_model_factory::object_types object_types;
typedef dogen::sml::test::mock_model_factory::property_types property_types;

BOOST_AUTO_TEST_SUITE(cpp_types_main_header_file_formatter)

BOOST_AUTO_TEST_CASE(enumeration_with_two_enumerators_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("enumeration_with_two_enumerators_produces_expected_types_header");

    const auto ot(object_types::enumeration);
    const auto m(factory.build_single_type_model(0, ot));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.enumerations().size() == 1);

    dogen::om::cpp_types_main_header_file_formatter f;
    const auto e(m.enumerations().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "enumeration: " << e;

    const auto r(f.format(e, empty_annotation));
    BOOST_CHECK(r.contents() == enumeration_two_enumerators);
    BOOST_LOG_SEV(lg, debug) << "expected: <start>"
                             << enumeration_two_enumerators
                             << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: <start>" << r.contents() << "<end>";
}

BOOST_AUTO_TEST_CASE(object_with_no_properties_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("object_with_no_properties_produces_expected_types_header");

    const auto m(factory.build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.objects().size() == 1);

    dogen::om::cpp_types_main_header_file_formatter f;
    const auto& o(find_object(m, 0));
    BOOST_LOG_SEV(lg, debug) << "object: " << o;

    const auto r(f.format(o, empty_annotation));
    BOOST_CHECK(r.contents() == object_no_properties);
    BOOST_LOG_SEV(lg, debug) << "expected: <start>" << object_no_properties
                             << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: <start>" << r.contents() << "<end>";
}

BOOST_AUTO_TEST_CASE(parent_object_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("parent_object_produces_expected_types_header");

    const auto m(factory.object_with_parent_in_the_same_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_CHECK(m.objects().size() == 2);

    const auto& o(find_object(m, 1));
    BOOST_LOG_SEV(lg, debug) << "object: " << o;

    dogen::om::cpp_types_main_header_file_formatter f;
    const auto r(f.format(o, empty_annotation));
    BOOST_CHECK(r.contents() == parent_object);
    BOOST_LOG_SEV(lg, debug) << "expected: <start>" << parent_object << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: <start>" << r << "<end>";
}

BOOST_AUTO_TEST_CASE(leaf_child_object_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("leaf_child_object_produces_expected_types_header");

    const auto m(factory.object_with_parent_in_the_same_model());
    BOOST_LOG_SEV(lg, debug) << "input model: " << m;
    BOOST_CHECK(m.objects().size() == 2);

    const auto& o(find_object(m, 0));
    BOOST_LOG_SEV(lg, debug) << "object: " << o;

    dogen::om::cpp_types_main_header_file_formatter f;
    const auto r(f.format(o, empty_annotation));
    BOOST_CHECK(r.contents() == leaf_child_object);
    BOOST_LOG_SEV(lg, debug) << "expected: <start>"
                             << leaf_child_object
                             << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: <start>" << r.contents() << "<end>";
}

BOOST_AUTO_TEST_CASE(non_leaf_child_object_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("non_leaf_child_object_produces_expected_types_header");

    const auto m(factory.object_with_third_degree_parent_in_same_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_CHECK(m.objects().size() == 4);

    const auto& o(find_object(m, 1));
    BOOST_LOG_SEV(lg, debug) << "object: " << o;

    dogen::om::cpp_types_main_header_file_formatter f;
    const auto r(f.format(o, empty_annotation));
    BOOST_CHECK(r.contents() == non_leaf_child_object);
    BOOST_LOG_SEV(lg, debug) << "expected: <start>" << non_leaf_child_object
                             << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: <start>" << r.contents() << "<end>";
}

BOOST_AUTO_TEST_CASE(generating_explicitly_defaulted_functions_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("generating_explicitly_defaulted_functions_produces_expected_types_header");

    auto m(factory.build_single_type_model());
    BOOST_CHECK(m.objects().size() == 1);
    auto& o(find_object(m, 0));
    o.documentation().clear();
    dogen::sml::meta_data_writer writer(o.meta_data());
    writer.add(
        dogen::sml::tags::cpp::types::generate_defaulted_functions,
        dogen::sml::tags::bool_true);
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::om::cpp_types_main_header_file_formatter f;
    const auto r(f.format(o, empty_annotation));
    BOOST_CHECK(r.contents() == all_explicitly_defaulted_functions);
    BOOST_LOG_SEV(lg, debug) << "expected: <start>"
                             << all_explicitly_defaulted_functions << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: <start>" << r.contents() << "<end>";
}

BOOST_AUTO_TEST_CASE(generating_manual_default_constructor_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("generating_manual_default_constructor_produces_expected_types_header");

    auto m(factory.build_single_type_model());
    BOOST_CHECK(m.objects().size() == 1);
    auto& o(find_object(m, 0));
    o.documentation().clear();
    dogen::sml::meta_data_writer writer(o.meta_data());
    writer.add(
        dogen::sml::tags::cpp::types::generate_defaulted_functions,
        dogen::sml::tags::bool_true);
    writer.add(
        dogen::sml::tags::cpp::types::generate_explicit_default_constructor,
        dogen::sml::tags::bool_true);

    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::om::cpp_types_main_header_file_formatter f;
    const auto r(f.format(o, empty_annotation));
    BOOST_CHECK(r.contents() == manual_default_constructor);
    BOOST_LOG_SEV(lg, debug) << "expected: <start>"
                             << manual_default_constructor << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: <start>" << r.contents() << "<end>";
}

BOOST_AUTO_TEST_CASE(generating_manual_move_constructor_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("generating_manual_move_constructor_produces_expected_types_header");

    auto m(factory.build_single_type_model());
    BOOST_CHECK(m.objects().size() == 1);
    auto& o(find_object(m, 0));
    o.documentation().clear();
    dogen::sml::meta_data_writer writer(o.meta_data());
    writer.add(
        dogen::sml::tags::cpp::types::generate_defaulted_functions,
        dogen::sml::tags::bool_true);
    writer.add(
        dogen::sml::tags::cpp::types::generate_explicit_move_constructor,
        dogen::sml::tags::bool_true);

    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    dogen::om::cpp_types_main_header_file_formatter f;
    const auto r(f.format(o, empty_annotation));
    BOOST_CHECK(r.contents() == manual_move_constructor);
    BOOST_LOG_SEV(lg, debug) << "expected: <start>"
                             << manual_move_constructor << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: <start>" << r.contents() << "<end>";
}

BOOST_AUTO_TEST_CASE(module_with_comments_produces_expected_types_header) {
    SETUP_TEST_LOG_SOURCE("module_with_comments_produces_expected_types_header");

    const auto m(factory.build_single_type_model_in_module(0,
            object_types::value_object, 1));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.modules().size() == 1);

    dogen::om::cpp_types_main_header_file_formatter f;
    const auto& module(m.modules().begin()->second);
    BOOST_LOG_SEV(lg, debug) << "module: " << module;

    const auto r(f.format(module, empty_annotation));
    BOOST_CHECK(r.contents() == module_in_named_model);
    BOOST_LOG_SEV(lg, debug) << "expected: <start>" << module_in_named_model
                             << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: <end>" << r.contents() << "<end>";
}

BOOST_AUTO_TEST_SUITE_END()
