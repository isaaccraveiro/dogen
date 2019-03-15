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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FABRIC_META_NAME_FACTORY_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FABRIC_META_NAME_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "masd.dogen.coding/types/meta_model/name.hpp"

namespace masd::dogen::generation::cpp::fabric {

class meta_name_factory final {
private:
    static coding::meta_model::location make_location();

private:
    static coding::meta_model::name make_name(const std::string& sn);

public:
    static coding::meta_model::name make_cmakelists_name();
    static coding::meta_model::name make_master_header_name();
    static coding::meta_model::name make_msbuild_targets_name();
    static coding::meta_model::name make_visual_studio_project_name();
    static coding::meta_model::name make_visual_studio_solution_name();
    static coding::meta_model::name make_common_odb_options_name();
    static coding::meta_model::name make_object_odb_options_name();
    static coding::meta_model::name make_registrar_name();
    static coding::meta_model::name make_forward_declarations_name();
    static coding::meta_model::name make_entry_point_name();
};

}

#endif
