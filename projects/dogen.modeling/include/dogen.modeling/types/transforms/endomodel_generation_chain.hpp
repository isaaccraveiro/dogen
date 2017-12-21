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
#ifndef DOGEN_MODELING_TYPES_TRANSFORMS_ENDOMODEL_GENERATION_CHAIN_HPP
#define DOGEN_MODELING_TYPES_TRANSFORMS_ENDOMODEL_GENERATION_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include "dogen.annotations/types/type.hpp"
#include "dogen.annotations/types/type_repository.hpp"
#include "dogen.modeling/types/meta_model/endomodel.hpp"
#include "dogen.modeling/types/transforms/context_fwd.hpp"

namespace dogen {
namespace modeling {
namespace transforms {

/**
 * @brief The endomodel generation chain is a top-level transformation
 * responsible for obtaining a set of endomodels to which all the
 * internal transforms have been applied.
 */
class endomodel_generation_chain final {
public:
    static std::list<meta_model::endomodel> transform(const context& ctx);
};

} } }

#endif
