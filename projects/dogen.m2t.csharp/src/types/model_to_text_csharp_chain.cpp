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
#include <boost/algorithm/string/join.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.m2t.csharp/types/formattables/workflow.hpp"
#include "dogen.m2t.csharp/types/transforms/workflow.hpp"
#include "dogen.m2t.csharp/types/formattables/locator.hpp"
#include "dogen.m2t.csharp/types/model_to_text_csharp_chain.hpp"

namespace {

const std::string
transform_id("m2t.csharp.model_to_text_csharp_chain");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty;
const std::string dot(".");
const std::string description(
    "Generates C# code according to the MASD generative model.");

}

namespace dogen::m2t::csharp {

model_to_text_csharp_chain::
~model_to_text_csharp_chain() noexcept { }

formattables::model
model_to_text_csharp_chain::create_formattables_model(
    const variability::entities::feature_model& feature_model,
    const transforms::repository& frp, const formattables::locator& l,
    const m2t::entities::model& m) const {
    formattables::workflow fw;
    return fw.execute(feature_model, frp, l, m);
}

std::string model_to_text_csharp_chain::id() const {
    return traits::backend_qn();
}

std::string model_to_text_csharp_chain::description() const {
    return ::description;
}

void model_to_text_csharp_chain::apply(formattables::model& fm) const {
    transforms::workflow wf;
    wf.execute(fm);
}

const std::forward_list<physical::entities::meta_name>&
model_to_text_csharp_chain::physical_meta_names() const {
    const auto& rg(transforms::workflow::registrar());
    return rg.physical_meta_names();
}

const std::unordered_map<std::string,
                         physical::entities::meta_name_group>&
model_to_text_csharp_chain::physical_meta_names_by_logical_meta_name() const {
    const auto& rg(transforms::workflow::registrar());
    return rg.physical_meta_names_by_logical_meta_name();
}

const std::unordered_map<std::string,
                         std::list<physical::entities::meta_name>>&
model_to_text_csharp_chain::physical_meta_names_by_family() const {
    const auto& rg(transforms::workflow::registrar());
    return rg.physical_meta_names_by_family();
}

const physical::entities::meta_name_repository_parts&
model_to_text_csharp_chain::
physical_meta_name_repository_parts() const {
    const auto& rg(transforms::workflow::registrar());
    return rg.physical_meta_name_repository_parts();
}

logical::entities::technical_space
model_to_text_csharp_chain::technical_space() const {
    return logical::entities::technical_space::csharp;
}

physical::entities::model
model_to_text_csharp_chain::apply(
    const m2t::transforms::context& ctx,
    const bool enable_backend_directories,
    const m2t::entities::model& m) const {
    tracing::scoped_transform_tracer stp(lg,
        "C# model to text transform", transform_id, m.name().qualified().dot(),
        *ctx.tracer());

    BOOST_LOG_SEV(lg, debug) << "Started backend.";

    /*
     * Create the locator.
     */
    const auto mn(m.name());
    const auto& rcfg(*m.root_module()->configuration());
    const auto& feature_model(*ctx.feature_model());
    const auto odp(ctx.output_directory_path());
    const auto& frp(transforms::workflow::registrar().formatter_repository());
    const bool ekd(enable_backend_directories);
    const formattables::locator l(odp, feature_model, frp, rcfg, mn, m.
        module_ids(), ekd);

    /*
     * Generate the formattables model.
     */
    auto fm(create_formattables_model(feature_model, frp, l, m));

    /*
     * Code-generate all artefacts.
     */
    apply(fm);

    /*
     * Copy them across into the physical model.
     */
    physical::entities::model r;
    r.managed_directories().push_back(l.project_path());
    for (const auto& fbl_pair : fm.formattables()) {
        for (const auto& art_pair : fbl_pair.second.artefacts()) {
            auto& ptr(art_pair.second);

            // FIXME: mega-hack: prune empty artefacts
            const auto& p(ptr->name().qualified());
            if (!p.empty())
                r.artefacts().push_back(art_pair.second);
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished backend.";
    return r;
}

}
