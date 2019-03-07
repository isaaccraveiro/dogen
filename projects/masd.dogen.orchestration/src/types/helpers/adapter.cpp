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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/string/splitter.hpp"
#include "masd.dogen.coding/io/meta_model/location_io.hpp"
#include "masd.dogen.coding/types/helpers/name_builder.hpp"
#include "masd.dogen.orchestration/types/helpers/adaptation_exception.hpp"
#include "masd.dogen.orchestration/types/helpers/adapter.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory("orchestration.helpers.adapter"));

const std::string empty_name("Name is empty.");
const std::string enumerator_with_type("Enumerators cannot have a type: ");

}

namespace masd::dogen::orchestration::helpers {

adapter::adapter(const annotations::annotation_expander& e)
    : annotation_expander_(e) {}

void adapter::ensure_not_empty(const std::string& n) const {
    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_name;
        BOOST_THROW_EXCEPTION(adaptation_exception(empty_name));
    }
}

coding::meta_model::name adapter::to_name(const coding::meta_model::location& l,
    const std::string& n) const {
    BOOST_LOG_SEV(lg, debug) << "Location: " << l;
    /*
     * Names are expected to be delimited by the scope operator,
     * denoting internal modules.
     */
    ensure_not_empty(n);
    auto tokens(utility::string::splitter::split_scoped(n));
    coding::helpers::name_builder b;
    b.simple_name(tokens.back());
    tokens.pop_back();
    if (!tokens.empty())
        b.internal_modules(tokens);

    b.external_modules(l.external_modules());
    b.model_modules(l.model_modules());

    return b.build();
}

coding::meta_model::attribute
adapter::to_attribute(const coding::meta_model::location& /*l*/,
    const injection::meta_model::attribute& ia) const {
    ensure_not_empty(ia.name());

    coding::meta_model::attribute r;
    r.name().simple(ia.name()); // FIXME
    r.unparsed_type(ia.type());
    r.documentation(ia.documentation());
    r.annotation(annotation_expander_.expand(ia.annotation()));

    return r;
}

coding::meta_model::enumerator
adapter::to_enumerator(const coding::meta_model::location& /*l*/,
    const injection::meta_model::attribute& ia) const {
    ensure_not_empty(ia.name());

    if (!ia.type().empty()) {
        const auto t(ia.type());
        BOOST_LOG_SEV(lg, error) << enumerator_with_type << t;
        BOOST_THROW_EXCEPTION(adaptation_exception(enumerator_with_type + t));
    }

    coding::meta_model::enumerator r;
    r.name().simple(ia.name()); // FIXME
    r.documentation(ia.documentation());
    r.annotation(annotation_expander_.expand(ia.annotation()));

    return r;
}

void adapter::populate_element(const coding::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie, coding::meta_model::element& e) const {
    e.name(to_name(l, ie.name()));
    e.origin_type(coding::meta_model::origin_types::not_yet_determined);
    e.documentation(ie.documentation());
    e.static_stereotypes(scr.static_stereotypes());

    const auto& ds(scr.dynamic_stereotypes());
    e.dynamic_stereotypes(ds);
    e.annotation(annotation_expander_.expand(ds, ie.annotation()));
    e.in_global_module(
        l.external_modules().empty() && l.model_modules().empty());
}

boost::shared_ptr<coding::meta_model::object>
adapter::to_object(const coding::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to object: "
                             << ie.name();

    auto r(boost::make_shared<coding::meta_model::object>());
    populate_element(l, scr, ie, *r);
    r->is_associative_container(ie.is_associative_container());
    r->can_be_primitive_underlier(ie.can_be_primitive_underlier());

    for (const auto& attr : ie.attributes())
        r->local_attributes().push_back(to_attribute(l, attr));

    for (const auto& p : ie.parents())
        r->parents().push_back(to_name(l, p));

    return r;
}

boost::shared_ptr<coding::meta_model::object_template>
adapter::to_object_template(const coding::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element "
                             << "to object template: " << ie.name();

    auto r(boost::make_shared<coding::meta_model::object_template>());
    populate_element(l, scr, ie, *r);

    for (const auto& attr : ie.attributes())
        r->local_attributes().push_back(to_attribute(l, attr));

    for (const auto& p : ie.parents())
        r->parents().push_back(to_name(l, p));

    return r;
}

boost::shared_ptr<coding::meta_model::exception>
adapter::to_exception(const coding::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to exception: "
                             << ie.name();

    auto r(boost::make_shared<coding::meta_model::exception>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<coding::meta_model::primitive>
adapter::to_primitive(const coding::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to primitive: "
                             << ie.name();

    auto r(boost::make_shared<coding::meta_model::primitive>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<coding::meta_model::enumeration>
adapter::to_enumeration(const coding::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to enumeration: "
                             << ie.name();

    auto r(boost::make_shared<coding::meta_model::enumeration>());
    populate_element(l, scr, ie, *r);

    for (const auto& attr : ie.attributes())
        r->enumerators().push_back(to_enumerator(l, attr));

    return r;
}

boost::shared_ptr<coding::meta_model::module> adapter::
to_module(const coding::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to module: "
                             << ie.name();

    auto r(boost::make_shared<coding::meta_model::module>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<coding::meta_model::builtin>
adapter::to_builtin(const coding::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to builtin: "
                             << ie.name();

    auto r(boost::make_shared<coding::meta_model::builtin>());
    populate_element(l, scr, ie, *r);

    r->can_be_primitive_underlier(ie.can_be_primitive_underlier());
    r->is_default_enumeration_type(ie.is_default_enumeration_type());
    r->is_floating_point(ie.is_floating_point());
    r->can_be_enumeration_underlier(ie.can_be_enumeration_underlier());

    return r;
}

}