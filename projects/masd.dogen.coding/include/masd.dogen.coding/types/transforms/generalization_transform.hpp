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
#ifndef MASD_DOGEN_CODING_TYPES_TRANSFORMS_GENERALIZATION_TRANSFORM_HPP
#define MASD_DOGEN_CODING_TYPES_TRANSFORMS_GENERALIZATION_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_set>
#include "masd.dogen.annotations/types/type.hpp"
#include "masd.dogen.annotations/types/type_repository.hpp"
#include "masd.dogen.coding/types/meta_model/name.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/model.hpp"
#include "masd.dogen.coding/types/transforms/context_fwd.hpp"
#include "masd.dogen.coding/types/helpers/indices.hpp"

namespace masd::dogen::coding::transforms {

/**
 * @brief Expands generalisation relationships in model.
 */
class generalization_transform final {
private:
    struct type_group {
        annotations::type is_final;
    };

    static type_group make_type_group(const annotations::type_repository& atrp);

    static boost::optional<bool> make_is_final(const type_group& tg,
        const annotations::annotation& a);

private:
    static std::unordered_set<std::string>
    update_and_collect_parent_ids(const helpers::indices& idx,
        meta_model::model& m);

    static void populate_properties_up_the_generalization_tree(
        const type_group& tg, const meta_model::name& leaf,
        meta_model::model& m, meta_model::object& o);

    static void populate_generalizable_properties(const type_group& tg,
        const std::unordered_set<std::string>& parent_ids,
        meta_model::model& m);

    static void sort_leaves(meta_model::model& m);

public:
    static void apply(const context& ctx, const helpers::indices& idx,
        meta_model::model& m);
};

}

#endif
