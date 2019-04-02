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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_DECORATION_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_DECORATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace masd::dogen::coding::meta_model {

/**
 * @brief Decoration for this element.
 */
class decoration final {
public:
    decoration() = default;
    decoration(const decoration&) = default;
    decoration(decoration&&) = default;
    ~decoration() = default;

public:
    decoration(
        const std::string& preamble,
        const std::string& postamble);

public:
    /**
     * @brief Preamble for all artefacts created from this element.
     *
     * The preamble is located at the top of an artefact and includes elements such as a
     * modeline, licence,  copyrights, etc.
     */
    /**@{*/
    const std::string& preamble() const;
    std::string& preamble();
    void preamble(const std::string& v);
    void preamble(const std::string&& v);
    /**@}*/

    /**
     * @brief Postamble for all artefacts created from this element.
     *
     * The postamble is located at the bottom of an artefact and includes elements such
     * as a modeline.
     */
    /**@{*/
    const std::string& postamble() const;
    std::string& postamble();
    void postamble(const std::string& v);
    void postamble(const std::string&& v);
    /**@}*/

public:
    bool operator==(const decoration& rhs) const;
    bool operator!=(const decoration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(decoration& other) noexcept;
    decoration& operator=(decoration other);

private:
    std::string preamble_;
    std::string postamble_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::decoration& lhs,
    masd::dogen::coding::meta_model::decoration& rhs) {
    lhs.swap(rhs);
}

}

#endif
