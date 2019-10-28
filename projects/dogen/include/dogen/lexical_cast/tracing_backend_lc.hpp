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
#ifndef DOGEN_LEXICAL_CAST_TRACING_BACKEND_LC_HPP
#define DOGEN_LEXICAL_CAST_TRACING_BACKEND_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen/types/tracing_backend.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::tracing_backend& v) {
    using dogen::tracing_backend;

    switch (v) {
    case tracing_backend::invalid:
        return "tracing_backend::invalid";
    case tracing_backend::file:
        return "tracing_backend::file";
    case tracing_backend::relational_database:
        return "tracing_backend::relational_database";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::tracing_backend lexical_cast(const std::string & s) {
    using dogen::tracing_backend;

    if (s == "invalid" || s == "tracing_backend::invalid")
        return tracing_backend::invalid;
    if (s == "file" || s == "tracing_backend::file")
        return tracing_backend::file;
    if (s == "relational_database" || s == "tracing_backend::relational_database")
        return tracing_backend::relational_database;
    throw boost::bad_lexical_cast();
}

}

#endif
