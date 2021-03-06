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
#include <boost/throw_exception.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.dia/types/hydrator.hpp"
#include "dogen.dia/io/diagram_io.hpp"
#include "dogen.dia/types/diagram.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.injection/types/transforms/context.hpp"
#include "dogen.injection/io/entities/model_io.hpp"
#include "dogen.injection/types/transforms/transformation_error.hpp"
#include "dogen.injection.dia/types/builder.hpp"
#include "dogen.injection.dia/types/visitor.hpp"
#include "dogen.injection.dia/types/processed_object.hpp"
#include "dogen.injection.dia/types/processed_comment.hpp"
#include "dogen.injection.dia/types/processed_object_factory.hpp"
#include "dogen.injection.dia/types/decoding_transform.hpp"

namespace {

using namespace dogen::utility::log;
const std::string transform_id("injection.dia.decoding_transform");
auto lg(logger_factory(transform_id));

const std::string decoder_id("injection.dia");
const std::string description("Decodes Dia diagrams.");
const std::string extension(".dia");
const std::string to_dia_support_unavailable(
    "Transformer cannot convert model into Dia representation");

}

namespace dogen::injection::dia {

inline bool is_not_relevant(const processed_object& po) {
    const auto ot(po.dia_object_type());
    const bool is_relevant(
        ot == dia_object_types::uml_large_package ||
        ot == dia_object_types::uml_generalization ||
        ot == dia_object_types::uml_class ||
        ot == dia_object_types::uml_note);

    return !is_relevant;
}

decoding_transform::~decoding_transform() noexcept {}

std::list<processed_object> decoding_transform::
obtain_processed_objects(const dogen::dia::diagram& d) const {
    BOOST_LOG_SEV(lg, debug) << "Converting diagram into processed objects.";

    /*
     * Convert the original dia diagram into a list of dia objects
     * reading for processing.
     */
    auto r(processed_object_factory::make(d));

    /*
     * Remove all the non-relevant process objects.
     */
    boost::range::remove_erase_if(r, is_not_relevant);

    /*
     * Sanity check the processed objects to make sure they are valid.
     */
    validator::validate(r);

    BOOST_LOG_SEV(lg, debug) << "Converted diagram into processed objects.";
    return r;
}

injection::entities::model
decoding_transform::obtain_model(const std::string& name,
    const std::list<processed_object>& pos) const {
    BOOST_LOG_SEV(lg, debug) << "Generating injection model.";

    /*
     * Create a dependency graph of the objects, and a map of children
     * to their respective parents.
     */
    grapher g;
    g.generate(pos);

    /*
     * Go through the dependency graph and build a injection model from
     * it.
     */
    builder b(g.parent_id_to_child_ids());
    visitor v(b);
    boost::depth_first_search(g.graph(), boost::visitor(v));
    auto r(b.build());
    r.name(name);

    BOOST_LOG_SEV(lg, debug) << "Generated injection model.";
    return r;
}

std::string decoding_transform::id() const {
    return ::decoder_id;
}

std::string decoding_transform::description() const {
    return ::description;
}

std::string decoding_transform::extension() const {
    return ::extension;
}

injection::entities::model
decoding_transform::apply(const injection::transforms::context& ctx,
    const boost::filesystem::path& p) {

    BOOST_LOG_SEV(lg, debug) << "Reading Dia diagram.";
    dogen::dia::hydrator h;
    const auto diagram(h.hydrate(p));
    BOOST_LOG_SEV(lg, debug) << "Read Dia diagram.";

    const auto model_name(p.stem().generic_string());
    tracing::scoped_transform_tracer stp(lg, "dia model transform",
        transform_id, model_name, *ctx.tracer(), diagram);

    const auto pos(obtain_processed_objects(diagram));
    const auto r(obtain_model(model_name, pos));
    stp.end_transform(r);

    BOOST_LOG_SEV(lg, debug) << "Finished converting diagram into "
                             << "an injection model.";
    return r;
}

}
