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
#include "dogen.m2t.csharp/types/transforms/registrar.hpp"
#include "dogen.m2t.csharp/types/transforms/types/class_transform.hpp"
#include "dogen.m2t.csharp/types/transforms/types/primitive_transform.hpp"
#include "dogen.m2t.csharp/types/transforms/types/enum_transform.hpp"
#include "dogen.m2t.csharp/types/transforms/types/exception_transform.hpp"
#include "dogen.m2t.csharp/types/transforms/types/builtin_transform.hpp"
#include "dogen.m2t.csharp/types/transforms/types/floating_point_number_helper.hpp"
#include "dogen.m2t.csharp/types/transforms/types/initializer.hpp"

namespace dogen::m2t::csharp::transforms::types {

void initializer::initialize(registrar& rg) {
    register_formatter<class_transform>(rg);
    register_formatter<primitive_transform>(rg);
    register_formatter<enum_transform>(rg);
    register_formatter<exception_transform>(rg);
    register_formatter<builtin_transform>(rg);
    register_formatter_helper<floating_point_number_helper>(rg);
}

}
