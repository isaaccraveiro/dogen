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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_VISUAL_STUDIO_ELEMENT_REPOSITORY_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_VISUAL_STUDIO_ELEMENT_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/entities/visual_studio/project_fwd.hpp"
#include "dogen.logical/types/entities/visual_studio/solution_fwd.hpp"
#include "dogen.logical/types/entities/visual_studio/msbuild_targets_fwd.hpp"

namespace dogen::logical::entities::visual_studio {

class element_repository final {
public:
    element_repository() = default;
    element_repository(const element_repository&) = default;
    element_repository(element_repository&&) = default;
    ~element_repository() = default;

public:
    element_repository(
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::solution> >& solutions,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::project> >& projects,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::msbuild_targets> >& msbuild_targets);

public:
    /**
     * @brief All solutions in this model.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::solution> >& solutions() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::solution> >& solutions();
    void solutions(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::solution> >& v);
    void solutions(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::solution> >&& v);
    /**@}*/

    /**
     * @brief All projects in this model.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::project> >& projects() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::project> >& projects();
    void projects(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::project> >& v);
    void projects(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::project> >&& v);
    /**@}*/

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::msbuild_targets> >& msbuild_targets() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::msbuild_targets> >& msbuild_targets();
    void msbuild_targets(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::msbuild_targets> >& v);
    void msbuild_targets(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::msbuild_targets> >&& v);

public:
    bool operator==(const element_repository& rhs) const;
    bool operator!=(const element_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_repository& other) noexcept;
    element_repository& operator=(element_repository other);

private:
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::solution> > solutions_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::project> > projects_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::visual_studio::msbuild_targets> > msbuild_targets_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::visual_studio::element_repository& lhs,
    dogen::logical::entities::visual_studio::element_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
