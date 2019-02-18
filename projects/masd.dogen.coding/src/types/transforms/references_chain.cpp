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
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/types/helpers/reference_paths_extractor.hpp"
#include "masd.dogen.coding/io/meta_model/endomodel_io.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.injection/types/transforms/context.hpp"
#include "masd.dogen.injection/types/transforms/model_generation_chain.hpp"
#include "masd.dogen.coding/types/transforms/external_model_to_endomodel_transform.hpp"
#include "masd.dogen.coding/types/transforms/endomodel_pre_processing_chain.hpp"
#include "masd.dogen.coding/types/transforms/references_chain.hpp"

namespace {

const std::string transform_id("coding.transforms.references_chain");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string non_absolute_target("Target path is not absolute: ");

}

namespace masd::dogen::coding::transforms {

std::unordered_set<meta_model::languages> references_chain::
obtain_relevant_languages(const meta_model::endomodel& target) {
    std::unordered_set<meta_model::languages> r;
    r.insert(target.input_language());

    for (const auto ol : target.output_languages())
        r.insert(ol);

    return r;
}

std::list<meta_model::endomodel> references_chain::
transform(const context& ctx, const meta_model::endomodel& target) {
    tracing::scoped_chain_tracer stp(lg, "references chain",
        transform_id, target.name().id(), ctx.tracer());

    /*
     * Obtain the absolute paths to all reference models - system and
     * user.
     */
    const auto rps(helpers::reference_paths_extractor::extract(ctx, target));

    /*
     * Obtain all languages that the target model is interested in. We
     * will use these to filter the references - in particular the
     * system models, since these span all languages supported by
     * dogen.
     */
    const auto rl(obtain_relevant_languages(target));

    /*
     * Load each reference model from the references path, filter and
     * pre-process them.
     */
    std::list<meta_model::endomodel> r;
    for (const auto& rp : rps) {
        /*
         * Obtain the reference model in the internal representation
         * of the exogenous model.
         */
        using injection::transforms::model_generation_chain;
        const injection::transforms::context ext_ctx(ctx.tracer());
        const auto em(model_generation_chain::transform(ext_ctx, rp));

        /*
         * Convert the internal representation of the exogenous model into
         * an endogenous model, ready for further processing.
         */
        auto m(external_model_to_endomodel_transform::transform(ctx, em));

        /*
         * Apply all of the pre-processing transforms to the reference
         * endmodel if its language is part of our set of relevant
         * languages. If not, its no use to us so drop it. Note that
         * this is not ideal for two reasons:
         *
         * - we are still loading system references for our langugage
         *   which may not be needed by the target and references
         *   models.
         *
         * - we still need to do some pre-processing before we can
         *   figure out the model's language. We could use the model's
         *   name as a clue to its language so we don't need to load
         *   it at all.
         *
         * Given that the list of system models is very small at
         * present, we are ignoring these problems.
         */
        if (endomodel_pre_processing_chain::try_transform(ctx, rl, m))
            r.push_back(m);
    }

    stp.end_chain(r);
    BOOST_LOG_SEV(lg, debug) << "Finished references chain.";
    return r;
}

}
