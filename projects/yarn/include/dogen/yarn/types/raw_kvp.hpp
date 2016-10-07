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
#ifndef DOGEN_YARN_TYPES_RAW_KVP_HPP
#define DOGEN_YARN_TYPES_RAW_KVP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include "dogen/yarn/serialization/raw_kvp_fwd_ser.hpp"

namespace dogen {
namespace yarn {

class raw_kvp final {
public:
    raw_kvp() = default;
    raw_kvp(const raw_kvp&) = default;
    raw_kvp(raw_kvp&&) = default;
    ~raw_kvp() = default;

public:
    raw_kvp(
        const std::list<std::pair<std::string, std::string> >& element,
        const std::unordered_map<std::string, std::list<std::pair<std::string, std::string> > >& attributes);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::raw_kvp& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::raw_kvp& v, unsigned int version);

public:
    const std::list<std::pair<std::string, std::string> >& element() const;
    std::list<std::pair<std::string, std::string> >& element();
    void element(const std::list<std::pair<std::string, std::string> >& v);
    void element(const std::list<std::pair<std::string, std::string> >&& v);

    const std::unordered_map<std::string, std::list<std::pair<std::string, std::string> > >& attributes() const;
    std::unordered_map<std::string, std::list<std::pair<std::string, std::string> > >& attributes();
    void attributes(const std::unordered_map<std::string, std::list<std::pair<std::string, std::string> > >& v);
    void attributes(const std::unordered_map<std::string, std::list<std::pair<std::string, std::string> > >&& v);

public:
    bool operator==(const raw_kvp& rhs) const;
    bool operator!=(const raw_kvp& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(raw_kvp& other) noexcept;
    raw_kvp& operator=(raw_kvp other);

private:
    std::list<std::pair<std::string, std::string> > element_;
    std::unordered_map<std::string, std::list<std::pair<std::string, std::string> > > attributes_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::raw_kvp& lhs,
    dogen::yarn::raw_kvp& rhs) {
    lhs.swap(rhs);
}

}

#endif
