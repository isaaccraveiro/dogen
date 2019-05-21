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
#ifndef DOGEN_GENERATION_CPP_TYPES_FORMATTERS_WORKFLOW_HPP
#define DOGEN_GENERATION_CPP_TYPES_FORMATTERS_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen.variability/types/helpers/configuration_factory.hpp"
#include "dogen.extraction/types/meta_model/artefact.hpp"
#include "dogen.coding/types/meta_model/element.hpp"
#include "dogen.generation/types/meta_model/element_archetype.hpp"
#include "dogen.generation.cpp/types/formattables/locator.hpp"
#include "dogen.generation.cpp/types/formattables/model.hpp"
#include "dogen.generation.cpp/types/formatters/registrar.hpp"
#include "dogen.generation.cpp/types/formatters/stitch_formatter.hpp"

namespace dogen::generation::cpp::formatters {

/**
 * @brief Generates all files for the supplied entity.
 */
class workflow final {
public:
    workflow(const formattables::locator& l,
        const variability::meta_model::feature_model& fm,
        const variability::helpers::configuration_factory& cf);

public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static cpp::formatters::registrar& registrar();

private:
    const coding::meta_model::artefact_properties&
    get_artefact_properties(const coding::meta_model::element& e,
        const std::string& archetype) const;

private:
    std::list<extraction::meta_model::artefact>
    format(const std::unordered_set<generation::meta_model::element_archetype>&
        enabled_archetype_for_element, const formattables::model& fm,
        const coding::meta_model::element& e,
        const formattables::element_properties& ep) const;

public:
    std::list<extraction::meta_model::artefact>
    execute(const std::unordered_set<generation::meta_model::element_archetype>&
        enabled_archetype_for_element, const formattables::model& fm) const;

private:
    static std::shared_ptr<cpp::formatters::registrar> registrar_;
    const stitch_formatter stitch_formatter_;
    const formattables::locator& locator_;
};

}

#endif
