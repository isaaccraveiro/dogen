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
#ifndef MASD_DOGEN_FORMATTNG_TYPES_CPP_NAMESPACE_FORMATTER_HPP
#define MASD_DOGEN_FORMATTNG_TYPES_CPP_NAMESPACE_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>

namespace masd::dogen::formatting::cpp {

/**
 * @brief Formats C++ namespaces.
 */
class namespace_formatter {
public:
    /**
     * @brief Creates a namespace formatter.
     *
     * @param create_anonymous_namespace if true, and the supplied
     * parameters are empty, creates an anoynymous namespace. Else,
     * ignores the namespace.
     *
     * FIXME: we should really handle anonymous namespaces separately,
     * rather than via create_anonymous_namespace - e.g.
     * format_begin_anonymous(std::ostream& s);
     *
     * @param add_new_line If true, adds a new line at the end.
     *
     * @param nested_namespace If true, nests namespaces using C++ 17
     * syntax. If false, creates multiple lines per namespace.
     */
    explicit namespace_formatter(const bool create_anonymous_namespace = true,
        const bool add_new_line = false,  const bool nested_namespace = false);

public:
    /**
     * @brief Formats the opening of a single namespace.
     */
    void format_begin(std::ostream& s, const std::string& ns) const;

    /**
     * @brief Formats the closing of a single namespace.
     */
    void format_end(std::ostream& s, const std::string& ns) const;

public:
    /**
     * @brief Formats the opening of the namespaces.
     */
    void format_begin(std::ostream& s, const std::list<std::string>& ns) const;

    /**
     * @brief Formats the closing of the namespaces.
     */
    void format_end(std::ostream& s, const std::list<std::string>& ns) const;

private:
    const bool create_anonymous_namespace_;
    const bool add_new_line_;
    const bool nested_namespace_;
};

}

#endif