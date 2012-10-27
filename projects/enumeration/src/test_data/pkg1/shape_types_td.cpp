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
#include "dogen/enumeration/test_data/pkg1/shape_types_td.hpp"

namespace dogen {
namespace enumeration {
namespace pkg1 {

shape_types_generator::shape_types_generator() : position_(0) { }
void shape_types_generator::
populate(const unsigned int position, result_type& v) {
    v = static_cast<shape_types>(position % 4);
}

shape_types_generator::result_type
shape_types_generator::create(const unsigned int  position) {
    result_type r;
    shape_types_generator::populate(position, r);
    return r;
}

shape_types_generator::result_type
shape_types_generator::operator()() {
    return create(position_++);
}

} } }