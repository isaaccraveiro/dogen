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
#include "masd.dogen.coding/hash/meta_model/name_hash.hpp"
#include "masd.dogen.coding/hash/meta_model/element_hash.hpp"
#include "masd.dogen.coding/hash/meta_model/attribute_hash.hpp"
#include "masd.dogen.coding/hash/meta_model/object_template_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_masd_dogen_coding_meta_model_attribute(const std::list<masd::dogen::coding::meta_model::attribute>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_masd_dogen_coding_meta_model_name_std_list_masd_dogen_coding_meta_model_attribute(const std::unordered_map<masd::dogen::coding::meta_model::name, std::list<masd::dogen::coding::meta_model::attribute> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_std_list_masd_dogen_coding_meta_model_attribute(i.second));
    }
    return seed;
}

inline std::size_t hash_std_list_masd_dogen_coding_meta_model_name(const std::list<masd::dogen::coding::meta_model::name>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace masd::dogen::coding::meta_model {

std::size_t object_template_hasher::hash(const object_template& v) {
    std::size_t seed(0);

    combine(seed, dynamic_cast<const masd::dogen::coding::meta_model::element&>(v));

    combine(seed, hash_std_list_masd_dogen_coding_meta_model_attribute(v.all_attributes()));
    combine(seed, hash_std_list_masd_dogen_coding_meta_model_attribute(v.local_attributes()));
    combine(seed, hash_std_unordered_map_masd_dogen_coding_meta_model_name_std_list_masd_dogen_coding_meta_model_attribute(v.inherited_attributes()));
    combine(seed, v.is_immutable());
    combine(seed, v.is_fluent());
    combine(seed, hash_std_list_masd_dogen_coding_meta_model_name(v.parents()));
    combine(seed, v.is_child());

    return seed;
}

}