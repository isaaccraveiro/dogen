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
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.injection/io/entities/model_io.hpp"
#include "dogen.logical/types/traits.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/structural/object_template.hpp"
#include "dogen.logical/types/entities/structural/assistant.hpp"
#include "dogen.logical/io/entities/name_io.hpp"
#include "dogen.logical/io/entities/location_io.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/io/entities/static_stereotypes_io.hpp"
#include "dogen.logical/types/helpers/name_builder.hpp"
#include "dogen.logical/types/helpers/location_builder.hpp"
#include "dogen.orchestration/io/helpers/stereotypes_conversion_result_io.hpp"
#include "dogen.orchestration/types/features/model_location.hpp"
#include "dogen.orchestration/types/helpers/stereotypes_helper.hpp"
#include "dogen.orchestration/types/transforms/context.hpp"
#include "dogen.orchestration/types/transforms/transform_exception.hpp"
#include "dogen.orchestration/types/transforms/injection_model_to_logical_model_transform.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.injection_model_to_logical_model_transform");

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
const std::string too_many_initializers(
    "Found more than one feature template initializer in model.");

using dogen::logical::entities::location;
const location empty_location = location();

}

namespace dogen::orchestration::transforms {

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

logical::entities::technical_space to_technical_space(const std::string& s) {
    using logical::entities::technical_space;
    if (s == cpp_technical_space)
        return technical_space::cpp;
    else if (s == csharp_technical_space)
        return technical_space::csharp;
    else if (s == agnostic_technical_space)
        return technical_space::agnostic;

    BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
    BOOST_THROW_EXCEPTION(transform_exception(unsupported_technical_space + s));
}

logical::entities::location
injection_model_to_logical_model_transform::
create_location(const context& ctx, const injection::entities::model& m) {
    const auto& fm(*ctx.logical_context().feature_model());
    const auto fg(features::model_location::make_feature_group(fm));
    const auto scfg(features::model_location::make_static_configuration(fg, m));

    logical::helpers::location_builder b;
    b.external_modules(scfg.external_modules);
    b.model_modules(scfg.model_modules);

    const auto r(b.build());
    BOOST_LOG_SEV(lg, debug) << "Computed location: " << r;
    return r;
}

logical::entities::static_stereotypes
injection_model_to_logical_model_transform::
compute_element_type(const std::list<logical::entities::static_stereotypes>& st,
    const std::string& fallback_element_type) {
    /*
     * Extract the element type information from the supplied static
     * stereotypes, and determine the course of action based on how
     * many we got back.
     */
    helpers::stereotypes_helper h;
    const auto et(h.extract_element_types(st));
    switch (et.size()) {
    case 0:
        /*
         * If no masd element type came up, attempt to use the
         * fallback stereotype suggested by the frontend. If none was
         * suggested, well, we tried out best. Just return invalid.
         */
        if (!fallback_element_type.empty())
            return h.from_string(fallback_element_type);
        return logical::entities::static_stereotypes::invalid;
    case 1:
        /*
         *  If we have exactly one, we're go to go.
         */
        return et.front();
    default:
        /*
         * If we've got more than one element type, there is a user
         * error so bomb out.
         */
        BOOST_LOG_SEV(lg, warn) << too_many_element_types;
        BOOST_THROW_EXCEPTION(transform_exception(too_many_element_types));
    }
}

void injection_model_to_logical_model_transform::
process_element(const helpers::adapter& ad,
    const logical::entities::location& l,
    const injection::entities::element& e, logical::entities::model& m) {

    BOOST_LOG_SEV(lg, debug) << "Injection stereotypes: " << e.stereotypes();
    helpers::stereotypes_helper h;
    const auto scr(h.from_string(e.stereotypes()));
    const auto& st(scr.static_stereotypes());
    BOOST_LOG_SEV(lg, debug) << "Static stereotypes: " << st;

    const auto et(compute_element_type(st, e.fallback_element_type()));
    BOOST_LOG_SEV(lg, debug) << "Element type: " << et;

    /*
     * Short-hand names for all element containers.
     */
    auto& se(m.structural_elements());
    auto& de(m.decoration_elements());
    auto& ve(m.variability_elements());
    auto& me(m.mapping_elements());
    auto& te(m.templating_elements());
    auto& sere(m.serialization_elements());
    auto& vse(m.visual_studio_elements());
    auto& oe(m.orm_elements());
    auto& be(m.build_elements());
    auto& pe(m.physical_elements());

    using ss = logical::entities::static_stereotypes;
    switch (et) {
    case ss::structural_object:
        insert(ad.to_object(l, scr, e), se.objects());
        break;
    case ss::structural_object_template:
        insert(ad.to_object_template(l, scr, e), se.object_templates());
        break;
    case ss::structural_exception:
        insert(ad.to_exception(l, scr, e), se.exceptions());
        break;
    case ss::structural_primitive:
        insert(ad.to_primitive(l, scr, e), se.primitives());
        break;
    case ss::structural_enumeration:
        insert(ad.to_enumeration(l, scr, e), se.enumerations());
        break;
    case ss::structural_module:
        insert(ad.to_module(l, scr, e), se.modules());
        break;
    case ss::structural_builtin:
        insert(ad.to_builtin(l, scr, e), se.builtins());
        break;
    case ss::structural_entry_point:
        insert(ad.to_entry_point(l, scr, e), se.entry_points());
        break;
    case ss::structural_assistant:
        insert(ad.to_assistant(l, scr, e), se.assistants());
        break;
   case ss::decoration_modeline_group:
        insert(ad.to_modeline_group(l, scr, e), de.modeline_groups());
        break;
    case ss::decoration_modeline:
        insert(ad.to_modeline(l, scr, e), de.modelines());
        break;
    case ss::decoration_generation_marker:
        insert(ad.to_generation_marker(l, scr, e), de.generation_markers());
        break;
    case ss::decoration_licence:
        insert(ad.to_licence(l, scr, e), de.licences());
        break;
    case ss::variability_profile:
        insert(ad.to_variability_profile(l, scr, e), ve.profiles());
        break;
    case ss::variability_profile_template:
        insert(ad.to_variability_profile_template(l, scr, e),
            ve.profile_templates());
        break;
    case ss::variability_feature_template_bundle:
        insert(ad.to_variability_feature_template_bundle(l, scr, e),
            ve.feature_template_bundles());
        break;
    case ss::variability_feature_bundle:
        insert(ad.to_variability_feature_bundle(l, scr, e),
            ve.feature_bundles());
        break;
    case ss::variability_initializer:
        /*
         * A model can only have zero or one feature template
         * initializers.
         */
        if (m.variability_elements().initializer()) {
            BOOST_LOG_SEV(lg, error) << too_many_initializers;
            BOOST_THROW_EXCEPTION(transform_exception(too_many_initializers));
        }
        ve.initializer(ad.to_variability_initializer(l, scr, e));
        break;
    case ss::mapping_fixed_mappable:
        insert(ad.to_fixed_mappable(l, scr, e), me.fixed_mappables());
        break;
    case ss::mapping_extensible_mappable:
        insert(ad.to_extensible_mappable(l, scr, e), me.extensible_mappables());
        break;
    case ss::templating_logic_less_template:
        insert(ad.to_logic_less_template(l, scr, e), te.logic_less_templates());
        break;
    case ss::serialization_type_registrar:
        insert(ad.to_type_registrar(l, scr, e), sere.type_registrars());
        break;
    case ss::visual_studio_solution:
        insert(ad.to_visual_studio_solution(l, scr, e), vse.solutions());
        break;
    case ss::visual_studio_project:
        insert(ad.to_visual_studio_project(l, scr, e), vse.projects());
        break;
    case ss::visual_studio_msbuild_targets:
        insert(ad.to_visual_studio_msbuild_targets(l, scr, e),
            vse.msbuild_targets());
        break;
    case ss::orm_common_odb_options:
        insert(ad.to_orm_common_odb_options(l, scr, e), oe.common_odb_options());
        break;
    case ss::build_cmakelists:
        insert(ad.to_build_cmakelists(l, scr, e), be.cmakelists());
        break;
    case ss::physical_backend:
        insert(ad.to_physical_backend(l, scr, e), pe.backends());
        break;
    case ss::physical_facet:
        insert(ad.to_physical_facet(l, scr, e), pe.facets());
        break;
    case ss::physical_archetype:
        insert(ad.to_physical_archetype(l, scr, e), pe.archetypes());
        break;
    case ss::physical_archetype_kind:
        insert(ad.to_physical_archetype_kind(l, scr, e), pe.archetype_kinds());
        break;
    case ss::physical_part:
        insert(ad.to_physical_part(l, scr, e), pe.parts());
        break;

    default: {
        const auto s(boost::lexical_cast<std::string>(et));
        BOOST_LOG_SEV(lg, error) << invalid_element_type << s;
        BOOST_THROW_EXCEPTION(transform_exception(invalid_element_type + s));
    } }
}

logical::entities::model injection_model_to_logical_model_transform::
apply(const context& ctx, const injection::entities::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "injection model to logical model transform", transform_id, m.name(),
        *ctx.logical_context().tracer(), m);

    /*
     * First we compute the model name and technical space by reading
     * data from configuration.
     */
    logical::entities::model r;
    logical::helpers::name_builder b(true/*model_name_mode*/);
    const auto model_location(create_location(ctx, m));
    b.external_modules(model_location.external_modules());
    b.model_modules(model_location.model_modules());
    r.name(b.build());
    r.input_technical_space(to_technical_space(m.input_technical_space()));
    r.origin_sha1_hash(m.origin_sha1_hash());

    BOOST_LOG_SEV(lg, debug) << "Computed model name: " << r.name();

    /*
     * Then we populate all model elements by adapting the injection
     * elements into logical elements.
     */
    const helpers::adapter ad;
    for (const auto& e : m.elements()) {
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << e.name();
        const auto l(e.in_global_module() ? empty_location : model_location);
        process_element(ad, l, e, r);
    }

    /*
     * Finally we handle the creation of the root module. This is done
     * separately from regular module processing due to the vagaries
     * of the root module: its not an element from an injection
     * perspective, etc.
     */
    r.root_module(boost::make_shared<logical::entities::structural::module>());
    auto& rm(*r.root_module());
    rm.name(r.name());
    rm.configuration(m.configuration());
    rm.configuration()->name().qualified(rm.name().qualified().dot());
    rm.is_root(true);
    rm.origin_sha1_hash(m.origin_sha1_hash());

    helpers::stereotypes_helper h;
    const auto scr(h.from_string(m.stereotypes()));
    rm.dynamic_stereotypes(scr.dynamic_stereotypes());
    rm.documentation(m.documentation());
    insert(r.root_module(), r.structural_elements().modules());

    stp.end_transform(r);
    return r;
}

}
