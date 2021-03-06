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
#include <iterator>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.m2t.cpp/types/workflow_error.hpp"
#include "dogen.logical/io/entities/formatting_styles_io.hpp"
#include "dogen.m2t.cpp/io/formattables/artefact_properties_io.hpp"
#include "dogen.m2t.cpp/types/transforms/context.hpp"
#include "dogen.m2t.cpp/types/transforms/wale_transform.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("m2t.cpp.transforms.workflow"));

const std::string archetype_not_found("Archetype not found: ");
const std::string invalid_formatting_style("Invalid formatting style");

}

namespace dogen::m2t::cpp::transforms {

std::shared_ptr<cpp::transforms::registrar> workflow::registrar_;

workflow::workflow(const formattables::locator& l,
    const variability::entities::feature_model& fm,
    const variability::helpers::configuration_factory& cf)
    : stitch_formatter_(l, fm, cf), locator_(l) { }

cpp::transforms::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<cpp::transforms::registrar>();

    return *registrar_;
}

const logical::entities::artefact_properties&
workflow::get_artefact_properties(const logical::entities::element& e,
    const std::string& archetype) const {

    const auto& ap(e.artefact_properties());
    const auto i(ap.find(archetype));
    if (i == ap.end()) {
        BOOST_LOG_SEV(lg, error) << archetype_not_found << archetype;
        BOOST_THROW_EXCEPTION(workflow_error(archetype_not_found + archetype));
    }
    return i->second;
}

boost::shared_ptr<physical::entities::artefact>
workflow::get_artefact(const std::unordered_map<std::string,
    boost::shared_ptr<physical::entities::artefact>>& artefacts,
    const std::string& archetype) const {

    const auto i(artefacts.find(archetype));
    if (i == artefacts.end()) {
        BOOST_LOG_SEV(lg, error) << archetype_not_found << archetype;
        BOOST_THROW_EXCEPTION(workflow_error(archetype_not_found + archetype));
    }
    return i->second;
}

void
workflow::execute(const std::unordered_set<m2t::entities::element_archetype>&
    enabled_archetype_for_element, const formattables::model& fm,
    formattables::formattable& fbl) const {

    const auto& e(*fbl.element());
    const auto id(e.name().qualified().dot());
    BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

    const auto mn(e.meta_name().qualified().dot());
    BOOST_LOG_SEV(lg, debug) << "Meta name: " << mn;

    const auto& frp(registrar().formatter_repository());
    const auto i(frp.stock_artefact_formatters_by_meta_name().find(mn));
    if (i == frp.stock_artefact_formatters_by_meta_name().end()) {
        BOOST_LOG_SEV(lg, debug) << "No formatters for meta name: " << mn;
        return;
    }

    const auto& ep(fbl.element_properties());
    const auto& fmts(i->second);
    for (const auto& ptr : fmts) {
        const auto& fmt(*ptr);
        const auto pn(fmt.physical_meta_name());
        const auto arch(pn.qualified());
        const auto& ap(get_artefact_properties(e, arch));
        auto aptr(get_artefact(fbl.artefacts(), arch));

        if (!ap.enabled()) {
            BOOST_LOG_SEV(lg, debug) << "Archetype is disabled: " << arch;
            continue;
        }
        BOOST_LOG_SEV(lg, debug) << "Archetype is enabled: " << arch;

        using logical::entities::formatting_styles;
        const auto& frp(registrar().formatter_repository());
        context ctx(enabled_archetype_for_element, ep, fm,
            frp.helper_formatters());

        auto& a(*aptr);
        const auto fs(ap.formatting_style());
         if (fs == formatting_styles::stock) {
             const auto id(fmt.id());
             BOOST_LOG_SEV(lg, debug) << "Using the stock formatter: " << id;
             fmt.apply(ctx, e, a);

             const auto& p(a.name().qualified());
             BOOST_LOG_SEV(lg, debug) << "Formatted artefact. Path: " << p;
         } else if (fs == formatting_styles::wale) {
             BOOST_LOG_SEV(lg, debug) << "Using the wale formatter.";
             wale_transform f;
             f.apply(locator_, fmt, ctx, e, a);

             const auto& p(a.name().qualified());
             BOOST_LOG_SEV(lg, debug) << "Formatted artefact. Path: " << p;
         } else if (fs == formatting_styles::stitch) {
             BOOST_LOG_SEV(lg, debug) << "Using the stitch formatter.";
             stitch_formatter_.apply(fmt, ctx, e, a);

             const auto& p(a.name().qualified());
             BOOST_LOG_SEV(lg, debug) << "Formatted artefact. Path: " << p;
             if (!a.content().empty()) {
                 BOOST_LOG_SEV(lg, debug) << "Template has content.";
             } else {
                 BOOST_LOG_SEV(lg, debug) << "Template has no content.";
             }
         } else {
             BOOST_LOG_SEV(lg, error) << invalid_formatting_style << fs;
             BOOST_THROW_EXCEPTION(formatting_error(invalid_formatting_style));
        }
    }
}

void workflow::
execute(const std::unordered_set<m2t::entities::element_archetype>&
    enabled_archetype_for_element, formattables::model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started formatting. Model "
                             << fm.name().qualified().dot();

    for (auto& pair : fm.formattables()) {
        auto& fbl(pair.second);
        execute(enabled_archetype_for_element, fm, fbl);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished formatting.";
}

}
