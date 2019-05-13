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
#ifndef DOGEN_CODING_TEST_DATA_META_MODEL_ORM_MODULE_PROPERTIES_TD_HPP
#define DOGEN_CODING_TEST_DATA_META_MODEL_ORM_MODULE_PROPERTIES_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.coding/types/meta_model/orm/module_properties.hpp"

namespace dogen::coding::meta_model::orm {

class module_properties_generator {
public:
    module_properties_generator();

public:
    typedef dogen::coding::meta_model::orm::module_properties result_type;

public:
    static void populate(const unsigned int position, result_type& v);
    static result_type create(const unsigned int position);
    result_type operator()();

private:
    unsigned int position_;
public:
    static result_type* create_ptr(const unsigned int position);
};

}

#endif