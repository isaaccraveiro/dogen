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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/erase.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.utility/types/exception/invalid_enum_value.hpp"
#include "dogen.logical/io/entities/static_stereotypes_io.hpp"
#include "dogen.logical/types/entities/static_stereotypes.hpp"
#include "dogen.orchestration/types/helpers/stereotypes_helper.hpp"

namespace {

const std::string
transform_id("orchestration.helpers.stereotypes_helper");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string stereotype_visitable("masd::visitable");
const std::string stereotype_fluent("masd::fluent");
const std::string stereotype_immutable("masd::immutable");
const std::string stereotype_structural_object("masd::object");
const std::string stereotype_structural_object_template("masd::object_template");
const std::string stereotype_structural_exception("masd::exception");
const std::string stereotype_structural_primitive("masd::primitive");
const std::string stereotype_structural_enumeration("masd::enumeration");
const std::string stereotype_structural_module("masd::module");
const std::string stereotype_structural_builtin("masd::builtin");
const std::string stereotype_structural_entry_point("masd::entry_point");
const std::string stereotype_structural_assistant("masd::assistant");
const std::string stereotype_orm_object("masd::orm::object");
const std::string stereotype_orm_value("masd::orm::value");
const std::string stereotype_decoration_modeline_group(
    "masd::decoration::modeline_group");
const std::string stereotype_decoration_modeline("masd::decoration::modeline");
const std::string stereotype_decoration_generation_marker(
    "masd::decoration::generation_marker");
const std::string stereotype_decoration_licence("masd::decoration::licence");
const std::string stereotype_variability_profile(
    "masd::variability::profile");
const std::string stereotype_variability_profile_template(
    "masd::variability::profile_template");
const std::string stereotype_variability_feature_template_bundle(
    "masd::variability::feature_template_bundle");
const std::string stereotype_variability_feature_bundle(
    "masd::variability::feature_bundle");
const std::string stereotype_variability_initializer(
    "masd::variability::initializer");
const std::string stereotype_mapping_fixed_mappable(
    "masd::mapping::fixed_mappable");
const std::string stereotype_mapping_extensible_mappable(
    "masd::mapping::extensible_mappable");
const std::string stereotype_templating_logic_less_templates(
    "masd::templating::logic_less_templates");
const std::string stereotype_serialization_type_registrar(
    "masd::serialization::type_registrar");
const std::string stereotype_visual_studio_solution(
    "masd::visual_studio::solution");
const std::string stereotype_visual_studio_project(
    "masd::visual_studio::project");
const std::string stereotype_visual_studio_msbuild_targets(
    "masd::visual_studio::msbuild_targets");
const std::string stereotype_orm_common_odb_options(
    "masd::orm::common_odb_options");
const std::string stereotype_build_cmakelists("masd::build::cmakelists");
const std::string stereotype_physical_backend("masd::physical::backend");
const std::string stereotype_physical_facet("masd::physical::facet");
const std::string stereotype_physical_archetype("masd::physical::archetype");
const std::string stereotype_physical_archetype_kind(
    "masd::physical::archetype_kind");
const std::string stereotype_physical_part("masd::physical::part");


const std::string unsupported_stereotype("Invalid or unsupported stereotype: ");

}

namespace dogen::orchestration::helpers {

using logical::entities::static_stereotypes;

static_stereotypes stereotypes_helper::from_string(const std::string& s) const {
    BOOST_LOG_SEV(lg, debug) << "Converting stereotype: " << s;

    if (s == stereotype_visitable)
        return static_stereotypes::visitable;
    else if (s == stereotype_fluent)
        return static_stereotypes::fluent;
    else if (s == stereotype_immutable)
        return static_stereotypes::immutable;
    else if (s == stereotype_structural_object)
        return static_stereotypes::structural_object;
    else if (s == stereotype_structural_object_template)
        return static_stereotypes::structural_object_template;
    else if (s == stereotype_structural_exception)
        return static_stereotypes::structural_exception;
    else if (s == stereotype_structural_primitive)
        return static_stereotypes::structural_primitive;
    else if (s == stereotype_structural_enumeration)
        return static_stereotypes::structural_enumeration;
    else if (s == stereotype_structural_module)
        return static_stereotypes::structural_module;
    else if (s == stereotype_structural_builtin)
        return static_stereotypes::structural_builtin;
    else if (s == stereotype_structural_entry_point)
        return static_stereotypes::structural_entry_point;
    else if (s == stereotype_structural_assistant)
        return static_stereotypes::structural_assistant;
    else if (s == stereotype_orm_object)
        return static_stereotypes::orm_object;
    else if (s == stereotype_orm_value)
        return static_stereotypes::orm_value;
    else if (s == stereotype_decoration_modeline_group)
        return static_stereotypes::decoration_modeline_group;
    else if (s == stereotype_decoration_modeline)
        return static_stereotypes::decoration_modeline;
    else if (s == stereotype_decoration_generation_marker)
        return static_stereotypes::decoration_generation_marker;
    else if (s == stereotype_decoration_licence)
        return static_stereotypes::decoration_licence;
    else if (s == stereotype_variability_profile)
        return static_stereotypes::variability_profile;
    else if (s == stereotype_variability_profile_template)
        return static_stereotypes::variability_profile_template;
    else if (s == stereotype_variability_feature_template_bundle)
        return static_stereotypes::variability_feature_template_bundle;
    else if (s == stereotype_variability_feature_bundle)
        return static_stereotypes::variability_feature_bundle;
    else if (s == stereotype_variability_initializer)
        return static_stereotypes::variability_initializer;
    else if (s == stereotype_mapping_fixed_mappable)
        return static_stereotypes::mapping_fixed_mappable;
    else if (s == stereotype_mapping_extensible_mappable)
        return static_stereotypes::mapping_extensible_mappable;
    else if (s == stereotype_templating_logic_less_templates)
        return static_stereotypes::templating_logic_less_template;
    else if (s == stereotype_serialization_type_registrar)
        return static_stereotypes::serialization_type_registrar;
    else if (s == stereotype_visual_studio_solution)
        return static_stereotypes::visual_studio_solution;
    else if (s == stereotype_visual_studio_project)
        return static_stereotypes::visual_studio_project;
    else if (s == stereotype_visual_studio_msbuild_targets)
        return static_stereotypes::visual_studio_msbuild_targets;
    else if (s == stereotype_orm_common_odb_options)
        return static_stereotypes::orm_common_odb_options;
    else if (s == stereotype_build_cmakelists)
        return static_stereotypes::build_cmakelists;
    else if (s == stereotype_physical_backend)
        return static_stereotypes::physical_backend;
    else if (s == stereotype_physical_facet)
        return static_stereotypes::physical_facet;
    else if (s == stereotype_physical_archetype)
        return static_stereotypes::physical_archetype;
    else if (s == stereotype_physical_archetype_kind)
        return static_stereotypes::physical_archetype_kind;
    else if (s == stereotype_physical_part)
        return static_stereotypes::physical_part;

    BOOST_LOG_SEV(lg, debug) << "Could not convert stereotype."
                             << " Assuming dynamic.";
    return static_stereotypes::invalid;
}

stereotypes_conversion_result
stereotypes_helper::from_csv_string(const std::string& s) const {
    if (s.empty()) {
        stereotypes_conversion_result r;
        return r;
    }

    using utility::string::splitter;
    const auto stereotypes(splitter::split_csv(s));
    return from_string(stereotypes);
}

stereotypes_conversion_result stereotypes_helper::
from_string(const std::list<std::string>& stereotypes) const {
    stereotypes_conversion_result r;
    if (stereotypes.empty())
        return r;

    for (const auto& stereotype : stereotypes) {
        const auto ss(from_string(stereotype));
        if (ss != static_stereotypes::invalid)
            r.static_stereotypes().push_back(ss);
        else
            r.dynamic_stereotypes().push_back(stereotype);
    }
    return r;
}

std::string stereotypes_helper::
to_string(const static_stereotypes ss) const {
    switch(ss) {
    case static_stereotypes::visitable: return stereotype_visitable;
    case static_stereotypes::fluent: return stereotype_fluent;
    case static_stereotypes::immutable: return stereotype_immutable;
    case static_stereotypes::structural_object:
        return stereotype_structural_object;
    case static_stereotypes::structural_object_template:
        return stereotype_structural_object;
    case static_stereotypes::structural_exception:
        return stereotype_structural_exception;
    case static_stereotypes::structural_primitive:
        return stereotype_structural_primitive;
    case static_stereotypes::structural_enumeration:
        return stereotype_structural_enumeration;
    case static_stereotypes::structural_module:
        return stereotype_structural_module;
    case static_stereotypes::structural_builtin:
        return stereotype_structural_builtin;
    case static_stereotypes::structural_entry_point:
        return stereotype_structural_entry_point;
    case static_stereotypes::structural_assistant:
        return stereotype_structural_assistant;
    case static_stereotypes::orm_object: return stereotype_orm_object;
    case static_stereotypes::orm_value: return stereotype_orm_value;
    case static_stereotypes::decoration_modeline_group:
        return stereotype_decoration_modeline_group;
    case static_stereotypes::decoration_modeline:
        return stereotype_decoration_modeline;
    case static_stereotypes::decoration_generation_marker:
        return stereotype_decoration_generation_marker;
    case static_stereotypes::decoration_licence:
        return stereotype_decoration_licence;
    case static_stereotypes::variability_profile:
        return stereotype_variability_profile;
    case static_stereotypes::variability_profile_template:
        return stereotype_variability_profile_template;
    case static_stereotypes::variability_feature_template_bundle:
        return stereotype_variability_feature_template_bundle;
    case static_stereotypes::variability_feature_bundle:
        return stereotype_variability_feature_bundle;
    case static_stereotypes::variability_initializer:
        return stereotype_variability_initializer;
    case static_stereotypes::mapping_fixed_mappable:
        return stereotype_mapping_fixed_mappable;
    case static_stereotypes::mapping_extensible_mappable:
        return stereotype_mapping_extensible_mappable;
    case static_stereotypes::templating_logic_less_template:
        return stereotype_templating_logic_less_templates;
    case static_stereotypes::serialization_type_registrar:
        return stereotype_serialization_type_registrar;
    case static_stereotypes::visual_studio_solution:
        return stereotype_visual_studio_solution;
    case static_stereotypes::visual_studio_project:
        return stereotype_visual_studio_project;
    case static_stereotypes::visual_studio_msbuild_targets:
        return stereotype_visual_studio_msbuild_targets;
    case static_stereotypes::orm_common_odb_options:
        return stereotype_orm_common_odb_options;
    case static_stereotypes::build_cmakelists:
        return stereotype_build_cmakelists;
    case static_stereotypes::physical_backend:
        return stereotype_physical_backend;
    case static_stereotypes::physical_facet:
        return stereotype_physical_facet;
    case static_stereotypes::physical_archetype:
        return stereotype_physical_archetype;
    case static_stereotypes::physical_archetype_kind:
        return stereotype_physical_archetype_kind;
    case static_stereotypes::physical_part:
        return stereotype_physical_part;

    default: {
        const std::string s(boost::lexical_cast<std::string>(ss));
        BOOST_LOG_SEV(lg, error) << unsupported_stereotype << s;
        using dogen::utility::exception::invalid_enum_value;
        BOOST_THROW_EXCEPTION(invalid_enum_value(unsupported_stereotype + s));
    } }
}

bool stereotypes_helper::
is_element_type(const static_stereotypes ss) const {
    return
        ss == static_stereotypes::structural_object ||
        ss == static_stereotypes::structural_object_template ||
        ss == static_stereotypes::structural_exception ||
        ss == static_stereotypes::structural_primitive ||
        ss == static_stereotypes::structural_enumeration ||
        ss == static_stereotypes::structural_module ||
        ss == static_stereotypes::structural_builtin ||
        ss == static_stereotypes::structural_entry_point ||
        ss == static_stereotypes::structural_assistant ||
        ss == static_stereotypes::decoration_modeline_group ||
        ss == static_stereotypes::decoration_modeline ||
        ss == static_stereotypes::decoration_generation_marker ||
        ss == static_stereotypes::decoration_licence ||
        ss == static_stereotypes::variability_profile ||
        ss == static_stereotypes::variability_profile_template ||
        ss == static_stereotypes::variability_feature_template_bundle ||
        ss == static_stereotypes::variability_feature_bundle ||
        ss == static_stereotypes::variability_initializer ||
        ss == static_stereotypes::mapping_fixed_mappable ||
        ss == static_stereotypes::mapping_extensible_mappable ||
        ss == static_stereotypes::templating_logic_less_template ||
        ss == static_stereotypes::serialization_type_registrar ||
        ss == static_stereotypes::visual_studio_solution ||
        ss == static_stereotypes::visual_studio_project ||
        ss == static_stereotypes::visual_studio_msbuild_targets ||
        ss == static_stereotypes::orm_common_odb_options ||
        ss == static_stereotypes::build_cmakelists ||
        ss == static_stereotypes::physical_backend ||
        ss == static_stereotypes::physical_facet ||
        ss == static_stereotypes::physical_archetype ||
        ss == static_stereotypes::physical_archetype_kind ||
        ss == static_stereotypes::physical_part;
}

std::list<static_stereotypes> stereotypes_helper::
extract_element_types(const std::list<static_stereotypes>& ss) const {

    std::list<static_stereotypes> r;
    for (const auto st : ss)
        if (is_element_type(st))
            r.push_back(st);

    return r;
}

std::list<static_stereotypes> stereotypes_helper::
extract_non_element_types(const std::list<static_stereotypes>& ss) const {
    std::list<static_stereotypes> r;
    for (const auto st : ss)
        if (!is_element_type(st))
            r.push_back(st);

    return r;
}

}
