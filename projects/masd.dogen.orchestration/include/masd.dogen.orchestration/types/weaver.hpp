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
#ifndef MASD_DOGEN_ORCHESTRATION_TYPES_WEAVER_HPP
#define MASD_DOGEN_ORCHESTRATION_TYPES_WEAVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen/types/weaver.hpp"

namespace masd::dogen::orchestration {

class weaver final : public masd::dogen::weaver {
public:
    weaver() = default;
    weaver(const weaver&) = delete;
    weaver(weaver&&) = delete;
    weaver& operator=(const weaver&) = delete;
    virtual ~weaver() noexcept { }

public:
    void weave(const configuration& cfg,
        const boost::filesystem::path& target,
        const boost::filesystem::path& tracing_output_directory) const;
};

}

#endif