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
#include "dogen.coding/test_data/meta_model/element_td.hpp"
#include "dogen.coding/test_data/meta_model/name_tree_td.hpp"
#include "dogen.coding/test_data/meta_model/mapping/fixed_mappable_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::coding::meta_model::name_tree
create_dogen_coding_meta_model_name_tree(const unsigned int position) {
    return dogen::coding::meta_model::name_tree_generator::create(position);
}

}

namespace dogen::coding::meta_model::mapping {

fixed_mappable_generator::fixed_mappable_generator() : position_(0) { }

void fixed_mappable_generator::
populate(const unsigned int position, result_type& v) {
    dogen::coding::meta_model::element_generator::populate(position, v);
    v.unparsed_destination(create_std_string(position + 0));
    v.destination(create_dogen_coding_meta_model_name_tree(position + 1));
}

fixed_mappable_generator::result_type
fixed_mappable_generator::create(const unsigned int position) {
    fixed_mappable r;
    fixed_mappable_generator::populate(position, r);
    return r;
}

fixed_mappable_generator::result_type*
fixed_mappable_generator::create_ptr(const unsigned int position) {
    fixed_mappable* p = new fixed_mappable();
    fixed_mappable_generator::populate(position, *p);
    return p;
}

fixed_mappable_generator::result_type
fixed_mappable_generator::operator()() {
    return create(position_++);
}

}
