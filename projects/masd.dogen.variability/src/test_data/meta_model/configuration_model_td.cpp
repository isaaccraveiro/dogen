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
#include "masd.dogen.variability/test_data/meta_model/configuration_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/configuration_model_td.hpp"

namespace {

masd::dogen::variability::meta_model::configuration*
create_masd_dogen_variability_meta_model_configuration_ptr(const unsigned int position) {
    return masd::dogen::variability::meta_model::configuration_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::variability::meta_model::configuration>
create_boost_shared_ptr_masd_dogen_variability_meta_model_configuration(unsigned int position) {
    boost::shared_ptr<masd::dogen::variability::meta_model::configuration> r(
        create_masd_dogen_variability_meta_model_configuration_ptr(position));
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::variability::meta_model::configuration> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_variability_meta_model_configuration(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::variability::meta_model::configuration> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_variability_meta_model_configuration(position + i)));
    }
    return r;
}

}

namespace masd::dogen::variability::meta_model {

configuration_model_generator::configuration_model_generator() : position_(0) { }

void configuration_model_generator::
populate(const unsigned int position, result_type& v) {
    v.global(create_boost_shared_ptr_masd_dogen_variability_meta_model_configuration(position + 0));
    v.local(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_variability_meta_model_configuration(position + 1));
}

configuration_model_generator::result_type
configuration_model_generator::create(const unsigned int position) {
    configuration_model r;
    configuration_model_generator::populate(position, r);
    return r;
}

configuration_model_generator::result_type*
configuration_model_generator::create_ptr(const unsigned int position) {
    configuration_model* p = new configuration_model();
    configuration_model_generator::populate(position, *p);
    return p;
}

configuration_model_generator::result_type
configuration_model_generator::operator()() {
    return create(position_++);
}

}