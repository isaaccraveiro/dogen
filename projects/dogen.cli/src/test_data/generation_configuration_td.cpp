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
#include "dogen.cli/test_data/generation_configuration_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

std::vector<boost::filesystem::path> create_std_vector_boost_filesystem_path(unsigned int position) {
    std::vector<boost::filesystem::path> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_filesystem_path(position + i));
    }
    return r;
}

}

namespace dogen::cli {

generation_configuration_generator::generation_configuration_generator() : position_(0) { }

void generation_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.reference_model_directories(create_std_vector_boost_filesystem_path(position + 0));
    v.target(create_boost_filesystem_path(position + 1));
    v.output_directory(create_boost_filesystem_path(position + 2));
}

generation_configuration_generator::result_type
generation_configuration_generator::create(const unsigned int position) {
    generation_configuration r;
    generation_configuration_generator::populate(position, r);
    return r;
}

generation_configuration_generator::result_type*
generation_configuration_generator::create_ptr(const unsigned int position) {
    generation_configuration* p = new generation_configuration();
    generation_configuration_generator::populate(position, *p);
    return p;
}

generation_configuration_generator::result_type
generation_configuration_generator::operator()() {
    return create(position_++);
}

}