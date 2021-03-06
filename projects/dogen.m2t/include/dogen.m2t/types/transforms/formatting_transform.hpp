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
#ifndef DOGEN_M2T_TYPES_TRANSFORMS_FORMATTING_TRANSFORM_HPP
#define DOGEN_M2T_TYPES_TRANSFORMS_FORMATTING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.physical/types/entities/meta_name.hpp"
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.m2t/types/transforms/context.hpp"
#include "dogen.m2t/types/entities/model.hpp"
#include "dogen.logical/types/entities/formatting_styles.hpp"
#include "dogen.m2t/types/transforms/formatting_configuration.hpp"

namespace dogen::m2t::transforms {

class formatting_transform final {
private:
    static entities::formatting_styles
    to_formatting_style(const std::string& s);

private:
    struct feature_group {
        variability::entities::feature formatting_style;
        variability::entities::feature formatting_input;
    };

    static std::unordered_map<std::string, feature_group>
    make_feature_groups(const variability::entities::feature_model& fm,
        const std::list<physical::entities::meta_name>& mns);

    static std::unordered_map<std::string, formatting_configuration>
    make_formatting_configuration(
        const std::unordered_map<std::string, feature_group>& fgs,
        const variability::entities::configuration& cfg);

    static void apply(const std::unordered_map<std::string, feature_group> fgs,
        logical::entities::element& e);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
