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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_MODEL_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.coding/types/meta_model/name.hpp"
#include "masd.dogen.coding/hash/meta_model/name_hash.hpp"
#include "masd.dogen.coding/types/meta_model/languages.hpp"
#include "masd.dogen.coding/types/meta_model/module_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/element_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/origin_types.hpp"
#include "masd.dogen.coding/types/meta_model/element_archetype.hpp"
#include "masd.dogen.coding/types/meta_model/locator_properties.hpp"
#include "masd.dogen.coding/types/meta_model/orm_model_properties.hpp"
#include "masd.dogen.coding/hash/meta_model/element_archetype_hash.hpp"
#include "masd.dogen.coding/types/meta_model/extraction_properties.hpp"
#include "masd.dogen.coding/types/meta_model/global_archetype_location_properties.hpp"

namespace masd::dogen::coding::meta_model {

/**
 * @brief Coding model.
 */
class model final {
public:
    model(const model&) = default;
    ~model() = default;

public:
    model();

public:
    model(model&& rhs);

public:
    model(
        const masd::dogen::coding::meta_model::name& name,
        const masd::dogen::coding::meta_model::name& meta_name,
        const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& references,
        const std::unordered_set<masd::dogen::coding::meta_model::name>& leaves,
        const std::vector<boost::shared_ptr<masd::dogen::coding::meta_model::element> >& elements,
        const boost::shared_ptr<masd::dogen::coding::meta_model::module>& root_module,
        const std::unordered_set<std::string>& module_ids,
        const bool has_generatable_types,
        const masd::dogen::coding::meta_model::languages input_language,
        const masd::dogen::coding::meta_model::languages output_language,
        const boost::optional<masd::dogen::coding::meta_model::orm_model_properties>& orm_properties,
        const std::unordered_set<masd::dogen::coding::meta_model::element_archetype>& enabled_archetype_for_element,
        const masd::dogen::coding::meta_model::locator_properties& locator_properties,
        const masd::dogen::coding::meta_model::global_archetype_location_properties& global_archetype_location_properties,
        const boost::optional<masd::dogen::coding::meta_model::extraction_properties>& extraction_properties);

public:
    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const masd::dogen::coding::meta_model::name& name() const;
    masd::dogen::coding::meta_model::name& name();
    void name(const masd::dogen::coding::meta_model::name& v);
    void name(const masd::dogen::coding::meta_model::name&& v);
    /**@}*/

    /**
     * @brief Name of the element in the meta-model that this instance conforms to.
     */
    /**@{*/
    const masd::dogen::coding::meta_model::name& meta_name() const;
    masd::dogen::coding::meta_model::name& meta_name();
    void meta_name(const masd::dogen::coding::meta_model::name& v);
    void meta_name(const masd::dogen::coding::meta_model::name&& v);
    /**@}*/

    /**
     * @brief All other models that this model depends on, mapped to their origin.
     */
    /**@{*/
    const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& references() const;
    std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& references();
    void references(const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& v);
    void references(const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>&& v);
    /**@}*/

    /**
     * @brief All leaf types in this endomodel.
     *
     * Leaves are types concrete types which have a parent.
     */
    /**@{*/
    const std::unordered_set<masd::dogen::coding::meta_model::name>& leaves() const;
    std::unordered_set<masd::dogen::coding::meta_model::name>& leaves();
    void leaves(const std::unordered_set<masd::dogen::coding::meta_model::name>& v);
    void leaves(const std::unordered_set<masd::dogen::coding::meta_model::name>&& v);
    /**@}*/

    const std::vector<boost::shared_ptr<masd::dogen::coding::meta_model::element> >& elements() const;
    std::vector<boost::shared_ptr<masd::dogen::coding::meta_model::element> >& elements();
    void elements(const std::vector<boost::shared_ptr<masd::dogen::coding::meta_model::element> >& v);
    void elements(const std::vector<boost::shared_ptr<masd::dogen::coding::meta_model::element> >&& v);

    /**
     * @brief The module that represents the model.
     */
    /**@{*/
    const boost::shared_ptr<masd::dogen::coding::meta_model::module>& root_module() const;
    boost::shared_ptr<masd::dogen::coding::meta_model::module>& root_module();
    void root_module(const boost::shared_ptr<masd::dogen::coding::meta_model::module>& v);
    void root_module(const boost::shared_ptr<masd::dogen::coding::meta_model::module>&& v);
    /**@}*/

    /**
     * @brief IDs of all of the model elements which are modules.
     */
    /**@{*/
    const std::unordered_set<std::string>& module_ids() const;
    std::unordered_set<std::string>& module_ids();
    void module_ids(const std::unordered_set<std::string>& v);
    void module_ids(const std::unordered_set<std::string>&& v);
    /**@}*/

    /**
     * @brief If true the intermediate model has at least one generable type, false otherwise.
     */
    /**@{*/
    bool has_generatable_types() const;
    void has_generatable_types(const bool v);
    /**@}*/

    /**
     * @brief Language in which this model was written.
     */
    /**@{*/
    masd::dogen::coding::meta_model::languages input_language() const;
    void input_language(const masd::dogen::coding::meta_model::languages v);
    /**@}*/

    /**
     * @brief Language in which to output the model.
     */
    /**@{*/
    masd::dogen::coding::meta_model::languages output_language() const;
    void output_language(const masd::dogen::coding::meta_model::languages v);
    /**@}*/

    const boost::optional<masd::dogen::coding::meta_model::orm_model_properties>& orm_properties() const;
    boost::optional<masd::dogen::coding::meta_model::orm_model_properties>& orm_properties();
    void orm_properties(const boost::optional<masd::dogen::coding::meta_model::orm_model_properties>& v);
    void orm_properties(const boost::optional<masd::dogen::coding::meta_model::orm_model_properties>&& v);

    const std::unordered_set<masd::dogen::coding::meta_model::element_archetype>& enabled_archetype_for_element() const;
    std::unordered_set<masd::dogen::coding::meta_model::element_archetype>& enabled_archetype_for_element();
    void enabled_archetype_for_element(const std::unordered_set<masd::dogen::coding::meta_model::element_archetype>& v);
    void enabled_archetype_for_element(const std::unordered_set<masd::dogen::coding::meta_model::element_archetype>&& v);

    const masd::dogen::coding::meta_model::locator_properties& locator_properties() const;
    masd::dogen::coding::meta_model::locator_properties& locator_properties();
    void locator_properties(const masd::dogen::coding::meta_model::locator_properties& v);
    void locator_properties(const masd::dogen::coding::meta_model::locator_properties&& v);

    const masd::dogen::coding::meta_model::global_archetype_location_properties& global_archetype_location_properties() const;
    masd::dogen::coding::meta_model::global_archetype_location_properties& global_archetype_location_properties();
    void global_archetype_location_properties(const masd::dogen::coding::meta_model::global_archetype_location_properties& v);
    void global_archetype_location_properties(const masd::dogen::coding::meta_model::global_archetype_location_properties&& v);

    const boost::optional<masd::dogen::coding::meta_model::extraction_properties>& extraction_properties() const;
    boost::optional<masd::dogen::coding::meta_model::extraction_properties>& extraction_properties();
    void extraction_properties(const boost::optional<masd::dogen::coding::meta_model::extraction_properties>& v);
    void extraction_properties(const boost::optional<masd::dogen::coding::meta_model::extraction_properties>&& v);

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    masd::dogen::coding::meta_model::name name_;
    masd::dogen::coding::meta_model::name meta_name_;
    std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types> references_;
    std::unordered_set<masd::dogen::coding::meta_model::name> leaves_;
    std::vector<boost::shared_ptr<masd::dogen::coding::meta_model::element> > elements_;
    boost::shared_ptr<masd::dogen::coding::meta_model::module> root_module_;
    std::unordered_set<std::string> module_ids_;
    bool has_generatable_types_;
    masd::dogen::coding::meta_model::languages input_language_;
    masd::dogen::coding::meta_model::languages output_language_;
    boost::optional<masd::dogen::coding::meta_model::orm_model_properties> orm_properties_;
    std::unordered_set<masd::dogen::coding::meta_model::element_archetype> enabled_archetype_for_element_;
    masd::dogen::coding::meta_model::locator_properties locator_properties_;
    masd::dogen::coding::meta_model::global_archetype_location_properties global_archetype_location_properties_;
    boost::optional<masd::dogen::coding::meta_model::extraction_properties> extraction_properties_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::model& lhs,
    masd::dogen::coding::meta_model::model& rhs) {
    lhs.swap(rhs);
}

}

#endif
