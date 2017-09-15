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
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia/types/hydrator.hpp"
#include "dogen/dia/types/persister.hpp"
#include "dogen/dia/io/diagram_io.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/io/meta_model/exomodel_io.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/helpers/scoped_transform_probing.hpp"
#include "dogen/yarn.dia/types/workflow.hpp"
#include "dogen/yarn.dia/types/exomodel_transform.hpp"

namespace {

using namespace dogen::utility::log;
const std::string transform_id("yarn.dia.exomodel_transform");
auto lg(logger_factory(transform_id));

const std::string extension(".dia");

const std::string to_dia_support_unavailable(
    "Transformer cannot convert model into Dia representation");

}

namespace dogen {
namespace yarn {
namespace dia {

exomodel_transform::~exomodel_transform() noexcept {}

std::string exomodel_transform::id() const {
    return transform_id;
}

yarn::transforms::exomodel_transform_types
exomodel_transform::transform_types() const {
    return transforms::exomodel_transform_types::unidirectional_from;
}

std::list<std::string> exomodel_transform::supported_extensions() const {
    static const auto extensions = std::list<std::string> { extension };
    return extensions;
}

meta_model::exomodel exomodel_transform::
transform(const transforms::context& ctx, const boost::filesystem::path& p) {
    BOOST_LOG_SEV(lg, debug) << "Reading Dia diagram.";

    dogen::dia::hydrator h;
    const auto diagram(h.hydrate(p));

    const auto model_name(p.filename().string());
    helpers::scoped_transform_probing stp(lg, "dia exomodel transform",
        transform_id, model_name, ctx.prober(), diagram);

    BOOST_LOG_SEV(lg, debug) << "Read Dia diagram.";

    BOOST_LOG_SEV(lg, debug) << "Converting it into yarn.";
    const auto r(yarn::dia::workflow::execute(diagram));
    BOOST_LOG_SEV(lg, debug) << "Finished converting it into yarn.";

    stp.end_transform(r);
    return r;
}

void exomodel_transform::transform(const transforms::context& /*ctx*/,
    const meta_model::exomodel& /*em*/, const boost::filesystem::path& /*p*/) {
    BOOST_LOG_SEV(lg, error) << to_dia_support_unavailable;

    using yarn::transforms::transformation_error;
    BOOST_THROW_EXCEPTION(transformation_error(to_dia_support_unavailable));
}

} } }
