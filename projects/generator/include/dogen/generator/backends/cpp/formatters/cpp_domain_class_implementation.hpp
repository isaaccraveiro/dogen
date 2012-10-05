/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_DOMAIN_CLASS_IMPLEMENTATION_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_DOMAIN_CLASS_IMPLEMENTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/generator/backends/cpp/formatters/cpp_class_implementation.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class cpp_domain_class_implementation : public cpp_class_implementation {
public:
    typedef view_models::class_view_model class_view_model;

public:
    cpp_domain_class_implementation() = delete;
    cpp_domain_class_implementation(
        const cpp_domain_class_implementation&) = default;
    cpp_domain_class_implementation(
        cpp_domain_class_implementation&&) = default;
    cpp_domain_class_implementation&
    operator=(const cpp_domain_class_implementation&) = default;

private:
    void hand_crafted_constructors(class_view_model vm);

public:
    cpp_domain_class_implementation(std::ostream& stream,
        bool disable_complete_constructor, bool disable_io);
    virtual ~cpp_domain_class_implementation() noexcept {}

public:
    virtual void format(class_view_model vm) override;

private:
    const bool disable_complete_constructor_;
    const bool disable_io_;
};

} } } } }

#endif
