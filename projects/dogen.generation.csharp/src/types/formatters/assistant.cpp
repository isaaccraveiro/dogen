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
#include <cctype>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.generation/types/formatters/indent_filter.hpp"
#include "dogen.generation/types/formatters/comment_formatter.hpp"
#include "dogen.generation/types/formatters/boilerplate_properties.hpp"
#include "dogen.assets/types/helpers/name_flattener.hpp"
#include "dogen.generation.csharp/io/formattables/helper_properties_io.hpp"
#include "dogen.generation.csharp/types/formatters/formatting_error.hpp"
#include "dogen.generation.csharp/types/formatters/assistant.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.csharp.formatters.assistant"));

const std::string empty;
const bool start_on_first_line(true);
const std::string sealed_keyword_text("sealed ");
const std::string abstract_keyword_text("abstract ");
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool documenting_previous_identifier(true);

const std::string default_family("Default");
const std::string static_reference_equals("object");
const std::string artefact_properties_missing(
    "Could not find formatter configuration for formatter: ");
const std::string no_helpers_for_family("No helpers found for family: ");
const std::string helpless_family("No registered helpers found for family: ");
const std::string attribute_with_no_simple_name(
    "Attribute has empty simple name.");

}

namespace dogen::generation::csharp::formatters {

assistant::
assistant(const context& ctx, const assets::meta_model::element& e,
    const physical::location& al) :
    element_id_(e.name().qualified().dot()), element_(e), context_(ctx),
    artefact_properties_(obtain_artefact_properties(al.archetype())),
    archetype_location_(al) {

    BOOST_LOG_SEV(lg, debug) << "Processing element: " << element_id_
                             << " for archetype: " << al.archetype();

    generation::formatters::indent_filter::push(filtering_stream_, 4);
    filtering_stream_.push(stream_);
}

std::string
assistant::get_qualified_name(const assets::meta_model::name& n) const {
    return n.qualified().dot();
}

std::string
assistant::get_qualified_name(const assets::meta_model::name_tree& nt) const {
    return nt.qualified().dot();
}

std::string
assistant::make_inheritance_keyword_text(const assets::meta_model::structural::object& o) {
    if (o.is_parent())
        return abstract_keyword_text;

    return o.is_final() ? sealed_keyword_text : empty;
}

const formattables::artefact_properties& assistant::
obtain_artefact_properties(const std::string& archetype) const {
    const auto& eprops(context_.element_properties());
    const auto i(eprops.artefact_properties().find(archetype));
    if (i == eprops.artefact_properties().end()) {
        BOOST_LOG_SEV(lg, error) << artefact_properties_missing
                                 << archetype;
        BOOST_THROW_EXCEPTION(
            formatting_error(artefact_properties_missing + archetype));
    }
    return i->second;
}

generation::formatters::scoped_boilerplate_formatter assistant::
make_scoped_boilerplate_formatter(const assets::meta_model::element& e,
    const assets::meta_model::technical_space ts) {
    generation::formatters::boilerplate_properties bp;

    const auto& art_props(artefact_properties_);
    bp.dependencies(art_props.using_dependencies());
    bp.technical_space(ts);
    const auto i(e.decoration().find(ts));
    if (i != e.decoration().end() && i->second) {
        const auto dec(*i->second);
        bp.preamble(dec.preamble());
        bp.postamble(dec.postamble());
    }
    bp.generate_preamble(true);

    using generation::formatters::scoped_boilerplate_formatter;
    return scoped_boilerplate_formatter(stream(), bp);

}

generation::formatters::scoped_namespace_formatter
assistant::make_scoped_namespace_formatter(const std::list<std::string>& ns) {
    return generation::formatters::scoped_namespace_formatter(
        stream(), assets::meta_model::technical_space::csharp, ns,
        true/*add_new_line*/);
}

std::list<std::string>
assistant::make_namespaces(const assets::meta_model::name& n) const {
    assets::helpers::name_flattener nf;
    return nf.flatten(n);
}

std::string
assistant::reference_equals(const assets::meta_model::attribute& attr) const {
    const auto& c(context_.model().aspect_properties());
    const auto n(attr.parsed_type().current());
    const auto i(c.find(n.qualified().dot()));

    bool requires_static_reference_equals(i == c.end() ?
        false : i->second.requires_static_reference_equals());

    if (requires_static_reference_equals)
        return static_reference_equals;

    return attr.name().simple();
}

void assistant::
comment(const std::string& c, const unsigned int identation_level) {
    if (c.empty())
        return;

    for (unsigned int i = 0; i < identation_level; ++i)
        stream() << generation::formatters::indent_in;

    generation::formatters::comment_formatter f(
        start_on_first_line,
        use_documentation_tool_markup,
        !documenting_previous_identifier,
        generation::formatters::comment_style::csharp_style,
        !last_line_is_blank);
    f.format(stream(), c);

    for (unsigned int i = 0; i < identation_level; ++i)
        stream() << generation::formatters::indent_out;
}

std::string assistant::comment_inline(const std::string& c) const {
    if (c.empty())
        return empty;

    std::ostringstream s;
    s << " ";
    generation::formatters::comment_formatter f(
        start_on_first_line,
        use_documentation_tool_markup,
        documenting_previous_identifier,
        generation::formatters::comment_style::csharp_style,
        !last_line_is_blank);

    f.format(s, c);
    return s.str();
}

std::string assistant::
make_argument_name(const assets::meta_model::attribute& attr) const {
    auto r(attr.name().simple());
    if (r.empty()) {
        BOOST_LOG_SEV(lg, error) << attribute_with_no_simple_name;
        BOOST_THROW_EXCEPTION(formatting_error(attribute_with_no_simple_name));
    }

    r[0] = static_cast<char>(std::tolower(r[0]));
    return r;
}

std::list<std::shared_ptr<formatters::helper_formatter_interface>>
assistant::get_helpers(const formattables::helper_properties& hp) const {
    const auto fam(hp.current().family());

    /*
     * Bit of a hack: we manually ignore the "Default" family. This is
     * a quick way to solve a mismatch between C# and C++: in C++ we
     * need a helper for all domain types, but not so in C#.
     */
    if (fam != default_family) {
        /*
         * A family must have at least one helper registered. This is a
         * good way to detect spurious families in data files.
         */
        const auto i(context_.helpers().find(fam));
        if (i == context_.helpers().end()) {
            BOOST_LOG_SEV(lg, error) << no_helpers_for_family << fam;
            BOOST_THROW_EXCEPTION(
                formatting_error(no_helpers_for_family + fam));
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
    }

    BOOST_LOG_SEV(lg, debug) << "Could not find helpers for formatter:"
                             << archetype_location_.archetype();
    return std::list<std::shared_ptr<formatters::helper_formatter_interface>>();
}

boost::optional<formattables::assistant_properties> assistant::
get_assistant_properties(const assets::meta_model::attribute& attr) const {

    const auto& ap(context_.model().assistant_properties());
    const auto i(ap.find(attr.parsed_type().current().qualified().dot()));
    if (i == ap.end())
        return boost::optional<formattables::assistant_properties>();

    return i->second;
}

void assistant::add_helper_methods(const std::string& element_id) {
    BOOST_LOG_SEV(lg, debug) << "Generating helper methods. Element: "
                             << element_id;

    if (context_.element_properties().helper_properties().empty())
        BOOST_LOG_SEV(lg, debug) << "No helper methods found.";

    bool has_helpers(false);
    const auto& eprops(context_.element_properties());
    for (const auto& hlp_props : eprops.helper_properties()) {
        BOOST_LOG_SEV(lg, debug) << "Helper configuration: " << hlp_props;
        const auto helpers(get_helpers(hlp_props));

        for (const auto& hlp : helpers) {
            if (!has_helpers) {
                has_helpers = true;
                stream() << "        #region Helpers" << std::endl;
            }

            BOOST_LOG_SEV(lg, debug) << "Formatting with helper: " << hlp->id();
            hlp->format(*this, hlp_props);
        }
    }

    if (has_helpers) {
        stream() << "        #endregion" << std::endl << std::endl;
        has_helpers = false;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished generating helper methods.";
}

std::ostream& assistant::stream() {
    return filtering_stream_;
}

extraction::meta_model::artefact assistant::make_artefact() const {
    extraction::meta_model::artefact r;
    r.content(stream_.str());
    r.path(artefact_properties_.file_path());

    const auto& ap(element_.artefact_properties());
    const auto arch(archetype_location_.archetype());
    const auto i(ap.find(arch));
    if (i == ap.end()) {
        BOOST_LOG_SEV(lg, error) << artefact_properties_missing << arch;
        BOOST_THROW_EXCEPTION(
            formatting_error(artefact_properties_missing + arch));
    }
    r.overwrite(i->second.overwrite());

    extraction::meta_model::operation op;
    using ot = extraction::meta_model::operation_type;
    op.type(r.overwrite() ? ot::write : ot::create_only);
    r.operation(op);

    return r;
}

}
