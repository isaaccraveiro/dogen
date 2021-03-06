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
#include "dogen.logical/io/entities/orm/database_system_io.hpp"

namespace dogen::logical::entities::orm {

std::ostream& operator<<(std::ostream& s, const database_system& v) {
    s << "{ " << "\"__type__\": " << "\"database_system\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case database_system::invalid:
        attr = "\"invalid\"";
        break;
    case database_system::mysql:
        attr = "\"mysql\"";
        break;
    case database_system::postgresql:
        attr = "\"postgresql\"";
        break;
    case database_system::oracle:
        attr = "\"oracle\"";
        break;
    case database_system::sql_server:
        attr = "\"sql_server\"";
        break;
    case database_system::sqlite:
        attr = "\"sqlite\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for database_system");
    }
    s << attr << " }";
    return s;
}

}
