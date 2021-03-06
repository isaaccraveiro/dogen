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
#include "dogen.m2t/types/transforms/context.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::physical::entities::meta_model>& lhs,
const boost::shared_ptr<dogen::physical::entities::meta_model>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::entities::feature_model>& lhs,
const boost::shared_ptr<dogen::variability::entities::feature_model>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::tracing::tracer>& lhs,
const boost::shared_ptr<dogen::tracing::tracer>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::m2t::transforms {

context::context(context&& rhs)
    : physical_meta_model_(std::move(rhs.physical_meta_model_)),
      output_directory_path_(std::move(rhs.output_directory_path_)),
      feature_model_(std::move(rhs.feature_model_)),
      tracer_(std::move(rhs.tracer_)),
      generation_timestamp_(std::move(rhs.generation_timestamp_)) { }

context::context(
    const boost::shared_ptr<dogen::physical::entities::meta_model>& physical_meta_model,
    const boost::filesystem::path& output_directory_path,
    const boost::shared_ptr<dogen::variability::entities::feature_model>& feature_model,
    const boost::shared_ptr<dogen::tracing::tracer>& tracer,
    const std::string& generation_timestamp)
    : physical_meta_model_(physical_meta_model),
      output_directory_path_(output_directory_path),
      feature_model_(feature_model),
      tracer_(tracer),
      generation_timestamp_(generation_timestamp) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(physical_meta_model_, other.physical_meta_model_);
    swap(output_directory_path_, other.output_directory_path_);
    swap(feature_model_, other.feature_model_);
    swap(tracer_, other.tracer_);
    swap(generation_timestamp_, other.generation_timestamp_);
}

bool context::operator==(const context& rhs) const {
    return physical_meta_model_ == rhs.physical_meta_model_ &&
        output_directory_path_ == rhs.output_directory_path_ &&
        feature_model_ == rhs.feature_model_ &&
        tracer_ == rhs.tracer_ &&
        generation_timestamp_ == rhs.generation_timestamp_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
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

const boost::filesystem::path& context::output_directory_path() const {
    return output_directory_path_;
}

boost::filesystem::path& context::output_directory_path() {
    return output_directory_path_;
}

void context::output_directory_path(const boost::filesystem::path& v) {
    output_directory_path_ = v;
}

void context::output_directory_path(const boost::filesystem::path&& v) {
    output_directory_path_ = std::move(v);
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

const std::string& context::generation_timestamp() const {
    return generation_timestamp_;
}

std::string& context::generation_timestamp() {
    return generation_timestamp_;
}

void context::generation_timestamp(const std::string& v) {
    generation_timestamp_ = v;
}

void context::generation_timestamp(const std::string&& v) {
    generation_timestamp_ = std::move(v);
}

}
