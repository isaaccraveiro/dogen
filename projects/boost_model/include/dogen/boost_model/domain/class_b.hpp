/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_BOOST_MODEL_DOMAIN_CLASS_B_HPP
#define DOGEN_BOOST_MODEL_DOMAIN_CLASS_B_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <unordered_map>
#include <vector>
#include "dogen/boost_model/domain/class_a.hpp"
#include "dogen/boost_model/domain/class_base.hpp"
#include "dogen/boost_model/domain/pkg1/class_c.hpp"
#include "dogen/boost_model/serialization/class_b_fwd_ser.hpp"

namespace dogen {
namespace boost_model {

class class_b final {
public:
    class_b() = default;
    class_b(const class_b&) = default;
    class_b(class_b&&) = default;
    ~class_b() = default;

public:
    class_b(
        const boost::shared_ptr<dogen::boost_model::class_a>& prop_0,
        const std::vector<boost::shared_ptr<dogen::boost_model::class_a> >& prop_1,
        const std::unordered_map<int, boost::shared_ptr<dogen::boost_model::class_a> >& prop_2,
        const boost::shared_ptr<dogen::boost_model::pkg1::class_c>& prop_3,
        const boost::shared_ptr<dogen::boost_model::class_base>& prop_4,
        const std::vector<boost::shared_ptr<dogen::boost_model::class_base> >& prop_5);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_b& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_b& v, unsigned int version);

public:
    boost::shared_ptr<dogen::boost_model::class_a> prop_0() const {
        return prop_0_;
    }

    void prop_0(const boost::shared_ptr<dogen::boost_model::class_a>& v) {
        prop_0_ = v;
    }

    std::vector<boost::shared_ptr<dogen::boost_model::class_a> > prop_1() const {
        return prop_1_;
    }

    void prop_1(const std::vector<boost::shared_ptr<dogen::boost_model::class_a> >& v) {
        prop_1_ = v;
    }

    std::unordered_map<int, boost::shared_ptr<dogen::boost_model::class_a> > prop_2() const {
        return prop_2_;
    }

    void prop_2(const std::unordered_map<int, boost::shared_ptr<dogen::boost_model::class_a> >& v) {
        prop_2_ = v;
    }

    boost::shared_ptr<dogen::boost_model::pkg1::class_c> prop_3() const {
        return prop_3_;
    }

    void prop_3(const boost::shared_ptr<dogen::boost_model::pkg1::class_c>& v) {
        prop_3_ = v;
    }

    boost::shared_ptr<dogen::boost_model::class_base> prop_4() const {
        return prop_4_;
    }

    void prop_4(const boost::shared_ptr<dogen::boost_model::class_base>& v) {
        prop_4_ = v;
    }

    std::vector<boost::shared_ptr<dogen::boost_model::class_base> > prop_5() const {
        return prop_5_;
    }

    void prop_5(const std::vector<boost::shared_ptr<dogen::boost_model::class_base> >& v) {
        prop_5_ = v;
    }

public:
    bool operator==(const class_b& rhs) const;
    bool operator!=(const class_b& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_b& other) noexcept;
    class_b& operator=(class_b other);

private:
    boost::shared_ptr<dogen::boost_model::class_a> prop_0_;
    std::vector<boost::shared_ptr<dogen::boost_model::class_a> > prop_1_;
    std::unordered_map<int, boost::shared_ptr<dogen::boost_model::class_a> > prop_2_;
    boost::shared_ptr<dogen::boost_model::pkg1::class_c> prop_3_;
    boost::shared_ptr<dogen::boost_model::class_base> prop_4_;
    std::vector<boost::shared_ptr<dogen::boost_model::class_base> > prop_5_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::boost_model::class_b& lhs,
    dogen::boost_model::class_b& rhs) {
    lhs.swap(rhs);
}

}

#endif
