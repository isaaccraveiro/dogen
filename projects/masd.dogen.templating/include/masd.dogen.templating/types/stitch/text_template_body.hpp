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
#ifndef MASD_DOGEN_TEMPLATING_TYPES_STITCH_TEXT_TEMPLATE_BODY_HPP
#define MASD_DOGEN_TEMPLATING_TYPES_STITCH_TEXT_TEMPLATE_BODY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include "masd.dogen.templating/types/stitch/line.hpp"

namespace masd::dogen::templating::stitch {

class text_template_body final {
public:
    text_template_body() = default;
    text_template_body(const text_template_body&) = default;
    text_template_body(text_template_body&&) = default;
    ~text_template_body() = default;

public:
    text_template_body(
        const std::list<std::pair<std::string, std::string> >& tagged_values,
        const std::list<masd::dogen::templating::stitch::line>& lines);

public:
    const std::list<std::pair<std::string, std::string> >& tagged_values() const;
    std::list<std::pair<std::string, std::string> >& tagged_values();
    void tagged_values(const std::list<std::pair<std::string, std::string> >& v);
    void tagged_values(const std::list<std::pair<std::string, std::string> >&& v);

    const std::list<masd::dogen::templating::stitch::line>& lines() const;
    std::list<masd::dogen::templating::stitch::line>& lines();
    void lines(const std::list<masd::dogen::templating::stitch::line>& v);
    void lines(const std::list<masd::dogen::templating::stitch::line>&& v);

public:
    bool operator==(const text_template_body& rhs) const;
    bool operator!=(const text_template_body& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(text_template_body& other) noexcept;
    text_template_body& operator=(text_template_body other);

private:
    std::list<std::pair<std::string, std::string> > tagged_values_;
    std::list<masd::dogen::templating::stitch::line> lines_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::templating::stitch::text_template_body& lhs,
    masd::dogen::templating::stitch::text_template_body& rhs) {
    lhs.swap(rhs);
}

}

#endif