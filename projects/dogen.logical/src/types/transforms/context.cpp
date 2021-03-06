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
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.logical/types/helpers/mapping_set_repository.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::entities::feature_model>& lhs,
const boost::shared_ptr<dogen::variability::entities::feature_model>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::physical::entities::meta_model>& lhs,
const boost::shared_ptr<dogen::physical::entities::meta_model>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::helpers::mapping_set_repository>& lhs,
const boost::shared_ptr<dogen::logical::helpers::mapping_set_repository>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::tracing::tracer>& lhs,
const boost::shared_ptr<dogen::tracing::tracer>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::logical::transforms {

context::context()
    : compatibility_mode_(static_cast<bool>(0)) { }

context::context(
    const bool compatibility_mode,
    const boost::shared_ptr<dogen::variability::entities::feature_model>& feature_model,
    const boost::shared_ptr<dogen::physical::entities::meta_model>& physical_meta_model,
    const boost::shared_ptr<dogen::logical::helpers::mapping_set_repository>& mapping_repository,
    const boost::shared_ptr<dogen::tracing::tracer>& tracer)
    : compatibility_mode_(compatibility_mode),
      feature_model_(feature_model),
      physical_meta_model_(physical_meta_model),
      mapping_repository_(mapping_repository),
      tracer_(tracer) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(compatibility_mode_, other.compatibility_mode_);
    swap(feature_model_, other.feature_model_);
    swap(physical_meta_model_, other.physical_meta_model_);
    swap(mapping_repository_, other.mapping_repository_);
    swap(tracer_, other.tracer_);
}

bool context::operator==(const context& rhs) const {
    return compatibility_mode_ == rhs.compatibility_mode_ &&
        feature_model_ == rhs.feature_model_ &&
        physical_meta_model_ == rhs.physical_meta_model_ &&
        mapping_repository_ == rhs.mapping_repository_ &&
        tracer_ == rhs.tracer_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool context::compatibility_mode() const {
    return compatibility_mode_;
}

void context::compatibility_mode(const bool v) {
    compatibility_mode_ = v;
}

const boost::shared_ptr<dogen::variability::entities::feature_model>& context::feature_model() const {
    return feature_model_;
}

boost::shared_ptr<dogen::variability::entities::feature_model>& context::feature_model() {
    return feature_model_;
}

void context::feature_model(const boost::shared_ptr<dogen::variability::entities::feature_model>& v) {
    feature_model_ = v;
}

void context::feature_model(const boost::shared_ptr<dogen::variability::entities::feature_model>&& v) {
    feature_model_ = std::move(v);
}

const boost::shared_ptr<dogen::physical::entities::meta_model>& context::physical_meta_model() const {
    return physical_meta_model_;
}

boost::shared_ptr<dogen::physical::entities::meta_model>& context::physical_meta_model() {
    return physical_meta_model_;
}

void context::physical_meta_model(const boost::shared_ptr<dogen::physical::entities::meta_model>& v) {
    physical_meta_model_ = v;
}

void context::physical_meta_model(const boost::shared_ptr<dogen::physical::entities::meta_model>&& v) {
    physical_meta_model_ = std::move(v);
}

const boost::shared_ptr<dogen::logical::helpers::mapping_set_repository>& context::mapping_repository() const {
    return mapping_repository_;
}

boost::shared_ptr<dogen::logical::helpers::mapping_set_repository>& context::mapping_repository() {
    return mapping_repository_;
}

void context::mapping_repository(const boost::shared_ptr<dogen::logical::helpers::mapping_set_repository>& v) {
    mapping_repository_ = v;
}

void context::mapping_repository(const boost::shared_ptr<dogen::logical::helpers::mapping_set_repository>&& v) {
    mapping_repository_ = std::move(v);
}

const boost::shared_ptr<dogen::tracing::tracer>& context::tracer() const {
    return tracer_;
}

boost::shared_ptr<dogen::tracing::tracer>& context::tracer() {
    return tracer_;
}

void context::tracer(const boost::shared_ptr<dogen::tracing::tracer>& v) {
    tracer_ = v;
}

void context::tracer(const boost::shared_ptr<dogen::tracing::tracer>&& v) {
    tracer_ = std::move(v);
}

}
