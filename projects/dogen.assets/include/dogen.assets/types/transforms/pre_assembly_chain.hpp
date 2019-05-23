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
#ifndef DOGEN_ASSETS_TYPES_TRANSFORMS_PRE_ASSEMBLY_CHAIN_HPP
#define DOGEN_ASSETS_TYPES_TRANSFORMS_PRE_ASSEMBLY_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.assets/types/meta_model/model.hpp"
#include "dogen.assets/types/meta_model/model_set.hpp"
#include "dogen.assets/types/transforms/context_fwd.hpp"

namespace dogen::assets::transforms {

/**
 * @brief Performs a set of pre-processing transforms to a model set,
 * prior to its assembly into a merged model.
 */
class pre_assembly_chain final {
private:
    /**
     * @brief Applies all of the pre-processing transforms to the
     * supplied model.
     */
    static void apply(const context& ctx, meta_model::model& m);

public:
    /**
     * @brief Transform the supplied model set.
     */
    static void apply(const context& ctx, meta_model::model_set& ms);
};

}

#endif