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
#include <string>
#include <ostream>
#include <stdexcept>
#include "masd.dogen.extraction/io/meta_model/operation_reason_io.hpp"

namespace masd::dogen::extraction::meta_model {

std::ostream& operator<<(std::ostream& s, const operation_reason& v) {
    s << "{ " << "\"__type__\": " << "\"operation_reason\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case operation_reason::invalid:
        attr = "\"invalid\"";
        break;
    case operation_reason::newly_generated:
        attr = "\"newly_generated\"";
        break;
    case operation_reason::changed_generated:
        attr = "\"changed_generated\"";
        break;
    case operation_reason::unchanged_generated:
        attr = "\"unchanged_generated\"";
        break;
    case operation_reason::already_exists:
        attr = "\"already_exists\"";
        break;
    case operation_reason::ignore_generated:
        attr = "\"ignore_generated\"";
        break;
    case operation_reason::force_write:
        attr = "\"force_write\"";
        break;
    case operation_reason::lint:
        attr = "\"lint\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for operation_reason");
    }
    s << attr << " }";
    return s;
}

}
