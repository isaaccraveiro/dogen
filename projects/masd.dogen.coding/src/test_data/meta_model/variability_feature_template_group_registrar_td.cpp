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
#include "masd.dogen.coding/test_data/meta_model/variability_feature_template_group_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability_feature_template_group_registrar_td.hpp"

namespace {

masd::dogen::coding::meta_model::variability_feature_template_group
create_masd_dogen_coding_meta_model_variability_feature_template_group(const unsigned int position) {
    return masd::dogen::coding::meta_model::variability_feature_template_group_generator::create(position);
}

std::list<masd::dogen::coding::meta_model::variability_feature_template_group> create_std_list_masd_dogen_coding_meta_model_variability_feature_template_group(unsigned int position) {
    std::list<masd::dogen::coding::meta_model::variability_feature_template_group> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_coding_meta_model_variability_feature_template_group(position + i));
    }
    return r;
}

}

namespace masd::dogen::coding::meta_model {

variability_feature_template_group_registrar_generator::variability_feature_template_group_registrar_generator() : position_(0) { }

void variability_feature_template_group_registrar_generator::
populate(const unsigned int position, result_type& v) {
    masd::dogen::coding::meta_model::element_generator::populate(position, v);
    v.template_groups(create_std_list_masd_dogen_coding_meta_model_variability_feature_template_group(position + 0));
}

variability_feature_template_group_registrar_generator::result_type
variability_feature_template_group_registrar_generator::create(const unsigned int position) {
    variability_feature_template_group_registrar r;
    variability_feature_template_group_registrar_generator::populate(position, r);
    return r;
}

variability_feature_template_group_registrar_generator::result_type*
variability_feature_template_group_registrar_generator::create_ptr(const unsigned int position) {
    variability_feature_template_group_registrar* p = new variability_feature_template_group_registrar();
    variability_feature_template_group_registrar_generator::populate(position, *p);
    return p;
}

variability_feature_template_group_registrar_generator::result_type
variability_feature_template_group_registrar_generator::operator()() {
    return create(position_++);
}

}