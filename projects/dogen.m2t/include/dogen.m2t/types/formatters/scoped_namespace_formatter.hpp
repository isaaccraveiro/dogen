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
#ifndef DOGEN_M2T_TYPES_FORMATTERS_SCOPED_NAMESPACE_FORMATTER_HPP
#define DOGEN_M2T_TYPES_FORMATTERS_SCOPED_NAMESPACE_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include "dogen.logical/types/entities/technical_space.hpp"
#include "dogen.m2t/types/formatters/namespace_formatter.hpp"

namespace dogen::m2t::formatters {

/**
 * @brief RAII wrapper around the namespaces formatter.
 */
class scoped_namespace_formatter final {
public:
    scoped_namespace_formatter(
        std::ostream& s,
        const logical::entities::technical_space ts,
        const std::list<std::string>& ns,
        const bool add_new_line = false,
        const bool use_nesting = false);
    ~scoped_namespace_formatter();

private:
    namespace_formatter formatter_;
};

}

#endif
