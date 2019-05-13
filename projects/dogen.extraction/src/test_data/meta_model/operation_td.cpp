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
#include "dogen.extraction/test_data/meta_model/operation_td.hpp"
#include "dogen.extraction/test_data/meta_model/operation_type_td.hpp"
#include "dogen.extraction/test_data/meta_model/operation_reason_td.hpp"

namespace {

dogen::extraction::meta_model::operation_type
create_dogen_extraction_meta_model_operation_type(const unsigned int position) {
    return dogen::extraction::meta_model::operation_type_generator::create(position);
}

dogen::extraction::meta_model::operation_reason
create_dogen_extraction_meta_model_operation_reason(const unsigned int position) {
    return dogen::extraction::meta_model::operation_reason_generator::create(position);
}

}

namespace dogen::extraction::meta_model {

operation_generator::operation_generator() : position_(0) { }

void operation_generator::
populate(const unsigned int position, result_type& v) {
    v.type(create_dogen_extraction_meta_model_operation_type(position + 0));
    v.reason(create_dogen_extraction_meta_model_operation_reason(position + 1));
}

operation_generator::result_type
operation_generator::create(const unsigned int position) {
    operation r;
    operation_generator::populate(position, r);
    return r;
}

operation_generator::result_type*
operation_generator::create_ptr(const unsigned int position) {
    operation* p = new operation();
    operation_generator::populate(position, *p);
    return p;
}

operation_generator::result_type
operation_generator::operator()() {
    return create(position_++);
}

}
