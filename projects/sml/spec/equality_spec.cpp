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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/types/all.hpp"
#include "dogen/sml/io/all_io.hpp"
#include "dogen/utility/test/equality_tester.hpp"
#include "dogen/sml/test_data/all_td.hpp"

namespace {

const std::string test_module("sml");
const std::string test_suite("equality");
const std::string documentation("@brief sample doc");

template<typename Sequence>
void test_equality() {
    Sequence sequence;
    const typename Sequence::result_type a(sequence());
    const typename Sequence::result_type b(a);
    const typename Sequence::result_type c(sequence());

    typedef dogen::utility::test::equality_tester
        <typename Sequence::result_type> equality_tester;
    equality_tester::an_object_is_equal_to_itself(a);
    equality_tester::identical_objects_are_equal(a, b);
    equality_tester::distinct_objects_are_unequal(a, c);
}

}

BOOST_AUTO_TEST_SUITE(equality)

BOOST_AUTO_TEST_CASE(equality_operator_behaves_correctly) {
    SETUP_TEST_LOG("equality_operator_behaves_correctly");
    using namespace dogen::sml;

    test_equality<meta_types_generator>();
    test_equality<qname_generator>();
    test_equality<property_generator>();
    test_equality<pod_generator>();
    test_equality<package_generator>();
    test_equality<model_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
