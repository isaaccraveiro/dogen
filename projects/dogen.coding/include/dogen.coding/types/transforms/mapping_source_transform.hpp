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
#ifndef DOGEN_CODING_TYPES_TRANSFORMS_MAPPING_SOURCE_TRANSFORM_HPP
#define DOGEN_CODING_TYPES_TRANSFORMS_MAPPING_SOURCE_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"
#include "dogen.variability/types/meta_model/template_kind.hpp"
#include "dogen.coding/types/meta_model/model.hpp"
#include "dogen.coding/types/transforms/context_fwd.hpp"
#include "dogen.coding/types/meta_model/mapping/action.hpp"
#include "dogen.coding/types/meta_model/variability/feature_bundle.hpp"

namespace dogen::coding::transforms {

class mapping_source_transform final {
private:
    struct feature_group {
        variability::meta_model::feature source;
        variability::meta_model::feature destination;
        variability::meta_model::feature action;
    };

    static feature_group make_feature_group(
        const variability::meta_model::feature_model& fm);

    static std::string make_source(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static std::string make_destination(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static meta_model::mapping::action make_action(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif