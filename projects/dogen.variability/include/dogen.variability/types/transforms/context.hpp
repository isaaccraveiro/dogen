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
#ifndef DOGEN_VARIABILITY_TYPES_TRANSFORMS_CONTEXT_HPP
#define DOGEN_VARIABILITY_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.tracing/types/tracer_fwd.hpp"
#include "dogen.archetypes/types/location_repository_fwd.hpp"

namespace dogen::variability::transforms {

/**
 * @brief Context for transformations.
 */
class context final {
public:
    context(const context&) = default;
    context(context&&) = default;
    ~context() = default;

public:
    context();

public:
    context(
        const std::vector<boost::filesystem::path>& data_directories,
        const boost::shared_ptr<dogen::archetypes::location_repository>& archetype_location_repository,
        const bool compatibility_mode,
        const boost::shared_ptr<dogen::tracing::tracer>& tracer);

public:
    const std::vector<boost::filesystem::path>& data_directories() const;
    std::vector<boost::filesystem::path>& data_directories();
    void data_directories(const std::vector<boost::filesystem::path>& v);
    void data_directories(const std::vector<boost::filesystem::path>&& v);

    const boost::shared_ptr<dogen::archetypes::location_repository>& archetype_location_repository() const;
    boost::shared_ptr<dogen::archetypes::location_repository>& archetype_location_repository();
    void archetype_location_repository(const boost::shared_ptr<dogen::archetypes::location_repository>& v);
    void archetype_location_repository(const boost::shared_ptr<dogen::archetypes::location_repository>&& v);

    bool compatibility_mode() const;
    void compatibility_mode(const bool v);

    const boost::shared_ptr<dogen::tracing::tracer>& tracer() const;
    boost::shared_ptr<dogen::tracing::tracer>& tracer();
    void tracer(const boost::shared_ptr<dogen::tracing::tracer>& v);
    void tracer(const boost::shared_ptr<dogen::tracing::tracer>&& v);

public:
    bool operator==(const context& rhs) const;
    bool operator!=(const context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(context& other) noexcept;
    context& operator=(context other);

private:
    std::vector<boost::filesystem::path> data_directories_;
    boost::shared_ptr<dogen::archetypes::location_repository> archetype_location_repository_;
    bool compatibility_mode_;
    boost::shared_ptr<dogen::tracing::tracer> tracer_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::transforms::context& lhs,
    dogen::variability::transforms::context& rhs) {
    lhs.swap(rhs);
}

}

#endif
