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
#include "masd.dogen.variability/io/meta_model/configuration_model_io.hpp"
#include "masd.dogen.variability/types/transforms/profile_binding_transform.hpp"
#include "masd.dogen.variability/types/transforms/profile_repository_production_chain.hpp"
#include "masd.dogen.variability/types/transforms/profile_binding_chain.hpp"

namespace {

const std::string
transform_id("variability.transforms.profile_binding_chain");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::variability::transforms {

void profile_binding_chain::apply(const context& ctx,
    const meta_model::feature_model& fm, meta_model::configuration_model& cm) {
    tracing::scoped_chain_tracer stp(lg, "feature model production chain",
        transform_id, transform_id, *ctx.tracer(), cm);

    const auto prp(profile_repository_production_chain::apply(ctx, fm));
    profile_binding_transform::apply(ctx, prp, fm, cm);

    stp.end_chain(cm);
}

}