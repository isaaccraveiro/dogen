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
#ifndef DOGEN_LOGICAL_TYPES_FEATURES_ENUMERATION_HPP
#define DOGEN_LOGICAL_TYPES_FEATURES_ENUMERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"

namespace dogen::logical::features {

/**
 * @brief Parameters related to enumerations.
 */
class enumeration final {
public:
    struct feature_group {
        variability::entities::feature use_implementation_defined_underlying_element;
        variability::entities::feature underlying_element;
        variability::entities::feature use_implementation_defined_enumerator_values;
        variability::entities::feature add_invalid_enumerator;
    };

    static feature_group
    make_feature_group(const variability::entities::feature_model& fm);

public:
    struct static_configuration {
        bool use_implementation_defined_underlying_element;
        std::string underlying_element;
        bool use_implementation_defined_enumerator_values;
        bool add_invalid_enumerator;

        static_configuration() :
            use_implementation_defined_underlying_element(),
            use_implementation_defined_enumerator_values(),
            add_invalid_enumerator() {}
    };

    static static_configuration make_static_configuration(
        const feature_group& fg,
        const variability::entities::configuration& cfg);

    template<typename Configurable>
    static static_configuration make_static_configuration(
        const feature_group& fg, const Configurable& c) {
        return make_static_configuration(fg, *c.configuration());
    }

public:
    static std::list<dogen::variability::entities::feature>
    make_features();
};

}

#endif
