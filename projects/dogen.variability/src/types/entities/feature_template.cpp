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
#include <ostream>
#include <boost/algorithm/string.hpp>
#include "dogen.variability/io/entities/value_io.hpp"
#include "dogen.variability/types/entities/value.hpp"
#include "dogen.variability/io/entities/element_io.hpp"
#include "dogen.variability/io/entities/value_type_io.hpp"
#include "dogen.variability/io/entities/binding_point_io.hpp"
#include "dogen.variability/io/entities/binding_action_io.hpp"
#include "dogen.variability/types/entities/feature_template.hpp"
#include "dogen.variability/io/entities/default_value_override_io.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::entities::value>& lhs,
const boost::shared_ptr<dogen::variability::entities::value>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::variability::entities::value>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::variability::entities::default_value_override>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::variability::entities {

feature_template::feature_template()
    : value_type_(static_cast<dogen::variability::entities::value_type>(0)),
      binding_point_(static_cast<dogen::variability::entities::binding_point>(0)),
      profile_binding_action_(static_cast<dogen::variability::entities::binding_action>(0)),
      configuration_binding_action_(static_cast<dogen::variability::entities::binding_action>(0)) { }

feature_template::feature_template(
    const dogen::variability::entities::name& name,
    const std::string& description,
    const boost::shared_ptr<dogen::variability::entities::value>& default_value,
    const dogen::variability::entities::value_type value_type,
    const dogen::variability::entities::binding_point binding_point,
    const dogen::variability::entities::binding_action profile_binding_action,
    const dogen::variability::entities::binding_action configuration_binding_action,
    const std::string& instantiation_domain_name,
    const std::list<dogen::variability::entities::default_value_override>& default_value_overrides)
    : dogen::variability::entities::element(
      name,
      description),
      default_value_(default_value),
      value_type_(value_type),
      binding_point_(binding_point),
      profile_binding_action_(profile_binding_action),
      configuration_binding_action_(configuration_binding_action),
      instantiation_domain_name_(instantiation_domain_name),
      default_value_overrides_(default_value_overrides) { }

void feature_template::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::variability::entities::feature_template\"" << ", "
      << "\"__parent_0__\": ";
    dogen::variability::entities::element::to_stream(s);
    s << ", "
      << "\"default_value\": " << default_value_ << ", "
      << "\"value_type\": " << value_type_ << ", "
      << "\"binding_point\": " << binding_point_ << ", "
      << "\"profile_binding_action\": " << profile_binding_action_ << ", "
      << "\"configuration_binding_action\": " << configuration_binding_action_ << ", "
      << "\"instantiation_domain_name\": " << "\"" << tidy_up_string(instantiation_domain_name_) << "\"" << ", "
      << "\"default_value_overrides\": " << default_value_overrides_
      << " }";
}

void feature_template::swap(feature_template& other) noexcept {
    dogen::variability::entities::element::swap(other);

    using std::swap;
    swap(default_value_, other.default_value_);
    swap(value_type_, other.value_type_);
    swap(binding_point_, other.binding_point_);
    swap(profile_binding_action_, other.profile_binding_action_);
    swap(configuration_binding_action_, other.configuration_binding_action_);
    swap(instantiation_domain_name_, other.instantiation_domain_name_);
    swap(default_value_overrides_, other.default_value_overrides_);
}

bool feature_template::equals(const dogen::variability::entities::element& other) const {
    const feature_template* const p(dynamic_cast<const feature_template* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool feature_template::operator==(const feature_template& rhs) const {
    return dogen::variability::entities::element::compare(rhs) &&
        default_value_ == rhs.default_value_ &&
        value_type_ == rhs.value_type_ &&
        binding_point_ == rhs.binding_point_ &&
        profile_binding_action_ == rhs.profile_binding_action_ &&
        configuration_binding_action_ == rhs.configuration_binding_action_ &&
        instantiation_domain_name_ == rhs.instantiation_domain_name_ &&
        default_value_overrides_ == rhs.default_value_overrides_;
}

feature_template& feature_template::operator=(feature_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::variability::entities::value>& feature_template::default_value() const {
    return default_value_;
}

boost::shared_ptr<dogen::variability::entities::value>& feature_template::default_value() {
    return default_value_;
}

void feature_template::default_value(const boost::shared_ptr<dogen::variability::entities::value>& v) {
    default_value_ = v;
}

void feature_template::default_value(const boost::shared_ptr<dogen::variability::entities::value>&& v) {
    default_value_ = std::move(v);
}

dogen::variability::entities::value_type feature_template::value_type() const {
    return value_type_;
}

void feature_template::value_type(const dogen::variability::entities::value_type v) {
    value_type_ = v;
}

dogen::variability::entities::binding_point feature_template::binding_point() const {
    return binding_point_;
}

void feature_template::binding_point(const dogen::variability::entities::binding_point v) {
    binding_point_ = v;
}

dogen::variability::entities::binding_action feature_template::profile_binding_action() const {
    return profile_binding_action_;
}

void feature_template::profile_binding_action(const dogen::variability::entities::binding_action v) {
    profile_binding_action_ = v;
}

dogen::variability::entities::binding_action feature_template::configuration_binding_action() const {
    return configuration_binding_action_;
}

void feature_template::configuration_binding_action(const dogen::variability::entities::binding_action v) {
    configuration_binding_action_ = v;
}

const std::string& feature_template::instantiation_domain_name() const {
    return instantiation_domain_name_;
}

std::string& feature_template::instantiation_domain_name() {
    return instantiation_domain_name_;
}

void feature_template::instantiation_domain_name(const std::string& v) {
    instantiation_domain_name_ = v;
}

void feature_template::instantiation_domain_name(const std::string&& v) {
    instantiation_domain_name_ = std::move(v);
}

const std::list<dogen::variability::entities::default_value_override>& feature_template::default_value_overrides() const {
    return default_value_overrides_;
}

std::list<dogen::variability::entities::default_value_override>& feature_template::default_value_overrides() {
    return default_value_overrides_;
}

void feature_template::default_value_overrides(const std::list<dogen::variability::entities::default_value_override>& v) {
    default_value_overrides_ = v;
}

void feature_template::default_value_overrides(const std::list<dogen::variability::entities::default_value_override>&& v) {
    default_value_overrides_ = std::move(v);
}

}
