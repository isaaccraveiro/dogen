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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_FORMATTABLE_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_FORMATTABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.modeling/types/meta_model/element_fwd.hpp"
#include "masd.dogen.generation.cpp/types/formattables/element_properties.hpp"

namespace masd::dogen::generation::cpp::formattables {

class formattable final {
public:
    formattable() = default;
    formattable(const formattable&) = default;
    formattable(formattable&&) = default;
    ~formattable() = default;

public:
    formattable(
        const boost::shared_ptr<masd::dogen::modeling::meta_model::element>& master_segment,
        const std::list<boost::shared_ptr<masd::dogen::modeling::meta_model::element> >& all_segments,
        const masd::dogen::generation::cpp::formattables::element_properties& element_properties);

public:
    const boost::shared_ptr<masd::dogen::modeling::meta_model::element>& master_segment() const;
    boost::shared_ptr<masd::dogen::modeling::meta_model::element>& master_segment();
    void master_segment(const boost::shared_ptr<masd::dogen::modeling::meta_model::element>& v);
    void master_segment(const boost::shared_ptr<masd::dogen::modeling::meta_model::element>&& v);

    const std::list<boost::shared_ptr<masd::dogen::modeling::meta_model::element> >& all_segments() const;
    std::list<boost::shared_ptr<masd::dogen::modeling::meta_model::element> >& all_segments();
    void all_segments(const std::list<boost::shared_ptr<masd::dogen::modeling::meta_model::element> >& v);
    void all_segments(const std::list<boost::shared_ptr<masd::dogen::modeling::meta_model::element> >&& v);

    const masd::dogen::generation::cpp::formattables::element_properties& element_properties() const;
    masd::dogen::generation::cpp::formattables::element_properties& element_properties();
    void element_properties(const masd::dogen::generation::cpp::formattables::element_properties& v);
    void element_properties(const masd::dogen::generation::cpp::formattables::element_properties&& v);

public:
    bool operator==(const formattable& rhs) const;
    bool operator!=(const formattable& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(formattable& other) noexcept;
    formattable& operator=(formattable other);

private:
    boost::shared_ptr<masd::dogen::modeling::meta_model::element> master_segment_;
    std::list<boost::shared_ptr<masd::dogen::modeling::meta_model::element> > all_segments_;
    masd::dogen::generation::cpp::formattables::element_properties element_properties_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::generation::cpp::formattables::formattable& lhs,
    masd::dogen::generation::cpp::formattables::formattable& rhs) {
    lhs.swap(rhs);
}

}

#endif