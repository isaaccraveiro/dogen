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

#include <list>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.coding/types/meta_model/name.hpp"
#include "masd.dogen.coding/hash/meta_model/name_hash.hpp"
#include "masd.dogen.coding/types/meta_model/origin_types.hpp"
#include "masd.dogen.coding/types/meta_model/technical_space.hpp"
#include "masd.dogen.coding/types/meta_model/orm/model_properties.hpp"
#include "masd.dogen.coding/types/meta_model/extraction_properties.hpp"
#include "masd.dogen.coding/types/meta_model/structural/module_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/decoration/element_repository.hpp"
#include "masd.dogen.coding/types/meta_model/structural/element_repository.hpp"
#include "masd.dogen.coding/types/meta_model/variability/element_repository.hpp"

namespace masd::dogen::coding::meta_model {

/**
 * @brief Intermediate representation of a masd model.
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
        const masd::dogen::coding::meta_model::origin_types origin_type,
        const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& references,
        const std::unordered_set<masd::dogen::coding::meta_model::name>& leaves,
        const boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>& root_module,
        const masd::dogen::coding::meta_model::technical_space input_technical_space,
        const std::list<masd::dogen::coding::meta_model::technical_space>& output_technical_spaces,
        const boost::optional<masd::dogen::coding::meta_model::orm::model_properties>& orm_properties,
        const masd::dogen::coding::meta_model::extraction_properties& extraction_properties,
        const masd::dogen::coding::meta_model::structural::element_repository& structural_elements,
        const masd::dogen::coding::meta_model::decoration::element_repository& decoration_elements,
        const masd::dogen::coding::meta_model::variability::element_repository& variability_elements);

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
     * @brief How was this model element originated.
     */
    /**@{*/
    masd::dogen::coding::meta_model::origin_types origin_type() const;
    void origin_type(const masd::dogen::coding::meta_model::origin_types v);
    /**@}*/

    /**
     * @brief All other intermediate models that this model depends on, mapped to their
     * origin.
     */
    /**@{*/
    const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& references() const;
    std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& references();
    void references(const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& v);
    void references(const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>&& v);
    /**@}*/

    /**
     * @brief All leaf types in this model.
     *
     * Leaves are types concrete types which have a parent.
     */
    /**@{*/
    const std::unordered_set<masd::dogen::coding::meta_model::name>& leaves() const;
    std::unordered_set<masd::dogen::coding::meta_model::name>& leaves();
    void leaves(const std::unordered_set<masd::dogen::coding::meta_model::name>& v);
    void leaves(const std::unordered_set<masd::dogen::coding::meta_model::name>&& v);
    /**@}*/

    const boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>& root_module() const;
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>& root_module();
    void root_module(const boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>& v);
    void root_module(const boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>&& v);

    /**
     * @brief Technical space in which this model was written.
     */
    /**@{*/
    masd::dogen::coding::meta_model::technical_space input_technical_space() const;
    void input_technical_space(const masd::dogen::coding::meta_model::technical_space v);
    /**@}*/

    /**
     * @brief Technical spaces into which to extract the final model.
     */
    /**@{*/
    const std::list<masd::dogen::coding::meta_model::technical_space>& output_technical_spaces() const;
    std::list<masd::dogen::coding::meta_model::technical_space>& output_technical_spaces();
    void output_technical_spaces(const std::list<masd::dogen::coding::meta_model::technical_space>& v);
    void output_technical_spaces(const std::list<masd::dogen::coding::meta_model::technical_space>&& v);
    /**@}*/

    const boost::optional<masd::dogen::coding::meta_model::orm::model_properties>& orm_properties() const;
    boost::optional<masd::dogen::coding::meta_model::orm::model_properties>& orm_properties();
    void orm_properties(const boost::optional<masd::dogen::coding::meta_model::orm::model_properties>& v);
    void orm_properties(const boost::optional<masd::dogen::coding::meta_model::orm::model_properties>&& v);

    const masd::dogen::coding::meta_model::extraction_properties& extraction_properties() const;
    masd::dogen::coding::meta_model::extraction_properties& extraction_properties();
    void extraction_properties(const masd::dogen::coding::meta_model::extraction_properties& v);
    void extraction_properties(const masd::dogen::coding::meta_model::extraction_properties&& v);

    /**
     * @brief All structural elements in this model.
     */
    /**@{*/
    const masd::dogen::coding::meta_model::structural::element_repository& structural_elements() const;
    masd::dogen::coding::meta_model::structural::element_repository& structural_elements();
    void structural_elements(const masd::dogen::coding::meta_model::structural::element_repository& v);
    void structural_elements(const masd::dogen::coding::meta_model::structural::element_repository&& v);
    /**@}*/

    /**
     * @brief All decoration elements in this model.
     */
    /**@{*/
    const masd::dogen::coding::meta_model::decoration::element_repository& decoration_elements() const;
    masd::dogen::coding::meta_model::decoration::element_repository& decoration_elements();
    void decoration_elements(const masd::dogen::coding::meta_model::decoration::element_repository& v);
    void decoration_elements(const masd::dogen::coding::meta_model::decoration::element_repository&& v);
    /**@}*/

    /**
     * @brief All variability elements in this model.
     */
    /**@{*/
    const masd::dogen::coding::meta_model::variability::element_repository& variability_elements() const;
    masd::dogen::coding::meta_model::variability::element_repository& variability_elements();
    void variability_elements(const masd::dogen::coding::meta_model::variability::element_repository& v);
    void variability_elements(const masd::dogen::coding::meta_model::variability::element_repository&& v);
    /**@}*/

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
    masd::dogen::coding::meta_model::origin_types origin_type_;
    std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types> references_;
    std::unordered_set<masd::dogen::coding::meta_model::name> leaves_;
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::module> root_module_;
    masd::dogen::coding::meta_model::technical_space input_technical_space_;
    std::list<masd::dogen::coding::meta_model::technical_space> output_technical_spaces_;
    boost::optional<masd::dogen::coding::meta_model::orm::model_properties> orm_properties_;
    masd::dogen::coding::meta_model::extraction_properties extraction_properties_;
    masd::dogen::coding::meta_model::structural::element_repository structural_elements_;
    masd::dogen::coding::meta_model::decoration::element_repository decoration_elements_;
    masd::dogen::coding::meta_model::variability::element_repository variability_elements_;
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
