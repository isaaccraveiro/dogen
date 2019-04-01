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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_MODELINE_GROUP_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_MODELINE_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.coding/types/meta_model/modeline_fwd.hpp"

namespace masd::dogen::coding::meta_model {

/**
 * @brief Group of modelines, logically associated.
 *
 * For example, one may choose to have a set of modelines for @e emacs , or for
 * @e vi, etc.
 */
class modeline_group final : public masd::dogen::coding::meta_model::element {
public:
    modeline_group() = default;
    modeline_group(const modeline_group&) = default;
    modeline_group(modeline_group&&) = default;

    virtual ~modeline_group() noexcept { }

public:
    modeline_group(
        const masd::dogen::coding::meta_model::name& name,
        const std::string& documentation,
        const masd::dogen::annotations::annotation& annotation,
        const masd::dogen::coding::meta_model::origin_types origin_type,
        const boost::optional<masd::dogen::coding::meta_model::name>& contained_by,
        const bool in_global_module,
        const std::list<masd::dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const masd::dogen::coding::meta_model::name& meta_name,
        const masd::dogen::coding::meta_model::technical_space intrinsic_technical_space,
        const bool is_element_extension,
        const masd::dogen::extraction::decoration_properties& decoration_properties,
        const std::unordered_map<std::string, masd::dogen::coding::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, masd::dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const boost::optional<masd::dogen::coding::meta_model::decoration>& decoration,
        const std::unordered_set<std::string>& modeline_ids,
        const std::list<boost::shared_ptr<masd::dogen::coding::meta_model::modeline> >& modelines);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief All the IDs for the modelines that belong to this group.
     */
    /**@{*/
    const std::unordered_set<std::string>& modeline_ids() const;
    std::unordered_set<std::string>& modeline_ids();
    void modeline_ids(const std::unordered_set<std::string>& v);
    void modeline_ids(const std::unordered_set<std::string>&& v);
    /**@}*/

    /**
     * @brief Modelines that make up the group.
     */
    /**@{*/
    const std::list<boost::shared_ptr<masd::dogen::coding::meta_model::modeline> >& modelines() const;
    std::list<boost::shared_ptr<masd::dogen::coding::meta_model::modeline> >& modelines();
    void modelines(const std::list<boost::shared_ptr<masd::dogen::coding::meta_model::modeline> >& v);
    void modelines(const std::list<boost::shared_ptr<masd::dogen::coding::meta_model::modeline> >&& v);
    /**@}*/

public:
    bool operator==(const modeline_group& rhs) const;
    bool operator!=(const modeline_group& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const masd::dogen::coding::meta_model::element& other) const override;

public:
    void swap(modeline_group& other) noexcept;
    modeline_group& operator=(modeline_group other);

private:
    std::unordered_set<std::string> modeline_ids_;
    std::list<boost::shared_ptr<masd::dogen::coding::meta_model::modeline> > modelines_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::modeline_group& lhs,
    masd::dogen::coding::meta_model::modeline_group& rhs) {
    lhs.swap(rhs);
}

}

#endif
