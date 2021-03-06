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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_OPERATION_TYPE_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_OPERATION_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen::physical::entities {

/**
 * @brief Operation to perform to a given artefact.
 */
enum class operation_type : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    create_only = 1, ///< Creates a file from an artefact only if it does not yet exist.
    write = 2, ///< Unconditionally writes an artefact into file.
    ignore = 3, ///< Ingores an artefact.
    remove = 4 ///< Deletes a file.
};

}

#endif
