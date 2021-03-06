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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_ELEMENT_REPOSITORY_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_ELEMENT_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/entities/variability/profile_fwd.hpp"
#include "dogen.logical/types/entities/variability/initializer_fwd.hpp"
#include "dogen.logical/types/entities/variability/feature_bundle_fwd.hpp"
#include "dogen.logical/types/entities/variability/profile_template_fwd.hpp"
#include "dogen.logical/types/entities/variability/feature_template_bundle_fwd.hpp"

namespace dogen::logical::entities::variability {

class element_repository final {
public:
    element_repository() = default;
    element_repository(const element_repository&) = default;
    element_repository(element_repository&&) = default;
    ~element_repository() = default;

public:
    element_repository(
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::profile_template> >& profile_templates,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::profile> >& profiles,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::feature_template_bundle> >& feature_template_bundles,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::feature_bundle> >& feature_bundles,
        const boost::shared_ptr<dogen::logical::entities::variability::initializer>& initializer);

public:
    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::profile_template> >& profile_templates() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::profile_template> >& profile_templates();
    void profile_templates(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::profile_template> >& v);
    void profile_templates(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::profile_template> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::profile> >& profiles() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::profile> >& profiles();
    void profiles(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::profile> >& v);
    void profiles(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::profile> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::feature_template_bundle> >& feature_template_bundles() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::feature_template_bundle> >& feature_template_bundles();
    void feature_template_bundles(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::feature_template_bundle> >& v);
    void feature_template_bundles(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::feature_template_bundle> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::feature_bundle> >& feature_bundles() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::feature_bundle> >& feature_bundles();
    void feature_bundles(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::feature_bundle> >& v);
    void feature_bundles(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::feature_bundle> >&& v);

    const boost::shared_ptr<dogen::logical::entities::variability::initializer>& initializer() const;
    boost::shared_ptr<dogen::logical::entities::variability::initializer>& initializer();
    void initializer(const boost::shared_ptr<dogen::logical::entities::variability::initializer>& v);
    void initializer(const boost::shared_ptr<dogen::logical::entities::variability::initializer>&& v);

public:
    bool operator==(const element_repository& rhs) const;
    bool operator!=(const element_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_repository& other) noexcept;
    element_repository& operator=(element_repository other);

private:
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::profile_template> > profile_templates_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::profile> > profiles_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::feature_template_bundle> > feature_template_bundles_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::variability::feature_bundle> > feature_bundles_;
    boost::shared_ptr<dogen::logical::entities::variability::initializer> initializer_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::variability::element_repository& lhs,
    dogen::logical::entities::variability::element_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
