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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FABRIC_FORWARD_DECLARATIONS_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FABRIC_FORWARD_DECLARATIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "masd.dogen.modeling/types/meta_model/name.hpp"
#include "masd.dogen.modeling/types/meta_model/element.hpp"

namespace masd::dogen::generation::cpp::fabric {

class forward_declarations final : public masd::dogen::modeling::meta_model::element {
public:
    forward_declarations(const forward_declarations&) = default;
    forward_declarations(forward_declarations&&) = default;

public:
    forward_declarations();

    virtual ~forward_declarations() noexcept { }

public:
    forward_declarations(
        const masd::dogen::modeling::meta_model::name& name,
        const std::string& documentation,
        const masd::dogen::annotations::annotation& annotation,
        const masd::dogen::modeling::meta_model::origin_types origin_type,
        const boost::optional<masd::dogen::modeling::meta_model::name>& contained_by,
        const bool in_global_module,
        const std::list<masd::dogen::modeling::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const masd::dogen::modeling::meta_model::name& meta_name,
        const bool is_element_extension,
        const masd::dogen::formatting::decoration_properties& decoration_properties,
        const std::unordered_map<std::string, masd::dogen::modeling::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, masd::dogen::modeling::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::modeling::meta_model::opaque_properties> >& opaque_properties,
        const bool is_enum,
        const masd::dogen::modeling::meta_model::name& underlying_element,
        const bool is_exception);

public:
    using masd::dogen::modeling::meta_model::element::accept;

    virtual void accept(const masd::dogen::modeling::meta_model::element_visitor& v) const override;
    virtual void accept(masd::dogen::modeling::meta_model::element_visitor& v) const override;
    virtual void accept(const masd::dogen::modeling::meta_model::element_visitor& v) override;
    virtual void accept(masd::dogen::modeling::meta_model::element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Returns true if the type for which we are creating a forward declaration is
     * an enumeration, false otherwise.
     */
    /**@{*/
    bool is_enum() const;
    void is_enum(const bool v);
    /**@}*/

    /**
     * @brief The underlying type of the enumeration, if we are an enum forward declaration.
     */
    /**@{*/
    const masd::dogen::modeling::meta_model::name& underlying_element() const;
    masd::dogen::modeling::meta_model::name& underlying_element();
    void underlying_element(const masd::dogen::modeling::meta_model::name& v);
    void underlying_element(const masd::dogen::modeling::meta_model::name&& v);
    /**@}*/

    bool is_exception() const;
    void is_exception(const bool v);

public:
    bool operator==(const forward_declarations& rhs) const;
    bool operator!=(const forward_declarations& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const masd::dogen::modeling::meta_model::element& other) const override;

public:
    void swap(forward_declarations& other) noexcept;
    forward_declarations& operator=(forward_declarations other);

private:
    bool is_enum_;
    masd::dogen::modeling::meta_model::name underlying_element_;
    bool is_exception_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::generation::cpp::fabric::forward_declarations& lhs,
    masd::dogen::generation::cpp::fabric::forward_declarations& rhs) {
    lhs.swap(rhs);
}

}

#endif