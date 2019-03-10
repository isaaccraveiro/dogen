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
#include "masd.dogen.injection/io/meta_model/model_set_io.hpp"
#include "masd.dogen.injection/types/transforms/context.hpp"
#include "masd.dogen.injection/types/transforms/model_production_chain.hpp"
#include "masd.dogen.injection/types/transforms/model_set_production_chain.hpp"

namespace {

const std::string
transform_id("injection.transforms.model_set_production_chain");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string library_dir("library");

}

namespace masd::dogen::injection::transforms {

std::list<boost::filesystem::path>
model_set_production_chain::obtain_directory_list(const context& ctx,
    const boost::filesystem::path& target_path) {
    std::list<boost::filesystem::path> r;
    /*
     * Add all system directories.
     */
    for (const auto& dir : ctx.data_directories())
        r.push_back(dir / library_dir);

    /*
     * Add the directory where target is located.
     */
    r.push_back(target_path.parent_path());
    return r;
}

std::list<meta_model::model>
model_set_production_chain::transform(const context& ctx,
    const helpers::references_resolver& res,
    const boost::filesystem::path& p,
    std::unordered_set<std::string>& processed_models) {

    BOOST_LOG_SEV(lg, trace) << "Processing: " << p.generic();

    std::list<meta_model::model> r;
    r.push_back(model_production_chain::apply(ctx, p));
    BOOST_LOG_SEV(lg, trace) << "References: " << r.front().references();
    for (const auto& ref : r.front().references()) {
        BOOST_LOG_SEV(lg, trace) << "Attempting to process reference: " << ref;
        const auto insert(processed_models.insert(ref).second);
        if (!insert) {
            BOOST_LOG_SEV(lg, trace) << "Reference already processed.";
            continue;
        }

        const auto rp(res.resolve(ref));
        BOOST_LOG_SEV(lg, trace) << "Resolved to path: " << rp.generic();
        r.splice(r.end(), transform(ctx, res, rp, processed_models));
        BOOST_LOG_SEV(lg, trace) << "Processed reference.";
    }

    return r;
}

meta_model::model_set
model_set_production_chain::apply(const context& ctx,
    const boost::filesystem::path& p) {
    const auto mn(p.filename().string());
    tracing::scoped_chain_tracer stp(lg, "injection model set production chain",
        transform_id, mn, *ctx.tracer());

    std::unordered_set<std::string> processed_models;
    const auto& rg(model_production_chain::registrar());
    const auto exts(rg.registered_decoding_extensions());
    const auto dirs(obtain_directory_list(ctx, p));
    helpers::references_resolver res(exts, dirs);

    meta_model::model_set r;
    auto models(transform(ctx, res, p, processed_models));
    BOOST_LOG_SEV(lg, debug) << "Read injection model graph. Total: "
                             << models.size();

    r.target(models.front());
    BOOST_LOG_SEV(lg, trace) << "Target: " << r.target().name();

    models.pop_front();
    r.references(models);

    stp.end_chain(r);

    return r;
}

}
