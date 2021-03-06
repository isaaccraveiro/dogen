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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_FEATURE_TEMPLATE_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_FEATURE_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include "dogen.logical/types/entities/variability/abstract_feature.hpp"
#include "dogen.logical/types/entities/variability/default_value_override.hpp"

namespace dogen::logical::entities::variability {

/**
 * @brief Represents a feature template in variability space.
 *
 * Feature templates are expanded into features within the variability model.
 */
class feature_template final : public dogen::logical::entities::variability::abstract_feature {
public:
    feature_template() = default;
    feature_template(const feature_template&) = default;
    feature_template(feature_template&&) = default;

    virtual ~feature_template() noexcept { }

public:
    feature_template(
        const std::string& documentation,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const dogen::logical::entities::name& name,
        const std::string& original_key,
        const std::string& key,
        const std::string& identifiable_key,
        const std::string& unparsed_type,
        const std::string& mapped_type,
        const dogen::logical::entities::name_tree& parsed_type,
        const std::string& default_value,
        const dogen::variability::entities::value_type value_type,
        const boost::optional<dogen::variability::entities::binding_point>& binding_point,
        const bool is_optional,
        const bool requires_optionality,
        const std::list<dogen::logical::entities::variability::default_value_override>& default_value_overrides);

public:
    void to_stream(std::ostream& s) const override;

public:
    const std::list<dogen::logical::entities::variability::default_value_override>& default_value_overrides() const;
    std::list<dogen::logical::entities::variability::default_value_override>& default_value_overrides();
    void default_value_overrides(const std::list<dogen::logical::entities::variability::default_value_override>& v);
    void default_value_overrides(const std::list<dogen::logical::entities::variability::default_value_override>&& v);

public:
    bool operator==(const feature_template& rhs) const;
    bool operator!=(const feature_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::variability::abstract_feature& other) const override;

public:
    void swap(feature_template& other) noexcept;
    feature_template& operator=(feature_template other);

private:
    std::list<dogen::logical::entities::variability::default_value_override> default_value_overrides_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::variability::feature_template& lhs,
    dogen::logical::entities::variability::feature_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
