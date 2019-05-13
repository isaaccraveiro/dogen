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
#include <string>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "dogen.extraction/io/meta_model/operation_reason_io.hpp"
#include "dogen.extraction/types/meta_model/operation_reason.hpp"
#include "dogen.extraction/hash/meta_model/operation_reason_hash.hpp"
#include "dogen.extraction/test_data/meta_model/operation_reason_td.hpp"

BOOST_AUTO_TEST_SUITE(operation_reason_tests)

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    dogen::extraction::meta_model::operation_reason_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_CASE(equal_enums_generate_the_same_hash) {
    dogen::extraction::meta_model::operation_reason_generator g;
    g();
    const auto a(g());
    const auto b(a);

    std::hash<dogen::extraction::meta_model::operation_reason> hasher;
    BOOST_CHECK(hasher(a) == hasher(b));
}

BOOST_AUTO_TEST_CASE(different_enums_generate_different_hashes) {
    dogen::extraction::meta_model::operation_reason_generator g;
    g();
    const auto a(g());
    const auto b(g());

    std::hash<dogen::extraction::meta_model::operation_reason> hasher;
    BOOST_CHECK(hasher(a) != hasher(b));
}

BOOST_AUTO_TEST_SUITE_END()