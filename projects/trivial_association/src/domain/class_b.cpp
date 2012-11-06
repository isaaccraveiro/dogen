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
#include "dogen/trivial_association/domain/class_b.hpp"

namespace dogen {
namespace trivial_association {

class_b::class_b(const dogen::trivial_association::class_a& prop_0)
    : prop_0_(prop_0) { }

void class_b::swap(class_b& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool class_b::operator==(const class_b& rhs) const {
    return prop_0_ == rhs.prop_0_;
}

class_b& class_b::operator=(class_b other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }