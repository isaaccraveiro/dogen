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
#ifndef DOGEN_M2T_CSHARP_TYPES_TRANSFORMS_CONTEXT_HPP
#define DOGEN_M2T_CSHARP_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen.m2t.csharp/types/formattables/model.hpp"
#include "dogen.m2t.csharp/types/formattables/element_properties.hpp"
#include "dogen.m2t.csharp/types/transforms/helper_transform.hpp"

namespace dogen::m2t::csharp::transforms {

class context final {
public:
    context(const formattables::element_properties& element_properties,
        const formattables::model& fm, const std::unordered_map<std::string,
        std::unordered_map<std::string, std::list<std::shared_ptr<
        helper_transform>>>>& helpers);

public:
    const formattables::element_properties& element_properties() const;
    const formattables::model& model() const;
    const std::unordered_map<
        std::string,
        std::unordered_map<
            std::string,
            std::list<std::shared_ptr<helper_transform>>>>&
        helpers() const;

private:
    const formattables::element_properties& element_properties_;
    const formattables::model& model_;
    const std::unordered_map<
        std::string,
        std::unordered_map<
            std::string, std::list<
                             std::shared_ptr<helper_transform>>>>&
        helpers_;
};

}

#endif
