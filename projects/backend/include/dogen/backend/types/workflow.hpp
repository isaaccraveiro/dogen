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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_BACKEND_TYPES_WORKFLOW_HPP
#define DOGEN_BACKEND_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include "dogen/sml/types/model.hpp"
#include "dogen/config/types/knitting_settings.hpp"
#include "dogen/formatters/types/file.hpp"
#include "dogen/backend/types/registrar.hpp"
#include "dogen/backend/types/backend_interface.hpp"

namespace dogen {
namespace backend {

/**
 * @brief Manages the entire backend workflow.
 */
class workflow {
public:
    explicit workflow(const config::knitting_settings& ts);

private:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static backend::registrar& registrar();

public:
    /**
     * @brief Registers a backend with the workflow.
     */
    static void register_backend(std::shared_ptr<backend_interface> b);

    /**
     * @brief Generates files for the supplied model using all
     * registered backends.
     */
    std::list<formatters::file> execute(const sml::model& m) const;

private:
    static std::shared_ptr<backend::registrar> registrar_;
    const config::knitting_settings knitting_settings_;
};

} }

#endif
