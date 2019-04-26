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
#ifndef MASD_DOGEN_CODING_TYPES_TRANSFORMS_TYPE_PARAMS_TRANSFORM_HPP
#define MASD_DOGEN_CODING_TYPES_TRANSFORMS_TYPE_PARAMS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/types/type_repository.hpp"
#include "masd.dogen.variability/types/type.hpp"
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.coding/types/meta_model/type_parameters.hpp"
#include "masd.dogen.coding/types/meta_model/model.hpp"
#include "masd.dogen.coding/types/transforms/context_fwd.hpp"

namespace masd::dogen::coding::transforms {

class type_params_transform final {
private:
    struct type_group {
        variability::type variable_number_of_parameters;
        variability::type type_parameters_count;
        variability::type type_parameters_always_in_heap;
    };

    static type_group make_type_group(const variability::type_repository& atrp);

    static meta_model::type_parameters make_type_parameters(
        const type_group& tg, const variability::annotation& a);

private:
    static void expand_type_parameters(const type_group& tg,
        meta_model::object& o);

private:
    struct feature_group {
        variability::meta_model::feature variable_number_of_parameters;
        variability::meta_model::feature type_parameters_count;
        variability::meta_model::feature type_parameters_always_in_heap;
    };

    static feature_group make_feature_group(
        const variability::meta_model::feature_model& fm);

    static meta_model::type_parameters
    make_type_parameters(const feature_group& fg,
        const variability::meta_model::configuration& a);

private:
    static void expand_type_parameters(const feature_group& fg,
        meta_model::object& o);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
