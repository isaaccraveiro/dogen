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
#ifndef MASD_DOGEN_MODELING_HASH_META_MODEL_NAME_TREE_HASH_HPP
#define MASD_DOGEN_MODELING_HASH_META_MODEL_NAME_TREE_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "masd.dogen.modeling/types/meta_model/name_tree.hpp"

namespace masd::dogen::modeling::meta_model {

struct name_tree_hasher {
public:
    static std::size_t hash(const name_tree& v);
};

}

namespace std {

template<>
struct hash<masd::dogen::modeling::meta_model::name_tree> {
public:
    size_t operator()(const masd::dogen::modeling::meta_model::name_tree& v) const {
        return masd::dogen::modeling::meta_model::name_tree_hasher::hash(v);
    }
};

}
#endif