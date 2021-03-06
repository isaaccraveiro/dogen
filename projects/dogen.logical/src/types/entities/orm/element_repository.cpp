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
#include "dogen.logical/types/entities/orm/common_odb_options.hpp"
#include "dogen.logical/types/entities/orm/element_repository.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::logical::entities::orm::common_odb_options>& lhs,
const boost::shared_ptr<dogen::logical::entities::orm::common_odb_options>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::logical::entities::orm {

element_repository::element_repository(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::orm::common_odb_options> >& common_odb_options)
    : common_odb_options_(common_odb_options) { }

void element_repository::swap(element_repository& other) noexcept {
    using std::swap;
    swap(common_odb_options_, other.common_odb_options_);
}

bool element_repository::operator==(const element_repository& rhs) const {
    return common_odb_options_ == rhs.common_odb_options_;
}

element_repository& element_repository::operator=(element_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::orm::common_odb_options> >& element_repository::common_odb_options() const {
    return common_odb_options_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::orm::common_odb_options> >& element_repository::common_odb_options() {
    return common_odb_options_;
}

void element_repository::common_odb_options(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::orm::common_odb_options> >& v) {
    common_odb_options_ = v;
}

void element_repository::common_odb_options(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::orm::common_odb_options> >&& v) {
    common_odb_options_ = std::move(v);
}

}
