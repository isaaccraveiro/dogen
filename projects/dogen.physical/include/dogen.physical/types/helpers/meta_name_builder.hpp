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
#ifndef DOGEN_PHYSICAL_TYPES_HELPERS_META_NAME_BUILDER_HPP
#define DOGEN_PHYSICAL_TYPES_HELPERS_META_NAME_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.physical/types/entities/meta_name.hpp"

namespace dogen::physical::helpers {

/**
 * @brief Builds a physical name.
 */
class meta_name_builder final {
public:
    /**
     * @brief Adds a backend to the name.
     */
    meta_name_builder& backend(const std::string& s);

    /**
     * @brief Adds a facet to the name.
     */
    meta_name_builder& facet(const std::string& s);

    /**
     * @brief Adds an archetype to the name.
     */
    meta_name_builder& archetype(const std::string& s);

public:
    entities::meta_name build();

private:
    entities::meta_name meta_name_;
};

}

#endif
