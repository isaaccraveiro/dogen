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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_OPERATION_REASON_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_OPERATION_REASON_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen::physical::entities {

/**
 * @brief Reasons for performing an operation.
 */
enum class operation_reason : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    newly_generated = 1, ///< Artefact will produce a new generated file.
    changed_generated = 2, ///< Artefact will produce a changed generated file.
    unchanged_generated = 3, ///< Generated artefact contents match file contents.
    already_exists = 4, ///< The file already exists and we we're asked to create only.
    ignore_generated = 5, ///< User requested artefact to be ignored.
    force_write = 6, ///< User requested to always write generated artefacts.
    unexpected = 7, ///< Artefact represents an unexpected file in project.
    ignore_unexpected = 8, ///< File is unexpected but the user asked us not to delete it.
    ignore_regex = 9 ///< File is unexpected but the user asked us to ignore it via regexes.
};

}

#endif
