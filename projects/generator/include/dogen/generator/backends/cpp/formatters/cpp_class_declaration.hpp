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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_CLASS_DECLARATION_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_CLASS_DECLARATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include "dogen/generator/backends/cpp/view_models/class_view_model.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_utility.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class cpp_class_declaration {
public:
    typedef view_models::class_view_model class_view_model;

public:
    cpp_class_declaration() = delete;
    cpp_class_declaration(const cpp_class_declaration&) = default;
    cpp_class_declaration(cpp_class_declaration&&) = default;
    cpp_class_declaration& operator=(const cpp_class_declaration&) = default;

public:
    explicit cpp_class_declaration(std::ostream& stream);
    virtual ~cpp_class_declaration() noexcept {}

protected:
    void open_class(class_view_model vm);
    void close_class();
    void compiler_generated_constuctors(class_view_model vm);
    void default_constructor(class_view_model vm);
    void complete_constructor(class_view_model vm);
    void friends(class_view_model vm);
    void getters_and_setters(class_view_model vm);
    void member_variables(class_view_model vm);
    void equality(class_view_model vm);
    void to_stream();
    void swap_and_assignment(class_view_model vm);

public:
    virtual void format(class_view_model vm) = 0;

protected:
    std::ostream& stream_;
    cpp_indenter indenter_;
    cpp_utility utility_;
};

} } } } }

#endif
