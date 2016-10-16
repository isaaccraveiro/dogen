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
#ifndef DOGEN_YARN_TYPES_ANNOTATIONS_EXPANDER_HPP
#define DOGEN_YARN_TYPES_ANNOTATIONS_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/ownership_hierarchy_repository.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Reads raw meta-data and uses it to create the annotations
 * objects.
 */
class annotations_expander {
private:
    void update_scribble_groups(intermediate_model& im) const;
    void update_annotations(
        const std::vector<boost::filesystem::path>& data_dirs,
        const annotations::archetype_location_repository& ohrp,
        const annotations::type_repository& atrp, intermediate_model& im) const;

public:
    void expand(const std::vector<boost::filesystem::path>& data_dirs,
        const annotations::archetype_location_repository& ohrp,
        const annotations::type_repository& atrp, intermediate_model& im) const;
};

} }

#endif
