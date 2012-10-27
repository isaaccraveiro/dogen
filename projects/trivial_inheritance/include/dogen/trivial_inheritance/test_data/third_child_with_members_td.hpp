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
#ifndef DOGEN_TRIVIAL_INHERITANCE_TEST_DATA_THIRD_CHILD_WITH_MEMBERS_TD_HPP
#define DOGEN_TRIVIAL_INHERITANCE_TEST_DATA_THIRD_CHILD_WITH_MEMBERS_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/trivial_inheritance/domain/third_child_with_members.hpp"

namespace dogen {
namespace trivial_inheritance {

class third_child_with_members_generator {
public:
    third_child_with_members_generator();

public:
    typedef dogen::trivial_inheritance::third_child_with_members result_type;

public:
    static void populate(const unsigned int position, result_type& v);
};

} }

#endif
