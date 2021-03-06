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
#ifndef DOGEN_VARIABILITY_TYPES_ENTITIES_CONFIGURATION_POINT_HPP
#define DOGEN_VARIABILITY_TYPES_ENTITIES_CONFIGURATION_POINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.variability/types/entities/element.hpp"
#include "dogen.variability/types/entities/value_fwd.hpp"

namespace dogen::variability::entities {

/**
 * @brief Maps a feature name to an instance value
 */
class configuration_point final : public dogen::variability::entities::element {
public:
    configuration_point() = default;
    configuration_point(const configuration_point&) = default;
    configuration_point(configuration_point&&) = default;

    virtual ~configuration_point() noexcept { }

public:
    configuration_point(
        const dogen::variability::entities::name& name,
        const std::string& description,
        const boost::shared_ptr<dogen::variability::entities::value>& value);

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Value that has been assigned to this element.
     */
    /**@{*/
    const boost::shared_ptr<dogen::variability::entities::value>& value() const;
    boost::shared_ptr<dogen::variability::entities::value>& value();
    void value(const boost::shared_ptr<dogen::variability::entities::value>& v);
    void value(const boost::shared_ptr<dogen::variability::entities::value>&& v);
    /**@}*/

public:
    bool operator==(const configuration_point& rhs) const;
    bool operator!=(const configuration_point& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::variability::entities::element& other) const override;

public:
    void swap(configuration_point& other) noexcept;
    configuration_point& operator=(configuration_point other);

private:
    boost::shared_ptr<dogen::variability::entities::value> value_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::entities::configuration_point& lhs,
    dogen::variability::entities::configuration_point& rhs) {
    lhs.swap(rhs);
}

}

#endif
