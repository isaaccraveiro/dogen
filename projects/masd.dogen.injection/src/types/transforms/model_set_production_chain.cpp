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
#include "masd.dogen.injection/types/transforms/model_production_chain.hpp"
#include "masd.dogen.injection/types/transforms/model_set_production_chain.hpp"

namespace masd::dogen::injection::transforms {

meta_model::model_set
model_set_production_chain::transform(const context& /*ctx*/,
    const boost::filesystem::path& /*p*/,
    std::unordered_set<std::string>& /*processed_models*/,
    const bool /*is_target*/) {

    meta_model::model_set r;
    return r;
}

meta_model::model_set
model_set_production_chain::transform(const context& ctx,
    const boost::filesystem::path& p) {
    std::unordered_set<std::string> processed_models;
    return transform(ctx, p, processed_models, true/*is_target*/);
}

}