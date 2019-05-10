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
#include "masd.dogen.coding/test_data/meta_model/element_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability/feature_bundle_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability/feature_template_initializer_td.hpp"

namespace {

masd::dogen::coding::meta_model::variability::feature_bundle
create_masd_dogen_coding_meta_model_variability_feature_bundle(const unsigned int position) {
    return masd::dogen::coding::meta_model::variability::feature_bundle_generator::create(position);
}

std::list<masd::dogen::coding::meta_model::variability::feature_bundle> create_std_list_masd_dogen_coding_meta_model_variability_feature_bundle(unsigned int position) {
    std::list<masd::dogen::coding::meta_model::variability::feature_bundle> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_coding_meta_model_variability_feature_bundle(position + i));
    }
    return r;
}

}

namespace masd::dogen::coding::meta_model::variability {

feature_template_initializer_generator::feature_template_initializer_generator() : position_(0) { }

void feature_template_initializer_generator::
populate(const unsigned int position, result_type& v) {
    masd::dogen::coding::meta_model::element_generator::populate(position, v);
    v.template_groups(create_std_list_masd_dogen_coding_meta_model_variability_feature_bundle(position + 0));
}

feature_template_initializer_generator::result_type
feature_template_initializer_generator::create(const unsigned int position) {
    feature_template_initializer r;
    feature_template_initializer_generator::populate(position, r);
    return r;
}

feature_template_initializer_generator::result_type*
feature_template_initializer_generator::create_ptr(const unsigned int position) {
    feature_template_initializer* p = new feature_template_initializer();
    feature_template_initializer_generator::populate(position, *p);
    return p;
}

feature_template_initializer_generator::result_type
feature_template_initializer_generator::operator()() {
    return create(position_++);
}

}