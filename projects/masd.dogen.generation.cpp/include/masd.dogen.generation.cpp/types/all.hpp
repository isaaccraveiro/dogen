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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_ALL_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.generation.cpp/types/cpp.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.generation.cpp/types/initializer.hpp"
#include "masd.dogen.generation.cpp/types/fabric/fabric.hpp"
#include "masd.dogen.generation.cpp/types/workflow_error.hpp"
#include "masd.dogen.generation.cpp/types/fabric/injector.hpp"
#include "masd.dogen.generation.cpp/types/fabric/registrar.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/io.hpp"
#include "masd.dogen.generation.cpp/types/fabric/cmakelists.hpp"
#include "masd.dogen.generation.cpp/types/fabric/odb_target.hpp"
#include "masd.dogen.generation.cpp/types/formatters/traits.hpp"
#include "masd.dogen.generation.cpp/types/fabric/entry_point.hpp"
#include "masd.dogen.generation.cpp/types/fabric/initializer.hpp"
#include "masd.dogen.generation.cpp/types/fabric/odb_targets.hpp"
#include "masd.dogen.generation.cpp/types/formattables/model.hpp"
#include "masd.dogen.generation.cpp/types/formatters/context.hpp"
#include "masd.dogen.generation.cpp/types/formatters/odb/odb.hpp"
#include "masd.dogen.generation.cpp/types/formatters/workflow.hpp"
#include "masd.dogen.generation.cpp/types/fabric/master_header.hpp"
#include "masd.dogen.generation.cpp/types/formattables/adapter.hpp"
#include "masd.dogen.generation.cpp/types/formattables/locator.hpp"
#include "masd.dogen.generation.cpp/types/formattables/reducer.hpp"
#include "masd.dogen.generation.cpp/types/formatters/assistant.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/hash.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/registrar.hpp"
#include "masd.dogen.generation.cpp/types/fabric/building_error.hpp"
#include "masd.dogen.generation.cpp/types/formattables/workflow.hpp"
#include "masd.dogen.generation.cpp/types/formatters/formatters.hpp"
#include "masd.dogen.generation.cpp/types/formatters/odb/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/repository.hpp"
#include "masd.dogen.generation.cpp/types/fabric/element_visitor.hpp"
#include "masd.dogen.generation.cpp/types/fabric/msbuild_targets.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/initializer.hpp"
#include "masd.dogen.generation.cpp/types/formatters/tests/tests.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/types.hpp"
#include "masd.dogen.generation.cpp/types/formatters/tests/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "masd.dogen.generation.cpp/types/fabric/dynamic_transform.hpp"
#include "masd.dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "masd.dogen.generation.cpp/types/fabric/registrar_factory.hpp"
#include "masd.dogen.generation.cpp/types/formattables/formattable.hpp"
#include "masd.dogen.generation.cpp/types/fabric/common_odb_options.hpp"
#include "masd.dogen.generation.cpp/types/fabric/object_odb_options.hpp"
#include "masd.dogen.generation.cpp/types/formattables/formattables.hpp"
#include "masd.dogen.generation.cpp/types/formattables/odb_expander.hpp"
#include "masd.dogen.generation.cpp/types/formatters/building_error.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/initializer.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/pair_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/wale_formatter.hpp"
#include "masd.dogen.generation.cpp/types/fabric/build_files_factory.hpp"
#include "masd.dogen.generation.cpp/types/fabric/decoration_expander.hpp"
#include "masd.dogen.generation.cpp/types/fabric/entry_point_factory.hpp"
#include "masd.dogen.generation.cpp/types/fabric/odb_options_factory.hpp"
#include "masd.dogen.generation.cpp/types/formattables/cpp_standards.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/ptree_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/odb/initializer.hpp"
#include "masd.dogen.generation.cpp/types/formatters/registrar_error.hpp"
#include "masd.dogen.generation.cpp/types/fabric/forward_declarations.hpp"
#include "masd.dogen.generation.cpp/types/formattables/building_error.hpp"
#include "masd.dogen.generation.cpp/types/formattables/location_error.hpp"
#include "masd.dogen.generation.cpp/types/formattables/model_expander.hpp"
#include "masd.dogen.generation.cpp/types/formattables/odb_properties.hpp"
#include "masd.dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/date_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/initializer.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/pair_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/path_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/string_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/rapidjson/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/stitch_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/traits.hpp"
#include "masd.dogen.generation.cpp/types/fabric/master_header_factory.hpp"
#include "masd.dogen.generation.cpp/types/fabric/visual_studio_factory.hpp"
#include "masd.dogen.generation.cpp/types/fabric/visual_studio_project.hpp"
#include "masd.dogen.generation.cpp/types/formattables/aspect_expander.hpp"
#include "masd.dogen.generation.cpp/types/formattables/directive_group.hpp"
#include "masd.dogen.generation.cpp/types/formattables/expansion_error.hpp"
#include "masd.dogen.generation.cpp/types/formattables/helper_expander.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/ptime_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/ptree_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/variant_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/tests/initializer.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/initializer.hpp"
#include "masd.dogen.generation.cpp/types/fabric/visual_studio_solution.hpp"
#include "masd.dogen.generation.cpp/types/formattables/adaptation_error.hpp"
#include "masd.dogen.generation.cpp/types/formattables/facet_properties.hpp"
#include "masd.dogen.generation.cpp/types/formattables/resolution_error.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/optional_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/repository_factory.hpp"
#include "masd.dogen.generation.cpp/types/formattables/aspect_properties.hpp"
#include "masd.dogen.generation.cpp/types/formattables/helper_descriptor.hpp"
#include "masd.dogen.generation.cpp/types/formattables/helper_properties.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/variant_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "masd.dogen.generation.cpp/types/formatters/rapidjson/rapidjson.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/test_data.hpp"
#include "masd.dogen.generation.cpp/types/formattables/element_properties.hpp"
#include "masd.dogen.generation.cpp/types/formattables/inclusion_expander.hpp"
#include "masd.dogen.generation.cpp/types/formattables/streaming_expander.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/optional_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/traits.hpp"
#include "masd.dogen.generation.cpp/types/formattables/artefact_properties.hpp"
#include "masd.dogen.generation.cpp/types/formatters/rapidjson/initializer.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/bool_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/char_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/date_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/initializer.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/pair_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/path_helper.hpp"
#include "masd.dogen.generation.cpp/types/formattables/build_files_expander.hpp"
#include "masd.dogen.generation.cpp/types/formattables/dependencies_builder.hpp"
#include "masd.dogen.generation.cpp/types/formattables/header_guard_factory.hpp"
#include "masd.dogen.generation.cpp/types/formattables/helper_configuration.hpp"
#include "masd.dogen.generation.cpp/types/formattables/streaming_properties.hpp"
#include "masd.dogen.generation.cpp/types/formattables/test_data_properties.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/ptime_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/ptree_helper.hpp"
#include "masd.dogen.generation.cpp/types/fabric/visual_studio_configuration.hpp"
#include "masd.dogen.generation.cpp/types/formattables/cpp_standard_expander.hpp"
#include "masd.dogen.generation.cpp/types/formattables/locator_configuration.hpp"
#include "masd.dogen.generation.cpp/types/formatters/inclusion_support_types.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/smart_pointer_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/master_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/number_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/string_helper.hpp"
#include "masd.dogen.generation.cpp/types/fabric/forward_declarations_factory.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/enum_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/variant_helper.hpp"
#include "masd.dogen.generation.cpp/types/model_to_extraction_model_transform.hpp"
#include "masd.dogen.generation.cpp/types/formattables/odb_file_path_generator.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/smart_pointer_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/time_duration_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/class_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/msbuild_targets_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/odb/enum_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/initializer.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/path_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/optional_helper.hpp"
#include "masd.dogen.generation.cpp/types/formattables/facet_directory_expander.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/enum_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/helper_formatter_interface.hpp"
#include "masd.dogen.generation.cpp/types/formatters/odb/class_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/smart_pointer_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/class_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/builtin_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/serialization.hpp"
#include "masd.dogen.generation.cpp/types/formatters/source_cmakelists_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/enum_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formattables/directive_group_repository.hpp"
#include "masd.dogen.generation.cpp/types/formatters/artefact_formatter_interface.hpp"
#include "masd.dogen.generation.cpp/types/formatters/include_cmakelists_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/sequence_container_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/odb/builtin_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/domain_type_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/class_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formattables/locator_facet_configuration.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/builtin_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/primitive_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formattables/canonical_archetype_expander.hpp"
#include "masd.dogen.generation.cpp/types/formattables/canonical_archetype_resolver.hpp"
#include "masd.dogen.generation.cpp/types/formattables/dependencies_builder_factory.hpp"
#include "masd.dogen.generation.cpp/types/formattables/file_path_and_guard_expander.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/sequence_container_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/odb/primitive_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/smart_pointer_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/time_duration_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/builtin_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/visitor_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formattables/test_data_properties_expander.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/primitive_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/associative_container_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/enum_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/visual_studio_project_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/enum_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/odb/common_odb_options_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/odb/object_odb_options_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/rapidjson/class_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/class_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/exception_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/namespace_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/primitive_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/visual_studio_solution_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formattables/locator_archetype_configuration.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/associative_container_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/class_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/inserter_implementation_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/builtin_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/class_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/enum_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/sequence_container_helper.hpp"
#include "masd.dogen.generation.cpp/types/formattables/directive_group_repository_factory.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/class_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/primitive_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/tests/class_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/class_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/forward_declarations_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/primitive_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/builtin_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/associative_container_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/primitive_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/enum_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/rapidjson/class_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/primitive_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/registrar_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/class_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/primitive_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/class_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/forward_declarations_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/primitive_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/primitive_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/registrar_implementation_formatter.hpp"

#endif
