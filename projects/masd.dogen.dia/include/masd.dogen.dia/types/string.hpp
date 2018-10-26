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
#ifndef MASD_DOGEN_DIA_TYPES_STRING_HPP
#define MASD_DOGEN_DIA_TYPES_STRING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "masd.dogen.dia/serialization/string_fwd_ser.hpp"

namespace masd::dogen::dia {

/**
 * @brief Represents a string value.
 */
class string final {
public:
    string() = default;
    string(const string&) = default;
    string(string&&) = default;
    ~string() = default;

public:
    explicit string(const std::string& value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const masd::dogen::dia::string& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, masd::dogen::dia::string& v, unsigned int version);

public:
    /**
     * @brief Text representation of a string value.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

public:
    bool operator==(const string& rhs) const;
    bool operator!=(const string& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(string& other) noexcept;
    string& operator=(string other);

private:
    std::string value_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::dia::string& lhs,
    masd::dogen::dia::string& rhs) {
    lhs.swap(rhs);
}

}

#endif