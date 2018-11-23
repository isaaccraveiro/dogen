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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_ENDOMODEL_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_ENDOMODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.coding/types/meta_model/name.hpp"
#include "masd.dogen.coding/hash/meta_model/name_hash.hpp"
#include "masd.dogen.coding/types/meta_model/languages.hpp"
#include "masd.dogen.coding/types/meta_model/module_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/object_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/builtin_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/visitor_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/origin_types.hpp"
#include "masd.dogen.coding/types/meta_model/exception_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/primitive_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/object_template_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/orm_model_properties.hpp"

namespace masd::dogen::coding::meta_model {

/**
 * @brief Intermediate representation of a yarn model.
 */
class endomodel final {
public:
    endomodel(const endomodel&) = default;
    ~endomodel() = default;

public:
    endomodel();

public:
    endomodel(endomodel&& rhs);

public:
    endomodel(
        const masd::dogen::coding::meta_model::name& name,
        const masd::dogen::coding::meta_model::name& meta_name,
        const masd::dogen::coding::meta_model::origin_types origin_type,
        const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& references,
        const std::unordered_set<masd::dogen::coding::meta_model::name>& leaves,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::module> >& modules,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object_template> >& object_templates,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::builtin> >& builtins,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::enumeration> >& enumerations,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::primitive> >& primitives,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object> >& objects,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::exception> >& exceptions,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::visitor> >& visitors,
        const boost::shared_ptr<masd::dogen::coding::meta_model::module>& root_module,
        const masd::dogen::coding::meta_model::languages input_language,
        const std::list<masd::dogen::coding::meta_model::languages>& output_languages,
        const boost::optional<masd::dogen::coding::meta_model::orm_model_properties>& orm_properties);

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
     * @brief All other intermediate models that this endomodel depends on, mapped to their
     * origin.
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

    /**
     * @brief Modules contained in the endomodel.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::module> >& modules() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::module> >& modules();
    void modules(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::module> >& v);
    void modules(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::module> >&& v);
    /**@}*/

    /**
     * @brief All the object templates available in this endomodel.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object_template> >& object_templates() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object_template> >& object_templates();
    void object_templates(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object_template> >& v);
    void object_templates(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object_template> >&& v);
    /**@}*/

    /**
     * @brief All built-ins contained in this endomodel.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::builtin> >& builtins() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::builtin> >& builtins();
    void builtins(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::builtin> >& v);
    void builtins(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::builtin> >&& v);
    /**@}*/

    /**
     * @brief All enumerations contained in this endomodel.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::enumeration> >& enumerations() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::enumeration> >& enumerations();
    void enumerations(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::enumeration> >& v);
    void enumerations(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::enumeration> >&& v);
    /**@}*/

    /**
     * @brief All primitives in this endomodel.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::primitive> >& primitives() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::primitive> >& primitives();
    void primitives(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::primitive> >& v);
    void primitives(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::primitive> >&& v);
    /**@}*/

    /**
     * @brief All objects contained in this endomodel.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object> >& objects() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object> >& objects();
    void objects(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object> >& v);
    void objects(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object> >&& v);
    /**@}*/

    /**
     * @brief All exceptions in this endomodel.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::exception> >& exceptions() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::exception> >& exceptions();
    void exceptions(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::exception> >& v);
    void exceptions(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::exception> >&& v);
    /**@}*/

    /**
     * @brief All visitors in this endomodel.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::visitor> >& visitors() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::visitor> >& visitors();
    void visitors(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::visitor> >& v);
    void visitors(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::visitor> >&& v);
    /**@}*/

    const boost::shared_ptr<masd::dogen::coding::meta_model::module>& root_module() const;
    boost::shared_ptr<masd::dogen::coding::meta_model::module>& root_module();
    void root_module(const boost::shared_ptr<masd::dogen::coding::meta_model::module>& v);
    void root_module(const boost::shared_ptr<masd::dogen::coding::meta_model::module>&& v);

    /**
     * @brief Language in which this endomodel was written.
     */
    /**@{*/
    masd::dogen::coding::meta_model::languages input_language() const;
    void input_language(const masd::dogen::coding::meta_model::languages v);
    /**@}*/

    /**
     * @brief Languages in which to output the final model.
     */
    /**@{*/
    const std::list<masd::dogen::coding::meta_model::languages>& output_languages() const;
    std::list<masd::dogen::coding::meta_model::languages>& output_languages();
    void output_languages(const std::list<masd::dogen::coding::meta_model::languages>& v);
    void output_languages(const std::list<masd::dogen::coding::meta_model::languages>&& v);
    /**@}*/

    const boost::optional<masd::dogen::coding::meta_model::orm_model_properties>& orm_properties() const;
    boost::optional<masd::dogen::coding::meta_model::orm_model_properties>& orm_properties();
    void orm_properties(const boost::optional<masd::dogen::coding::meta_model::orm_model_properties>& v);
    void orm_properties(const boost::optional<masd::dogen::coding::meta_model::orm_model_properties>&& v);

public:
    bool operator==(const endomodel& rhs) const;
    bool operator!=(const endomodel& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(endomodel& other) noexcept;
    endomodel& operator=(endomodel other);

private:
    masd::dogen::coding::meta_model::name name_;
    masd::dogen::coding::meta_model::name meta_name_;
    masd::dogen::coding::meta_model::origin_types origin_type_;
    std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types> references_;
    std::unordered_set<masd::dogen::coding::meta_model::name> leaves_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::module> > modules_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object_template> > object_templates_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::builtin> > builtins_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::enumeration> > enumerations_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::primitive> > primitives_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object> > objects_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::exception> > exceptions_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::visitor> > visitors_;
    boost::shared_ptr<masd::dogen::coding::meta_model::module> root_module_;
    masd::dogen::coding::meta_model::languages input_language_;
    std::list<masd::dogen::coding::meta_model::languages> output_languages_;
    boost::optional<masd::dogen::coding::meta_model::orm_model_properties> orm_properties_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::endomodel& lhs,
    masd::dogen::coding::meta_model::endomodel& rhs) {
    lhs.swap(rhs);
}

}

#endif