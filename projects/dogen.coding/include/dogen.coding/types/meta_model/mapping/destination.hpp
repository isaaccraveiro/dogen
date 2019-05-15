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
#ifndef DOGEN_CODING_TYPES_META_MODEL_MAPPING_DESTINATION_HPP
#define DOGEN_CODING_TYPES_META_MODEL_MAPPING_DESTINATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.coding/types/meta_model/name.hpp"
#include "dogen.coding/types/meta_model/mapping/action.hpp"
#include "dogen.coding/types/meta_model/technical_space.hpp"

namespace dogen::coding::meta_model::mapping {

class destination final {
public:
    destination(const destination&) = default;
    destination(destination&&) = default;
    ~destination() = default;

public:
    destination();

public:
    destination(
        const dogen::coding::meta_model::name& name,
        const dogen::coding::meta_model::mapping::action action,
        const dogen::coding::meta_model::technical_space technical_space);

public:
    const dogen::coding::meta_model::name& name() const;
    dogen::coding::meta_model::name& name();
    void name(const dogen::coding::meta_model::name& v);
    void name(const dogen::coding::meta_model::name&& v);

    dogen::coding::meta_model::mapping::action action() const;
    void action(const dogen::coding::meta_model::mapping::action v);

    dogen::coding::meta_model::technical_space technical_space() const;
    void technical_space(const dogen::coding::meta_model::technical_space v);

public:
    bool operator==(const destination& rhs) const;
    bool operator!=(const destination& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(destination& other) noexcept;
    destination& operator=(destination other);

private:
    dogen::coding::meta_model::name name_;
    dogen::coding::meta_model::mapping::action action_;
    dogen::coding::meta_model::technical_space technical_space_;
};

}

namespace std {

template<>
inline void swap(
    dogen::coding::meta_model::mapping::destination& lhs,
    dogen::coding::meta_model::mapping::destination& rhs) {
    lhs.swap(rhs);
}

}

#endif
