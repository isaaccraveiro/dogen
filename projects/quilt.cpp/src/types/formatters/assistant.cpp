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
#include <sstream>
#include <boost/pointer_cast.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/formatters/types/comment_formatter.hpp"
#include "dogen/formatters/types/decoration_formatter.hpp"
#include "dogen/formatters/types/utility_formatter.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/io/letter_cases_io.hpp"
#include "dogen/yarn/types/name_flattener.hpp"
#include "dogen/quilt.cpp/io/formattables/streaming_properties_io.hpp"
#include "dogen/quilt.cpp/io/formattables/helper_properties_io.hpp"
#include "dogen/quilt.cpp/types/formattables/canonical_archetype_resolver.hpp"
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formatters.assistant"));

const std::string empty;
const std::string by_ref_text("&");
const std::string void_keyword_text("void");
const std::string final_keyword_text("final ");
const std::string override_keyword_text(" override");
const std::string noexcept_keyword_text(" noexcept");
const std::string namespace_separator("::");
const std::string member_variable_postfix("_");
const std::string underscore("_");
const std::string odb_value_type("value");
const std::string odb_object_type("object");

const bool start_on_first_line(true);
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool documenting_previous_identifier(true);

const std::string upper_case("upper");
const std::string lower_case("lower");

const std::string file_path_not_set(
    "File path for formatter is not set. Formatter: ");
const std::string header_guard_not_set(
    "Header guard for formatter is not set. Formatter: ");
const std::string artefact_properties_missing(
    "Could not find formatter configuration for formatter: ");
const std::string facet_properties_missing(
    "Could not find facet configuration for formatter: ");
const std::string facet_directory_missing(
    "Facet directory is missing for facet: ");
const std::string family_not_found("Family not found: ");
const std::string element_not_found("Element not found: ");
const std::string no_helpers_for_family("No helpers found for family: ");
const std::string qn_missing("Could not find qualified name for language.");
const std::string helpless_family("No registered helpers found for family: ");
const std::string invalid_case("Letter case is invalid or unsupported: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

template<typename IdentifiableAndQualified>
inline std::pair<std::string, std::string>
get_identifiable_and_qualified(const IdentifiableAndQualified& iaq) {
    const auto i(iaq.qualified().find(yarn::languages::cpp));
    if (i == iaq.qualified().end()) {
        BOOST_LOG_SEV(lg, error) << qn_missing << yarn::languages::cpp;
        BOOST_THROW_EXCEPTION(formatting_error(qn_missing));
    }

    return std::make_pair(iaq.identifiable(), i->second);
}

assistant::
assistant(const context& ctx, const annotations::archetype_location& al,
    const bool requires_header_guard, const std::string& id) :
    element_id_(id),
    context_(ctx),
    artefact_properties_(
        obtain_artefact_properties(element_id_, al.archetype())),
    archetype_location_(al), requires_header_guard_(requires_header_guard) {

    BOOST_LOG_SEV(lg, debug) << "Processing element: " << element_id_
                             << " for archetype: " << al.archetype();

    dogen::formatters::indent_filter::push(filtering_stream_, 4);
    filtering_stream_.push(stream_);

    validate();
}

void assistant::validate() const {
    const auto& fn(archetype_location_.archetype());
    const auto& fp(artefact_properties_);
    if (fp.file_path().empty()) {
        BOOST_LOG_SEV(lg, error) << file_path_not_set << fn;
        BOOST_THROW_EXCEPTION(formatting_error(file_path_not_set + fn));
    }

    if (!requires_header_guard_)
        return;

    if (fp.header_guard().empty()) {
        BOOST_LOG_SEV(lg, error) << header_guard_not_set << fn;
        BOOST_THROW_EXCEPTION(formatting_error(header_guard_not_set + fn));
    }
}

std::string assistant::make_final_keyword_text(const yarn::object& o) const {
    if (context_.model().cpp_standard() == formattables::cpp_standards::cpp_98)
        return empty;

    return o.is_final() ? final_keyword_text : empty;
}

std::string assistant::make_override_keyword_text() const {
    if (context_.model().cpp_standard() == formattables::cpp_standards::cpp_98)
        return empty;

    return override_keyword_text;
}

std::string assistant::make_noexcept_keyword_text() const {
    if (context_.model().cpp_standard() == formattables::cpp_standards::cpp_98)
        return empty;

    return noexcept_keyword_text;
}

std::string assistant::make_by_ref_text(const yarn::attribute& attr) {
    return attr.parsed_type().is_current_simple_type() ? empty : by_ref_text;
}

std::string assistant::make_setter_return_type(
    const std::string& containing_type_name, const yarn::attribute& attr) {

    std::ostringstream s;
    if (attr.is_fluent())
        s << containing_type_name << by_ref_text;
    else
        s << void_keyword_text;

    return s.str();
}

std::string assistant::get_qualified_name(const yarn::name& n) const {
    const auto pair(get_identifiable_and_qualified(n));
    return pair.second;
}

std::string assistant::get_qualified_name(const yarn::name_tree& nt) const {
    const auto pair(get_identifiable_and_qualified(nt));
    return pair.second;
}

std::string assistant::get_identifiable_model_name(const yarn::name& n) const {
    using boost::algorithm::join;
    return join(n.location().model_modules(), underscore);
}

std::string assistant::get_product_name(const yarn::name& n) const {
    if (n.location().external_modules().empty())
        return empty;

    return n.location().external_modules().front();
}

const formattables::element_properties& assistant::obtain_element_properties(
    const std::string& element_id) const {

    if (element_id == element_id_)
        return context_.element_properties();

    const auto& formattables(context_.model().formattables());
    const auto i(formattables.find(element_id));
    if (i == formattables.end()) {
        BOOST_LOG_SEV(lg, error) << element_not_found << element_id;
        BOOST_THROW_EXCEPTION(formatting_error(element_not_found + element_id));
    }
    return i->second.element_properties();
}

const formattables::artefact_properties& assistant::obtain_artefact_properties(
    const std::string& element_id, const std::string& archetype) const {

    const auto& formattables(context_.model().formattables());
    formattables::canonical_archetype_resolver res(formattables);
    const auto resolved_arch(res.resolve(element_id, archetype));

    const auto& eprops(obtain_element_properties(element_id));
    const auto i(eprops.artefact_properties().find(resolved_arch));
    if (i == eprops.artefact_properties().end()) {
        BOOST_LOG_SEV(lg, error) << artefact_properties_missing
                                 << resolved_arch;
        BOOST_THROW_EXCEPTION(
            formatting_error(artefact_properties_missing + resolved_arch));
    }
    return i->second;
}

formattables::facet_properties assistant::
obtain_facet_properties(const std::string& facet_name) const {
    const auto& fct_props(context_.model().facet_properties());
    const auto i(fct_props.find(facet_name));
    if (i == fct_props.end()) {
        BOOST_LOG_SEV(lg, error) << facet_properties_missing
                                 << facet_name;
        BOOST_THROW_EXCEPTION(formatting_error(facet_properties_missing +
                facet_name));
    }
    return i->second;
}

std::string assistant::
make_member_variable_name(const yarn::attribute& attr) const {
    return attr.name().simple() + member_variable_postfix;
}

std::string assistant::
make_getter_setter_name(const yarn::attribute& attr) const {
    return attr.name().simple();
}

std::list<std::string> assistant::make_namespaces(const yarn::name& n) const {
    yarn::name_flattener nf;
    return nf.flatten(n);
}

bool assistant::is_archetype_enabled(const std::string& archetype) const {
    const auto& art_props(obtain_artefact_properties(element_id_, archetype));
    return art_props.enabled();
}

bool assistant::is_facet_enabled(const std::string& facet) const {
    const auto& fct_props(obtain_facet_properties(facet));
    return fct_props.enabled();
}

std::string assistant::
get_facet_directory_for_facet(const std::string& facet_name) const {
    const auto& fct_props(obtain_facet_properties(facet_name));
    if (fct_props.directory().empty()) {
        BOOST_LOG_SEV(lg, error) << facet_directory_missing << facet_name;
        BOOST_THROW_EXCEPTION(
            formatting_error(facet_directory_missing + facet_name));
    }
    return fct_props.directory();
}

std::string assistant::get_odb_facet_directory() const {
    using formatters::odb::traits;
    return get_facet_directory_for_facet(traits::facet());
}

bool assistant::requires_manual_default_constructor() const {
    const auto& ap(context_.element_properties().aspect_properties());
    return ap.requires_manual_default_constructor();
}

bool assistant::requires_manual_move_constructor() const {
    const auto& ap(context_.element_properties().aspect_properties());
    return ap.requires_manual_move_constructor();
}

bool assistant::requires_stream_manipulators() const {
    const auto& ap(context_.element_properties().aspect_properties());
    return ap.requires_stream_manipulators();
}

bool assistant::is_serialization_enabled() const {
    using formatters::serialization::traits;
    return is_archetype_enabled(traits::canonical_archetype());
}

bool assistant::is_io_enabled() const {
    using formatters::io::traits;
    return is_archetype_enabled(traits::canonical_archetype());
}

bool assistant::is_odb_facet_enabled() const {
    using formatters::odb::traits;
    return is_facet_enabled(traits::facet());
}

dogen::formatters::cpp::scoped_boilerplate_formatter
assistant::make_scoped_boilerplate_formatter() {
    const auto& ep(context_.element_properties());
    const auto& dp(ep.decoration_properties());

    const auto& art_props(artefact_properties_);
    const auto& deps(art_props.inclusion_dependencies());
    const auto& hg(art_props.header_guard());

    using dogen::formatters::cpp::scoped_boilerplate_formatter;
    return scoped_boilerplate_formatter(stream(), dp, deps, hg);
}

dogen::formatters::cpp::scoped_namespace_formatter
assistant::make_scoped_namespace_formatter(const std::list<std::string>& ns) {
    return dogen::formatters::cpp::scoped_namespace_formatter(
        stream(), ns, false/*create_anonymous_namespace*/,
        true/*add_new_line*/);
}

void assistant::make_decoration_preamble() {
    const auto dc(context_.element_properties().decoration_properties());
    make_decoration_preamble(dc);
}

void assistant::make_decoration_preamble(
    const boost::optional<dogen::formatters::decoration_properties> dc) {
    if (!dc)
        return;

    // FIXME: we should not hard code the comment styles.
    dogen::formatters::decoration_formatter fmt;
    const auto comment_style(dogen::formatters::comment_styles::shell_style);
    fmt.format_preamble(stream(), comment_style, *dc);
}

void assistant::comment(const std::string& c) {
    if (c.empty())
        return;

    dogen::formatters::comment_formatter f(
        !start_on_first_line,
        use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::formatters::comment_styles::c_style,
        !last_line_is_blank);
    f.format(stream(), c);
}

void assistant::
comment_start_method_group(const std::string& documentation,
    const bool add_comment_blocks) {
    if (documentation.empty())
        return;

    {
        dogen::formatters::positive_indenter_scope pis(stream());
        dogen::formatters::comment_formatter f(
            !start_on_first_line,
            use_documentation_tool_markup,
            !documenting_previous_identifier,
            dogen::formatters::comment_styles::c_style,
            !last_line_is_blank);

        f.format(stream(), documentation);
        if (add_comment_blocks) {
            f.format_doxygen_start_block(stream(), documentation);
            stream() << std::endl;
        }
    }
}

void assistant::comment_end_method_group(const std::string& documentation,
    const bool add_comment_blocks) {
    if (documentation.empty())
        return;

    {
        dogen::formatters::positive_indenter_scope pis(stream());
        dogen::formatters::comment_formatter f(
            start_on_first_line,
            use_documentation_tool_markup,
            !documenting_previous_identifier,
            dogen::formatters::comment_styles::c_style,
            !last_line_is_blank);

        if (add_comment_blocks) {
            f.format_doxygen_end_block(stream(), documentation);
            stream() << std::endl;
        }
    }
}

std::string assistant::comment_inline(const std::string& c) const {
    if (c.empty())
        return empty;

    std::ostringstream s;
    s << " ";
    dogen::formatters::comment_formatter f(
        start_on_first_line,
        use_documentation_tool_markup,
        documenting_previous_identifier,
        dogen::formatters::comment_styles::cpp_style,
        !last_line_is_blank);

    f.format(s, c);
    return s.str();
}

std::list<std::shared_ptr<formatters::helper_formatter_interface>>
assistant::get_helpers(const formattables::helper_properties& hp) const {
    /*
     * A family must have at least one helper registered. This is a
     * good way to detect spurious families in data files.
     */
    const auto fam(hp.current().family());
    const auto i(context_.helpers().find(fam));
    if (i == context_.helpers().end()) {
        BOOST_LOG_SEV(lg, error) << no_helpers_for_family << fam;
        BOOST_THROW_EXCEPTION(formatting_error(no_helpers_for_family + fam));
    }
    BOOST_LOG_SEV(lg, debug) << "Found helpers for family: " << fam;

    /*
     * Not all formatters need help, so its fine not to have a
     * helper registered against a particular formatter.
     */
    const auto j(i->second.find(archetype_location_.archetype()));
    if (j != i->second.end()) {
        BOOST_LOG_SEV(lg, debug) << "Found helpers for formatter: "
                                 << archetype_location_.archetype();
        return j->second;
    }

    BOOST_LOG_SEV(lg, debug) << "Could not find helpers for formatter:"
                             << archetype_location_.archetype();
    return std::list<std::shared_ptr<formatters::helper_formatter_interface>>();
}

bool assistant::is_io() const {
    const auto fn(archetype_location_.facet());
    return formatters::io::traits::facet()  == fn;
}

bool assistant::
is_streaming_enabled(const formattables::helper_properties& hp) const {
    /*
     * If the IO facet is globally disabled, we don't need streaming.
     */
    if (!is_io_enabled())
        return false;

    /*
     * If we are in the IO facet, and we are not in an inheritance
     * relationship we need streaming.
     */
    if (is_io() && !hp.in_inheritance_relationship())
        return true;

    /*
     * If we are in the types class implementation and we are in an
     * inheritance relationship, we'll need streaming.
     */
    using tt = formatters::types::traits;
    const auto cifn(tt::class_implementation_archetype());
    const auto arch(archetype_location_.archetype());
    bool in_types_class_implementation(arch == cifn);
    return in_types_class_implementation && hp.in_inheritance_relationship();
}

void assistant::add_helper_methods(const std::string& element_id) {
    BOOST_LOG_SEV(lg, debug) << "Generating helper methods. Element: "
                             << element_id;

    if (context_.element_properties().helper_properties().empty())
        BOOST_LOG_SEV(lg, debug) << "No helper methods found.";

    const auto& eprops(context_.element_properties());
    for (const auto& hlp_props : eprops.helper_properties()) {
        BOOST_LOG_SEV(lg, debug) << "Helper configuration: " << hlp_props;
        const auto helpers(get_helpers(hlp_props));

        /*
         * Check to see if the helper is enabled, given the system's
         * current configuration. If enabled, format it.
         */
        for (const auto& hlp : helpers) {
            const auto fmtn(hlp->formatter_name());
            if (!hlp->is_enabled(*this, hlp_props)) {
                BOOST_LOG_SEV(lg, debug) << "Helper is not enabled." << fmtn;
                continue;
            }

            BOOST_LOG_SEV(lg, debug) << "Formatting with helper: " << fmtn;
            hlp->format(*this, hlp_props);
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished generating helper methods.";
}

std::string assistant::
streaming_for_type(const formattables::streaming_properties& sp,
    const std::string& s) const {

    std::ostringstream stream;
    dogen::formatters::utility_formatter uf(stream);
    BOOST_LOG_SEV(lg, debug) << "Streaming properties for type: " << sp;
    if (sp.remove_unprintable_characters())
        uf.insert_streamed("tidy_up_string(" + s + ")");
    else if (!sp.string_conversion_method().empty()) {
        // FIXME: hack to determine if we are being dereferenced.
        std::string s1(s);
        const auto i(s1.find('*'));
        if (i != std::string::npos)
            s1 = "(" + s + ")";
        uf.insert_streamed(s1 + "." + sp.string_conversion_method());
    } else if (sp.requires_quoting())
        uf.insert_streamed(s);
    else
        uf.insert(s);

    return stream.str();
}

std::string assistant::
streaming_for_type(const yarn::name& n, const std::string& s) const {

    const auto str_propss(context_.model().streaming_properties());
    const auto i(str_propss.find(n.id()));
    if (i == str_propss.end())
        return s;

    return streaming_for_type(i->second, s);
}

std::string assistant::
streaming_for_type(const formattables::helper_descriptor& hd,
    const std::string& s) const {

    const auto sp(hd.streaming_properties());
    if (!sp)
        return s;

    return streaming_for_type(*sp, s);
}

bool assistant::
requires_hashing_helper_method(const yarn::attribute& attr) const {
    const auto& eprops(context_.element_properties());
    for (const auto& hlp_props : eprops.helper_properties()) {
        const auto ident(attr.parsed_type().identifiable());
        const auto& desc(hlp_props.current());
        if (ident != desc.name_tree_identifiable())
            continue;

        if (desc.requires_hashing_helper())
            return true;
    }
    return false;
}

std::list<std::string> assistant::get_odb_pragmas() const {
    const auto& eprops(context_.element_properties());
    const auto& odb_props(eprops.odb_properties());
    if (!odb_props)
        return std::list<std::string>();

    return odb_props->top_level_odb_pragmas();
}

std::list<std::string>
assistant::get_odb_pragmas(const std::string& attr_id) const {
    const auto& eprops(context_.element_properties());
    const auto& odb_props(eprops.odb_properties());
    if (!odb_props)
        return std::list<std::string>();

    const auto& attr_pragmas(odb_props->attribute_level_odb_pragmas());
    const auto i(attr_pragmas.find(attr_id));
    if (i == attr_pragmas.end())
        return std::list<std::string>();

    return i->second;
}

std::string assistant::get_odb_type() const {
    const auto& eprops(context_.element_properties());
    const auto& odb_props(eprops.odb_properties());
    if (!odb_props)
        return std::string();

    if (odb_props->is_value())
        return odb_value_type;
    return odb_object_type;
}

std::string assistant::get_letter_case(const yarn::letter_cases lc) const {
    if (lc == yarn::letter_cases::upper_case)
        return upper_case;
    else if (lc == yarn::letter_cases::lower_case)
        return lower_case;

    const auto s(boost::lexical_cast<std::string>(lc));
    BOOST_LOG_SEV(lg, error) << invalid_case << s;
    BOOST_THROW_EXCEPTION(formatting_error(invalid_case + s));
}

std::list<yarn::name> assistant::
names_with_enabled_archetype(const std::string& archetype,
    const std::list<yarn::name> names) const {
    std::list<yarn::name> r;
    for (const auto& n : names) {
        const auto id(n.id());
        BOOST_LOG_SEV(lg, debug) << "Checking enablement for name: " << id;
        const auto& art_props(obtain_artefact_properties(id, archetype));
        if (!art_props.enabled())
            continue;

        r.push_back(n);
    }
    return r;
}

const formattables::artefact_properties&
assistant::artefact_properties() const {
    return artefact_properties_;
}

std::ostream& assistant::stream() {
    return filtering_stream_;
}

dogen::formatters::artefact assistant::make_artefact() const {
    dogen::formatters::artefact r;
    r.content(stream_.str());
    r.path(artefact_properties_.file_path());
    r.overwrite(artefact_properties_.overwrite());

    return r;
}

} } } }
