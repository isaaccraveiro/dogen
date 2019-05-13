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
#include "dogen.utility/test_data/log/logging_configuration_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

}

namespace dogen::utility::log {

logging_configuration_generator::logging_configuration_generator() : position_(0) { }

void logging_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.severity(create_std_string(position + 0));
    v.filename(create_std_string(position + 1));
    v.output_to_console(create_bool(position + 2));
    v.output_directory(create_boost_filesystem_path(position + 3));
}

logging_configuration_generator::result_type
logging_configuration_generator::create(const unsigned int position) {
    logging_configuration r;
    logging_configuration_generator::populate(position, r);
    return r;
}

logging_configuration_generator::result_type*
logging_configuration_generator::create_ptr(const unsigned int position) {
    logging_configuration* p = new logging_configuration();
    logging_configuration_generator::populate(position, *p);
    return p;
}

logging_configuration_generator::result_type
logging_configuration_generator::operator()() {
    return create(position_++);
}

}