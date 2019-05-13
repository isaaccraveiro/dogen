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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.injection/io/meta_model/model_io.hpp"
#include "dogen.coding/types/traits.hpp"
#include "dogen.coding/types/meta_model/structural/module.hpp"
#include "dogen.coding/types/meta_model/structural/object.hpp"
#include "dogen.coding/types/meta_model/structural/builtin.hpp"
#include "dogen.coding/types/meta_model/element.hpp"
#include "dogen.coding/types/meta_model/structural/visitor.hpp"
#include "dogen.coding/types/meta_model/structural/exception.hpp"
#include "dogen.coding/types/meta_model/structural/primitive.hpp"
#include "dogen.coding/types/meta_model/structural/enumeration.hpp"
#include "dogen.coding/types/meta_model/structural/object_template.hpp"
#include "dogen.coding/io/meta_model/name_io.hpp"
#include "dogen.coding/io/meta_model/location_io.hpp"
#include "dogen.coding/io/meta_model/model_io.hpp"
#include "dogen.coding/io/meta_model/static_stereotypes_io.hpp"
#include "dogen.coding/types/helpers/name_builder.hpp"
#include "dogen.coding/types/helpers/location_builder.hpp"
#include "dogen.engine/io/helpers/stereotypes_conversion_result_io.hpp"
#include "dogen.engine/types/helpers/stereotypes_helper.hpp"
#include "dogen.engine/types/transforms/context.hpp"
#include "dogen.engine/types/transforms/transform_exception.hpp"
#include "dogen.engine/types/transforms/injection_model_to_coding_model_transform.hpp"

namespace {

const std::string transform_id(
    "engine.transforms.injection_model_to_coding_model_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string cpp_technical_space("cpp");
const std::string csharp_technical_space("csharp");
const std::string agnostic_technical_space("agnostic");

const std::string duplicate_element("Element id already exists: ");
const std::string missing_model_modules("Must supply model modules.");
const std::string missing_element_type("Missing masd element type. Element: ");
const std::string invalid_element_type(
    "Invalid or usupported masd element type: ");
const std::string too_many_element_types(
    "Attempting to set the masd type more than once.");
const std::string unsupported_technical_space(
    "Technical space is not supported: ");

using dogen::coding::meta_model::location;
const location empty_location = location();

}

namespace dogen::engine::transforms {

template<typename Element>
inline void
insert(const boost::shared_ptr<Element>& e,
    std::unordered_map<std::string, boost::shared_ptr<Element>>& dst) {
    const auto id(e->name().qualified().dot());
    bool inserted(dst.insert(std::make_pair(id, e)).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_element << id;
        BOOST_THROW_EXCEPTION(transform_exception(duplicate_element + id));
    }
}

coding::meta_model::technical_space to_technical_space(const std::string& s) {
    using coding::meta_model::technical_space;
    if (s == cpp_technical_space)
        return technical_space::cpp;
    else if (s == csharp_technical_space)
        return technical_space::csharp;
    else if (s == agnostic_technical_space)
        return technical_space::agnostic;

    BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
    BOOST_THROW_EXCEPTION(transform_exception(unsupported_technical_space + s));
}

injection_model_to_coding_model_transform::feature_group
injection_model_to_coding_model_transform::
make_feature_group(const variability::meta_model::feature_model& fm) {
    feature_group r;

    const variability::helpers::feature_selector s(fm);

    const auto& em(coding::traits::external_modules());
    r.external_modules = s.get_by_name(em);

    const auto& mm(coding::traits::model_modules());
    r.model_modules = s.get_by_name(mm);

    return r;
}

naming_configuration
injection_model_to_coding_model_transform::
make_naming_configuration(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    if (!s.has_configuration_point(fg.model_modules)) {
        BOOST_LOG_SEV(lg, error) << missing_model_modules;
        BOOST_THROW_EXCEPTION(transform_exception(missing_model_modules));
    }

    naming_configuration r;
    r.model_modules(s.get_text_content(fg.model_modules));

    if (s.has_configuration_point(fg.external_modules))
        r.external_modules(s.get_text_content(fg.external_modules));

    return r;
}

coding::meta_model::location injection_model_to_coding_model_transform::
create_location(const naming_configuration& nc) {
    coding::helpers::location_builder b;
    b.external_modules(nc.external_modules());
    b.model_modules(nc.model_modules());

    const auto r(b.build());
    BOOST_LOG_SEV(lg, debug) << "Computed location: " << r;
    return r;
}

coding::meta_model::static_stereotypes
injection_model_to_coding_model_transform::
compute_element_type(
    const std::list<coding::meta_model::static_stereotypes>& st,
    const std::string& fallback_element_type) {

    /*
     * Extract the element type information from the supplied static
     * stereotypes. If we have exactly one, we're go to go.
     */
    helpers::stereotypes_helper h;
    const auto et(h.extract_element_types(st));
    if (et.size() == 1)
        return et.front();

    /*
     * If we've got more than one element type, there is a user error
     * so bomb out.
     */
    if (et.size() > 1) {
        BOOST_LOG_SEV(lg, warn) << too_many_element_types;
        BOOST_THROW_EXCEPTION(transform_exception(too_many_element_types));
    }

    /*
     * If no masd element type came up, attempt to use the fallback
     * stereotype suggested by the frontend. If none was suggested
     * just return invalid.
     */
    if (fallback_element_type.empty())
        return coding::meta_model::static_stereotypes::invalid;

    return h.from_string(fallback_element_type);
}

void injection_model_to_coding_model_transform::
process_element(const helpers::adapter& ad,
    const coding::meta_model::location& l,
    const injection::meta_model::element& e, coding::meta_model::model& m) {

    helpers::stereotypes_helper h;
    const auto scr(h.from_string(e.stereotypes()));
    const auto& st(scr.static_stereotypes());
    const auto et(compute_element_type(st, e.fallback_element_type()));

    using coding::meta_model::static_stereotypes;
    switch (et) {
    case static_stereotypes::object:
        insert(ad.to_object(l, scr, e),
            m.structural_elements().objects());
        break;
    case static_stereotypes::object_template:
        insert(ad.to_object_template(l, scr, e),
            m.structural_elements().object_templates());
        break;
    case static_stereotypes::exception:
        insert(ad.to_exception(l, scr, e),
            m.structural_elements().exceptions());
        break;
    case static_stereotypes::primitive:
        insert(ad.to_primitive(l, scr, e),
            m.structural_elements().primitives());
        break;
    case static_stereotypes::enumeration:
        insert(ad.to_enumeration(l, scr, e),
            m.structural_elements().enumerations());
        break;
    case static_stereotypes::module:
        insert(ad.to_module(l, scr, e),
            m.structural_elements().modules());
        break;
    case static_stereotypes::builtin:
        insert(ad.to_builtin(l, scr, e),
            m.structural_elements().builtins());
        break;
    case static_stereotypes::modeline_group:
        insert(ad.to_modeline_group(l, scr, e),
            m.decoration_elements().modeline_groups());
        break;
    case static_stereotypes::modeline:
        insert(ad.to_modeline(l, scr, e),
            m.decoration_elements().modelines());
        break;
    case static_stereotypes::generation_marker:
        insert(ad.to_generation_marker(l, scr, e),
            m.decoration_elements().generation_markers());
        break;
    case static_stereotypes::licence:
        insert(ad.to_licence(l, scr, e),
            m.decoration_elements().licences());
        break;
    case static_stereotypes::variability_profile_template:
        insert(ad.to_variability_profile_template(l, scr, e),
            m.variability_elements().profile_templates());
        break;
    case static_stereotypes::variability_feature_bundle:
        insert(ad.to_variability_feature_bundle(l, scr, e),
            m.variability_elements().feature_bundles());
        break;
    case static_stereotypes::variability_feature_template_initializer:
        // FIXME: throw if already set.
        m.variability_elements().feature_template_initializer(
            ad.to_variability_feature_template_initializer(l, scr, e));
        break;
    default: {
        const auto s(boost::lexical_cast<std::string>(et));
        BOOST_LOG_SEV(lg, error) << invalid_element_type << s;
        BOOST_THROW_EXCEPTION(transform_exception(invalid_element_type + s));
    } }
}

coding::meta_model::model injection_model_to_coding_model_transform::
apply(const context& ctx, const injection::meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "injection model to coding model transform", transform_id, m.name(),
        *ctx.coding_context().tracer(), m);

    /*
     * First we compute the model name and technical space by reading
     * data from configuration.
     */
    const auto& cfg(*m.configuration());
    auto& gcfg(m.configuration());
    const auto& fm(*ctx.coding_context().feature_model());
    const auto fg(make_feature_group(fm));
    const auto nc(make_naming_configuration(fg, cfg));
    const auto model_location(create_location(nc));

    coding::meta_model::model r;
    coding::helpers::name_builder b(true/*model_name_mode*/);
    b.external_modules(model_location.external_modules());
    b.model_modules(model_location.model_modules());
    r.name(b.build());
    r.input_technical_space(to_technical_space(m.input_technical_space()));
    BOOST_LOG_SEV(lg, debug) << "Computed model name: " << r.name();

    /*
     * Then we populate all model elements by adapting the injection
     * elements into coding elements.
     */
    const helpers::adapter ad;
    for (const auto& e : m.elements()) {
        const auto l(e.in_global_module() ? empty_location : model_location);
        process_element(ad, l, e, r);
    }

    /*
     * Finally we handle the creation of the root module. This is done
     * separately from regular module processing due to the vagaries
     * of the root module: its not an element from an injection
     * perspective, etc.
     */
    r.root_module(boost::make_shared<coding::meta_model::structural::module>());
    auto& rm(*r.root_module());
    rm.name(r.name());
    rm.configuration(gcfg);
    rm.configuration()->name().qualified(rm.name().qualified().dot());
    rm.is_root(true);

    helpers::stereotypes_helper h;
    const auto scr(h.from_string(m.stereotypes()));
    rm.dynamic_stereotypes(scr.dynamic_stereotypes());
    rm.documentation(m.documentation());
    insert(r.root_module(), r.structural_elements().modules());

    stp.end_transform(r);
    return r;
}

}