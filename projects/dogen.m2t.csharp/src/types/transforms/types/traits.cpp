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
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/types/traits.hpp"

namespace dogen::m2t::csharp::transforms::types {

std::string traits::facet_qn() {
    static std::string r(csharp::traits::backend_qn() + ".types");
    return r;
}

std::string traits::facet_sn() {
    static std::string r("types");
    return r;
}

std::string traits::class_archetype_qn() {
    static std::string r(traits::facet_qn() + ".class");
    return r;
}

std::string traits::class_archetype_sn() {
    static std::string r("class");
    return r;
}

std::string traits::enum_archetype_qn() {
    static std::string r(traits::facet_qn() + ".enum");
    return r;
}

std::string traits::enum_archetype_sn() {
    static std::string r("enum");
    return r;
}

std::string traits::primitive_archetype_qn() {
    static std::string r(traits::facet_qn() + ".primitive");
    return r;
}

std::string traits::primitive_archetype_sn() {
    static std::string r("primitive");
    return r;
}

std::string traits::exception_archetype_qn() {
    static std::string r(traits::facet_qn() + ".exception");
    return r;
}

std::string traits::exception_archetype_sn() {
    static std::string r("exception");
    return r;
}

std::string traits::builtin_archetype_qn() {
    static std::string r(traits::facet_qn() + ".builtin");
    return r;
}

std::string traits::builtin_archetype_sn() {
    static std::string r("builtin");
    return r;
}

}
