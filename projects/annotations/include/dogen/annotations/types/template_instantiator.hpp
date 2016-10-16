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
#ifndef DOGEN_ANNOTATIONS_TYPES_TEMPLATE_INSTANTIATOR_HPP
#define DOGEN_ANNOTATIONS_TYPES_TEMPLATE_INSTANTIATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/type_template.hpp"
#include "dogen/annotations/types/entry_template.hpp"
#include "dogen/annotations/types/ownership_hierarchy_repository.hpp"
#include "dogen/annotations/types/type_repository.hpp"

namespace dogen {
namespace annotations {

class template_instantiator {
public:
    template_instantiator(const archetype_location_repository& ohrp);

private:
    void validate(const archetype_location& oh, const name& n,
        const template_kinds tk) const;

public:
    type to_type(const type_template& tt) const;
    boost::shared_ptr<value>
    to_value(const type_repository& trp, const std::string& qn,
        const entry_template& et) const;

private:
    std::list<type> instantiate_global_template(const type_template& tt) const;
    std::list<type> instantiate_facet_template(const type_template& tt) const;
    std::list<type>
    instantiate_formatter_template(const type_template& tt) const;

private:
    std::list<std::pair<std::string, boost::shared_ptr<value>>>
    instantiate_global_template(
        const type_repository& trp, const entry_template& et) const;

    std::list<std::pair<std::string, boost::shared_ptr<value>>>
    instantiate_facet_template(const type_repository& trp,
        const entry_template& et) const;

    std::list<std::pair<std::string, boost::shared_ptr<value>>>
    instantiate_formatter_template(const type_repository& trp,
        const entry_template& et) const;

public:
    bool is_instantiable(const template_kinds tk) const;

    std::list<type> instantiate(const type_template& tt) const;

    std::list<std::pair<std::string, boost::shared_ptr<value>>>
    instantiate(const type_repository& trp, const entry_template& et) const;

private:
    const archetype_location_repository& repository_;
};

} }

#endif
