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
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/serialization/class_implementation_transform.hpp"

namespace dogen::m2t::cpp::transforms::serialization {

std::string class_implementation_transform::static_id() {
    return traits::class_implementation_archetype_qn();
}

std::string class_implementation_transform::id() const {
    return static_id();
}

physical::entities::meta_name
class_implementation_transform::physical_meta_name() const {
    using physical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make(cpp::traits::backend_sn(),
        traits::facet_sn(), traits::class_implementation_archetype_sn()));
    return r;
}

const logical::entities::name& class_implementation_transform::logical_meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_object_name());
    return r;
}

inclusion_support_types class_implementation_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path class_implementation_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(class_implementation_transform::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path class_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
}

std::list<std::string> class_implementation_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    const auto& o(assistant::as<logical::entities::structural::object>(e));
    auto builder(f.make());

    const auto ch_fn(traits::class_header_archetype_qn());
    builder.add(o.name(), ch_fn);

    using ic = inclusion_constants;
    builder.add(ic::boost::archive::text_iarchive());
    builder.add(ic::boost::archive::text_oarchive());
    builder.add(ic::boost::archive::binary_iarchive());
    builder.add(ic::boost::archive::binary_oarchive());
    builder.add(ic::boost::archive::polymorphic_iarchive());
    builder.add(ic::boost::archive::polymorphic_oarchive());

    // XML serialisation
    builder.add(ic::boost::serialization::nvp());
    builder.add(ic::boost::archive::xml_iarchive());
    builder.add(ic::boost::archive::xml_oarchive());

    const auto carch(traits::canonical_archetype());
    builder.add(o.transparent_associations(), carch);
    builder.add(o.opaque_associations(), carch);
    builder.add(o.parents(), carch);
    builder.add(o.leaves(), carch);

    return builder.build();
}

void class_implementation_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, physical_meta_name(), false/*requires_header_guard*/, a);
    const auto& o(ast.as<logical::entities::structural::object>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        ast.add_helper_methods(o.name().qualified().dot());

        const auto qn(ast.get_qualified_name(o.name()));
        const bool has_attributes(!o.local_attributes().empty());
        const bool has_parent(!o.parents().empty());
        const bool has_attributes_or_parent(has_attributes || has_parent);

        if (o.is_parent() || !o.parents().empty()) {
ast.stream() << std::endl;
ast.stream() << "BOOST_CLASS_TRACKING(" << std::endl;
ast.stream() << "    " << qn << "," << std::endl;
ast.stream() << "    boost::serialization::track_selectively)" << std::endl;
        }
ast.stream() << std::endl;
ast.stream() << "namespace boost {" << std::endl;
ast.stream() << "namespace serialization {" << std::endl;

        /*
         * Save function
         */
ast.stream() << std::endl;
ast.stream() << "template<typename Archive>" << std::endl;
ast.stream() << "void save(Archive& " << (has_attributes_or_parent ? "ar" : "/*ar*/") << "," << std::endl;
ast.stream() << "    const " << qn << "& " << (has_attributes_or_parent ? "v" : "/*v*/") << "," << std::endl;
ast.stream() << "    const unsigned int /*version*/) {" << std::endl;
        if (!o.parents().empty()) {
            const auto& pn(o.parents().front());
            const auto pqn(ast.get_qualified_name(pn));
ast.stream() << "    ar << make_nvp(\"" << pn.simple() << "\", base_object<" << pqn << ">(v));" << std::endl;
        }

        if (has_attributes && has_parent)
ast.stream() << std::endl;
        for (const auto& attr : o.local_attributes()) {
ast.stream() << "    ar << make_nvp(\"" << attr.name().simple() << "\", v." << attr.member_variable_name() << ");" << std::endl;
        }
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        /*
         * Load function
         */
ast.stream() << "template<typename Archive>" << std::endl;
ast.stream() << "void load(Archive& " << (has_attributes_or_parent ? "ar," : "/*ar*/,") << std::endl;
ast.stream() << "    " << qn << "& " << (has_attributes_or_parent ? "v" : "/*v*/") << "," << std::endl;
ast.stream() << "    const unsigned int /*version*/) {" << std::endl;
        if (!o.parents().empty()) {
            const auto& pn(o.parents().front());
            const auto pqn(ast.get_qualified_name(pn));
ast.stream() << "    ar >> make_nvp(\"" << pn.simple() << "\", base_object<" << pqn << ">(v));" << std::endl;
            if (has_attributes && has_parent)
ast.stream() << std::endl;
        }

        for (const auto& attr : o.local_attributes()) {
ast.stream() << "    ar >> make_nvp(\"" << attr.name().simple() << "\", v." << attr.member_variable_name() << ");" << std::endl;
        }
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "} }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "namespace boost {" << std::endl;
ast.stream() << "namespace serialization {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template void save(archive::polymorphic_oarchive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << "template void load(archive::polymorphic_iarchive& ar, " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template void save(archive::text_oarchive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << "template void load(archive::text_iarchive& ar, " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template void save(archive::binary_oarchive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << "template void load(archive::binary_iarchive& ar, " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template void save(archive::xml_oarchive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << "template void load(archive::xml_iarchive& ar, " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "} }" << std::endl;
    } // sbf
    ast.update_artefact();
}

}
