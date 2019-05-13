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
#include "dogen.templating/test_data/stitch/properties_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

std::unordered_map<std::string, std::string> create_std_unordered_map_std_string_std_string(unsigned int position) {
    std::unordered_map<std::string, std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_string(position + i)));
    }
    return r;
}

}

namespace dogen::templating::stitch {

properties_generator::properties_generator() : position_(0) { }

void properties_generator::
populate(const unsigned int position, result_type& v) {
    v.stream_variable_name(create_std_string(position + 0));
    v.relative_output_directory(create_boost_filesystem_path(position + 1));
    v.inclusion_dependencies(create_std_list_std_string(position + 2));
    v.containing_namespaces(create_std_list_std_string(position + 3));
    v.wale_template(create_std_string(position + 4));
    v.wale_kvps(create_std_unordered_map_std_string_std_string(position + 5));
}

properties_generator::result_type
properties_generator::create(const unsigned int position) {
    properties r;
    properties_generator::populate(position, r);
    return r;
}

properties_generator::result_type*
properties_generator::create_ptr(const unsigned int position) {
    properties* p = new properties();
    properties_generator::populate(position, *p);
    return p;
}

properties_generator::result_type
properties_generator::operator()() {
    return create(position_++);
}

}
