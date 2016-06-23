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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_IO_ASSOCIATIVE_CONTAINER_HELPER_STITCH_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_IO_ASSOCIATIVE_CONTAINER_HELPER_STITCH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/quilt.cpp/types/formatters/formatter_helper_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/nested_type_formatting_assistant.hpp"
#include "dogen/quilt.cpp/types/properties/nested_type_info.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace io {

class associative_container_helper : public formatter_helper_interface {
public:
    std::string family() const;
    std::list<std::string> owning_formatters() const;
    bool requires_explicit_call() const;
    std::string function_name() const;
    bool is_enabled(const assistant& a, const bool in_inheritance) const;
    void format(assistant& a, const properties::helper_properties& hp) const;
};

void associative_container_helper_stitch(
    formatters::nested_type_formatting_assistant& fa,
    const properties::nested_type_info& t);

} } } } }

#endif
