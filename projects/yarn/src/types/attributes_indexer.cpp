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
#include <set>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <boost/lexical_cast.hpp>
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/indexing_error.hpp"
#include "dogen/yarn/types/attributes_indexer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("yarn.attributes_indexer"));

const std::string relationship_not_found(
    "Could not find relationship in object. Details: ");
const std::string object_not_found("Object not found in model: ");
const std::string concept_not_found("Concept not found in concept container: ");

}

namespace dogen {
namespace yarn {

object& attributes_indexer::find_object(const name& n, intermediate_model& m) {
    const auto id(n.id());
    auto i(m.objects().find(id));
    if (i == m.objects().end()) {
        BOOST_LOG_SEV(lg, error) << object_not_found << id;
        BOOST_THROW_EXCEPTION(indexing_error(object_not_found + id));
    }
    return i->second;
}

concept& attributes_indexer::
find_concept(const name& n, intermediate_model& m) {
    const auto& id(n.id());
    auto i(m.concepts().find(id));
    if (i == m.concepts().end()) {
        BOOST_LOG_SEV(lg, error) << concept_not_found << id;
        BOOST_THROW_EXCEPTION(indexing_error(concept_not_found + id));
    }
    return i->second;
}

void attributes_indexer::index_object(object& o, intermediate_model& m,
    std::unordered_set<std::string>& processed_ids) {
    const auto id(o.name().id());
    BOOST_LOG_SEV(lg, debug) << "Indexing object: " << id;

    if (processed_ids.find(id) != processed_ids.end()) {
        BOOST_LOG_SEV(lg, debug) << "Object already processed: " << id;
        return;
    }

    /*
     * We first grab all of the concept attributes in one go, and them
     * add them to the local attributes at the beginning. The idea is
     * to keep changes from rippling through, but there is no evidence
     * that this order is more effective than other alternatives.
     */
    std::list<attribute> concept_attributes;
    for (const auto& n : o.modeled_concepts()) {
        auto& c(find_concept(n, m));
        const auto& p(c.local_attributes());
        concept_attributes.insert(concept_attributes.end(), p.begin(), p.end());
    }

    /*
     * If we are a fluent or an immutable object, we need to mark all
     * properties we've inherited via concepts. All of the properties
     * we own directly have already been marked during attribute
     * expansion, but we couldn't do the same to concept owned
     * properties until they were indexed.
     */
    if (o.is_fluent() || o.is_immutable()) {
        for(auto& attr : concept_attributes) {
            attr.is_fluent(o.is_fluent());
            attr.is_immutable(o.is_immutable());
        }
    }

    o.local_attributes().insert(o.local_attributes().begin(),
        concept_attributes.begin(), concept_attributes.end());

    /*
     * Now handle all of the inherited properties. We insert our
     * parent properties first on our all attributes container by
     * design; local attributes are last.
     */
    for (const auto& n : o.parents()) {
        auto& parent(find_object(n, m));
        index_object(parent, m, processed_ids);

        if (!parent.all_attributes().empty()) {
            const auto& pn(parent.name());
            const auto pair(std::make_pair(pn, parent.all_attributes()));
            o.inherited_attributes().insert(pair);
        }

        const auto p(parent.all_attributes());
        o.all_attributes().insert(o.all_attributes().end(), p.begin(), p.end());
    }

    o.all_attributes().insert(o.all_attributes().end(),
        o.local_attributes().begin(), o.local_attributes().end());

    processed_ids.insert(id);
}

void attributes_indexer::index_objects(intermediate_model& m) {
    BOOST_LOG_SEV(lg, debug) << "Indexing objects: " << m.objects().size();

    std::unordered_set<std::string> processed_ids;
    for (auto& pair : m.objects()) {
        auto& o(pair.second);

        if (o.generation_type() == generation_types::no_generation)
            continue;

        index_object(o, m, processed_ids);
    }
}

void attributes_indexer::index_concept(concept& c, intermediate_model& m,
    std::unordered_set<std::string>& processed_ids) {
    const auto id(c.name().id());
    BOOST_LOG_SEV(lg, debug) << "Indexing concept: " << id;

    if (processed_ids.find(c.name().id()) != processed_ids.end()) {
        BOOST_LOG_SEV(lg, debug) << "Object already processed:" << id;
        return;
    }

    c.all_attributes().insert(c.all_attributes().end(),
        c.local_attributes().begin(), c.local_attributes().end());

    for (const auto& n : c.refines()) {
        auto& parent(find_concept(n, m));
        index_concept(parent, m, processed_ids);

        c.inherited_attributes().insert(
            std::make_pair(parent.name(), parent.local_attributes()));

        c.all_attributes().insert(c.all_attributes().end(),
            parent.local_attributes().begin(), parent.local_attributes().end());
    }
    processed_ids.insert(id);
}

void attributes_indexer::index_concepts(intermediate_model& m) {
    BOOST_LOG_SEV(lg, debug) << "Indexing concepts: " << m.concepts().size();

    std::unordered_set<std::string> processed_ids;
    for (auto& pair : m.concepts()) {
        auto& c(pair.second);

        if (c.generation_type() == generation_types::no_generation)
            continue;

        index_concept(c, m, processed_ids);
    }
}

void attributes_indexer::index(intermediate_model& m) {
    index_concepts(m);
    index_objects(m);
}

} }
