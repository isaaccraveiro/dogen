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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.archetypes/types/building_error.hpp"
#include "masd.dogen.archetypes/io/location_repository_io.hpp"
#include "masd.dogen.archetypes/types/location_repository_builder.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger
lg(logger_factory("archetypes.location_repository_builder"));

const std::string empty_backend("Backend name cannot be empty. Archetype: ");
const std::string empty_facet("Facet name cannot be empty. Archetype: ");
const std::string empty_archetype("Archetype name cannot be empty.");
const std::string duplicate_family("Duplicate family: ");
const std::string duplicate_archetype("Archetype name already inserted: ");

}

namespace masd::dogen::archetypes {

void location_repository_builder::
validate(const std::list<location>& als) const {
    BOOST_LOG_SEV(lg, debug) << "Validating archetype locations.";

    for (const auto& al : als) {
        /*
         * We expect all three key coordinates of the location to be
         * populated.
         */
        if (al.archetype().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_archetype;
            BOOST_THROW_EXCEPTION(building_error(empty_archetype));
        }

        if (al.backend().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_backend << al.archetype();
            BOOST_THROW_EXCEPTION(
                building_error(empty_backend + al.archetype()));
        }

        if (al.facet().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_facet << al.archetype();
            BOOST_THROW_EXCEPTION(building_error(empty_facet + al.archetype()));
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Archetype locations are valid.";
}

void location_repository_builder::
populate_locations(const std::list<location>& als) {
    for(const auto& al : als)
        repository_.all().push_back(al);
}

void location_repository_builder::
populate_facet_names_by_backend_name() {
    auto& fnbkn(repository_.facet_names_by_backend_name());
    for (const auto& al : repository_.all())
        fnbkn[al.backend()].insert(al.facet());
}

void location_repository_builder::
populate_formatter_names_by_backend_name() {
    auto& fnbkn(repository_.formatter_names_by_backend_name());
    for (const auto& al : repository_.all())
        fnbkn[al.backend()].insert(al.archetype());
}

void location_repository_builder::
populate_archetypes_by_facet_by_backend() {
    auto& abbbf(repository_.by_backend_by_facet());
    for (const auto& al : repository_.all())
        abbbf[al.backend()][al.facet()].push_back(al.archetype());
}

void location_repository_builder::
add(const std::list<location>& als) {
    BOOST_LOG_SEV(lg, debug) << "Adding list of archetype location.";

    validate(als);
    populate_locations(als);

    BOOST_LOG_SEV(lg, debug) << "Added archetype location list. ";
}

void location_repository_builder::
add(const std::unordered_map<std::string, locations_group>&
    locations_by_meta_name) {
    auto& albmn(repository_.by_meta_name());
    for (const auto& pair : locations_by_meta_name) {
        /*
         * We start by inserting the archetype locations into the
         * overall container with all archetype locations across all
         * backends.
         */
        const auto& src(pair.second);
        add(src.locations());

        /*
         * Now lets populate the meta-name specific container.
         */
        const auto& mn(pair.first);
        auto& dst(albmn[mn]);

        /*
         * We need to merge the archetype locations at the meta-type
         * level because each backend is reusing the same yarn
         * meta-types.
         */
        for (const auto& al : src.locations())
            dst.locations().push_back(al);

        /*
         * However, when it comes down to the canonical archetype
         * mapping, we expect each archetype to be unique - after all,
         * no two formatters can be pointing to the same archetype
         * location (by definition). So, if we spot any duplicates,
         * its a logic error.
         */
        auto& cal(dst.canonical_locations());
        for (const auto& pair : src.canonical_locations()) {
            const bool inserted(cal.insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_archetype << pair.first;
                BOOST_THROW_EXCEPTION(
                    building_error(duplicate_archetype + pair.first));
            }
        }
    }
}

void location_repository_builder::
add(const std::unordered_map<std::string,
    std::list<location>>& locations_by_family) {
    auto& albf(repository_.by_family());
    for (const auto& pair : locations_by_family) {
        const auto& family(pair.first);
        const auto src(pair.second);

        /*
         * Note that we impose families to be unique across all
         * backends and all kernels, so that we can safely merge them
         * all into one big container. If they were not unique this
         * would mean users could set conflicting properties at the
         * family level per kernel; to fix this we'd ended up having
         * separate collections of families per kernel.
         *
         * This is not an ideal limitation, but its not a problem for
         * now since families are quite distinct on a per backend
         * basis - e.g. c++ include files, c# implementation files,
         * etc.
         *
         * Thus here, we just ensure that they are indeed unique.
         */
        auto& dst(albf[family]);
        if (!dst.empty()) {
            BOOST_LOG_SEV(lg, error) << duplicate_family << family;
            BOOST_THROW_EXCEPTION(building_error(duplicate_family + family));
        }

        for (const auto& al : src)
            dst.push_back(al);
    }
}

void location_repository_builder::
add(const location_repository_parts& parts) {
    add(parts.all());
    add(parts.by_meta_name());
    add(parts.by_family());
    add(parts.by_intra_backend_segment());
}

const location_repository&
location_repository_builder::build() {
    populate_facet_names_by_backend_name();
    populate_formatter_names_by_backend_name();
    populate_archetypes_by_facet_by_backend();

    BOOST_LOG_SEV(lg, debug) << "Repository built: " << repository_;
    return repository_;
}

}