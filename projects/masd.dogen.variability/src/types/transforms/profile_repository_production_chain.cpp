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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.variability/io/meta_model/feature_model_io.hpp"
#include "masd.dogen.variability/io/meta_model/profile_repository_io.hpp"
#include "masd.dogen.variability/types/transforms/profile_merging_transform.hpp"
#include "masd.dogen.variability/types/transforms/profile_template_hydration_transform.hpp"
#include "masd.dogen.variability/types/transforms/profile_template_instantiation_transform.hpp"
#include "masd.dogen.variability/types/transforms/profile_repository_production_chain.hpp"

namespace {

const std::string transform_id(
    "variability.transforms.profile_repository_production_chain");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::variability::transforms {

meta_model::profile_repository profile_repository_production_chain::
apply(const context& ctx, const meta_model::feature_model& fm) {
    tracing::scoped_chain_tracer stp(lg, "profile repository production chain",
        transform_id, transform_id, *ctx.tracer(), fm);

    const auto t(profile_template_hydration_transform::apply(ctx));
    const auto p(profile_template_instantiation_transform::apply(ctx, fm, t));
    const auto r(profile_merging_transform::apply(ctx, p));

    stp.end_chain(r);
    return r;
}

}