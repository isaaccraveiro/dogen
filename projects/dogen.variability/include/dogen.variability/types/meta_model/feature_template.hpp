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
#ifndef DOGEN_VARIABILITY_TYPES_META_MODEL_FEATURE_TEMPLATE_HPP
#define DOGEN_VARIABILITY_TYPES_META_MODEL_FEATURE_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.archetypes/types/location.hpp"
#include "dogen.variability/types/meta_model/element.hpp"
#include "dogen.variability/types/meta_model/value_fwd.hpp"
#include "dogen.variability/types/meta_model/value_type.hpp"
#include "dogen.variability/types/meta_model/binding_point.hpp"
#include "dogen.variability/types/meta_model/template_kind.hpp"
#include "dogen.variability/types/meta_model/binding_action.hpp"

namespace dogen::variability::meta_model {

/**
 * @brief Defines a template that can be used to instantiate features.
 */
class feature_template final : public dogen::variability::meta_model::element {
public:
    feature_template(const feature_template&) = default;
    feature_template(feature_template&&) = default;

public:
    feature_template();

    virtual ~feature_template() noexcept { }

public:
    feature_template(
        const dogen::variability::meta_model::name& name,
        const std::string& description,
        const dogen::archetypes::location& location,
        const boost::shared_ptr<dogen::variability::meta_model::value>& default_value,
        const dogen::variability::meta_model::value_type value_type,
        const dogen::variability::meta_model::binding_point binding_point,
        const dogen::variability::meta_model::binding_action profile_binding_action,
        const dogen::variability::meta_model::binding_action configuration_binding_action,
        const dogen::variability::meta_model::template_kind kind);

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief The location of this element in archetype space.
     */
    /**@{*/
    const dogen::archetypes::location& location() const;
    dogen::archetypes::location& location();
    void location(const dogen::archetypes::location& v);
    void location(const dogen::archetypes::location&& v);
    /**@}*/

    /**
     * @brief Default value for element, if any.
     */
    /**@{*/
    const boost::shared_ptr<dogen::variability::meta_model::value>& default_value() const;
    boost::shared_ptr<dogen::variability::meta_model::value>& default_value();
    void default_value(const boost::shared_ptr<dogen::variability::meta_model::value>& v);
    void default_value(const boost::shared_ptr<dogen::variability::meta_model::value>&& v);
    /**@}*/

    /**
     * @brief Type of the value for the feature that will result of the template instantiation.
     */
    /**@{*/
    dogen::variability::meta_model::value_type value_type() const;
    void value_type(const dogen::variability::meta_model::value_type v);
    /**@}*/

    /**
     * @brief How the feature binds against other model elements.
     */
    /**@{*/
    dogen::variability::meta_model::binding_point binding_point() const;
    void binding_point(const dogen::variability::meta_model::binding_point v);
    /**@}*/

    dogen::variability::meta_model::binding_action profile_binding_action() const;
    void profile_binding_action(const dogen::variability::meta_model::binding_action v);

    dogen::variability::meta_model::binding_action configuration_binding_action() const;
    void configuration_binding_action(const dogen::variability::meta_model::binding_action v);

    /**
     * @brief Kind of the template.
     */
    /**@{*/
    dogen::variability::meta_model::template_kind kind() const;
    void kind(const dogen::variability::meta_model::template_kind v);
    /**@}*/

public:
    bool operator==(const feature_template& rhs) const;
    bool operator!=(const feature_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::variability::meta_model::element& other) const override;

public:
    void swap(feature_template& other) noexcept;
    feature_template& operator=(feature_template other);

private:
    dogen::archetypes::location location_;
    boost::shared_ptr<dogen::variability::meta_model::value> default_value_;
    dogen::variability::meta_model::value_type value_type_;
    dogen::variability::meta_model::binding_point binding_point_;
    dogen::variability::meta_model::binding_action profile_binding_action_;
    dogen::variability::meta_model::binding_action configuration_binding_action_;
    dogen::variability::meta_model::template_kind kind_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::meta_model::feature_template& lhs,
    dogen::variability::meta_model::feature_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
