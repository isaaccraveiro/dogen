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
#include "masd.dogen.modeling/hash/meta_model/name_hash.hpp"
#include "masd.dogen.modeling/hash/helpers/mapping_set_hash.hpp"
#include "masd.dogen.modeling/hash/meta_model/languages_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_unordered_map_std_string_masd_dogen_modeling_meta_model_name(const std::unordered_map<std::string, masd::dogen::modeling::meta_model::name>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_masd_dogen_modeling_meta_model_languages_std_unordered_map_std_string_masd_dogen_modeling_meta_model_name(const std::unordered_map<masd::dogen::modeling::meta_model::languages, std::unordered_map<std::string, masd::dogen::modeling::meta_model::name> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_std_unordered_map_std_string_masd_dogen_modeling_meta_model_name(i.second));
    }
    return seed;
}

inline std::size_t hash_std_unordered_set_std_string(const std::unordered_set<std::string>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_masd_dogen_modeling_meta_model_languages_std_unordered_set_std_string(const std::unordered_map<masd::dogen::modeling::meta_model::languages, std::unordered_set<std::string> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_std_unordered_set_std_string(i.second));
    }
    return seed;
}

}

namespace masd::dogen::modeling::helpers {

std::size_t mapping_set_hasher::hash(const mapping_set& v) {
    std::size_t seed(0);

    combine(seed, v.name());
    combine(seed, hash_std_unordered_map_masd_dogen_modeling_meta_model_languages_std_unordered_map_std_string_masd_dogen_modeling_meta_model_name(v.by_language_agnostic_id()));
    combine(seed, hash_std_unordered_map_masd_dogen_modeling_meta_model_languages_std_unordered_set_std_string(v.erasures_by_language()));

    return seed;
}

}