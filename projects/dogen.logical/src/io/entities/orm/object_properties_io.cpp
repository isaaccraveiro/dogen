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
#include <ostream>
#include <boost/io/ios_state.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen.logical/io/entities/orm/letter_case_io.hpp"
#include "dogen.logical/io/entities/orm/odb_options_io.hpp"
#include "dogen.logical/io/entities/orm/type_mapping_io.hpp"
#include "dogen.logical/io/entities/orm/object_properties_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::logical::entities::orm::letter_case>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::logical::entities::orm::type_mapping>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen::logical::entities::orm {

std::ostream& operator<<(std::ostream& s, const object_properties& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::orm::object_properties\"" << ", "
      << "\"odb_options\": " << v.odb_options() << ", "
      << "\"schema_name\": " << "\"" << tidy_up_string(v.schema_name()) << "\"" << ", "
      << "\"capitalised_schema_name\": " << "\"" << tidy_up_string(v.capitalised_schema_name()) << "\"" << ", "
      << "\"letter_case\": " << v.letter_case() << ", "
      << "\"generate_mapping\": " << v.generate_mapping() << ", "
      << "\"type_mappings\": " << v.type_mappings() << ", "
      << "\"odb_pragmas\": " << v.odb_pragmas() << ", "
      << "\"table_name\": " << "\"" << tidy_up_string(v.table_name()) << "\"" << ", "
      << "\"is_value\": " << v.is_value() << ", "
      << "\"has_primary_key\": " << v.has_primary_key()
      << " }";
    return(s);
}

}
